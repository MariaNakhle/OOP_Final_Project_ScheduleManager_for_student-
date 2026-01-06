#include "Lesson.h"
#include <iostream>
using namespace std;

// Constructor with parameters - uses initialization list for better performance
Lesson::Lesson(string type, int courseId, string day, int startHour, int endHour, string classroom, string teacherName, int groupNumber)
    : type(type), courseId(courseId), day(day), startHour(startHour), endHour(endHour), classroom(classroom), teacherName(teacherName), groupNumber(groupNumber) {
    // All member variables initialized in initialization list
}

// Virtual function for printing lesson details - can be overridden by derived classes
void Lesson::print() const {
    cout << "Type: " << type
        << ", Course ID: " << courseId
        << ", Day: " << day
        << ", Start Hour: " << startHour
        << ", End Hour: " << endHour
        << ", Classroom: " << classroom
        << ", Teacher: " << teacherName
        << ", Group: " << groupNumber;
}

// Getter functions - all const since they don't modify the object
string Lesson::getType() const { return type; }
int Lesson::getCourseId() const { return courseId; }
string Lesson::getDay() const { return day; }
int Lesson::getStartHour() const { return startHour; }
int Lesson::getEndHour() const { return endHour; }
string Lesson::getClassroom() const { return classroom; }
string Lesson::getTeacherName() const { return teacherName; }
int Lesson::getGroupNumber() const { return groupNumber; }

// Setter functions - allow changing lesson data after creation
void Lesson::setType(const string& t) { type = t; }
void Lesson::setCourseId(int id) { courseId = id; } // Note: not recommended to change after creation
void Lesson::setDay(const string& d) { day = d; }
void Lesson::setStartHour(int h) { startHour = h; }
void Lesson::setEndHour(int h) { endHour = h; }
void Lesson::setClassroom(const string& c) { classroom = c; }
void Lesson::setTeacherName(const string& t) { teacherName = t; }
void Lesson::setGroupNumber(int g) { groupNumber = g; }

// Operator overload for printing lesson to output stream
ostream& operator<<(ostream& os, const Lesson& lesson) {
    lesson.print(); // Simply calls the print() function
    return os;
}
