#ifndef BERKELEYLM_ARPA_LM_READER_H_
#define BERKELEYLM_ARPA_LM_READER_H_
#include <string>
#include <list>
#include <ifstream>

/**
 * @author Bharath Ramsundar
 * Contains class ArpaLmReader that reads in ARPA format files
 */
class WordIndexer;
class ArpaLmReaderCallback;

class ArpaLmReader {
    private:
        static const string startSymbol = "<s>";
        static const string endSymbol = "</s>";
        static const string unkSymbol = "<unk>";
        int currentNGramCount = 0;
        int currentNGramLength = 1;
        int lineNumber = 1;
        int maxOrder;
        ifstream file;
        string line;
        WordIndexer& wordIndexer;
        ArpaLmReaderCallback& callback;
        int[] parseNGram(string, int);

    protected:
        string readLine();
        list<long> parseHeader();
        void parseNGrams();
        void parseLine(string);
        
    
    public:
        string readLine();
        ArpaLmReader(string, WordIndexer, int);
        ~ArpaLmReader();
        void parse(ArpaLmReaderCallback);
}

#endif // BEREKELEYLM_ARPA_LM_READER_H_
