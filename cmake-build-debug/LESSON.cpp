
#include "LESSON.h"
#include <bits/stdc++.h>

Room::Room(){

    letter = 'A';
    number = 100;
}

Room::Room(char let, int num){

    letter = let;
    number = num;
}

Room::Room(Room const &room){

    letter = room.letter;
    number = room.number;
}

bool operator==(Room& a, Room& b){

    return ((a.number == b.number) && (a.letter == b.letter));
}

Room& Room::operator=(const Room& b){
    if (this == &b){
        return *this;
    }
    letter = b.letter;
    number = b.number;
    return *this;
}

Room& Room::operator=(Room&& b) noexcept {
    if (this == &b){
        return *this;
    }
    letter = b.letter;
    number = b.number;
    return *this;
}

Lesson::Lesson(){

    _room = Room();
    _name = "Крестникова";
    _surname = "Ольга";
    _lastname = "Александровна";
    _hour = 1;
    _minute = 0;
    _subject = "ФСДиА";
}

Lesson::Lesson(char let,
               int num,
               std::string surname,
               std::string name,
               std::string lastname,
               int hour,
               int minute,
               std::string subject){

    _room = Room(let, num);
    _name = std::move(name);
    _surname = std::move(surname);
    _lastname = std::move(lastname);
    _hour = hour;
    _minute = minute;
    _subject = std::move(subject);
}

std::ostream& operator<<(std::ostream& os, const Lesson& a){

    os  << a._room.letter << ' '
        << a._room.number << ' '
        << a._surname << ' '
        << a._name << ' '
        << a._lastname << ' '
        << a._hour << ' '
        << a._minute << ' '
        << a._subject;
    return os;
}

std::ostream& operator<<(std::ostream& os, const Lesson* a){

    os  << a->_room.letter << ' '
        << a->_room.number << ' '
        << a->_surname << ' '
        << a->_name << ' '
        << a->_lastname << ' '
        << a->_hour << ' '
        << a->_minute << ' '
        << a->_subject;
    return os;
}

std::istream& operator>>(std::istream& is, Lesson& a){

    try {
        is >> a._room.letter
           >> a._room.number
           >> a._surname
           >> a._name
           >> a._lastname
           >> a._hour
           >> a._minute
           >> a._subject;
    }
    catch (...) {
        is.setstate(std::ios::failbit);
    }
    return is;
}

bool Lesson::operator==(const Lesson& other) const{
    return (
            (this->_room.letter == other._room.letter) &&
            (this->_room.number == other._room.number) &&
            (this->_surname == other._surname) &&
            (this->_name == other._name) &&
            (this->_lastname == other._lastname) &&
            (this->_minute == other._minute) &&
            (this->_hour == other._hour) &&
            (this->_subject == other._subject)
            );
}

bool Lesson::operator!=(const Lesson& other) const{
    return !(this == &other);
}