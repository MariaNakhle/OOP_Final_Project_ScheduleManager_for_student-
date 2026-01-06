#include "Tutorial.h"
#include <iostream>
using namespace std;

Tutorial::Tutorial(string type, int courseId, string day, int startHour, int endHour,
    string classroom, string teacherName, int groupNumber)
    : Lesson(type, courseId, day, startHour, endHour, classroom, teacherName, groupNumber) {
}

void Tutorial::print() const {
    cout << "[Tutorial] ";
    Lesson::print();
    cout << endl;
}
