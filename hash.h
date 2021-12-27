//
// Created by Katherine on 16.12.2021.
//

#ifndef TASK2_HASH_H
#define TASK2_HASH_H

#include <vector>
#include <list>

struct Student {
    unsigned age;
    unsigned weight;
};

using namespace std;

typedef std::string Key;
typedef Student Value;

int hash(const Key& s, int table_size);

class HashTable
{
    const int default_len = 8, //default len of vector
    rehash_size = 8; //size to rehash
    vector<list<pair<Key, Value>>*> arr;
    int vectors_len, //len of vector
    table_size; //count elems
    Value mask_student{};

    void resize();

public:
    HashTable();
    ~HashTable();
    HashTable(const HashTable& b);
    HashTable(HashTable&& b);
    HashTable& operator=(const HashTable& b);
    HashTable& operator=(HashTable&& b);
// Обменивает значения двух хэш-таблиц.
    void swap(HashTable& b);
// Очищает контейнер.
    void clear();
// Удаляет элемент по заданному ключу.
    bool erase(const Key& k);
// Вставка в контейнер. Возвращаемое значение - успешность вставки.
    bool insert(const Key& k, const Value& v);
// Проверка наличия значения по заданному ключу.
    bool contains(const Key& k) const;
// Возвращает значение по ключу. Небезопасный метод.
// В случае отсутствия ключа в контейнере, следует вставить в контейнер
// значение, созданное конструктором по умолчанию и вернуть ссылку на него.
    Value& operator[](const Key& k);
// Возвращает значение по ключу. Бросает исключение при неудаче.
    const Value& at(const Key& k) const;
    size_t size() const;
    bool empty() const;

    friend bool operator==(const HashTable& a, const HashTable& b);

    friend bool operator!=(const HashTable& a, const HashTable& b);
};
bool operator==(const HashTable& a, const HashTable& b);
bool operator!=(const HashTable& a, const HashTable& b);

#endif //TASK2_HASH_H
