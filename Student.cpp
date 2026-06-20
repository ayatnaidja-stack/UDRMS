#include "Student.h"
#include<iostream>
using namespace std  ;
Student::Student():id(0),FullName("unknown"),academicYear(1),hasRoom(false){}
Student::Student(int id,const string& full,int year):id(id),FullName(full),academicYear(year),hasRoom(false){}
int Student::getId()const {return id;}
string Student::getFullName()const {return FullName;}
int Student::getAcademicYear()const{return academicYear;}
bool Student::getHasRoom()const{return hasRoom;}

void Student::setFullName(const string& name){
    FullName=name;
}
void Student::setAcademicYear(int year){
    academicYear = year;
}
void Student:: setHasRoom(bool assigned){
    hasRoom= assigned;
}
void Student::display()const{
    cout<<" student information : "<<endl;
    cout<<" Student ID : "<<id<<endl;
cout<<" Full Name : "<<FullName<<endl;
cout<<" Academic Year : "<<academicYear<<endl;
cout<<" Has Room ? "<<(hasRoom ? "yes": "No")<<endl;

}