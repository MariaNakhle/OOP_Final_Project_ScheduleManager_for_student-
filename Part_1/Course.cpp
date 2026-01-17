#include "Course.h"
#include <iostream>
using namespace std; 

// Default constructor - creates empty course
Course::Course() 
    : id(0), name(""), credits(0), moedA(""), moedB(""), lecturer(""), semester("") {
    // Using initialization list to set default values
}

// Constructor with parameters - creates course with given data
// Constructor do not 
Course::Course(int id, string name, int credits, string moedA, string moedB, string lecturer, string semester)
    : id(id), name(name), credits(credits), moedA(moedA), moedB(moedB), lecturer(lecturer), semester(semester) {
    // Using initialization list for better performance
}

// Getter functions - all marked const since they don't change the object
//  const :  Because it allows us to call these methods on const instances of the class. without changing the object.
//  get : To provide read-only access to private member variables. 
int Course::getId() const { return id; }
string Course::getName() const { return name; }
int Course::getCredits() const { return credits; }
string Course::getMoedA() const { return moedA; }
string Course::getMoedB() const { return moedB; }
string Course::getLecturer() const { return lecturer; }
string Course::getSemester() const { return semester; }

// Setter functions - allow changing course data
//set :  To modify private member variables after object creation.
void Course::setName(const string& newName) { name = newName; }
void Course::setCredits(int newCredits) { credits = newCredits; }
void Course::setMoedA(const string& date) { moedA = date; }
void Course::setMoedB(const string& date) { moedB = date; }
void Course::setLecturer(const string& name) { lecturer = name; }
void Course::setSemester(const string& s) { semester = s; }

// Operator overload for printing course to output stream
// This function formats the course details and sends them to the output stream
ostream& operator<<(ostream& os, const Course& course) {
    os << "Course ID: " << course.id << endl;
    os << "Course Name: " << course.name << endl;
    os << "Credits: " << course.credits << endl;
    os << "Moed A: " << course.moedA << endl;
    os << "Moed B: " << course.moedB << endl;
    os << "Lecturer: " << course.lecturer << endl;
    os << "Semester: " << course.semester << endl;
    return os;
}