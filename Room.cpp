#include "Room.h"
#include <iostream>
#include<algorithm>
using namespace std ;
Room::Room():roomNumber(0),capacity(2){}
Room::Room(int roomnumber,int cap):roomNumber(roomnumber),capacity(cap){}
int Room::getRoomNumber()const {return roomNumber;}
int Room::getCapacity()const {return capacity;}
int Room::getOccupantCount()const {return occupants.size();}
bool Room::isFull()const {
    return (int)occupants.size()>=capacity;
}
bool Room::isEmpty()const {
    return occupants.empty();
}
bool Room::addStudent(Student* student){
    if(isFull()){
        cout<<"Room "<<roomNumber<<" is full! "<<endl;
    return false;
    }
    occupants.push_back(student);
    student->setHasRoom(true);
    return true;
}
bool Room::removeStudent(int studentID){
     for (auto it = occupants.begin(); it != occupants.end(); ++it) {
        if ((*it)->getId() == studentID) {
            (*it)->setHasRoom(false);
            occupants.erase(it);
            return true;
        }
    }
    cout << "Student with ID " << studentID<< " not found in room " << roomNumber << endl;
    return false;
}
void Room::display()const{
    cout<<" Room informations : "<<endl;
    cout<<" Room Number : "<<roomNumber<<endl;
    cout<<" Capacity : "<<capacity<<endl;
    cout<<" Occupied : "<<occupants.size()<<"/"<<capacity<<endl;
    if(occupants.empty()){
        cout<<"(Room is empty!)"<<endl;

    }
    else {
        cout<< "occupants: "<<endl;
    for(const Student*s:occupants){
        cout<<" -["<<s->getId()<< "] "<<s->getFullName()<<endl;
    }
    }
    cout<<"-------------------------"<<endl;
}