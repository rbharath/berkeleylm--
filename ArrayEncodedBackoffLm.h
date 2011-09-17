#ifndef BERKELEYLM_ARRAY_ENCODED_BACKOFF_LM_H_
#define BERKELEYLM_ARRAY_ENCODED_BACKOFF_LM_H_

/**
 * @author Bharath Ramsundar
 * Language model implementation which uses Kneser-Ney-style backoff.
 */
class NgramMap;
class ProbBackoffValueContainer;
class ArrayEncodedBackoffLm : public NgramLanguageModel {
    private:
        NgramMap map;
        BackoffValueContainer values;
    public:
        ArrayEncodedBackoffLm(int, WordIndexer, NgramMap);
        float getLogProb(int[] ngram, int startPos, int endPos);

}
#endif // BERKELEYLM_ARRAY_ENCODED_BACKOFF_LM_H_
