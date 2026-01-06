#include "Lecture.h"
#include <iostream>
#include <iomanip>

// Default constructor
Lecture::Lecture() : Lesson() {}

// Parameterized constructor
Lecture::Lecture(const std::string& type, int courseId, const std::string& day, 
                int startHour, int endHour, const std::string& classroom, 
                const std::string& teacherName, int groupNumber)
    : Lesson(courseId, groupNumber, teacherName, day, startHour, endHour - startHour, "", classroom) {}

// Returns the type of the lesson
std::string Lecture::getType() const {
    return "Lecture";
}

// Enhanced print method with better formatting
void Lecture::print() const {
    std::cout << "--- LECTURE - Course " << std::setw(3) << courseId 
              << " - Group " << std::setw(2) << groupId
              << " - " << std::setw(9) << day
              << " - " << getTimeRange()
              << " - " << std::setw(20) << teacherName
              << " - " << building << " " << room << std::endl;
}

// Clone method returning smart pointer
std::unique_ptr<Lesson> Lecture::clone() const {
    return std::make_unique<Lecture>("Lecture", courseId, day, startHour, 
                                    startHour + duration, room, teacherName, groupId);
}

// Workload factor for lectures (typically lower than labs)
double Lecture::getWorkloadFactor() const {
    return 1.0; // Base workload factor
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Lecture& lecture) {
    os << "Type: Lecture, "
       << "Course ID: " << lecture.getCourseId()
       << ", Group: " << lecture.getGroupId()
       << ", Day: " << lecture.getDay()
       << ", Time: " << lecture.getTimeRange()
       << ", Teacher: " << lecture.getTeacherName()
       << ", Location: " << lecture.getBuilding() << " " << lecture.getRoom();
    return os;
}