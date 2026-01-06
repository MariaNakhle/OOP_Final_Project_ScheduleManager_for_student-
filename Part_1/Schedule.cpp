#include "Schedule.h"
#include <iostream>
using namespace std;

// קונסטרקטור
Schedule::Schedule(int id)
    : scheduleId(id) {
}


Schedule::~Schedule() {
    for (Lesson* lesson : lessons) {
        delete lesson; // Free each lesson
    }
	lessons.clear(); // Clear the vector to remove all pointers
}

// הוספת שיעור לווקטור
void Schedule::addLesson(Lesson* l) {
    lessons.push_back(l);
}

// הדפסת כל השיעורים במערכת
void Schedule::print() const {
    cout << "Schedule ID: " << scheduleId << endl;
    cout << "Lessons:" << endl;
    for (Lesson* l : lessons) {
        l->print();
		//cout << endl; // הדפסת שורה חדשה אחרי כל שיעור
    }
}

// Getters
int Schedule::getId() const {
    return scheduleId;
}

int Schedule::getLessonCount() const {
	return lessons.size(); // number of lessons in the schedule
}

//Called when: Schedule object is const
// Returns a constant reference to the vector of lessons
// Purpose: Read-only access to lessons
const vector<Lesson*>& Schedule::getLessons() const {
    return lessons;
}

// Called when: Schedule object is non-const
// Returns a non-constant reference to the vector of lessons
// Purpose: Read-write access to lessons
vector<Lesson*>& Schedule::getLessons() {
    return lessons;
}

void Schedule::printTable() const {
    cout << "\nSchedule ID: " << scheduleId << "\n";

    const vector<string> days = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday" };

    // הדפסת כותרות שעות
    cout << "          ";
    for (int hour = 8; hour <= 17; ++hour) {
        cout << hour << "  ";
    }
    cout << "\n";

    for (const string& day : days) {
        cout.width(9);
        cout << left << day;

        for (int hour = 8; hour <= 17; ++hour) {
            bool hasLesson = false;
            for (Lesson* l : lessons) {
                if (l->getDay() == day &&
                    l->getStartHour() <= hour &&
                    hour < l->getEndHour()) {
                    hasLesson = true;
                    break;
                }
            }
            cout << (hasLesson ? " X " : " . ");
        }
        cout << "\n";
    }
}

bool Schedule::removeLesson(int courseId) {
    bool removed = false;
    
    vector<Lesson*>::iterator it = lessons.begin();
    while (it != lessons.end()) {
        if ((*it)->getCourseId() == courseId) {
            delete *it;  
            it = lessons.erase(it);  
            removed = true;
        }
        else {
            it++;  
        }
    }
    return removed;
}