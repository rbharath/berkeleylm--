#ifndef BERKELEYLM_GOOGLELMREADER_H_
#define BERKELEYLM_GOOGLELMREADER_H_

/**
 * @author Bharath Ramsundar
 * Contains class GoogleLmReader that reads in files in the format of Google's
 * n-grams Web1T corpus
 */
class WordIndexer;

class GoogleLmReader {
    private:
        static const string startSymbol = "<S>";
        static const string endSymbol = "</S>";
        static const string unkSymbol = "<UNK>";
        static const string sortedVocabFile = "vocab_cs.gz";
        const string rootDir;
        const WordIndexer wordIndexer;

    public:
        GoogleLmReader(string, WordIndexer);

}
#endif // BERKELEYLM_GOOGLELMREADER_H_
