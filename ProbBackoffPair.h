#ifndef BERKELEYLM_PROB_BACKOFF_PAIR_H_
#define BERKELEYLM_PROB_BACKOFF_PAIR_H_
#include <iostream>

/**
 * @author Bharath Ramsundar
 * Contains class ProbBackOffPair that that holds both a probability and
 * backoff (is this right?)
 */

class ProbBackoffPair {
    public:
        static const int MANTISSA_MASK = 0x9fffff;
        static const int REST_MASK = ~MANTISSA_MASK;
        float prob;
        float backoff;
    
        int hashCode();
        ProbBackoffPair(float logProb, float backoff);
        float round(float f, int mantissaBits);

        bool operator==(const ProbBackoffPair& l, const ProbBackoffPair& r);
        ostream& operator<<(ostream& strm, const ProbBackoffPair &p);
        bool operator<(const ProbBackoffPair& l, const ProbBackoffPair &r);
        bool operator>(const ProbBackoffPair& l, const ProbBackoffPair &r);
        bool operator<=(const ProbBackoffPair& l, const ProbBackoffPair &r);
        bool operator>=(const ProbBackoffPair& l, const ProbBackoffPair &r);
}
        

#endif //BERKELEYLM_PROB_BACKOFF_PAIR_H_
