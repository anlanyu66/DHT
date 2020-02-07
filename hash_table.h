//
// Created by Anlan Yu on 1/27/20.
//

#ifndef DHT_HASH_TABLE_H
#define DHT_HASH_TABLE_H
#define size 100000
#define NOVAL 0XFFFFFFFF
#define LOCK_NUM 100
#define NULL 0
#include <vector>
#include <altivec.h>
#include <shared_mutex>
#include <mutex>

template<class T>
struct element{
    int key;
    T value;
};

template<class T>
class hash_table{
public:
    hash_table(){
        elem = new element<T>[size];
        for(int i=0;i<size;i++){
            elem[i].key = NOVAL;
        }
    };
    int put(int K, int V);
    int get(int K);
    std::shared_timed_mutex lock[LOCK_NUM];

private:
    element<T>* elem;
    int hash_func(int K);
};
template<class T>
int hash_table<T>::hash_func(int K) {
    int idx;
    idx = K%size;
    return idx;
}

template<class T>
int hash_table<T>::put(int K, int V) {
    int idx = hash_func(K);
    lock[K%LOCK_NUM].lock_shared();
    if(elem[idx].key == NOVAL){
        elem[idx].key = K;
        elem[idx].value = V;
        lock[K%LOCK_NUM].unlock_shared();
        return true;
    }
    else{
        lock[K%LOCK_NUM].unlock_shared();
        return false;
    }

}

template<class T>
int hash_table<T>::get(int K) {
    int idx =  hash_func(K);
    lock[K%LOCK_NUM].lock_shared();
    if(elem[idx].key == NOVAL){
        lock[K%LOCK_NUM].unlock_shared();
        return NULL;
    }
    else{
        lock[K%LOCK_NUM].unlock_shared();
        return elem[idx].value;
    }
}
#endif //DHT_HASH_TABLE_H
