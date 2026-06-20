#ifndef STUDENT_H
#define STUDENT_H
#include<string>
#include<iostream>
using namespace std;
class Student {
    private: 
    int id;
    string FullName;
    int academicYear;
bool hasRoom;
public:
Student();
Student(int id,const string& full,int academicyear);
int getId()const;
string getFullName()const;
int getAcademicYear()const;
bool getHasRoom()const;

void setFullName(const string& name);
void setAcademicYear(int year);
void setHasRoom(bool assigned);
void display()const;
};


#endif