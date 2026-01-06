#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
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
#include "FileManager.h"
#include "MenuFunctions.h"  
#include "TestFunctions.h"

using namespace std;

int main() {
    // Vectors to store our data
    vector<Course> courses;
    vector<Schedule*> schedules;
    size_t courseDisplayIndex = 0; // For pagination

    // Load data from files when program starts
    loadCourses(courses);
    loadSchedules(schedules);

    bool running = true;

    while (running) {
        printMenu();

        int choice;
        cin >> choice;
        if (cin.fail()) {
            cout << "Invalid input. Please enter a number.\n";
            clearCin();
            continue;
        }
        clearCin();

        if (choice == 1) { // PrintCourse <course_id>
            int courseId;
            cout << "Enter Course ID: ";
            cin >> courseId;
            if (cin.fail()) {
                cout << "Invalid input.\n";
                clearCin();
            }
            else {
                clearCin();
                // Use the new function to display course and lesson info from CSV files
                printAllLessonsFromCSV(courseId, courses);
            }
        }
        else if (choice == 2) { // PrintCourses
            cout << "\n----- First 10 Courses -----\n";
            if (courses.empty()) {
                cout << "No courses available.\n";
            }
            else {
                courseDisplayIndex = 0;
                size_t end = min(courseDisplayIndex + 10, courses.size());
                for (size_t i = courseDisplayIndex; i < end; ++i) {
                    cout << courses[i] << endl;
                }
                courseDisplayIndex = end;
                if (courseDisplayIndex < courses.size()) {
                    cout << "\nUse option 3 (More) to see next 10 courses.\n";
                }
                else {
                    cout << "\nEnd of course list.\n";
                    courseDisplayIndex = 0;
                }
            }
        }
        else if (choice == 3) { // More
            if (courses.empty()) {
                cout << "No courses available.\n";
            }
            else if (courseDisplayIndex >= courses.size()) {
                cout << "No more courses to display. Use option 2 (PrintCourses) to start from beginning.\n";
                courseDisplayIndex = 0;
            }
            else {
                cout << "\n----- Next 10 Courses -----\n";
                size_t end = min(courseDisplayIndex + 10, courses.size());
                for (size_t i = courseDisplayIndex; i < end; ++i) {
                    cout << courses[i] << endl;
                }
                courseDisplayIndex = end;
                if (courseDisplayIndex < courses.size()) {
                    cout << "\nUse option 3 (More) to see next 10 courses.\n";
                }
                else {
                    cout << "\nEnd of course list.\n";
                    courseDisplayIndex = 0;
                }
            }
        }
        else if (choice == 4) { // PrintSchedule <schedule_id>
            int scheduleId;
            cout << "Enter Schedule ID: ";
            cin >> scheduleId;
            if (cin.fail()) {
                cout << "Invalid input.\n";
                clearCin();
            }
            else {
                clearCin();
                // Print schedule table directly from CSV file
                printScheduleTable(scheduleId);
            }
        }
        else if (choice == 5) { // PrintSchedules
            cout << "\n----- All Schedules -----\n";

            // First check if we have any schedules in memory
            if (schedules.empty()) {
                cout << "No schedules loaded in memory.\n";
                cout << "Checking for CSV files...\n";

                // Try to find Schedule CSV files (now unlimited)
                bool foundAnySchedule = false;
                for (int i = 1; i <= 100; i++) { // Check reasonable range
                    string filename = "Schedule" + to_string(i) + ".csv";
                    ifstream testFile(filename);
                    if (testFile.is_open()) {
                        testFile.close();
                        foundAnySchedule = true;

                        // Print this schedule using the clean table format
                        cout << "\n==========================================\n";
                        cout << "Schedule " << i << ":\n";
                        cout << "==========================================\n";
                        printScheduleTableClean(i);
                    }
                }

                if (!foundAnySchedule) {
                    cout << "No schedule CSV files found.\n";
                }
            }
            else {
                // We have schedules in memory, show each one in table format
                for (Schedule* s : schedules) {
                    int scheduleId = s->getId();
                    cout << "\n==========================================\n";
                    cout << "Schedule " << scheduleId << ":\n";
                    cout << "==========================================\n";

                    // Use the clean table format
                    printScheduleTableClean(scheduleId);
                }
            }
        }
        else if (choice == 6) { // AddSchedule
            cout << "\n----- Adding New Schedule -----\n";

            // Find the highest existing schedule ID
            int maxId = 0;

            // Check schedules in memory
            for (Schedule* s : schedules) {
                if (s->getId() > maxId) {
                    maxId = s->getId();
                }
            }

            // Dynamically check for existing CSV files (unlimited)
            bool foundFile = true;
            int checkId = 1;
            while (foundFile) {
                string filename = "Schedule" + to_string(checkId) + ".csv";
                ifstream testFile(filename);
                if (testFile.is_open()) {
                    testFile.close();
                    if (checkId > maxId) {
                        maxId = checkId;
                    }
                    checkId++;
                }
                else {
                    foundFile = false;
                }
            }

            // The new schedule ID will be maxId + 1
            int newScheduleId = maxId + 1;

            // Create the new schedule
            Schedule* newSchedule = new Schedule(newScheduleId);
            schedules.push_back(newSchedule);

            cout << " SUCCESS: New empty schedule created with ID " << newScheduleId << "\n";
            cout << "You can now add lessons to this schedule using option 8.\n";

            // Save the updated schedules list
            saveSchedules(schedules);
            cout << "Schedule list updated and saved.\n";
        }
        else if (choice == 7) { // RmSchedule <schedule_id>
            int scheduleId;
            cout << "Enter Schedule ID to remove: ";
            cin >> scheduleId;
            if (cin.fail()) {
                cout << "Invalid Schedule ID.\n";
                clearCin();
            }
            else {
                clearCin();

                // Remove from memory
                bool removedFromMemory = false;
                for (vector<Schedule*>::iterator it = schedules.begin(); it != schedules.end(); ++it) {
                    if ((*it)->getId() == scheduleId) {
                        delete* it;
                        schedules.erase(it);
                        removedFromMemory = true;
                        break;
                    }
                }

                // Remove CSV file
                string filename = "Schedule" + to_string(scheduleId) + ".csv";
                bool csvRemoved = false;
                ifstream testFile(filename);
                if (testFile.is_open()) {
                    testFile.close();
                    if (remove(filename.c_str()) == 0) {
                        csvRemoved = true;
                    }
                }

                if (!removedFromMemory && !csvRemoved) {
                    cout << "Schedule ID " << scheduleId << " not found.\n";
                }
                else {
                    cout << "Schedule " << scheduleId << " removed successfully.\n";

                    // COMPACT SCHEDULE IDs - מצמצום מספרים מזהים
                    cout << "Compacting schedule IDs to remove gaps...\n";

                    // Get all existing schedule IDs
                    vector<int> existingIds;
                    for (Schedule* s : schedules) {
                        existingIds.push_back(s->getId());
                    }

                    // Also check for CSV files
                    for (int i = 1; i <= 100; i++) { // Check reasonable range
                        string checkFilename = "Schedule" + to_string(i) + ".csv";
                        ifstream checkFile(checkFilename);
                        if (checkFile.is_open()) {
                            checkFile.close();
                            bool alreadyInVector = false;
                            for (int id : existingIds) {
                                if (id == i) {
                                    alreadyInVector = true;
                                    break;
                                }
                            }
                            if (!alreadyInVector) {
                                existingIds.push_back(i);
                            }
                        }
                    }

                    // Sort existing IDs
                    sort(existingIds.begin(), existingIds.end());

                    // Rename files to compact sequence (1, 2, 3, ...)
                    vector<pair<string, string>> renameOperations;

                    for (size_t i = 0; i < existingIds.size(); i++) {
                        int currentId = existingIds[i];
                        //int newId = i + 1;
                        int newId = static_cast<int>(i) + 1;

                        if (currentId != newId) {
                            string oldFilename = "Schedule" + to_string(currentId) + ".csv";
                            string newFilename = "Schedule" + to_string(newId) + ".csv";
                            renameOperations.push_back(make_pair(oldFilename, newFilename));

                            // Update schedule ID in memory
                            for (Schedule* s : schedules) {
                                if (s->getId() == currentId) {
                                    // Deep copy the lessons before deleting the schedule
                                    vector<Lesson*> lessonsBackup;
                                    const vector<Lesson*>& originalLessons = s->getLessons();

                                    for (Lesson* originalLesson : originalLessons) {
                                        if (originalLesson) {
                                            // Create a new copy of the lesson based on its type
                                            Lesson* lessonCopy = nullptr;
                                            if (dynamic_cast<Lecture*>(originalLesson)) {
                                                lessonCopy = new Lecture(
                                                    originalLesson->getType(),
                                                    originalLesson->getCourseId(),
                                                    originalLesson->getDay(),
                                                    originalLesson->getStartHour(),
                                                    originalLesson->getEndHour(),
                                                    originalLesson->getClassroom(),
                                                    originalLesson->getTeacherName(),
                                                    originalLesson->getGroupNumber()
                                                );
                                            }
                                            else if (dynamic_cast<Tutorial*>(originalLesson)) {
                                                lessonCopy = new Tutorial(
                                                    originalLesson->getType(),
                                                    originalLesson->getCourseId(),
                                                    originalLesson->getDay(),
                                                    originalLesson->getStartHour(),
                                                    originalLesson->getEndHour(),
                                                    originalLesson->getClassroom(),
                                                    originalLesson->getTeacherName(),
                                                    originalLesson->getGroupNumber()
                                                );
                                            }
                                            else if (dynamic_cast<Lab*>(originalLesson)) {
                                                lessonCopy = new Lab(
                                                    originalLesson->getType(),
                                                    originalLesson->getCourseId(),
                                                    originalLesson->getDay(),
                                                    originalLesson->getStartHour(),
                                                    originalLesson->getEndHour(),
                                                    originalLesson->getClassroom(),
                                                    originalLesson->getTeacherName(),
                                                    originalLesson->getGroupNumber()
                                                );
                                            }

                                            if (lessonCopy) {
                                                lessonsBackup.push_back(lessonCopy);
                                            }
                                        }
                                    }

                                    schedules.erase(find(schedules.begin(), schedules.end(), s));
                                    delete s;  // Now safe to delete

                                    Schedule* newSchedule = new Schedule(newId);
                                    for (Lesson* lesson : lessonsBackup) {
                                        newSchedule->addLesson(lesson);
                                    }
                                    schedules.push_back(newSchedule);
                                    break;
                                }
                            }

                        }
                    }

                    // Perform file renames
                    for (const pair<string, string>& op : renameOperations) {
                        if (rename(op.first.c_str(), op.second.c_str()) == 0) {
                            cout << "Renamed " << op.first << " to " << op.second << "\n";
                        }
                    }

                    // Update schedules.csv with new compact IDs
                    saveSchedules(schedules);
                    cout << "Schedule IDs have been compacted. No gaps in numbering.\n";
                }
            }
        }


        else if (choice == 8) { // Add <sched> <course> <group>
            int scheduleId, courseId;
            cout << "Enter Schedule ID: ";
            cin >> scheduleId;
            if (cin.fail()) {
                cout << "Invalid Schedule ID.\n";
                clearCin();
            }
            else {
                clearCin();

                cout << "Enter Course ID: ";
                cin >> courseId;
                if (cin.fail()) {
                    cout << "Invalid Course ID.\n";
                    clearCin();
                }
                else {
                    clearCin();

                    // Find the schedule
                    Schedule* target = nullptr;
                    for (Schedule* s : schedules) {
                        if (s->getId() == scheduleId) {
                            target = s;
                            break;
                        }
                    }
                    if (!target) {
                        cout << "Schedule not found.\n";
                    }
                    else {
                        // Check if course exists
                        bool courseExists = false;
                        for (const Course& c : courses) {
                            if (c.getId() == courseId) {
                                courseExists = true;
                                break;
                            }
                        }
                        if (!courseExists) {
                            cout << "Course " << courseId << " not found.\n";
                        }
                        else {
                            // Get lesson type
                            cout << "Choose lesson type to add:\n";
                            cout << "1 - Lecture\n";
                            cout << "2 - Tutorial\n";
                            cout << "3 - Lab\n";
                            cout << "Enter choice: ";
                            int lessonChoice;
                            cin >> lessonChoice;
                            if (cin.fail()) {
                                cout << "Invalid choice.\n";
                                clearCin();
                            }
                            else {
                                clearCin();

                                // Use the new function to add lesson from CSV
                                if (addLessonFromCSV(courseId, lessonChoice, courses, target)) {
                                    cout << "Lesson added to schedule " << scheduleId << ".\n";

                                    // ADD THE IMPORTANT MESSAGE HERE
                                    cout << "\n*** IMPORTANT REMINDER ***\n";
                                    cout << "For a complete course experience, you should add ALL lesson types\n";
                                    cout << "(Lecture, Tutorial, AND Lab) for Course " << courseId << " to Schedule " << scheduleId << ".\n";
                                    cout << "\nRecommendation: Continue adding the remaining lesson types for Course " << courseId << ":\n";

                                    // Check what lesson types are already in this schedule for this course
                                    const vector<Lesson*>& currentLessons = target->getLessons();
                                    bool hasLecture = false, hasTutorial = false, hasLab = false;

                                    for (Lesson* lesson : currentLessons) {
                                        if (lesson->getCourseId() == courseId) {
                                            string lessonType = lesson->getType();
                                            if (lessonType == "Lecture") hasLecture = true;
                                            else if (lessonType == "Tutorial") hasTutorial = true;
                                            else if (lessonType == "Lab") hasLab = true;
                                        }
                                    }


                                    if (hasLecture && hasTutorial && hasLab) {
                                        cout << "\n COMPLETE! Course " << courseId << " now has all lesson types in Schedule " << scheduleId << ".\n";
                                    }
                                    else {
                                        cout << "\n  To complete Course " << courseId << ", please add the missing lesson types using option 8 again.\n";
                                    }
                                    cout << "************************\n\n";

                                    saveSchedules(schedules);
                                    cout << "Schedule saved to CSV file.\n";
                                }
                                else {
                                    cout << "Failed to add lesson.\n";
                                }
                            }
                        }
                    }
                }
            }
        }   

         
        else if (choice == 9) { // Rm <sched> <course> <group> <type>
            int scheduleId, courseId, groupNumber;
            cout << "Enter Schedule ID: ";
            cin >> scheduleId;
            if (cin.fail()) {
                cout << "Invalid Schedule ID.\n";
                clearCin();
            }
            else {
                clearCin();

                cout << "Enter Course ID: ";
                cin >> courseId;
                if (cin.fail()) {
                    cout << "Invalid Course ID.\n";
                    clearCin();
                }
                else {
                    clearCin();

                    cout << "Enter Group Number: ";
                    cin >> groupNumber;
                    if (cin.fail()) {
                        cout << "Invalid Group Number.\n";
                        clearCin();
                    }
                    else {
                        clearCin();

                        // Ask for lesson type
                        cout << "Choose lesson type to remove:\n";
                        cout << "1 - Lecture\n";
                        cout << "2 - Tutorial\n";
                        cout << "3 - Lab\n";
                        cout << "Enter choice: ";
                        int lessonTypeChoice;
                        cin >> lessonTypeChoice;
                        if (cin.fail() || lessonTypeChoice < 1 || lessonTypeChoice > 3) {
                            cout << "Invalid lesson type choice.\n";
                            clearCin();
                        }
                        else {
                            clearCin();

                            // Convert choice to lesson type string
                            string targetLessonType;
                            if (lessonTypeChoice == 1) targetLessonType = "Lecture";
                            else if (lessonTypeChoice == 2) targetLessonType = "Tutorial";
                            else if (lessonTypeChoice == 3) targetLessonType = "Lab";

                            Schedule* target = nullptr;
                            for (Schedule* s : schedules) {
                                if (s->getId() == scheduleId) {
                                    target = s;
                                    break;
                                }
                            }
                            if (!target) {
                                cout << "Schedule not found.\n";
                            }
                            else {
                                vector<Lesson*>& lessons = target->getLessons();
                                size_t beforeSize = lessons.size();

                                // Debug: Print what lessons we have for this course
                                cout << "\n=== DEBUG: Lessons for Course " << courseId << " ===\n";
                                for (size_t i = 0; i < lessons.size(); i++) {
                                    Lesson* l = lessons[i];
                                    if (l->getCourseId() == courseId) {
                                        cout << "Lesson " << i << ": Course " << l->getCourseId() 
                                             << ", Type " << l->getType() 
                                             << ", Group " << l->getGroupNumber() 
                                             << ", Day " << l->getDay() << endl;
                                    }
                                }
                                cout << "==============================\n";

                                // Remove lessons that match course ID, group number, AND lesson type
                                // Simple loop to remove lessons instead of using lambda
                                vector<Lesson*>::iterator it = lessons.begin();
                                while (it != lessons.end()) {
                                    Lesson* l = *it;
                                    bool shouldRemove = (l->getCourseId() == courseId) && 
                                                       (l->getGroupNumber() == groupNumber) &&
                                                       (l->getType() == targetLessonType);
                                    
                                    if (shouldRemove) {
                                        cout << "REMOVING: Course " << l->getCourseId() 
                                             << ", Type " << l->getType() 
                                             << ", Group " << l->getGroupNumber() << endl;
                                        delete l;
                                        it = lessons.erase(it);
                                    }
                                    else {
                                        it++;
                                    }
                                }

                                size_t afterSize = lessons.size();
                                size_t removed = beforeSize - afterSize;

                                if (removed == 0) {
                                    cout << "No matching " << targetLessonType << " lessons found for Course " 
                                         << courseId << ", Group " << groupNumber << ".\n";
                                }
                                else {
                                    cout << removed << " " << targetLessonType << " lesson(s) removed from schedule " 
                                         << scheduleId << ".\n";
                                    saveSchedules(schedules);
                                    cout << "Schedule " << scheduleId << " updated and saved to CSV file.\n";
                                }
                            }
                        }
                    }
                }
            }
        }
        else if (choice == 10) { // Clear
            cout << "Clear screen feature disabled.\n";

        }
        else if (choice == 11) { // Help
            showHelp();
        }
        else if (choice == 12) { // Exit
            cout << "Saving data...\n";
            saveCourses(courses);
            saveSchedules(schedules);
            //saveAllLessons(allLessons);
            cout << "Data saved successfully. Goodbye!\n";
            running = false;
        }
        else if (choice == 13) { // Find Time Conflicts
            findTimeConflicts(schedules, courses);
        }
        else if (choice == 14) { // Course Workload Analysis
            analyzeCourseWorkload(schedules, courses);
        }
        else if (choice == 15) { // Teacher Schedule Analysis
            analyzeTeacherSchedules(schedules, courses);
        }
        else if (choice == 16) { // Add testing option
            runAllTests();
          }
        else {
            cout << "Invalid option. Please try again.\n";
        }
    }

    // Clean up
    for (Schedule* s : schedules) {
        delete s;
    }

    return 0;
}