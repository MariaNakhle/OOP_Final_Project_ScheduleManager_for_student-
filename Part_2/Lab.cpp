#include "Lab.h"
#include <iostream>
#include <iomanip>

// Default constructor
Lab::Lab() : Lesson() {}

// Parameterized constructor
Lab::Lab(const std::string& type, int courseId, const std::string& day, 
         int startHour, int endHour, const std::string& classroom, 
         const std::string& teacherName, int groupNumber)
    : Lesson(courseId, groupNumber, teacherName, day, startHour, endHour - startHour, "", classroom) {}

// Enhanced print method
void Lab::print() const {
    std::cout << "--- LAB - Course " << std::setw(3) << courseId 
              << " - Group " << std::setw(2) << groupId
              << " - " << std::setw(9) << day
              << " - " << getTimeRange()
              << " - " << std::setw(20) << teacherName
              << " - " << building << " " << room << std::endl;
}

// Returns the type of the lesson
std::string Lab::getType() const {
    return "Lab";
}

// Clone method returning smart pointer
std::unique_ptr<Lesson> Lab::clone() const {
    return std::make_unique<Lab>("Lab", courseId, day, startHour, 
                                startHour + duration, room, teacherName, groupId);
}

// Workload factor for labs (highest due to hands-on nature)
double Lab::getWorkloadFactor() const {
    return 1.5; // Higher workload factor due to practical work
}

// Stream insertion operator
std::ostream& operator<<(std::ostream& os, const Lab& lab) {
    os << "Type: Lab, "
       << "Course ID: " << lab.getCourseId()
       << ", Group: " << lab.getGroupId()
       << ", Day: " << lab.getDay()
       << ", Time: " << lab.getTimeRange()
       << ", Teacher: " << lab.getTeacherName()
       << ", Location: " << lab.getBuilding() << " " << lab.getRoom();
    return os;
}