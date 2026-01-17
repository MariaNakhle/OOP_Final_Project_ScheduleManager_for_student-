#ifndef FILEMANAGER_H
#define FILEMANAGER_H

#include <vector>
#include <string>
#include "Course.h"
#include "Schedule.h"

void loadCourses(std::vector<Course>& courses);

void saveCourses(const std::vector<Course>& courses);

void loadSchedules(std::vector<Schedule*>& schedules);

//void loadLessonFromCSV(Schedule* sched, int courseId, const std::string& lessonType);
void loadIndividualSchedule(Schedule* sched, int id);

void saveSchedules(const std::vector<Schedule*>& schedules);

void loadAllLessons(std::vector<Lesson*>& lessons);

void saveAllLessons(const std::vector<Lesson*>& lessons);

// functions for individual lesson type loading
void loadLessonsFromFile(const std::string& filename, const std::string& lessonType, std::vector<Lesson*>& lessons);

void saveLessonsToFile(const std::string& filename, const std::vector<Lesson*>& lessons, const std::string& lessonType);

#endif

int parseTimeToHour(const std::string& timeStr);
void writeCourseData(std::ofstream& file, const std::vector<Course>& courses);
