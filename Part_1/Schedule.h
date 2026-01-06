#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include "Lesson.h"
using namespace std;

class Schedule {
private:
    int scheduleId;  
    
    vector<Lesson*> lessons;        

public:
  
    Schedule(int id);

    ~Schedule();

    // פונקציה להוספת שיעור
    void addLesson(Lesson* l);

    // פונקציה להדפסת כל המערכת
    void print() const;

    //  פונקציה נוספת להדפסת טבלה
    void printTable() const;

    // Getters
    int getId() const; // Read-only access to schedule ID
    int getLessonCount() const; // Returns current number of lessons

  
    const vector<Lesson*>& getLessons() const;
    vector<Lesson*>& getLessons();

    bool removeLesson(int courseId); //  edit/remove specific lessons from a schedule [new]

};

#endif
