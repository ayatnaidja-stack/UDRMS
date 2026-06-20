#include "University.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

University::University() : name("Unnamed University") {}

University::University(const string& name) : name(name) {}

University::~University() {
    for (Student* s : allStudents)
        delete s;
    allStudents.clear();
}

string University::getName() const { return name; }
int University::getTotalDormitories() const { return dormitories.size(); }
int University::getTotalStudents() const { return allStudents.size(); }

void University::addDormitory(const Dormitory& dorm) {
    dormitories.push_back(dorm);
    cout << "Dormitory [" << dorm.getName() << "] added to " << name << endl;
}

Dormitory* University::findDormitory(const string& name) {
    for (Dormitory& d : dormitories)
        if (d.getName() == name) return &d;
    cout << "Dormitory [" << name << "] not found." << endl;
    return nullptr;
}

Student* University::addStudent(int id, const string& fullName, int academicYear) {
    if (findStudent(id)) {
        cout << "Student with ID " << id << " already exists!" << endl;
        return nullptr;
    }
    Student* s = new Student(id, fullName, academicYear);
    allStudents.push_back(s);
    cout << "Student [" << fullName << "] added to university." << endl;
    return s;
}

bool University::removeStudent(int studentId) {
    for (auto it = allStudents.begin(); it != allStudents.end(); ++it) {
        if ((*it)->getId() == studentId) {
            delete *it;
            allStudents.erase(it);
            cout << "Student " << studentId << " removed." << endl;
            return true;
        }
    }
    cout << "Student " << studentId << " not found." << endl;
    return false;
}

Student* University::findStudent(int studentId) {
    for (Student* s : allStudents)
        if (s->getId() == studentId) return s;
    return nullptr;
}

void University::saveToFile(const string& filename) const {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file: " << filename << endl;
        return;
    }

    file << "UNIVERSITY:" << name << "\n";

    for (const Student* s : allStudents) {
        file << "STUDENT:"
             << s->getId() << ","
             << s->getFullName() << ","
             << s->getAcademicYear() << ","
             << s->getHasRoom() << "\n";
    }

    for (const Dormitory& d : dormitories) {
        file << "DORMITORY:" << d.getName() << "\n";
        file << "MENU:" << d.getName() << ","
             << d.getRestaurant().getBreakfastMenu() << ","
             << d.getRestaurant().getLunchMenu() << ","
             << d.getRestaurant().getDinnerMenu() << "\n";
    }

    file.close();
    cout << "Data saved to [" << filename << "] successfully." << endl;
}

void University::loadFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: Could not open file: " << filename << endl;
        return;
    }

    for (Student* s : allStudents) delete s;
    allStudents.clear();
    dormitories.clear();

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line.rfind("UNIVERSITY:", 0) == 0) {
            name = line.substr(11);

        } else if (line.rfind("STUDENT:", 0) == 0) {
            stringstream ss(line.substr(8));
            string token, fullName;
            int id, year; bool hasRoom;
            getline(ss, token, ','); id = stoi(token);
            getline(ss, fullName, ',');
            getline(ss, token, ','); year = stoi(token);
            getline(ss, token, ','); hasRoom = stoi(token);
            Student* s = new Student(id, fullName, year);
            s->setHasRoom(hasRoom);
            allStudents.push_back(s);

        } else if (line.rfind("DORMITORY:", 0) == 0) {
            dormitories.push_back(Dormitory(line.substr(10)));

        } else if (line.rfind("MENU:", 0) == 0) {
            stringstream ss(line.substr(5));
            string dormName, breakfast, lunch, dinner;
            getline(ss, dormName, ',');
            getline(ss, breakfast, ',');
            getline(ss, lunch, ',');
            getline(ss, dinner);
            Dormitory* d = findDormitory(dormName);
            if (d) {
                d->getRestaurant().setBreakfastMenu(breakfast);
                d->getRestaurant().setLunchMenu(lunch);
                d->getRestaurant().setDinnerMenu(dinner);
            }
        }
    }
    file.close();
    cout << "Data loaded from [" << filename << "] successfully." << endl;
}

void University::display() const {
    cout << "\n---------------------------------------" << endl;
    cout << "  University : " << name << endl;
    cout << "  Dormitories: " << dormitories.size() << endl;
    cout << "  Students   : " << allStudents.size() << endl;
    cout << "------------------------------------------" << endl;
    for (const Dormitory& d : dormitories)
        d.display();
}

void University::displayAllStudents() const {
    cout << "\n--- All Students in " << name << " ---" << endl;
    if (allStudents.empty()) {
        cout << "(No students yet)" << endl;
        return;
    }
    for (const Student* s : allStudents)
        s->display();
}