#ifndef DORMITORY_H
#define DORMITORY_H
 
#include "Room.h"
#include "Restaurant.h"
#include "Student.h"
#include <string>
#include <vector>
using namespace std;
class Dormitory {
private:
    string name;
    vector<Room> rooms;
    Restaurant restaurant;      
    vector<Student*> students;
public:
   
    Dormitory();
    Dormitory(const string& name);
 
    string getName() const;
    int getTotalRooms() const;
    int getAvailableRooms() const;
    Restaurant& getRestaurant(); 
const Restaurant& getRestaurant() const;
 void addRoom(const Room& room);
    bool assignStudentToRoom(Student* student, int roomNumber);
    bool removeStudentFromRoom(int studentId, int roomNumber);
 
    void registerStudent(Student* student);
    bool removeStudent(int studentId);
    Student* findStudent(int studentId);
 
    void displayRooms() const;
    void displayStudents() const;
    void display() const;

};
#endif
