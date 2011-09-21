#include <string>
#include <list>
#include <cstdlib>
#include <ifstream>
#include <stdexcept>
#include <boost/lexical_cast.hpp>

class WordIndexer;
class ArpaLmReaderCallback;

ArpaLmReader::ArpaLmReader(string filename, WordIndexer w, int maxNgramOrder) :
    wordIndexer(wordIndexer), maxOrder(maxOrder) {
    file.open(filename);
}

ArpaLmReader::~ArpaLmReader() {
    file.close();
}

string ArpaLmReader::readLine() {
    lineNumber++;
    getline(file, line);
    return line;
}

void ArpaLmReader::parse(ArpaLmReaderCallBack callback_) {
    currentNGramLength = 1;
    currentNGramCount = 0;
    lineNumber = 1;
    callback = callback_;
    list<long> numNGrams = this->parseHeader();
    callback->initWithLengths(numNGrams);
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
            string line = readLine();
            string ngramTotalPrefix = "ngram ";
            if(startsWith(line, ngramTotalPrefix)) {
                const int equalsIndex = line.find('=');
                if (equals == string::npos) {
                    throw "Malformed Arpa File";
                }
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
    }
    catch (...) {
        throw runtime_error("Error Reading Arpa File Header");
    }
    String error = "\"\\1-grams: expected (line ";
    error += boost::lexical_cast<string>(lineNumber); error += ")";
    throw runtime_error(error);
}

void ArpaLmReader::parseNGrams() {
    int currLine = 0;
    //TODO: implement Logger
    //Logger.startTract("Reading 1-grams");

