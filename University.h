#ifndef UNIVERSITY_H
#define UNIVERITY_H
#include "Dormitory.h"
#include<string>
#include<vector>
using namespace std ;
class University {
private :
string name ;
vector<Dormitory> dormitories;
vector<Student*> allStudents;
public:
University();
University(const string& name);
~University();

string getName() const;
    int getTotalDormitories() const;
    int getTotalStudents() const;

void addDormitory(const Dormitory& dorm);
    Dormitory* findDormitory(const string& name);
 
 Student* addStudent(int id, const string& fullName, int academicYear);
    bool removeStudent(int studentId);
    Student* findStudent(int studentId);
 
    void saveToFile(const string& filename) const;
    void loadFromFile(const string& filename);
 
    void display() const;
    void displayAllStudents() const;



};



#endif