#include "Tutorial.h"
#include <iostream>
#include <iomanip>

// Default constructor
Tutorial::Tutorial() : Lesson() {}

// Parameterized constructor
Tutorial::Tutorial(const std::string& type, int courseId, const std::string& day, 
                  int startHour, int endHour, const std::string& classroom, 
                  const std::string& teacherName, int groupNumber)
    : Lesson(courseId, groupNumber, teacherName, day, startHour, endHour - startHour, "", classroom) {}

// Returns the type of the lesson
std::string Tutorial::getType() const {
    return "Tutorial";
}

// Enhanced print method
void Tutorial::print() const {
    std::cout << "--- TUTORIAL - Course " << std::setw(3) << courseId 
              << " - Group " << std::setw(2) << groupId
              << " - " << std::setw(9) << day
              << " - " << getTimeRange()
              << " - " << std::setw(20) << teacherName
              << " - " << building << " " << room << std::endl;
}

// Clone method returning smart pointer
std::unique_ptr<Lesson> Tutorial::clone() const {
    return std::make_unique<Tutorial>("Tutorial", courseId, day, startHour, 
                                     startHour + duration, room, teacherName, groupId);
}

// Workload factor for tutorials (moderate workload)
double Tutorial::getWorkloadFactor() const {
    return 0.8; // Lower than lectures since tutorials are usually shorter and less intensive
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Tutorial& tutorial) {
    os << "Type: Tutorial, "
       << "Course ID: " << tutorial.getCourseId()
       << ", Group: " << tutorial.getGroupId()
       << ", Day: " << tutorial.getDay()
       << ", Time: " << tutorial.getTimeRange()
       << ", Teacher: " << tutorial.getTeacherName()
       << ", Location: " << tutorial.getBuilding() << " " << tutorial.getRoom();
    return os;
}