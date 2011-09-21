#include <string>
#include <list>
#include <cstdlib>
#include <iostream>
#include <ifstream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>
#define LOGGING_NUM 100000
//TODO: implement Logger, WordIndexer, ArpaLmReaderCallback
class WordIndexer;
class ArpaLmReaderCallback;
class ProbBackoffPair;

ArpaLmReader::ArpaLmReader(string filename, WordIndexer w, int maxNgramOrder) :
    filename(filename), wordIndexer(wordIndexer), maxOrder(maxOrder);

ArpaLmReader::~ArpaLmReader() {
    //TODO: do this correctly
    file.close();
}

string ArpaLmReader::readLine() {
    lineNumber++;
    getline(file, read_line);
    return read_line;
}

void ArpaLmReader::parse(ArpaLmReaderCallBack callback_) {
    currentNGramLength = 1;
    currentNGramCount = 0;
    lineNumber = 1;
    callback = callback_;
    file.open(filename);
    //Logger.startTrack("Parsing ARPA language model file");
    list<long> numNGrams = parseHeader();
    callback.initWithLengths(numNGrams);
    parseNGrams();
    callback.cleanup();
    wordIndexer.setStartSymbol(
        wordIndexer.getWord(wordIndexer.getOrAddIndexFromString(START_SYMBOL)));
    wordIndexer.setEndSymbol(
        wordIndexer.getWord(wordIndexer.getOrAddIndexFromString(END_SYMBOL)));
    wordIndexer->setUnkSymbol(
        wordIndexer.getWord(wordIndexer.getOrAddIndexFromString(UNK_SYMBOL)));
}

bool startsWith(string str, string prefix) {
    int i;
    if (prefix.length() > str.length()) 
        return false;
    for(i = 0; i < prefix.length(); i++) {
        if (prefix[i] != str[i])
            return false;
    }
    return true;
}

list<long> ArpaLmReader::parseHeader() {
    char** endptr;
    list<long> numEachNgrams = new list<long>;
    try {
        while (!reader.eof()) {
            const string line = readLine();
            string ngramTotalPrefix = "ngram ";
            if(startsWith(line, ngramTotalPrefix)) {
                const int equalsIndex = line.find('=');
                if (equals == string::npos) {throw "Malformed Arpa File; no '='";}
                const long currNumNGrams 
                    = strol(line.substring(equalsIndex + 1).c_str(), endPtr, 10);
                if (numEachNgrams.size() < maxOrder)  {
                    numEachNgrams.push_back(currNumNGrams);
                }
            }
            if (line.find(string("\\1-grams:")) != string::npos) {
                return numEachNgrams;
            }
        } 
    } catch (ios_base::failure f) {
        throw runtime_error(f.what());
    } catch (string str) {
       throw runtime_error(str); 
    } catch (...) {
        throw runtime_error("Error Reading Arpa File Header");
    }
    String error = "\"\\1-grams: expected (line ";
    error += boost::lexical_cast<string>(lineNumber); error += ")";
    throw runtime_error(error);
}

void ArpaLmReader::parseNGrams() {
    int currLine = 0;
    //Logger.startTract("Reading 1-grams");
    try {
        while (file) {
        // if (currLIne % LOGGING_NUM == 0) Logger.logs("Read " + currLine + "lines");
            currLine++;
            const string line = readLine();
            if (line.length()) {
                // nothing to do (skip blank lines)
                continue;
            } else if (line[0] == '\\') {
                // a new block of n-grams is beginning
                if (!startsWith(line, string("\\end"))) {
                    //Logger.logs(currentNgramCount + " " + currentNGramLength + "-gram read");
                    // Logger.endTrack();
                    callback.handleNgramOrderFinished(currentNGramLength);  
                    currentNGramLength++;
                    if (currentNGramLength > maxOrder) return;  
                    currentNGramCount = 0;  
                    // Logger.startStrack("Reading " + currentNGramLength +"-grams");
                } 
            } else {
                parseLine(line);
            }
        }                
        file.close();
    } catch (ios_base::failure f) {
        return runtime_exception(f.what());
    }
    // handle final ngram not handled by above loop
    // Logger.endTrack();
    callback.handleNgramOrderFinished(currentNgramLength);
}

void ArpaLmReader::parseLine(string line) {
    const int firstTab = line.find('\t');
    if (firstTab == string::npos )  { throw "Malformed Arpa File; improper tabs"; }
    const int secondTab = line.find('\t', firstTab +1);
    const bool hasBackOff = (secondTab >= 0);
    const int length = line.length();
    string logProbString = line.substr(0, firstTab);
    string firstWord 
        = line.subString(firstTab + 1, secondTab < 0 ? length : secondTab);
    int ngram [] = parseNGram(firstWord, currentNgramLength);
    
    // the first coulmn contains the log probability
    float logProbability = atof(logProbString);
    float backoff = 0.0f;

    // and its backoff, if specified
    if (hasBackOff) {
        backOff = atof(line.substr(secondTab + 1, length));
    }
    
    if (logProbability > 0.0f) { 
        string error = "Bad ARPA line "; error += line;
        throw runtime_error(error);
    }
    callback.call(ngram, 0, ngram.length, 
                  new ProbBackoffPair(logProbability, backoff), line);
    currentNGramCount++;
}

int[] ArpaLmReader::parseNGram(string str, int numWords) {
    int retVal [] = new int[numWords];
    int spaceIndex = 0;
    int k = 0;
    while (true) {
        int nextIndex = str.find(' ', spaceIndex);
        string currWord = string.substr(spaceIndex,
                                        nextIndex < 0 ? str.length() : nextIndex);
        retVal[k++] = wordIndexer.getOrAddIndexFromString(currWord);
        if (nextIndex < 0) break;
        spaceIndex = nextIndex + 1;
    }
    return retVal;
}

    
