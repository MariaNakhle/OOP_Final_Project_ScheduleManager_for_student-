// (Lesson)  יורשות  ממנה Lecture
// 
//

#ifndef LECTURE_H
#define LECTURE_H

#include "Lesson.h"
#include <string>
using namespace std;

class Lecture : public Lesson { // direct base class of Lesson
public:
	// every thing in Lesson defined as a public the values here also public
	// but everything in Lesson is protected the values here also protected
    Lecture(string type, int courseId, string day, int startHour, int endHour, string classroom, string teacherName, int groupNumber);


    void print() const override;
};

#endif
