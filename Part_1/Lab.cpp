#include "Lab.h"
#include <iostream>
using namespace std;

Lab::Lab(string type, int courseId, string day, int startHour, int endHour,
    string classroom, string teacherName, int groupNumber)
    : Lesson(type, courseId, day, startHour, endHour, classroom, teacherName, groupNumber) {
}

void Lab::print() const {
    cout << "[Lab] ";
    Lesson::print();
    cout << endl;
}
