#include "HASHTABLE.h"
#include <bits/stdc++.h>

#include <utility>

Hs_item::Hs_item(Lesson* lesson, Room room){
    _key = std::move(room);
    _lesson = *lesson;
    _status = true;
    _prev = nullptr;
    _checked = false;
}

Hashtable::Hashtable(int size){
    this->_capacity = size;
    this->_count = 0;
    this->_max_count = size;
    this->_items = std::vector<Hs_item*>(size);
    this->_realcount = 0;

    for (int i = 0; i < this->_capacity; i++)
        this->_items[i] = nullptr;
}

void Hashtable::FreeItems(){

    for (auto i = 0; i < _capacity; ++i){
        _items[i]->_prev = nullptr;
        _items[i] = nullptr;
    }
    _count = 0;
}

void FreeTable(Hashtable* table){

    table->FreeItems();

    table->_items.resize(0);
    table->_capacity = 0;
    table->_count = 0;
    table->_max_count = 0;

    free(table);
}

void Hashtable::Print_HashTable(){

    std::cout << "Hash Table\n----------------------------\n";
    for (auto i = 0; i < _capacity; ++i){
        if (_items[i])
            std::cout << i << " : " <<
            _items[i]->_key.letter << " " <<
            _items[i]->_key.number << " -> " <<
            _items[i]->_lesson._room.letter << ' ' <<
            _items[i]->_lesson._room.number << ' ' <<
            _items[i]->_lesson._surname << ' ' <<
            _items[i]->_lesson._name << ' ' <<
            _items[i]->_lesson._lastname << ' ' <<
            _items[i]->_lesson._hour << ' ' <<
            _items[i]->_lesson._minute << ' ' <<
            _items[i]->_lesson._subject << " (" <<
            Hash_function(_items[i]->_lesson._room) << ") " <<
            _items[i]->_status <<
            std::endl;
        else
            std::cout << i << " : " << "nullptr" <<std::endl;
    }
    std::cout << "\n----------------------------\n";
}

void Hashtable::Insert_item(Lesson lesson){

    if (_capacity == _count){

        std::cout << "Hashtable is full.\n";
        return;
    }

    int hash1 = Hash_function(lesson._room);
    int hash2 = Hash_function2(lesson._room);
    Hs_item* current = _items[hash1];
    bool success = false;
    do{
        int i = 0;
        int _free = -1;
            while ((i <= _max_count)&&(current)&&(current->_lesson._room != lesson._room)){
                if ((!current->_status)&&(_free == -1))
                    _free = i;
                ++i;
                current = _items[(hash1 + i * hash2) % _capacity];
            }
            if ((current)&&(current->_lesson._room == lesson._room)) {
                std::cout << "Such element exists.\n";
                success = true;
            }
            else
            if ((i <= _max_count)||(_free != -1)){
                if (_free != -1){
                    current = _items[(hash1 + _free * hash2) % _capacity];
                    current->_lesson = lesson;
                    current->_status = true;
                    current->_key = lesson._room;
                    _realcount++;
                    success = true;
                }
                else {
                    _items[(hash1 + i * hash2) % _capacity] = new Hs_item(&lesson, lesson._room);
                    _count++;
                    _realcount++;
                    success = true;
                }
            }
            else {
                UpSize();
            }

            if ((_realcount * 4 / 3) >= _capacity)
            UpSize();
    } while(!success);

}


Lesson* Hashtable::Search(Room room){

    int i = 0;
    int hash1 = Hash_function(room);
    int hash2 = Hash_function2(room);
    Hs_item* current = _items[hash1];
    while ((i <= _max_count)&&(current != nullptr)&&(current->_key != room)){
        i++;
        current = _items[(hash1 + i * hash2) % _capacity];
    }
    if (!current) {
        std::cout << "Such lesson hasn't been found.\n";
        return nullptr;
    }
    else
    if ((i <= _max_count)&&(current->_key == room)){
        if (current->_status)
        return &current->_lesson;
    }
    else{
        std::cout << "This lesson has been deleted.\n";
        return nullptr;
    }
}

void Hashtable::Delete_item(char let, int num){
    Room room = Room(let, num);
    Delete_item(room);
}

void Hashtable::Delete_item(Room room){

    int i = 0;
    int hash1 = Hash_function(room);
    int hash2 = Hash_function2(room);
    Hs_item* current = _items[hash1];
    while ((i <= _max_count)&&(current)&&(current->_key != room)){
        i++;
        current = _items[(hash1 + i * hash2) % _capacity];
    }
    if ((i <= _max_count)&&(current)&&(current->_key == room)&&(current->_status)) {
        current->_status = false;
        _realcount--;
    }
    else{
        std::cout << "Such item hasn't been found.\n";
    }

    if ((_realcount * 4) <= _capacity)
        DownSize();

}

void Hashtable::DownSize(){

    auto* newtable = new Hashtable(_capacity/2);
    int count = 0;
    for (auto i = 0; i < _capacity; ++i)
        if ((_items[i] != nullptr)&&(_items[i]->_status)){
            newtable->Insert_item(_items[i]->_lesson);
            count++;
    }

    _items = std::move(newtable->_items);
    newtable->_capacity = 0;
    delete(newtable);
    _capacity /= 2;
    _max_count /= 2;
    _realcount = count;
    _count = count;
}

void Hashtable::UpSize(){

    auto* newtable = new Hashtable(_capacity*2);
    int count = 0;
    for (auto i = 0; i < _capacity; ++i)
        if ((_items[i] != nullptr)&&(_items[i]->_status)) {
            newtable->Insert_item(_items[i]->_lesson);
            count++;
        }

    _items = std::move(newtable->_items);
    newtable->_capacity = 0;
    FreeTable(newtable);
    _capacity *= 2;
    _max_count *= 2;
    _realcount = count;
    _count = count;
}

int Hashtable::Hash_function(char letter, int number) const{

    int result = letter + number;
    result *= result;
    if (result > 10000) {
        result %= 100000;
        result /= 1000;
    }
    else {
        result /= 100;
    }

    result %= _capacity;
    return result;
}

int Hashtable::Hash_function(Room room){
    return Hash_function(room.letter, room.number);
}

int Hashtable::Hash_function2(char letter, int number) const{

    int result = 1 + (((int)letter * 1000 + number) % (GetMaxPrimeUpTo(_capacity)));//Ближайшее просто чилсло
    return result;
}

int Hashtable::Hash_function2(const Room& room){
    return Hash_function2(room.letter, room.number);
}

int GetMaxPrimeUpTo (int const limit) {
    std::vector<bool> sieve(limit);
    for (unsigned long long x2 = 1ull, dx2 = 3ull; x2 < limit; x2 += dx2, dx2 += 2ull)
        for (unsigned long long y2 = 1ull, dy2 = 3ull, n; y2 < limit; y2 += dy2, dy2 += 2ull) {
            // n = 4x² + y²
            n = (x2 << 2ull) + y2;
            if (n <= limit && (n % 12ull == 1ull || n % 12ull == 5ull))
                sieve[n].flip();
            // n = 3x² + y²
            n -= x2;
            if (n <= limit && n % 12ull == 7ull)
                sieve[n].flip();
            // n = 3x² - y² (при x > y)
            if (x2 > y2) {
                n -= y2 << 1ull;
                if (n <= limit && n % 12ull == 11ull)
                    sieve[n].flip();
            }
        }
    unsigned r = 5u;
    for (unsigned long long r2 = r * r, dr2 = (r << 1ull) + 1ull; r2 < limit; ++r, r2 += dr2, dr2 += 2ull)
        if (sieve[r])
            for (unsigned long long mr2 = r2; mr2 < limit; mr2 += r2)
                sieve[mr2] = false;
    if (limit > 2u)
        sieve[2u] = true;
    if (limit > 3u)
        sieve[3u] = true;
    for (auto i = sieve.size() - 1; i > 1; --i)
        if (sieve[i])
            return (++i);
}

