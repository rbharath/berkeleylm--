#ifndef BERKELEYLM_WORD_INDEXER_H_
#define BERKELEYLM_WORD_INDEXER_H_
#include <string>
#include <list>

/**
 * Contains class WordIndexer that enumerates words in the vocabulary of 
 * a language model. Stores a two-way mapping between integers and words.
 * 
 * @author Bharath Ramsundar
 */
class WordIndexer {
    private:
        Indexer<string> sparseIndexer;
        string startSymbol;
        string endSymbol;   
        string unkSymbol;
        int unkIndex = -1;
            

    public:
        WordIndexer();
        ~WordIndexer();
        int getOrAddIndex(string word);
        int getIndexPossiblyUnk(string word);
        string getWord(int index);
        int numWords(); 
        string getStartSymbol();
        void setStartSymbol(string sym);
        string getEndSymbol();
        void setEndSymbol(string sym);
        string getUnkSymbol();
        void setUnkSymbol(string sym);

		/**
		 * Converts a string representation to an int array. Does not add to
		 * the indexer.
		 * 
		 * @param wordIndexer
		 * @param list
		 * @return
		 */
        static int[] toArray(WordIndexer wordIndexer, list<string> l) {
            int[] ret = new int[list.size()];
            for(list<string>::iterator it = l.begin(); it != l.end(); it++) {
                ret[i] = wordIndexer.getIndexPossiblyUnk(*it);
            }
            return ret;
        }
        
		/**
		 * Converts an string representation to an int array, adding to the
		 * indexer.
		 * 
		 * @param <W>
		 * @param wordIndexer
		 * @param list
		 * @return
		 */
        static int[] toArray(WordIndexer wordIndexer, list<string> l) {
            int[] ret = new int[list.size()];
            for(list<string>::iterator it = l.begin(); it != l.end(); it++) {
                ret[i] = wordIndexer.getOrAddIndexFromString(*it);
            }
            return ret;
        }
		/**
		 * Converts an int representation of an n-gram to a list. Converts only
		 * the range of the array specified by [startPos,endPos)
		 * 
		 * @param wordIndexer
		 * @param intNgram
		 * @param startPos
		 * @param endPos
		 * @return
		 */
		static list<string> toList(WordIndexer wordIndexer, int intNgram [], 
                                   int startPos, int endPos) {
			list<W> l = new list<string>();
			for (int i = startPos; i < endPos; ++i) {
				l.push_back(wordIndexer.getWord(intNgram[i]));
			}
			return l;
		}

		static list<strign> toList(WordIndexer wordIndexer, int[] intNgram) {
			return toList(wordIndexer, intNgram, 0, intNgram.length);
		}
	}
}
#endif //BERKELEYLM_WORD_INDEXER_H_

