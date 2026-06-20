#ifndef ROOM_H
#define ROOM_H
#include "Student.h"
#include <vector>
using namespace std ;
class Room {
    private :
    int roomNumber ;
    int capacity ;
    vector<Student*>occupants;
    public :
    Room();
    Room(int roomnumber ,int cap);
    int getRoomNumber()const ;
    int getCapacity()const ;
    int getOccupantCount()const ;
    bool isFull()const;
    bool isEmpty()const ;
    bool addStudent(Student* student);
    bool removeStudent( int studentID);
    void display()const;
    
};

#endif