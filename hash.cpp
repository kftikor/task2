#include <iostream>
#include "hash.h"
#include <stdexcept>


int hash(const Key& name, int table_size)
{
    int result = 0;
    for (char i : name)
        result = (result + i);
    result = (result * 2) % table_size;
    return result;
}

void HashTable::resize(){
    vector<list<pair<Key, Value>>*> temp = arr;
    arr.clear();
    vectors_len *= 2;
    for (int i = 0; i < vectors_len / 2; i++){
        if (!temp[i]->empty()){
            for (auto & it : *temp[i]){
                insert(it.first, it.second);
            }

        }
    }
}

HashTable::HashTable() {
    mask_student.weight = 0;
    mask_student.age = 0;
    vectors_len = default_len;
    table_size = 0;
    list<pair<Key, Value>>* elem = nullptr;
    arr.resize(vectors_len, elem);
}

HashTable::~HashTable() {
    arr.clear();
}

HashTable::HashTable(const HashTable& b): HashTable(){
    arr = b.arr;
    vectors_len = b.vectors_len;
    table_size = b.table_size;
    mask_student = b.mask_student;
}

HashTable::HashTable(HashTable &&b){
    arr = b.arr;
    vectors_len = b.vectors_len;
    table_size = b.table_size;
    mask_student = b.mask_student;
    for (auto & it : b.arr){
        it = nullptr;
    }
}

HashTable& HashTable::operator=(const HashTable& b) {
    vectors_len = b.vectors_len;
    table_size = b.table_size;
    arr = b.arr;
    return *this;
}

HashTable& HashTable::operator=(HashTable &&b){
    if (this == &b){
        return *this;
    }
    vectors_len = b.vectors_len;
    table_size = b.table_size;
    arr = b.arr;
    b.table_size = 0;
    for(auto it : b.arr){
        it = nullptr;
    }
    return *this;
}

void HashTable::swap(HashTable &b) {
    int temp = vectors_len;
    vectors_len = b.vectors_len;
    b.vectors_len = temp;
    temp = table_size;
    table_size = b.table_size;
    b.table_size = temp;

    vector<list<pair<Key, Value>>*> temp_vec = b.arr;
    b.arr = arr;
    arr = temp_vec;
}

void HashTable::clear(){
    arr.clear();
    vectors_len = default_len;
    table_size = 0;
    arr.resize(vectors_len, nullptr);
}

bool HashTable::erase(const Key& name) {
    int h = ::hash(name, vectors_len);
    for (auto it = arr[h]->begin(); it != arr[h]->end(); it++){

        if (it->first == name) {
            arr[h]->erase(it);
            table_size--;
            return true;
        }

    }
    return false;
}


bool HashTable::insert(const Key& name, const Value& v){
    int h = ::hash(name, vectors_len);
    if (arr[h] == nullptr){
        arr[h] = new list<pair<Key, Value>>;
    }
    arr[h]->push_front(make_pair(name, v));
    if(arr[h]->size() > rehash_size){
        resize();
    }
    table_size++;
    return true;
}

bool HashTable::contains(const Key& name) const{
    int h = ::hash(name, vectors_len);
    if(arr[h] == nullptr){
        return false;
    }

    for (const auto & it : *arr[h]) {
        if (it.first == name){
            return true;
        }
    }
    return false;
}

Value& HashTable::operator[](const Key &name) {
    if (contains(name)){
        int h = ::hash(name, vectors_len);
        for (auto & it : *arr[h]){
            if (it.first == name){
                return it.second;
            }
        }
    }
    insert(name, mask_student);
    return mask_student;
}



const Value &HashTable::at(const Key &name) const {
    if (contains(name)){
        int h = ::hash(name, vectors_len);
        for (auto & it : *arr[h]){
            if (it.first == name){
                return it.second;
            }
        }
    }
    throw invalid_argument("This student was not found");
}

size_t HashTable::size() const {
    return table_size;
}

bool HashTable::empty() const {
    for (const auto it : arr) {
        if (it != nullptr) return false;
    }
    return true;
}

bool operator==(const HashTable &a, const HashTable &b) {
    return ((a.table_size == b.table_size)&&(a.arr == b.arr));
}

bool operator!=(const HashTable &a, const HashTable &b) {
    return (!((a.table_size == b.table_size)&&(a.arr == b.arr)));
}