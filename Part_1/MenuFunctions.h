#ifndef MENUFUNCTIONS_H
#define MENUFUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <limits>
#include <tuple>
#include <map>
#include <iomanip>
#include <algorithm>
#include <set>
#include "Course.h"
#include "Schedule.h"
#include "Lecture.h"
#include "Tutorial.h"
#include "Lab.h"

using namespace std;

struct ExamDateTime {
    string day;
    int startHour; 
    int endHour;
    bool isValid;
    string originalDate;

	ExamDateTime(); // Default constructor initializes to invalid state (брай)
	ExamDateTime(const string& examDateStr); // Constructor that parses the exam date string
};

// Menu and utility functions
void printMenu();
void clearCin(); // Clear input buffer to handle invalid input
void showHelp();

// Function to print all lessons for a specific course from CSV files
// Course information functions
void printAllLessonsFromCSV(int courseId, const vector<Course>& courses);

// Schedule display functions
void printScheduleTable(int scheduleId);
void printScheduleTableClean(int scheduleId);

// Lesson management functions
bool addLessonFromCSV(int courseId, int lessonChoice, const vector<Course>& courses, Schedule* target);

int parseTimeToHour(const string& timeStr);

// Analysis functions
void findTimeConflicts(const vector<Schedule*>& schedules, const vector<Course>& courses);
void analyzeCourseWorkload(const vector<Schedule*>& schedules, const vector<Course>& courses);
void analyzeTeacherSchedules(const vector<Schedule*>& schedules, const vector<Course>& courses);

bool containsSlash(const string& str); // Helper function to check if string contains '/'
bool containsColon(const string& str); // Helper function to check if string contains ':'

#endif