#include <bits/stdc++.h>
#include "HASHTABLE.h"
#include "cmake-build-debug/HASHTABLE.h"

int main() {


    std::ifstream input("input.txt", std::ios::in);
    int n;
    input >> n;
    auto* table = new Hashtable(10);
//    for (auto i = 0; i < 1; ++i){

        int h, m, num;
        char let;
        std::string name, surname, lastname, subject;
        input >> let >> num >> surname >> name >> lastname >> h >> m >> subject;
        Lesson lesson = Lesson(let, num, surname, name, lastname, h, m, subject);
//        table->Insert_item(lesson);

//        table->Print_HashTable();
//    }
    lesson._room.letter = 'C';
    lesson._room.number = 1;

    table->Insert_item(lesson);

    table->Print_HashTable();

    lesson._room.letter = 'C';
    lesson._room.number = 1;

    table->Insert_item(lesson);

    table->Print_HashTable();

    lesson._room.letter = 'A';
    lesson._room.number = 3;

    table->Insert_item(lesson);

    table->Print_HashTable();

    lesson._room.letter = 'C';
    lesson._room.number = 154;

    table->Insert_item(lesson);

    table->Print_HashTable();

    Room room = Room('C', 154);
    if (table->Search(room))
        std::cout << "C 154 has been found.\n";
    else
        std::cout << "C 154 hasn't been found.\n";

    room = Room('A', 3);
    if (table->Search(room))
        std::cout << "A 3 has been found.\n";
    else
        std::cout << "A 3 hasn't been found.\n";

    room = Room('A', 5);
    if (table->Search(room))
        std::cout << "A 5 has been found.\n";
    else
        std::cout << "A 5 hasn't been found.\n";

    table->Delete_item('A', 3);

    table->Print_HashTable();

    table->Delete_item('A', 3);

    table->Delete_item('C', 154);

    table->Print_HashTable();

    return 0;
}
