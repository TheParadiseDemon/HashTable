//
// Created by user on 08.06.2023.
//
#include <bits/stdc++.h>

#ifndef HASHTABLE_LESSON_H
#define HASHTABLE_LESSON_H

struct Room{

    int number;
    char letter;

    ~Room() = default;
    Room();
    Room(Room const &);
    Room(char, int);

    friend bool operator==(Room&, Room&);
    Room& operator=(const Room&);
    Room& operator=(Room&&) noexcept ;
};

struct Lesson{

    Room _room;
    std::string _surname;
    std::string _name;
    std::string _lastname;
    int _hour;
    int _minute;
    std::string _subject;

    ~Lesson() = default;
    Lesson();
    Lesson(char, int, std::string, std::string, std::string, int, int, std::string);

    friend std::ostream& operator<<(std::ostream&, const Lesson&);
    friend std::istream& operator>>(std::istream&, Lesson&);
    bool operator==(const Lesson&) const;
    bool operator!=(const Lesson&) const;
};

#endif //HASHTABLE_LESSON_H
