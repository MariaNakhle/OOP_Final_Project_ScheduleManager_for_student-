#include "Lesson.h"
#include "Lecture.h"
#include "Tutorial.h"
#include "Lab.h"
#include <algorithm>
#include <iostream>
#include <sstream>
#include <vector>

// Default constructor
Lesson::Lesson() : courseId(0), groupId(0), startHour(0), duration(0) {}

// Parameterized constructor with validation
Lesson::Lesson(int courseId, int groupId, const std::string& teacherName, 
               const std::string& day, int startHour, int duration, 
               const std::string& building, const std::string& room)
    : courseId(courseId), groupId(groupId), teacherName(teacherName), 
      day(day), startHour(startHour), duration(duration), 
      building(building), room(room) {
    validateCourseId(courseId);
    validateGroupId(groupId);
    validateTime(startHour, duration);
    validateDay(day);
}

// Validation helper methods
void Lesson::validateCourseId(int id) const {
    if (id <= 0) {
        throw std::invalid_argument("Course ID must be positive");
    }
}

void Lesson::validateGroupId(int id) const {
    if (id <= 0) {
        throw std::invalid_argument("Group ID must be positive");
    }
}

void Lesson::validateTime(int hour, int dur) const {
    if (hour < 0 || hour > 23) {
        throw std::invalid_argument("Start hour must be between 0 and 23");
    }
    if (dur <= 0 || dur > 12) {
        throw std::invalid_argument("Duration must be between 1 and 12 hours");
    }
    if (hour + dur > 24) {
        throw std::invalid_argument("Lesson cannot extend beyond 24:00");
    }
}

void Lesson::validateDay(const std::string& dayName) const {
    static const std::vector<std::string> validDays = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };
    
    if (std::find(validDays.begin(), validDays.end(), dayName) == validDays.end()) {
        throw std::invalid_argument("Invalid day name: " + dayName);
    }
}

// Const getters with noexcept guarantee
int Lesson::getCourseId() const noexcept {
    return courseId;
}

int Lesson::getGroupId() const noexcept {
    return groupId;
}

const std::string& Lesson::getTeacherName() const noexcept {
    return teacherName;
}

const std::string& Lesson::getDay() const noexcept {
    return day;
}

int Lesson::getStartHour() const noexcept {
    return startHour;
}

int Lesson::getDuration() const noexcept {
    return duration;
}

int Lesson::getEndHour() const noexcept {
    return startHour + duration;
}

const std::string& Lesson::getBuilding() const noexcept {
    return building;
}

const std::string& Lesson::getRoom() const noexcept {
    return room;
}

// Setters with validation
void Lesson::setTeacherName(const std::string& name) {
    if (name.empty() || name.length() > 100) {
        throw std::invalid_argument("Teacher name must be between 1 and 100 characters");
    }
    teacherName = name;
}

void Lesson::setDay(const std::string& newDay) {
    validateDay(newDay);
    day = newDay;
}

void Lesson::setStartHour(int hour) {
    validateTime(hour, duration);
    startHour = hour;
}

void Lesson::setDuration(int newDuration) {
    validateTime(startHour, newDuration);
    duration = newDuration;
}

void Lesson::setBuilding(const std::string& newBuilding) {
    if (newBuilding.length() > 50) {
        throw std::invalid_argument("Building name too long");
    }
    building = newBuilding;
}

void Lesson::setRoom(const std::string& newRoom) {
    if (newRoom.length() > 20) {
        throw std::invalid_argument("Room name too long");
    }
    room = newRoom;
}

// Utility methods
bool Lesson::isValid() const noexcept {
    try {
        validateCourseId(courseId);
        validateGroupId(groupId);
        validateTime(startHour, duration);
        validateDay(day);
        return !teacherName.empty() && teacherName.length() <= 100 &&
               building.length() <= 50 && room.length() <= 20;
    } catch (...) {
        return false;
    }
}

std::string Lesson::getTimeRange() const {
    std::ostringstream oss;
    oss << (startHour < 10 ? "0" : "") << startHour << ":00-"
        << (getEndHour() < 10 ? "0" : "") << getEndHour() << ":00";
    return oss.str();
}

bool Lesson::conflictsWith(const Lesson& other) const noexcept {
    if (day != other.day) {
        return false;
    }
    
    int thisEnd = startHour + duration;
    int otherEnd = other.startHour + other.duration;
    
    return (startHour < otherEnd) && (other.startHour < thisEnd);
}

// Comparison operators
bool Lesson::operator==(const Lesson& other) const noexcept {
    return courseId == other.courseId && groupId == other.groupId;
}

bool Lesson::operator!=(const Lesson& other) const noexcept {
    return !(*this == other);
}

bool Lesson::operator<(const Lesson& other) const noexcept {
    static const std::vector<std::string> dayOrder = {
        "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"
    };
    
    auto thisDay = std::find(dayOrder.begin(), dayOrder.end(), day) - dayOrder.begin();
    auto otherDay = std::find(dayOrder.begin(), dayOrder.end(), other.day) - dayOrder.begin();
    
    if (thisDay != otherDay) {
        return thisDay < otherDay;
    }
    return startHour < other.startHour;
}

void Lesson::print() const {
    std::cout << "Course ID: " << courseId 
              << ", Group: " << groupId
              << ", Day: " << day
              << ", Time: " << getTimeRange()
              << ", Teacher: " << teacherName
              << ", Location: " << building << " " << room;
}

// Factory function implementation
LessonPtr createLesson(const std::string& type, int courseId, int groupId,
                      const std::string& teacherName, const std::string& day,
                      int startHour, int duration, const std::string& building,
                      const std::string& room) {
    if (type == "Lecture") {
        return std::make_unique<Lecture>(type, courseId, day, startHour, startHour + duration, room, teacherName, groupId);
    } else if (type == "Tutorial") {
        return std::make_unique<Tutorial>(type, courseId, day, startHour, startHour + duration, room, teacherName, groupId);
    } else if (type == "Lab") {
        return std::make_unique<Lab>(type, courseId, day, startHour, startHour + duration, room, teacherName, groupId);
    } else {
        throw std::invalid_argument("Unknown lesson type: " + type);
    }
}

