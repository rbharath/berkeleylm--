#ifndef BERKELEYLM_ARPALMREADER_H_
#define BERKELEYLM_ARPALMREADER_H_
#include <string>
#include <list>

/**
 * @author Bharath Ramsundar
 * Contains class ArpaLmReader that reads in ARPA format files
 */
class WordIndexer;

class ArpaLmReader {
    private:
        int currentNGramCount = 0;
        int currentNGramLength = 1;
        int lineNumber = 1;
        string file;
        WordIndexer wordIndexer;
        const int maxOrder;
        private int[] parseNGram(string, int);

    protected:
        list<long> parseHeader();
        parseNGrams();
        parseLine(string);
        
    
    public:
        static const string startSymbol = "<s>";
        static const string endSymbol = "</s>";
        static const string unkSymbol = "<unk>";
        string readLine();
        ArpaLmReader(string, WordIndexer, int);
        ~ArpaLmReader();
        parse(ArpaLmReaderCallback);
}

#endif // BEREKELEYLM_ARPALMREADER_H_
