//
// Created by Katherine on 27.12.2021.
//
#include <gtest/gtest.h>
#include "hash.h"
using namespace  std;

class HashTableTest : public testing::Test{
protected:
    HashTable t0,
            t1,
            t2;
    void SetUp() override{
        t1.insert("James", { 21, 70 });
        t1.insert("Lara", { 21, 55 });
        t1.insert("Lily", { 20, 73 });
        t1.insert("John", { 19, 67 });
        t1.insert("Timothy", { 22, 80 });
        t1.insert("Tom", { 18, 65 });
        t1.insert("Anne", { 20, 60 });
        t1.insert("Barry", { 21, 65 });

        t2.insert("Paul", { 19, 68 });
        t2.insert("Edgar", { 23, 91 });
        t2.insert("Emily", { 20, 74 });
        t2.insert("William", { 21, 84 });
        t2.insert("Ringo", { 22, 68 });
        t2.insert("Stephany", { 20, 50 });
        t2.insert("Anastasia", { 19, 68 });
    }
};

TEST_F(HashTableTest, test_swap){
t1.swap(t2);
EXPECT_EQ(t1.size(), 7);
EXPECT_EQ(t2.size(), 8);
EXPECT_EQ(t2["Lara"].weight, 55);
}

TEST_F(HashTableTest, test_erase){
bool ret = t1.erase("Anne");
EXPECT_EQ(ret, true);
EXPECT_EQ(t1["Anne"].weight, 0);
}

TEST_F(HashTableTest,test_empty){
bool ret = t1.empty();
EXPECT_EQ(ret, false);
ret = t0.empty();
EXPECT_EQ(ret, true);
}

TEST_F(HashTableTest, test_contains){
bool ret = t1.contains("Net");
EXPECT_EQ(ret, false);
ret = t1.contains("Tom");
EXPECT_EQ(ret, true);
}

TEST_F(HashTableTest, test_at){
Value val = t1.at("James");
EXPECT_EQ(val.weight, 70);
ASSERT_ANY_THROW(t1.at("net"));
}

TEST_F(HashTableTest, test_operators){
bool ret1 = t1 == t2;
EXPECT_EQ(ret1, false);
bool ret2 = t1 != t2;
EXPECT_EQ(ret2, true);
unsigned int ret3 = t1["Timothy"].weight;
EXPECT_EQ(ret3, 80);
t1 = t2;
ret1 = t1 == t2;
EXPECT_EQ(ret1, true);
}

TEST_F(HashTableTest, test_copy){
HashTable t3 = t1;
EXPECT_EQ(t3.size(), 8);
bool ret = t3.contains("Anne");
EXPECT_EQ(ret, true);
ret = t3.contains("Lara");
EXPECT_EQ(ret, true);
ret = t3.contains("net");
EXPECT_EQ(ret, false);

}

TEST_F(HashTableTest, test_move){
HashTable t4 = std::move(t2);

bool ret = t4.contains("Paul");
EXPECT_EQ(ret, true);
ret = t4.contains("Edgar");
EXPECT_EQ(ret, true);
ret = t4.contains("Emily");
EXPECT_EQ(ret, true);
ret = t4.contains("William");
EXPECT_EQ(ret, true);
ret = t4.contains("Ringo");
EXPECT_EQ(ret, true);
ret = t4.contains("Stephany");
EXPECT_EQ(ret, true);
ret = t4.contains("Anastasia");
EXPECT_EQ(ret, true);
cout << t2.size();
ret = t2.empty();
EXPECT_EQ(ret, true);
}
