#include <bits/stdc++.h>
#include "LESSON.h"

#ifndef HASHTABLE_HASHTABLE_H
#define HASHTABLE_HASHTABLE_H

struct Hs_item{

    Lesson _lesson;
    Room _key;
    bool _checked;
    Hs_item* _prev;
    bool _status;


    Hs_item(Lesson*, Room);
    ~Hs_item() = default;
};

class Hashtable{
private:
    int _count;//Number of items
    int _max_count;//Max number of tryies to put item
    int _capacity;
    int _realcount;
    std::vector<Hs_item*> _items;

    int Hash_function(char, int) const;
    int Hash_function(Room);
    int Hash_function2(char, int) const;
    int Hash_function2(const Room&);

    void UpSize();
    void DownSize();

    void FreeItems();
    friend void FreeTable(Hashtable*);


public:
    explicit Hashtable(int a = 10);
    void Delete_item(char, int);
    void Insert_item(Lesson);
    void Delete_item(Room);
    void Print_HashTable();
    Lesson* Search(Room);

    ~Hashtable() = default;
};

void FreeTable(Hashtable*);
int GetMaxPrimeUpTo (int const);


#endif //HASHTABLE_HASHTABLE_H
