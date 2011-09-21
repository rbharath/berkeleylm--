#ifndef BERKELEYLM_INDEXER_H_
#define BERKELEYLM_INDEXER_H_

template class<E> class TIntMap;
template class<E> class Indexer {

    protected:
        list<E> objects;
        TIntMap<E> indexes;
        bool locked = false;
        boost::mutex mutex;

    public:
        Indexer();
        ~Indexer();
        void lock();
        E getObject(int index);
        bool add(E elem);
        int size();
        int indexOf(E o);
        int getIndex(E e);
        void trim();
}

#endif //BERKELEYLM_INDEXER_H_
