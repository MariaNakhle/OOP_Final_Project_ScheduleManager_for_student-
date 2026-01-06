#ifndef LESSON_H
#define LESSON_H

#include <string>
#include <iostream>
#include <memory>
#include <stdexcept>

class Lesson {
protected:
    int courseId;
    int groupId;
    std::string teacherName;
    std::string day;
    int startHour;
    int duration;
    std::string building;
    std::string room;

    // Validation helper methods
    void validateCourseId(int id) const;
    void validateGroupId(int id) const;
    void validateTime(int hour, int dur) const;
    void validateDay(const std::string& dayName) const;

public:
    // Constructors
    Lesson(); 
    Lesson(int courseId, int groupId, const std::string& teacherName, 
           const std::string& day, int startHour, int duration, 
           const std::string& building, const std::string& room);
    // rule of 5
    // Virtual destructor for proper polymorphic cleanup
    virtual ~Lesson() = default;
    
    // Copy constructor and assignment (Rule of 5)
    Lesson(const Lesson& other) = default;
    Lesson& operator=(const Lesson& other) = default;
    
    // Move constructor and assignment
    Lesson(Lesson&& other) noexcept = default;
    Lesson& operator=(Lesson&& other) noexcept = default;
    //////////////////////////////////////////////////////////////////////////////////////
    
    // Const getters with noexcept guarantee
    int getCourseId() const noexcept;
    int getGroupId() const noexcept;
    const std::string& getTeacherName() const noexcept;
    const std::string& getDay() const noexcept;
    int getStartHour() const noexcept;
    int getDuration() const noexcept;
    int getEndHour() const noexcept; // New convenient method
    const std::string& getBuilding() const noexcept;
    const std::string& getRoom() const noexcept;

    // Setters with validation
    void setTeacherName(const std::string& name);
    void setDay(const std::string& newDay);
    void setStartHour(int hour);
    void setDuration(int newDuration);
    void setBuilding(const std::string& newBuilding);
    void setRoom(const std::string& newRoom);

    // Utility methods
    bool isValid() const noexcept;
    std::string getTimeRange() const;
    bool conflictsWith(const Lesson& other) const noexcept;
    
    // Comparison operators for sorting and searching
    bool operator==(const Lesson& other) const noexcept;
    bool operator!=(const Lesson& other) const noexcept;
    bool operator<(const Lesson& other) const noexcept; // Sort by day, then time
    
    // Pure virtual methods for polymorphism
    virtual std::string getType() const = 0;
    virtual void print() const = 0;
    virtual std::unique_ptr<Lesson> clone() const = 0; // Return smart pointer
    virtual double getWorkloadFactor() const = 0; // Different lesson types have different workloads
};

// Smart pointer type alias for convenience
using LessonPtr = std::unique_ptr<Lesson>;

// Factory function for creating lessons
LessonPtr createLesson(const std::string& type, int courseId, int groupId,
                      const std::string& teacherName, const std::string& day,
                      int startHour, int duration, const std::string& building,
                      const std::string& room);

#endif // LESSON_H