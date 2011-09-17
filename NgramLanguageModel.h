#ifndef BERKELEYLM_NGRAMLANGUAGEMODEL_H_
#define BERKELEYLM_NGRAMLANGUAGEMODEL_H_

/**
 * @author Bharath Ramsundar
 * Contains class NgramLanguageModel. This class has only pure virtual methods
 * and is used to provide a basic interface for ngram-language models
 */
class Word;
class NgramLanguageModel {
    public:
        int getLmOrder();
        WordIndexer getWordIndexer();
}
#endif // BERKELEYLM_NGRAMLANGUAGEMODEL_H_
