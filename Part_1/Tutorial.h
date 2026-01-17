#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Lesson.h"
#include <string>
using namespace std;

class Tutorial : public Lesson {
public:
    Tutorial(string type, int courseId, string day, int startHour, int endHour,
        string classroom, string teacherName, int groupNumber);

    void print() const override;
};

#endif
