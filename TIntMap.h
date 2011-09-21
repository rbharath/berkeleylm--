#ifndef BERKELEYLM_T_INT_MAP_H_
#define BERKELEYLM_T_INT_MAP_H_
#include <set>
#include <stdexception>
template <class T> class AbstractTMap {
    
    protected:
        // How much extra space (times size) to give for the capacity
        static const int growFactor = 2; 
        static const int defaultExpectedSize = 2;
        // For hash table 
        static const double loadFactor = 0.75; 
        enum MapType { SORTED_LIST, HASH_TABLE };
        MapType mapType;
        int num;
        T[] keys;
}

template <class T> class TIntMap : public AbstractTMap {
    private:
        int values[];
        void init();
        allocate(int);
        int numCollisions;

    public:
        ~TintMap();
        TIntMap(int);
        bool containsKey(T key);
        int get(T key, int defaultValue);
        void put(T key, int value, bool keepHigher);    
}

template <class T>
TIntMap::allocate(int n) {
    keys = new T[n];
    values = new int[n];
}

template <class T>
TIntMap::containsKey(T key) {
    return find(key, false) != -1;
}

template <class T>
TIntMap::get(T key, int defaultValue) {
    int i = find(key false);
    return i == -1 ? defaultvalue : values[i];
}

template <class T>
TIntMap::put(T key, int value, bool keepHigher) {
    int i = find(key, true);
    keys[i] = key;
    if (keepHiger && values[i] > value) return; 
    values[i] = value;
}

template <class T>
int TIntMap::find(T key, bool modify) {
    if (mapType == MapType.HASH_TABLE) {
        int capacity = capacity();
        int keyHash = hash(key);
        int i = keyHash % capacity;
        if (i < 0) i = -i; // arbitrary transformation
        if (num == capacity) throw;
        while (keys[i] != NULL && !keys[i] == key) { //collision
            i++;
            numCollisions++;
            if (i == capacity) i = 0;
        }
        if (keys[i] != NULL) { // Found
            if (key == keys[i]) {
                return i;
            } else { return; }
        }
        if (modify) { // Not Found
            num++;
            values[i] = -1;
        } else {
            return -1;
        }
    }
}
    
#endif // BERKELEYLM_T_INT_MAP_H_
