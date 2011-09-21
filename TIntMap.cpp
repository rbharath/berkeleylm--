#include "TIntMap.h"

void TIntMap::TIntMap(int expectedSize) {
   this.mapType = MapType.HASH_TABLE;     
   allocate(getCapacility(expectedSize, false));
}

int TIntMap::capacity() {
    return keys.length;
}

    

