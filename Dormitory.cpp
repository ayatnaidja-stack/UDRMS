#include "Dormitory.h"
#include <iostream>
using namespace std;

Dormitory::Dormitory() : name("Unnamed Dormitory") {}
Dormitory::Dormitory(const string& name) : name(name) {}

string Dormitory::getName() const { return name; }
int Dormitory::getTotalRooms() const { return rooms.size(); }
 
int Dormitory::getAvailableRooms() const {
    int count = 0;
    for (const Room& r : rooms)
        if (!r.isFull()) count++;
    return count;
}
Restaurant& Dormitory::getRestaurant() { return restaurant; }
const Restaurant& Dormitory::getRestaurant() const { return restaurant; }
void Dormitory::addRoom(const Room& room) {
    rooms.push_back(room);
}
 void Dormitory::registerStudent(Student* student) {
    students.push_back(student);
    cout << "Student [" << student->getFullName() << "] registered in " << name << endl;
}
Student* Dormitory::findStudent(int studentId) {
    for (Student* s : students)
        if (s->getId() == studentId) return s;
    return nullptr;
}
 

bool Dormitory::removeStudent(int studentId) {
    for (auto it = students.begin(); it != students.end(); ++it) {
        if ((*it)->getId() == studentId) {
            students.erase(it);
            cout << "Student removed from dormitory." << endl;
            return true;
        }
    }
    cout << "Student not found in dormitory." << endl;
    return false;
}
bool Dormitory::assignStudentToRoom(Student* student, int roomNumber) {
    for (Room& r : rooms) {
        if (r.getRoomNumber() == roomNumber) {
            return r.addStudent(student);
        }
    }
    cout << "Room " << roomNumber << " does not exist in " << name << endl;
    return false;
}
 

bool Dormitory::removeStudentFromRoom(int studentId, int roomNumber) {
    for (Room& r : rooms) {
        if (r.getRoomNumber() == roomNumber) {
            return r.removeStudent(studentId);
        }
    }
    cout << "Room " << roomNumber << " not found." << endl;
    return false;
}
void Dormitory::displayRooms() const {
    cout << "\n--- Rooms in " << name << " ---" << endl;
    if (rooms.empty()) {
        cout << "(No rooms added yet!)" << endl;
        return;
    }
    for (const Room& r : rooms)
        r.display();
}
 

void Dormitory::displayStudents() const {
    cout << "\n--- Students in " << name << " ---" << endl;
    if (students.empty()) {
        cout << "(No students registered yet!)" << endl;
        return;
    }
    for (const Student* s : students)
        s->display();
}
 
void Dormitory::display() const {
    cout << "\n------------ Dormitory: " << name << " ---------" << endl;
    cout << "Total Rooms    : " << rooms.size() << endl;
    cout << "Available Rooms: " << getAvailableRooms() << endl;
    cout << "Total Students : " << students.size() << endl;
    cout << "--- Restaurant ---" << endl;
    restaurant.displayMenu();
}