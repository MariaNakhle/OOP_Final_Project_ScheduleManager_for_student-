#include "Lecture.h"
#include <iostream>
using namespace std;


Lecture::Lecture(string type, int courseId, string day, int startHour, int endHour, string classroom, string teacherName, int groupNumber)
    : Lesson(type, courseId, day, startHour, endHour, classroom, teacherName, groupNumber) {
}

// פונקציית ההדפסה
void Lecture::print() const {
    cout << "[Lecture] ";
    Lesson::print(); 
    cout << endl;
}
// The purpose of this function is to print the details of the lecture.
//  i can see in the output: 
// You can see the : type, course ID, day, start hour, end hour, classroom, teacher name, and group number of the lecture.