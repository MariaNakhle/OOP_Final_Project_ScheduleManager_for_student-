#ifndef SYSTEM_H
#define SYSTEM_H

#include "Course.h"
#include "Schedule.h"
#include "Lesson.h"
#include "Lecture.h"
#include "Tutorial.h" 
#include "Lab.h"
#include <vector>
#include <string>

class System {
private:
    std::vector<Course> courses;
    std::vector<Lesson*> lessons;
    std::vector<Schedule> schedules;
    int lastPrintedCourseIndex;

    void loadCourses();
    void loadLessons();
    void loadSchedules();
    void saveSchedules();
    void saveCourses();
    void saveLessons();
    
    // Helper methods for enhanced functionality
    void waitForUser();
    void clearScreen();
    void setConsoleSize();

public:
    System();
    ~System();

    void run();

private:
    // Menu system
    void showMainMenu();
    void processMenuChoice(int choice);
    
    void handlePrintCourse(const std::string& courseId);
    void handlePrintCourses();
    void handleMore();
    void handlePrintSchedule(const std::string& scheduleId);
    void handlePrintSchedules();
    void handleAddSchedule();
    void handleRemoveSchedule(const std::string& scheduleId);
    void handleAddLessonToSchedule(const std::string& scheduleId, const std::string& courseId, const std::string& groupId);
    void handleRemoveLessonFromSchedule(const std::string& scheduleId, const std::string& courseId, const std::string& groupId);
    void handleCheckConflicts(const std::string& scheduleId);
    void handleClear();
    
    // Data management functions
    void handleAddCourse();
    void handleRemoveCourse(const std::string& courseId);
    void handleAddLesson();
    void handleRemoveLesson(const std::string& courseId, const std::string& groupId);
    
    // Analysis functions
    void handleFindTimeConflicts();
    void handleAnalyzeCourseWorkload(const std::string& scheduleId);
    void handleAnalyzeTeacherSchedules(const std::string& teacherName);
    
    void handleHelp();
    void handleExit();

    void printWelcomeMessage();
    Lesson* findLesson(int courseId, int groupId);
    
    // New method to find all lessons for a course/group combination
    std::vector<Lesson*> findLessonsForCourseAndGroup(int courseId, int groupId);
    
    // Helper method to get course name by ID
    std::string getCourseName(int courseId) const;
    
    // Helper method for workload analysis
    void analyzeScheduleWorkload(const Schedule& schedule) const;
    
    // Helper method for user confirmation
    bool getUserConfirmation(const std::string& question) const;
    
    // Method to save individual schedule file
    void saveIndividualSchedule(const Schedule& schedule) const;
    
    // Helper methods for clean input handling
    std::string getStringInput(const std::string& prompt);
    int getIntInput(const std::string& prompt);
    void printSeparator(char c = '=', int length = 60);
};

#endif // SYSTEM_H