#ifndef SCHEDULE_H
#define SCHEDULE_H

#include <vector>
#include <string>
#include <memory>
#include "Lesson.h"

class Schedule {
private:
    int id;  
    int studentId;  // Added for comprehensive schedule management
    int courseId;   // Added for course association
    std::string semester;  // Added for semester tracking
    int year;       // Added for year tracking
    std::vector<std::unique_ptr<Lesson>> lessons;  // Use smart pointers for automatic memory management

public:
    // Constructors
    Schedule();                     
    Schedule(int id);             
    Schedule(int id, int studentId, int courseId, const std::string& semester, int year);  // Added comprehensive constructor
    
    // Copy constructor and assignment operator
    Schedule(const Schedule& other);
    Schedule& operator=(const Schedule& other);
    
    // Move constructor and assignment operator
    Schedule(Schedule&& other) noexcept = default;
    Schedule& operator=(Schedule&& other) noexcept = default;

    // Getters and Setters
    int getId() const noexcept;
    void setId(int newId);
    
    int getStudentId() const noexcept;
    void setStudentId(int newStudentId);
    
    int getCourseId() const noexcept;
    void setCourseId(int newCourseId);
    
    const std::string& getSemester() const noexcept;
    void setSemester(const std::string& newSemester);
    
    int getYear() const noexcept;
    void setYear(int newYear);

    // Lesson management with smart pointers
    void addLesson(std::unique_ptr<Lesson> lesson);                       
    void addLessonForce(std::unique_ptr<Lesson> lesson);  // Force add lesson even with conflicts                      
    void removeLesson(int courseId, int groupId);               
    void removeLesson(int courseId, int groupId, const std::string& type); // Remove specific lesson type
    void clearLessons();  // Clear all lessons from schedule           
    std::vector<std::unique_ptr<Lesson>>& getLessons();
    const std::vector<std::unique_ptr<Lesson>>& getLessons() const; // Const version                              

    // Helper functions for backward compatibility
    void addLesson(Lesson* lesson); // Convert raw pointer to smart pointer
    void addLessonForce(Lesson* lesson); // Convert raw pointer to smart pointer

    // Utility methods
    void printSchedule() const;                                 
    bool hasConflict(const Lesson* newLesson) const;            
    int totalHours() const;                                     
    void printConflicts() const;  // Show all conflicts

    // File operations (optional)
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);

    // Destructor (smart pointers handle cleanup automatically)
    ~Schedule() = default;
};

#endif // SCHEDULE_H
