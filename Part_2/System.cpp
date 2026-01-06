#include "System.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <set>
#include <map>
#include <cctype>
#include <cstdio>  // Added for std::remove

#ifdef _WIN32
#include <windows.h>
#endif

// Constructor: Initializes the system by loading data from files.
System::System() : lastPrintedCourseIndex(0) {
    setConsoleSize();
    clearScreen();
    std::cout << std::string(50, '=') << std::endl;
    std::cout << " INITIALIZING COURSE MANAGEMENT SYSTEM " << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    loadCourses();
    loadLessons();
    loadSchedules();
    std::cout << std::string(50, '=') << std::endl;
    std::cout << " INITIALIZATION COMPLETE " << std::endl;
    std::cout << std::string(50, '=') << std::endl;
}

// Destructor: Saves all data to files before shutting down.
System::~System() {
    std::cout << "\nSaving all data before exit..." << std::endl;
    
    // Save main data files
    saveSchedules();
    saveCourses();
    saveLessons();
    
    // Save all individual schedule files with current IDs
    for (const auto& schedule : schedules) {
        saveIndividualSchedule(schedule);
    }
    
    std::cout << "All data saved successfully." << std::endl;
    
    // Clean up dynamically allocated lessons
    for (auto lesson : lessons) {
        delete lesson;
    }
    lessons.clear();
}

void System::waitForUser() {
    std::cout << "\nPress Enter to continue...";
    std::cin.ignore();
    std::cin.get();
}

void System::clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void System::setConsoleSize() {
#ifdef _WIN32
    // Try to make console bigger
    HWND console = GetConsoleWindow();
    if (console != NULL) {
        RECT rect;
        GetWindowRect(console, &rect);
        MoveWindow(console, rect.left, rect.top, 1000, 700, TRUE);
    }
    
    // Set buffer size
    HANDLE hConsole = GetStdHandle(STD_OUTPUT_HANDLE);
    COORD bufferSize = {120, 1000};
    SetConsoleScreenBufferSize(hConsole, bufferSize);
#endif
}

// Loads course data from "courses.csv".
void System::loadCourses() {
    std::ifstream file("courses.csv");
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open courses.csv. No courses loaded." << std::endl;
        waitForUser();
        return;
    }
    
    // Skip the header line
    if (getline(file, line)) {
        // Header line skipped: course_id,course_name,credits,exam_date_a,exam_date_b,responsible_lecturer,semester
    }
    
    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }
        
        std::stringstream ss(line);
        std::string id_str, name, credits_str, moedA, moedB, lecturer;
        getline(ss, id_str, ',');
        getline(ss, name, ',');
        getline(ss, credits_str, ',');
        getline(ss, moedA, ',');
        getline(ss, moedB, ',');
        getline(ss, lecturer, ',');
        
        // Validate required fields before parsing
        if (id_str.empty() || credits_str.empty()) {
            std::cerr << "Warning: Skipping invalid course line: " << line << std::endl;
            continue;
        }
        
        try {
            courses.emplace_back(std::stoi(id_str), name, std::stoi(credits_str), moedA, moedB, lecturer);
        } catch (const std::exception& e) {
            std::cerr << "Warning: Failed to parse course line: " << line << " - Error: " << e.what() << std::endl;
        }
    }
    file.close();
    std::cout << "SUCCESS: Loaded " << courses.size() << " courses." << std::endl;
}

// Loads lesson data from "lessons.csv".
void System::loadLessons() {
    std::ifstream file("lessons.csv");
    std::string line;
    if (!file.is_open()) {
        std::cerr << "Warning: Could not open lessons.csv. No lessons loaded." << std::endl;
        waitForUser();
        return;
    }
    
    // Skip the header line
    if (getline(file, line)) {
        // Header line skipped: type,course_id,day,start_time,end_time,room,lecturer,group
    }
    
    while (getline(file, line)) {
        // Skip empty lines
        if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
            continue;
        }
        
        std::stringstream ss(line);
        std::string type, courseId_str, day, start_time, end_time, room, teacher, groupId_str;
        
        // Parse CSV: type,course_id,day,start_time,end_time,room,lecturer,group
        getline(ss, type, ',');
        getline(ss, courseId_str, ',');
        getline(ss, day, ',');
        getline(ss, start_time, ',');
        getline(ss, end_time, ',');
        getline(ss, room, ',');
        getline(ss, teacher, ',');
        getline(ss, groupId_str);

        // Validate required fields before parsing
        if (courseId_str.empty() || groupId_str.empty() || start_time.empty() || end_time.empty()) {
            std::cerr << "Warning: Skipping invalid lesson line: " << line << std::endl;
            continue;
        }
        
        try {
            int courseId = std::stoi(courseId_str);
            int groupId = std::stoi(groupId_str);
            
            // Validate time format and extract hour
            if (start_time.find(':') == std::string::npos || end_time.find(':') == std::string::npos) {
                std::cerr << "Warning: Invalid time format in line: " << line << std::endl;
                continue;
            }
            
            // Convert time format "10:00" to hour integer
            int start = std::stoi(start_time.substr(0, start_time.find(':')));
            int end = std::stoi(end_time.substr(0, end_time.find(':')));
            int duration = end - start;
            int endHour = start + duration;

            if (type == "Lecture") {
                lessons.push_back(new Lecture(type, courseId, day, start, endHour, room, teacher, groupId));
            } else if (type == "Tutorial") {
                lessons.push_back(new Tutorial(type, courseId, day, start, endHour, room, teacher, groupId));
            } else if (type == "Lab") {
                lessons.push_back(new Lab(type, courseId, day, start, endHour, room, teacher, groupId));
            } else {
                std::cerr << "Warning: Unknown lesson type '" << type << "' in line: " << line << std::endl;
            }
        } catch (const std::exception& e) {
            std::cerr << "Warning: Failed to parse lesson line: " << line << " - Error: " << e.what() << std::endl;
        }
    }
    file.close();
    std::cout << "SUCCESS: Loaded " << lessons.size() << " lessons." << std::endl;
}

// Loads schedule data from "schedules.csv".
void System::loadSchedules() {
    // First, try to load from main schedules.csv for backward compatibility
    std::ifstream mainFile("schedules.csv");
    if (mainFile.is_open()) {
        std::string line;
        // Skip header if present
        if (getline(mainFile, line)) {
            // Check if this looks like a header (contains "schedule" or "course")
            if (line.find("schedule") == std::string::npos && line.find(";") != std::string::npos) {
                // This is old format data, not a header - process it
                std::stringstream ss(line);
                std::string scheduleId_str;
                getline(ss, scheduleId_str, ';');
                
                if (!scheduleId_str.empty()) {
                    try {
                        Schedule newSchedule(std::stoi(scheduleId_str));
                        
                        std::string lesson_data;
                        while(getline(ss, lesson_data, ';') && !lesson_data.empty()){
                            std::stringstream lesson_ss(lesson_data);
                            std::string courseId_str, groupId_str;
                            getline(lesson_ss, courseId_str, ',');
                            getline(lesson_ss, groupId_str, ',');
                            
                            if (!courseId_str.empty() && !groupId_str.empty()) {
                                try {
                                    Lesson* lesson = findLesson(std::stoi(courseId_str), std::stoi(groupId_str));
                                    if(lesson){
                                        newSchedule.addLesson(lesson->clone());
                                    }
                                } catch (...) {
                                    // Skip invalid lesson data
                                }
                            }
                        }
                        schedules.push_back(newSchedule);
                    } catch (...) {
                        // Skip invalid schedule
                    }
                }
            }
        }
        
        // Process remaining lines
        while (getline(mainFile, line)) {
            if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
                continue;
            }
            
            std::stringstream ss(line);
            std::string scheduleId_str;
            getline(ss, scheduleId_str, ';');
            
            if (!scheduleId_str.empty()) {
                try {
                    Schedule newSchedule(std::stoi(scheduleId_str));
                    
                    std::string lesson_data;
                    while(getline(ss, lesson_data, ';') && !lesson_data.empty()){
                        std::stringstream lesson_ss(lesson_data);
                        std::string courseId_str, groupId_str;
                        getline(lesson_ss, courseId_str, ',');
                        getline(lesson_ss, groupId_str, ',');
                        
                        if (!courseId_str.empty() && !groupId_str.empty()) {
                            try {
                                Lesson* lesson = findLesson(std::stoi(courseId_str), std::stoi(groupId_str));
                                if(lesson){
                                    newSchedule.addLesson(lesson->clone());
                                }
                            } catch (...) {
                                // Skip invalid lesson data
                            }
                        }
                    }
                    schedules.push_back(newSchedule);
                } catch (...) {
                    // Skip invalid schedule
                }
            }
        }
        mainFile.close();
    }
    
    // Now try to load from individual schedule files (Schedule1.csv, Schedule2.csv, etc.)
    // This will override/supplement the main schedules.csv data
    for (int scheduleId = 1; scheduleId <= 10; ++scheduleId) {  // Check up to 10 schedules
        std::string filename = "Schedule" + std::to_string(scheduleId) + ".csv";
        std::ifstream scheduleFile(filename);
        
        if (scheduleFile.is_open()) {
            std::string line;
            
            // Skip the header line
            if (getline(scheduleFile, line)) {
                // Header line skipped: course_id,day,start_time,end_time,room,type
            }
            
            // Find if this schedule already exists or create new one
            Schedule* targetSchedule = nullptr;
            for (auto& existingSchedule : schedules) {
                if (existingSchedule.getId() == scheduleId) {
                    targetSchedule = &existingSchedule;
                    break;
                }
            }
            
            // If schedule doesn't exist, create it
            if (!targetSchedule) {
                schedules.emplace_back(scheduleId);
                targetSchedule = &schedules.back();
            } else {
                // Clear existing lessons to reload from file
                targetSchedule->clearLessons();
            }
            
            // Load lessons from the individual schedule file
            int lessonsLoaded = 0;
            while (getline(scheduleFile, line)) {
                if (line.empty() || line.find_first_not_of(" \t\r\n") == std::string::npos) {
                    continue;
                }
                
                std::stringstream ss(line);
                std::string courseId_str, day, start_time, end_time, room, type;
                
                // Parse CSV: course_id,day,start_time,end_time,room,type
                getline(ss, courseId_str, ',');
                getline(ss, day, ',');
                getline(ss, start_time, ',');
                getline(ss, end_time, ',');
                getline(ss, room, ',');
                getline(ss, type);
                
                // Validate required fields
                if (courseId_str.empty() || day.empty() || start_time.empty() || end_time.empty()) {
                    std::cerr << "Warning: Skipping invalid lesson line in " << filename << ": " << line << std::endl;
                    continue;
                }
                
                try {
                    int courseId = std::stoi(courseId_str);
                    
                    // Extract hour from time format "HH:MM"
                    int startHour = std::stoi(start_time.substr(0, start_time.find(':')));
                    int endHour = std::stoi(end_time.substr(0, end_time.find(':')));
                    
                    // Instead of creating new lessons with default group ID,
                    // find matching lessons from the main lessons database
                    Lesson* matchingLesson = nullptr;
                    for (const auto& lesson : lessons) {
                        if (lesson->getCourseId() == courseId &&
                            lesson->getDay() == day &&
                            lesson->getStartHour() == startHour &&
                            lesson->getStartHour() + lesson->getDuration() == endHour &&
                            lesson->getRoom() == room &&
                            lesson->getType() == type) {
                            matchingLesson = lesson;
                            break;
                        }
                    }
                    
                    if (matchingLesson) {
                        // Use the actual lesson from the database (with correct group ID)
                        targetSchedule->addLessonForce(matchingLesson->clone());
                        lessonsLoaded++;
                    } else {
                        // Fallback: create lesson with default values if no match found
                        std::unique_ptr<Lesson> newLesson;
                        std::string teacherName = "TBD";  // Default teacher name
                        int groupId = 1;  // Default group ID (only as fallback)
                        
                        // Constructor signature: (type, courseId, day, startHour, endHour, classroom, teacherName, groupNumber)
                        if (type == "Lecture") {
                            newLesson = std::make_unique<Lecture>(type, courseId, day, startHour, endHour, room, teacherName, groupId);
                        } else if (type == "Tutorial") {
                            newLesson = std::make_unique<Tutorial>(type, courseId, day, startHour, endHour, room, teacherName, groupId);
                        } else if (type == "Lab") {
                            newLesson = std::make_unique<Lab>(type, courseId, day, startHour, endHour, room, teacherName, groupId);
                        }
                        
                        if (newLesson) {
                            targetSchedule->addLessonForce(std::move(newLesson));
                            lessonsLoaded++;
                        }
                    }
                    
                } catch (const std::exception& e) {
                    std::cerr << "Warning: Failed to parse lesson line in " << filename << ": " << line 
                              << " - Error: " << e.what() << std::endl;
                }
            }
            
            scheduleFile.close();
            std::cout << "SUCCESS: Loaded schedule " << scheduleId << " from " << filename 
                      << " with " << lessonsLoaded << " lessons." << std::endl;
        }
    }
    
    if (!schedules.empty()) {
        std::cout << "SUCCESS: Total " << schedules.size() << " schedules loaded." << std::endl;
    } else {
        std::cout << "INFO: No schedule files found." << std::endl;
    }
}

// Saves all current schedules to "schedules.csv".
void System::saveSchedules() {
    std::ofstream file("schedules.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open schedules.csv for saving." << std::endl;
        return;
    }
    for (const auto& schedule : schedules) {
        file << schedule.getId();
        for (const auto& lesson : schedule.getLessons()) {
            file << ";" << lesson->getCourseId() << "," << lesson->getGroupId();
        }
        file << std::endl;
    }
    file.close();
}

// Saves all current courses to "courses.csv".
void System::saveCourses() {
    std::ofstream file("courses.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open courses.csv for saving." << std::endl;
        return;
    }
    for (const auto& course : courses) {
        file << course.getId() << ","
             << course.getName() << ","
             << course.getCredits() << ","
             << course.getMoedA() << ","
             << course.getMoedB() << ","
             << course.getLecturer() << std::endl;
    }
    file.close();
}

// Saves all current lessons to "lessons.csv".
void System::saveLessons() {
    std::ofstream file("lessons.csv");
    if (!file.is_open()) {
        std::cerr << "Error: Could not open lessons.csv for saving." << std::endl;
        return;
    }
    
    // Write header line
    file << "type,course_id,day,start_time,end_time,room,lecturer,group" << std::endl;
    
    for (const auto& lesson : lessons) {
        int startHour = lesson->getStartHour();
        int endHour = startHour + lesson->getDuration();
        
        // Format times as "HH:MM"
        std::string startTime = (startHour < 10 ? "0" : "") + std::to_string(startHour) + ":00";
        std::string endTime = (endHour < 10 ? "0" : "") + std::to_string(endHour) + ":00";
        
        file << lesson->getType() << ","
             << lesson->getCourseId() << ","
             << lesson->getDay() << ","
             << startTime << ","
             << endTime << ","
             << lesson->getRoom() << ","
             << lesson->getTeacherName() << ","
             << lesson->getGroupId() << std::endl;
    }
    file.close();
}

// NEW: Method to save individual schedule file
void System::saveIndividualSchedule(const Schedule& schedule) const {
    std::string filename = "Schedule" + std::to_string(schedule.getId()) + ".csv";
    std::ofstream file(filename);
    
    if (!file.is_open()) {
        std::cerr << "Error: Could not open " << filename << " for saving." << std::endl;
        return;
    }
    
    // Write header
    file << "course_id,day,start_time,end_time,room,type" << std::endl;
    
    // Write lessons
    for (const auto& lesson : schedule.getLessons()) {
        int startHour = lesson->getStartHour();
        int endHour = startHour + lesson->getDuration();
        
        // Format times as "HH:MM"
        std::string startTime = (startHour < 10 ? "0" : "") + std::to_string(startHour) + ":00";
        std::string endTime = (endHour < 10 ? "0" : "") + std::to_string(endHour) + ":00";
        
        file << lesson->getCourseId() << ","
             << lesson->getDay() << ","
             << startTime << ","
             << endTime << ","
             << lesson->getRoom() << ","
             << lesson->getType() << std::endl;
    }
    
    file.close();
}

// Main application loop
void System::run() {
    printWelcomeMessage();
    std::string command_line;
    while (true) {
        std::cout << "\nCMS> ";
        getline(std::cin, command_line);
        
        if (command_line == "Exit" || command_line == "exit") {
            std::cout << "Saving schedules and exiting. Goodbye!" << std::endl;
            break;
        }

        std::stringstream ss(command_line);
        std::string command;
        ss >> command;

        if (command == "PrintCourse") {
            std::string courseId; ss >> courseId;
            handlePrintCourse(courseId);
        } else if (command == "PrintCourses") {
            handlePrintCourses();
        } else if (command == "More") {
            handleMore();
        } else if (command == "PrintSchedule") {
            std::string scheduleId; ss >> scheduleId;
            handlePrintSchedule(scheduleId);
        } else if (command == "PrintSchedules") {
            handlePrintSchedules();
        } else if (command == "AddSchedule") {
            handleAddSchedule();
        } else if (command == "RmSchedule") {
            std::string scheduleId; ss >> scheduleId;
            handleRemoveSchedule(scheduleId);
        } else if (command == "Add") {
            std::string scheduleId, courseId, groupId;
            ss >> scheduleId >> courseId >> groupId;
            handleAddLessonToSchedule(scheduleId, courseId, groupId);
        } else if (command == "Rm") {
            std::string scheduleId, courseId, groupId;
            ss >> scheduleId >> courseId >> groupId;
            handleRemoveLessonFromSchedule(scheduleId, courseId, groupId);
        } else if (command == "CheckConflicts") {
            std::string scheduleId; ss >> scheduleId;
            handleCheckConflicts(scheduleId);
        } else if (command == "FindTimeConflicts") {
            handleFindTimeConflicts();
        } else if (command == "AnalyzeWorkload") {
            std::string scheduleId; ss >> scheduleId;
            handleAnalyzeCourseWorkload(scheduleId);
        } else if (command == "AnalyzeTeacher") {
            std::string teacherName;
            getline(ss, teacherName);
            // Remove leading whitespace
            if (!teacherName.empty() && teacherName[0] == ' ') {
                teacherName = teacherName.substr(1);
            }
            handleAnalyzeTeacherSchedules(teacherName);
        } else if (command == "AddCourse") {
            handleAddCourse();
        } else if (command == "RmCourse") {
            std::string courseId; ss >> courseId;
            handleRemoveCourse(courseId);
        } else if (command == "AddLesson") {
            handleAddLesson();
        } else if (command == "RmLesson") {
            std::string courseId, groupId;
            ss >> courseId >> groupId;
            handleRemoveLesson(courseId, groupId);
        } else if (command == "Clear" || command == "clear") {
            handleClear();
        } else if (command == "Help" || command == "help") {
            handleHelp();
        } else if (command.empty()) {
            // Do nothing for empty input
        } else {
            std::cout << "ERROR: Unknown command '" << command << "'. Type 'Help' for available commands." << std::endl;
        }
    }
}

// Finds a lesson from the main lesson list.
Lesson* System::findLesson(int courseId, int groupId) {
    for (const auto& lesson : lessons) {
        if (lesson->getCourseId() == courseId && lesson->getGroupId() == groupId) {
            return lesson;
        }
    }
    return nullptr;
}

// New method to find all lessons for a course/group combination
std::vector<Lesson*> System::findLessonsForCourseAndGroup(int courseId, int groupId) {
    std::vector<Lesson*> foundLessons;
    for (const auto& lesson : lessons) {
        if (lesson->getCourseId() == courseId && lesson->getGroupId() == groupId) {
            foundLessons.push_back(lesson);
        }
    }
    return foundLessons;
}

// --- Command Handlers ---

void System::handlePrintCourse(const std::string& courseId_str) {
    try {
        int courseId = std::stoi(courseId_str);
        Course* course = nullptr;
        for(auto& c : courses){
            if(c.getId() == courseId){
                course = &c;
                break;
            }
        }

        if (course) {
            // Header section
            std::cout << "\n" << std::string(80, '=') << std::endl;
            std::cout << "                            COURSE DETAILS" << std::endl;
            std::cout << std::string(80, '=') << std::endl;
            
            // Course information in organized format
            std::cout << "Course ID: " << std::setw(20) << std::left << course->getId() 
                      << "Name: " << course->getName() << std::endl;
            std::cout << "Credits: " << std::setw(22) << std::left << course->getCredits() 
                      << "Lecturer: " << course->getLecturer() << std::endl;
            std::cout << "Moed A: " << std::setw(23) << std::left << course->getMoedA() 
                      << "Moed B: " << course->getMoedB() << std::endl;
            
            std::cout << "\n" << std::string(80, '-') << std::endl;
            std::cout << "                        LESSONS FOR THIS COURSE" << std::endl;
            std::cout << std::string(80, '-') << std::endl;

            // Collect lessons by type
            std::vector<Lesson*> lectures, tutorials, labs;
            for (const auto& lesson : lessons) {
                if (lesson->getCourseId() == courseId) {
                    if (lesson->getType() == "Lecture") {
                        lectures.push_back(lesson);
                    } else if (lesson->getType() == "Tutorial") {
                        tutorials.push_back(lesson);
                    } else if (lesson->getType() == "Lab") {
                        labs.push_back(lesson);
                    }
                }
            }

            // Display lessons organized by type
            if (!lectures.empty()) {
                std::cout << "\n--- LECTURES (" << lectures.size() << " session" << (lectures.size() > 1 ? "s" : "") << "):" << std::endl;
                std::cout << std::string(80, '-') << std::endl;
                for (size_t i = 0; i < lectures.size(); ++i) {
                    auto lesson = lectures[i];
                    std::cout << "  " << (i + 1) << ". Group " << std::setw(3) << lesson->getGroupId() 
                              << " - " << std::setw(9) << lesson->getDay() 
                              << " - " << std::setw(5) << (lesson->getStartHour() < 10 ? "0" : "") << lesson->getStartHour() << ":00"
                              << " - " << lesson->getDuration() << "h"
                              << " - " << std::setw(20) << lesson->getTeacherName()
                              << " - " << lesson->getBuilding() << " " << lesson->getRoom() << std::endl;
                    
                    if (i < lectures.size() - 1) {
                        std::cout << std::string(80, '-') << std::endl;
                    }
                }
                std::cout << std::endl;
            }

            if (!tutorials.empty()) {
                std::cout << "\n--- TUTORIALS (" << tutorials.size() << " session" << (tutorials.size() > 1 ? "s" : "") << "):" << std::endl;
                std::cout << std::string(80, '-') << std::endl;
                for (size_t i = 0; i < tutorials.size(); ++i) {
                    auto lesson = tutorials[i];
                    std::cout << "  " << (i + 1) << ". Group " << std::setw(3) << lesson->getGroupId() 
                              << " - " << std::setw(9) << lesson->getDay() 
                              << " - " << std::setw(5) << (lesson->getStartHour() < 10 ? "0" : "") << lesson->getStartHour() << ":00"
                              << " - " << lesson->getDuration() << "h"
                              << " - " << std::setw(20) << lesson->getTeacherName()
                              << " - " << lesson->getBuilding() << " " << lesson->getRoom() << std::endl;
                    
                    if (i < tutorials.size() - 1) {
                        std::cout << std::string(80, '-') << std::endl;
                    }
                }
                std::cout << std::endl;
            }

            if (!labs.empty()) {
                std::cout << "\n--- LABS (" << labs.size() << " session" << (labs.size() > 1 ? "s" : "") << "):" << std::endl;
                std::cout << std::string(80, '-') << std::endl;
                for (size_t i = 0; i < labs.size(); ++i) {
                    auto lesson = labs[i];
                    std::cout << "  " << (i + 1) << ". Group " << std::setw(3) << lesson->getGroupId() 
                              << " - " << std::setw(9) << lesson->getDay() 
                              << " - " << std::setw(5) << (lesson->getStartHour() < 10 ? "0" : "") << lesson->getStartHour() << ":00"
                              << " - " << lesson->getDuration() << "h"
                              << " - " << std::setw(20) << lesson->getTeacherName()
                              << " - " << lesson->getBuilding() << " " << lesson->getRoom() << std::endl;
                    
                    if (i < labs.size() - 1) {
                        std::cout << std::string(80, '-') << std::endl;
                    }
                }
                std::cout << std::endl;
            }

            // Summary section
            int totalLessons = lectures.size() + tutorials.size() + labs.size();
            if (totalLessons == 0) {
                std::cout << "\n   ---  No lessons found for this course." << std::endl;
            } else {
                std::cout << "\n" << std::string(80, '-') << std::endl;
                std::cout << "--- SUMMARY: " << totalLessons << " total lesson" << (totalLessons > 1 ? "s" : "") 
                          << " (" << lectures.size() << " lecture" << (lectures.size() != 1 ? "s" : "")
                          << ", " << tutorials.size() << " tutorial" << (tutorials.size() != 1 ? "s" : "")
                          << ", " << labs.size() << " lab" << (labs.size() != 1 ? "s" : "") << ")" << std::endl;
            }
            
            std::cout << std::string(80, '=') << std::endl;
        } else {
            std::cout << "ERROR: Course with ID " << courseId << " not found." << std::endl;
        }
    } catch (...) {
        std::cout << "ERROR: Invalid course ID format." << std::endl;
    }
}

void System::handlePrintCourses() {
    lastPrintedCourseIndex = 0;
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "DISPLAYING FIRST 10 COURSES" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    // Fixed: Use size_t to avoid conversion warning
    size_t count = 0;
    for (size_t i = 0; i < courses.size() && i < 10; ++i) {
        std::cout << std::setw(2) << (i+1) << ". " << courses[i] << std::endl;
        count++;
    }
    lastPrintedCourseIndex = static_cast<int>(count);  // Safe cast since count is <= 10
    
    if (count == 0) {
        std::cout << "No courses to display." << std::endl;
    } else {
        std::cout << std::string(60, '-') << std::endl;
        std::cout << "Showing " << count << " of " << courses.size() << " total courses." << std::endl;
        if (count < courses.size()) {
            std::cout << "Type 'More' to see the next 10 courses." << std::endl;
        }
        std::cout << std::string(60, '=') << std::endl;
    }
}

void System::handleMore() {
    if (lastPrintedCourseIndex == 0) {
        std::cout << "ERROR: You must use 'PrintCourses' first." << std::endl;
        return;
    }
    if (static_cast<size_t>(lastPrintedCourseIndex) >= courses.size()) {
        std::cout << "INFO: No more courses to display." << std::endl;
        return;
    }

    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "DISPLAYING NEXT 10 COURSES" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    
    int count = 0;
    for (size_t i = static_cast<size_t>(lastPrintedCourseIndex); i < courses.size() && count < 10; ++i) {
        std::cout << std::setw(2) << (i+1) << ". " << courses[i] << std::endl;
        count++;
    }
    lastPrintedCourseIndex += count;
    std::cout << std::string(60, '-') << std::endl;
    std::cout << "Showing " << lastPrintedCourseIndex << " of " << courses.size() << " total courses." << std::endl;
    if (static_cast<size_t>(lastPrintedCourseIndex) < courses.size()) {
        std::cout << "Type 'More' to see the next 10 courses." << std::endl;
    }
    std::cout << std::string(60, '=') << std::endl;
}

void System::handlePrintSchedule(const std::string& scheduleId_str) {
    // Check if schedule ID is empty or whitespace only
    if (scheduleId_str.empty() || scheduleId_str.find_first_not_of(" \t\n\r") == std::string::npos) {
        std::cout << "ERROR: Missing schedule ID. Usage: PrintSchedule <schedule_id>" << std::endl;
        if (schedules.empty()) {
            std::cout << "INFO: No schedules available. Use 'AddSchedule' to create a new schedule." << std::endl;
        } else {
            std::cout << "INFO: Available schedule IDs: ";
            for (size_t i = 0; i < schedules.size(); ++i) {
                std::cout << schedules[i].getId();
                if (i < schedules.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
            std::cout << "      Or use 'PrintSchedules' to see all schedules." << std::endl;
        }
        return;
    }

    try {
        int scheduleId = std::stoi(scheduleId_str);
        Schedule* schedule = nullptr;
        for(auto& s : schedules){
            if(s.getId() == scheduleId){
                schedule = &s;
                break;
            }
        }

        if(schedule){
            std::cout << "\n" << std::string(50, '=') << std::endl;
            std::cout << "--- SCHEDULE " << schedule->getId() << " ---" << std::endl;
            std::cout << std::string(50, '=') << std::endl;
            schedule->printSchedule();
            
            // Print conflict analysis
            schedule->printConflicts();
            
            std::cout << std::string(50, '=') << std::endl;
        } else {
            std::cout << "ERROR: Schedule with ID " << scheduleId << " not found." << std::endl;
            if (!schedules.empty()) {
                std::cout << "INFO: Available schedule IDs: ";
                for (size_t i = 0; i < schedules.size(); ++i) {
                    std::cout << schedules[i].getId();
                    if (i < schedules.size() - 1) std::cout << ", ";
                }
                std::cout << std::endl;
            }
        }
    } catch (...) {
        std::cout << "ERROR: Invalid schedule ID format. Please enter a valid number." << std::endl;
        std::cout << "Usage: PrintSchedule <schedule_id>" << std::endl;
        if (!schedules.empty()) {
            std::cout << "INFO: Available schedule IDs: ";
            for (size_t i = 0; i < schedules.size(); ++i) {
                std::cout << schedules[i].getId();
                if (i < schedules.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
    }
}

void System::handlePrintSchedules() {
    if (schedules.empty()) {
        std::cout << "INFO: No schedules to print." << std::endl;
        return;
    }
    
    // Sort schedules by ID before displaying
    std::sort(schedules.begin(), schedules.end(), 
              [](const Schedule& a, const Schedule& b) {
                  return a.getId() < b.getId();
              });
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "ALL SCHEDULES (" << schedules.size() << " total)" << std::endl;
    std::cout << std::string(60, '=') << std::endl;
    for (size_t i = 0; i < schedules.size(); ++i) {
        const auto& schedule = schedules[i];
        std::cout << "\n--- SCHEDULE " << schedule.getId() << " ---" << std::endl;
        schedule.printSchedule();
        if (i < schedules.size() - 1) {
            std::cout << std::string(40, '-') << std::endl;
        }
    }
    std::cout << std::string(60, '=') << std::endl;
}

void System::handleAddSchedule() {
    // Find the next available schedule ID
    int maxId = 0;
    for (const auto& schedule : schedules) {
        if (schedule.getId() > maxId) {
            maxId = schedule.getId();
        }
    }
    
    int newId = maxId + 1;
    schedules.emplace_back(newId);
    
    // Auto-save main schedules file
    saveSchedules();
    
    // Create individual schedule file (ScheduleX.csv)
    saveIndividualSchedule(schedules.back());
    
    std::cout << "SUCCESS: Added new empty schedule with ID " << newId 
              << " and created Schedule" << newId << ".csv (Auto-saved)" << std::endl;
}

void System::handleRemoveSchedule(const std::string& scheduleId_str) {
    try {
        int scheduleId = std::stoi(scheduleId_str);
        
        // Find the schedule to remove
        auto it = std::find_if(schedules.begin(), schedules.end(), 
            [scheduleId](const Schedule& s){ return s.getId() == scheduleId; });

        if (it == schedules.end()) {
            std::cout << "ERROR: Schedule with ID " << scheduleId << " not found." << std::endl;
            return;
        }

        // Store original schedule count for file renaming
        int originalCount = static_cast<int>(schedules.size());
        
        // Remove the schedule from memory
        schedules.erase(it);
        
        // Re-index all schedules: assign new consecutive IDs starting from 1
        for (size_t i = 0; i < schedules.size(); ++i) {
            schedules[i].setId(static_cast<int>(i + 1));
        }
        
        // Delete all old individual schedule files
        for (int i = scheduleId; i <= originalCount; ++i) {
            std::string oldFilename = "Schedule" + std::to_string(i) + ".csv";
            std::remove(oldFilename.c_str());  // Delete file (returns 0 on success)
        }
        
        // Re-create all individual schedule files with new IDs
        for (const auto& schedule : schedules) {
            saveIndividualSchedule(schedule);
        }
        
        // Save main schedules file with updated IDs
        saveSchedules();
        
        std::cout << "SUCCESS: Schedule " << scheduleId << " removed successfully!" << std::endl;
        std::cout << "         All subsequent schedules re-indexed (Auto-saved)" << std::endl;
        std::cout << "         Individual CSV files updated: Schedule1.csv to Schedule" 
                  << schedules.size() << ".csv" << std::endl;
        
        // Show current schedule status
        if (schedules.empty()) {
            std::cout << "         No schedules remaining." << std::endl;
        } else {
            std::cout << "         Current schedules: ";
            for (size_t i = 0; i < schedules.size(); ++i) {
                std::cout << schedules[i].getId();
                if (i < schedules.size() - 1) std::cout << ", ";
            }
            std::cout << std::endl;
        }
        
    } catch (...) {
        std::cout << "ERROR: Invalid schedule ID format." << std::endl;
    }
}

// Helper method to get course name by ID
std::string System::getCourseName(int courseId) const {
    for (const auto& course : courses) {
        if (course.getId() == courseId) {
            return course.getName();
        }
    }
    return "Unknown Course";
}

void System::handleAddLessonToSchedule(const std::string& scheduleId_str, const std::string& courseId_str, const std::string& groupId_str) {
     try {
        int scheduleId = std::stoi(scheduleId_str);
        int courseId = std::stoi(courseId_str);
        int groupId = std::stoi(groupId_str);

        Schedule* schedule = nullptr;
        for(auto& s : schedules){
            if(s.getId() == scheduleId){
                schedule = &s;
                break;
            }
        }

        if (!schedule) {
            std::cout << "ERROR: Schedule with ID " << scheduleId << " not found." << std::endl;
            return;
        }

        // Find all lessons for this course and group
        std::vector<Lesson*> availableLessons = findLessonsForCourseAndGroup(courseId, groupId);
        
        if (availableLessons.empty()) {
            std::cout << "ERROR: No lessons found for Course ID " << courseId << " and Group ID " << groupId << std::endl;
            return;
        }

        // If only one lesson type exists, use it directly
        Lesson* selectedLesson = nullptr;
        if (availableLessons.size() == 1) {
            selectedLesson = availableLessons[0];
        } else {
            // Multiple lesson types available - ask user to choose
            const std::string COLOR_CYAN = "\033[1;36m";       // Bright Cyan
            const std::string COLOR_GREEN = "\033[1;32m";      // Bright Green
            const std::string COLOR_YELLOW = "\033[1;33m";     // Bright Yellow
            const std::string COLOR_BLUE = "\033[1;34m";       // Bright Blue
            const std::string COLOR_WHITE = "\033[1;37m";      // Bright White
            const std::string COLOR_RESET = "\033[0m";         // Reset
            
            std::cout << "\n" << std::string(80, '=') << std::endl;
            std::cout << COLOR_CYAN << "          LESSON TYPE SELECTION FOR COURSE " << courseId << " GROUP " << groupId << COLOR_RESET << std::endl;
            std::cout << std::string(80, '=') << std::endl;
            
            std::string courseName = getCourseName(courseId);
            std::cout << COLOR_WHITE << "Course: " << COLOR_GREEN << courseId << " - " << courseName << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "Group:  " << COLOR_GREEN << groupId << COLOR_RESET << std::endl;
            std::cout << std::endl;
            
            std::cout << COLOR_YELLOW << "Multiple lesson types are available for this course and group:" << COLOR_RESET << std::endl;
            std::cout << std::string(80, '-') << std::endl;
            
            // Display available lesson types with details
            for (size_t i = 0; i < availableLessons.size(); ++i) {
                Lesson* lesson = availableLessons[i];
                std::string typeColor = (lesson->getType() == "Lecture") ? COLOR_BLUE :
                                      (lesson->getType() == "Tutorial") ? COLOR_GREEN : COLOR_YELLOW;
                
                std::cout << COLOR_WHITE << "[" << (i + 1) << "] " << typeColor << lesson->getType() << COLOR_RESET << std::endl;
                std::cout << COLOR_WHITE << "    Day:      " << COLOR_CYAN << lesson->getDay() << COLOR_RESET << std::endl;
                std::cout << COLOR_WHITE << "    Time:     " << COLOR_CYAN << lesson->getTimeRange() << COLOR_RESET << std::endl;
                std::cout << COLOR_WHITE << "    Teacher:  " << COLOR_CYAN << lesson->getTeacherName() << COLOR_RESET << std::endl;
                std::cout << COLOR_WHITE << "    Location: " << COLOR_CYAN << lesson->getBuilding() << " " << lesson->getRoom() << COLOR_RESET << std::endl;
                
                if (i < availableLessons.size() - 1) {
                    std::cout << std::string(60, '-') << std::endl;
                }
            }
            
            std::cout << std::endl;
            std::cout << COLOR_YELLOW << "Which lesson type would you like to add to schedule " << scheduleId << "?" << COLOR_RESET << std::endl;
            
            // Get user choice
            int choice = -1;
            bool validChoice = false;
            
            while (!validChoice) {
                std::cout << COLOR_CYAN << "Enter your choice [1-" << availableLessons.size() << "] or [0] to cancel: " << COLOR_RESET;
                std::string userInput;
                std::getline(std::cin, userInput);
                
                try {
                    choice = std::stoi(userInput);
                    
                    if (choice == 0) {
                        std::cout << COLOR_GREEN << "Operation cancelled. No lesson was added." << COLOR_RESET << std::endl;
                        std::cout << std::string(80, '=') << std::endl;
                        return;
                    } else if (choice >= 1 && choice <= static_cast<int>(availableLessons.size())) {
                        validChoice = true;
                        selectedLesson = availableLessons[choice - 1];
                    } else {
                        std::cout << COLOR_YELLOW << "Invalid choice! Please enter a number between 1 and " 
                                  << availableLessons.size() << ", or 0 to cancel." << COLOR_RESET << std::endl;
                    }
                } catch (...) {
                    std::cout << COLOR_YELLOW << "Invalid input! Please enter a valid number." << COLOR_RESET << std::endl;
                }
            }
            
            std::cout << std::endl;
            std::cout << COLOR_GREEN << "You selected: " << selectedLesson->getType() 
                      << " for Course " << courseId << " Group " << groupId << COLOR_RESET << std::endl;
            std::cout << std::string(80, '=') << std::endl;
        }

        // Now proceed with the selected lesson
        if (!selectedLesson) {
            std::cout << "ERROR: No lesson was selected." << std::endl;
            return;
        }

        // Check for conflicts before adding and provide detailed information
        bool hasConflict = false;
        std::string conflictingCourseName = "";
        int conflictingCourseId = 0;
        int conflictingGroupId = 0;
        std::string conflictingDay = "";
        int conflictingStart = 0, conflictingEnd = 0;
        
        for (const auto& existingLesson : schedule->getLessons()) {
            if (existingLesson->getDay() == selectedLesson->getDay()) {
                int start1 = existingLesson->getStartHour();
                int end1 = start1 + existingLesson->getDuration();
                int start2 = selectedLesson->getStartHour();
                int end2 = start2 + selectedLesson->getDuration();
                if ((start1 < end2) && (start2 < end1)) {
                    hasConflict = true;
                    conflictingCourseId = existingLesson->getCourseId();
                    conflictingGroupId = existingLesson->getGroupId();
                    conflictingCourseName = getCourseName(conflictingCourseId);
                    conflictingDay = existingLesson->getDay();
                    conflictingStart = start1;
                    conflictingEnd = end1;
                    break;
                }
            }
        }
        
        if (hasConflict) {
            // ANSI Color codes for enhanced visual impact
            const std::string COLOR_RED = "\033[1;31m";        // Bright Red
            const std::string COLOR_YELLOW = "\033[1;33m";     // Bright Yellow
            const std::string COLOR_CYAN = "\033[1;36m";       // Bright Cyan
            const std::string COLOR_WHITE = "\033[1;37m";      // Bright White
            const std::string COLOR_RESET = "\033[0m";         // Reset
            const std::string COLOR_GREEN = "\033[1;32m";      // Bright Green
            const std::string COLOR_BLUE = "\033[1;34m";       // Bright Blue
            
            std::cout << "\n" << std::string(80, '=') << std::endl;
            std::cout << COLOR_RED << "                    ?  SCHEDULE CONFLICT DETECTED  ?" << COLOR_RESET << std::endl;
            std::cout << std::string(80, '=') << std::endl;
            
            std::string newCourseName = getCourseName(courseId);
            
            std::cout << COLOR_YELLOW << "? WARNING: The lesson you're trying to add conflicts with an existing lesson!" << COLOR_RESET << std::endl;
            std::cout << std::endl;
            
            // Display new lesson details with colored formatting
            std::cout << COLOR_CYAN << "?? NEW LESSON YOU'RE TRYING TO ADD:" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Course:   " << COLOR_GREEN << courseId << " - " << newCourseName << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Group:    " << COLOR_GREEN << groupId << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Type:     " << COLOR_GREEN << selectedLesson->getType() << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Day:      " << COLOR_GREEN << selectedLesson->getDay() << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Time:     " << COLOR_GREEN << selectedLesson->getTimeRange() << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Teacher:  " << COLOR_GREEN << selectedLesson->getTeacherName() << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Location: " << COLOR_GREEN << selectedLesson->getBuilding() << " " << selectedLesson->getRoom() << COLOR_RESET << std::endl;
            
            std::cout << std::endl;
            
            // Display conflicting lesson details
            std::cout << COLOR_RED << "? CONFLICTS WITH EXISTING LESSON:" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Course:   " << COLOR_YELLOW << conflictingCourseId << " - " << conflictingCourseName << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Group:    " << COLOR_YELLOW << conflictingGroupId << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Day:      " << COLOR_YELLOW << conflictingDay << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Time:     " << COLOR_YELLOW << (conflictingStart < 10 ? "0" : "") << conflictingStart 
                      << ":00-" << (conflictingEnd < 10 ? "0" : "") << conflictingEnd << ":00" << COLOR_RESET << std::endl;
            
            // Calculate and display overlap details
            int newStart = selectedLesson->getStartHour();
            int newEnd = newStart + selectedLesson->getDuration();
            int overlapStart = (std::max)(conflictingStart, newStart);
            int overlapEnd = (std::min)(conflictingEnd, newEnd);
            int overlapMinutes = (overlapEnd - overlapStart) * 60;
            
            std::cout << std::endl;
            std::cout << COLOR_RED << "? OVERLAP DETAILS:" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Overlap Period: " << COLOR_RED << (overlapStart < 10 ? "0" : "") << overlapStart 
                      << ":00-" << (overlapEnd < 10 ? "0" : "") << overlapEnd << ":00" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  Overlap Duration: " << COLOR_RED << (overlapEnd - overlapStart) << " hour(s) (" 
                      << overlapMinutes << " minutes)" << COLOR_RESET << std::endl;
            
            std::cout << std::endl;
            std::cout << COLOR_YELLOW << "? POTENTIAL CONSEQUENCES:" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  • You will have " << COLOR_RED << "OVERLAPPING CLASSES" << COLOR_WHITE 
                      << " - impossible to attend both!" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  • Your schedule will show " << COLOR_RED << "CONFLICT WARNINGS" << COLOR_WHITE 
                      << " in timetable view" << std::endl;
            std::cout << COLOR_WHITE << "  • You may miss important course content during overlap periods" << COLOR_RESET << std::endl;
            
            std::cout << std::endl;
            std::cout << COLOR_GREEN << "?? SUGGESTED ALTERNATIVES:" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  • Try a different group for Course " << courseId << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  • Remove the conflicting lesson first (Course " << conflictingCourseId << ")" << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "  • Choose a different time slot for this course" << COLOR_RESET << std::endl;
            
            std::cout << std::endl;
            std::cout << std::string(80, '-') << std::endl;
            
            // Ask user for confirmation with clear options
            std::cout << COLOR_CYAN << "? WHAT WOULD YOU LIKE TO DO?" << COLOR_RESET << std::endl;
            std::cout << COLOR_GREEN << "  [Y] YES - Add anyway (FORCE ADD with conflict)" << COLOR_RESET << std::endl;
            std::cout << COLOR_RED << "  [N] NO  - Cancel and don't add this lesson" << COLOR_RESET << std::endl;
            std::cout << std::endl;
            
            // Get user choice with enhanced prompting
            std::string userChoice;
            bool validChoice = false;
            
            while (!validChoice) {
                std::cout << COLOR_YELLOW << "? Enter your choice [Y/N]: " << COLOR_RESET;
                std::getline(std::cin, userChoice);
                
                // Convert to uppercase and trim
                if (!userChoice.empty()) {
                    userChoice[0] = std::toupper(static_cast<unsigned char>(userChoice[0]));
                }
                
                if (userChoice == "Y" || userChoice == "YES") {
                    validChoice = true;
                    
                    // Force add the lesson using smart pointer interface
                    schedule->addLessonForce(selectedLesson->clone());
                    
                    // Auto-save main schedules file
                    saveSchedules();
                    
                    // NEW: Also save individual schedule file
                    saveIndividualSchedule(*schedule);
                    
                    std::cout << std::endl;
                    std::cout << COLOR_YELLOW << "??  CONFLICT ADDED TO SCHEDULE " << scheduleId << " ??" << COLOR_RESET << std::endl;
                    std::cout << COLOR_GREEN << "? Added " << newCourseName << " (Course " << courseId 
                              << ", Group " << groupId << ", " << selectedLesson->getType() << ") WITH CONFLICTS (Auto-saved)" << COLOR_RESET << std::endl;
                    std::cout << COLOR_RED << "?? WARNING: Your schedule now contains time conflicts!" << COLOR_RESET << std::endl;
                    std::cout << COLOR_CYAN << "?? TIP: Use 'CheckConflicts " << scheduleId 
                              << "' to see detailed conflict analysis" << COLOR_RESET;
                    
                } else if (userChoice == "N" || userChoice == "NO") {
                    validChoice = true;
                    
                    std::cout << std::endl;
                    std::cout << COLOR_GREEN << "? WISE CHOICE!" << COLOR_RESET << std::endl;
                    std::cout << COLOR_WHITE << "Lesson NOT added to avoid scheduling conflicts." << COLOR_RESET << std::endl;
                    std::cout << COLOR_CYAN << "?? Consider choosing a different group or time slot." << COLOR_RESET << std::endl;
                    
                } else {
                    std::cout << COLOR_RED << "? Invalid choice! Please enter 'Y' for Yes or 'N' for No." << COLOR_RESET << std::endl;
                }
            }
            
            std::cout << std::string(80, '=') << std::endl;
            return;
        }

        // If no conflict, add the lesson using smart pointer interface
        schedule->addLesson(selectedLesson->clone());
        
        // Auto-save main schedules file
        saveSchedules();
        
        // NEW: Also save individual schedule file
        saveIndividualSchedule(*schedule);
        
        std::string courseName = getCourseName(courseId);
        std::cout << "SUCCESS: Added " << courseName << " (Course " << courseId 
                  << ", Group " << groupId << ", " << selectedLesson->getType() << ") to schedule " << scheduleId << " (Auto-saved)" << std::endl;

    } catch (...) {
        std::cout << "ERROR: Invalid ID format." << std::endl;
    }
}

void System::handleRemoveLessonFromSchedule(const std::string& scheduleId_str, const std::string& courseId_str, const std::string& groupId_str) {
    try {
        int scheduleId = std::stoi(scheduleId_str);
        int courseId = std::stoi(courseId_str);
        int groupId = std::stoi(groupId_str);

        Schedule* schedule = nullptr;
        for(auto& s : schedules){
            if(s.getId() == scheduleId){
                schedule = &s;
                break;
            }
        }

        if (!schedule) {
            std::cout << "ERROR: Schedule with ID " << scheduleId << " not found." << std::endl;
            return;
        }

        // Find all lessons in the schedule that match the course and group
        std::vector<std::unique_ptr<Lesson>*> lessonsInSchedule;
        for (auto& lesson : schedule->getLessons()) {
            if (lesson->getCourseId() == courseId && lesson->getGroupId() == groupId) {
                lessonsInSchedule.push_back(&lesson);
            }
        }

        if (lessonsInSchedule.empty()) {
            std::cout << "ERROR: No lessons found for Course ID " << courseId << " and Group ID " << groupId << " in schedule " << scheduleId << std::endl;
            return;
        }

        // If only one lesson type exists in the schedule, remove it directly
        std::string selectedType = "";
        if (lessonsInSchedule.size() == 1) {
            selectedType = (*lessonsInSchedule[0])->getType();
        } else {
            // Multiple lesson types available - ask user to choose
            const std::string COLOR_RED = "\033[1;31m";        // Bright Red
            const std::string COLOR_CYAN = "\033[1;36m";       // Bright Cyan
            const std::string COLOR_GREEN = "\033[1;32m";      // Bright Green
            const std::string COLOR_YELLOW = "\033[1;33m";     // Bright Yellow
            const std::string COLOR_BLUE = "\033[1;34m";       // Bright Blue
            const std::string COLOR_WHITE = "\033[1;37m";      // Bright White
            const std::string COLOR_RESET = "\033[0m";         // Reset
            
            std::cout << "\n" << std::string(80, '=') << std::endl;
            std::cout << COLOR_RED << "          LESSON REMOVAL SELECTION FOR COURSE " << courseId << " GROUP " << groupId << COLOR_RESET << std::endl;
            std::cout << std::string(80, '=') << std::endl;
            
            std::string courseName = getCourseName(courseId);
            std::cout << COLOR_WHITE << "Course: " << COLOR_GREEN << courseId << " - " << courseName << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "Group:  " << COLOR_GREEN << groupId << COLOR_RESET << std::endl;
            std::cout << COLOR_WHITE << "Schedule: " << COLOR_GREEN << scheduleId << COLOR_RESET << std::endl;
            std::cout << std::endl;
            
            std::cout << COLOR_YELLOW << "Multiple lesson types found in this schedule for this course/group:" << COLOR_RESET << std::endl;
            std::cout << std::string(80, '-') << std::endl;
            
            // Display available lesson types with details
            for (size_t i = 0; i < lessonsInSchedule.size(); ++i) {
                const auto& lesson = *lessonsInSchedule[i];
                std::string typeColor = (lesson->getType() == "Lecture") ? COLOR_BLUE :
                                      (lesson->getType() == "Tutorial") ? COLOR_GREEN : COLOR_YELLOW;
                
                std::cout << COLOR_WHITE << "[" << (i + 1) << "] " << typeColor << lesson->getType() << COLOR_RESET << std::endl;
                std::cout << COLOR_WHITE << "    Day:      " << COLOR_CYAN << lesson->getDay() << COLOR_RESET << std::endl;
                std::cout << COLOR_WHITE << "    Time:     " << COLOR_CYAN << lesson->getTimeRange() << COLOR_RESET << std::endl;
                std::cout << COLOR_WHITE << "    Teacher:  " << COLOR_CYAN << lesson->getTeacherName() << COLOR_RESET << std::endl;
                std::cout << COLOR_WHITE << "    Location: " << COLOR_CYAN << lesson->getBuilding() << " " << lesson->getRoom() << COLOR_RESET << std::endl;
                
                if (i < lessonsInSchedule.size() - 1) {
                    std::cout << std::string(60, '-') << std::endl;
                }
            }
            
            std::cout << std::endl;
            std::cout << COLOR_YELLOW << "Which lesson type would you like to remove from schedule " << scheduleId << "?" << COLOR_RESET << std::endl;
            
            // Get user choice
            int choice = -1;
            bool validChoice = false;
            
            while (!validChoice) {
                std::cout << COLOR_CYAN << "Enter your choice [1-" << lessonsInSchedule.size() << "], [ALL], or [0] to cancel: " << COLOR_RESET;
                std::string userInput;
                std::getline(std::cin, userInput);
                
                // Convert input to uppercase for ALL option
                std::string upperInput = userInput;
                std::transform(upperInput.begin(), upperInput.end(), upperInput.begin(), ::toupper);
                
                if (upperInput == "ALL") {
                    validChoice = true;
                    selectedType = "ALL";
                } else {
                    try {
                        choice = std::stoi(userInput);
                        
                        if (choice == 0) {
                            std::cout << COLOR_GREEN << "Operation cancelled. No lesson was removed." << COLOR_RESET << std::endl;
                            std::cout << std::string(80, '=') << std::endl;
                            return;
                        } else if (choice >= 1 && choice <= static_cast<int>(lessonsInSchedule.size())) {
                            validChoice = true;
                            selectedType = (*lessonsInSchedule[choice - 1])->getType();
                        } else {
                            std::cout << COLOR_YELLOW << "Invalid choice! Please enter a number between 1 and " 
                                      << lessonsInSchedule.size() << ", 'ALL', or 0 to cancel." << COLOR_RESET << std::endl;
                        }
                    } catch (...) {
                        std::cout << COLOR_YELLOW << "Invalid input! Please enter a valid number, 'ALL', or 0 to cancel." << COLOR_RESET << std::endl;
                    }
                }
            }
            
            std::cout << std::endl;
            if (selectedType == "ALL") {
                std::cout << COLOR_RED << "You selected to remove ALL lesson types for Course " << courseId << " Group " << groupId << COLOR_RESET << std::endl;
            } else {
                std::cout << COLOR_RED << "You selected to remove: " << selectedType 
                          << " for Course " << courseId << " Group " << groupId << COLOR_RESET << std::endl;
            }
            std::cout << std::string(80, '=') << std::endl;
        }

        // Now proceed with removal based on the selected type
        if (selectedType.empty()) {
            std::cout << "ERROR: No lesson type was selected." << std::endl;
            return;
        }

        // Store lesson count before removal to verify if anything was actually removed
        size_t lessonCountBefore = schedule->getLessons().size();
        
        // Perform removal
        if (selectedType == "ALL") {
            // Remove all lessons for this course and group
            schedule->removeLesson(courseId, groupId);
        } else {
            // Remove specific lesson type for this course and group
            schedule->removeLesson(courseId, groupId, selectedType);
        }
        
        // Check if lesson was actually removed and auto-save
        if (schedule->getLessons().size() < lessonCountBefore) {
            saveSchedules();
            
            // NEW: Also save individual schedule file
            saveIndividualSchedule(*schedule);
            
            // Enhanced success message with colors
            const std::string COLOR_GREEN = "\033[1;32m";      // Bright Green
            const std::string COLOR_CYAN = "\033[1;36m";       // Bright Cyan
            const std::string COLOR_RESET = "\033[0m";         // Reset
            
            std::string courseName = getCourseName(courseId);
            int removedCount = static_cast<int>(lessonCountBefore - schedule->getLessons().size());
            
            std::cout << std::endl;
            std::cout << COLOR_GREEN << "? REMOVAL SUCCESSFUL!" << COLOR_RESET << std::endl;
            if (selectedType == "ALL") {
                std::cout << COLOR_CYAN << "???  Removed ALL lesson types (" << removedCount << " lesson" 
                          << (removedCount != 1 ? "s" : "") << ") for " << courseName 
                          << " (Course " << courseId << ", Group " << groupId << ") from schedule " << scheduleId << COLOR_RESET << std::endl;
            } else {
                std::cout << COLOR_CYAN << "???  Removed " << selectedType << " lesson for " << courseName 
                          << " (Course " << courseId << ", Group " << groupId << ") from schedule " << scheduleId << COLOR_RESET << std::endl;
            }
            std::cout << COLOR_GREEN << "?? Auto-saved changes to schedule " << scheduleId << COLOR_RESET << std::endl;
        } else {
            // No lessons were removed
            const std::string COLOR_RED = "\033[1;31m";        // Bright Red
            const std::string COLOR_RESET = "\033[0m";         // Reset
            
            std::cout << COLOR_RED << "? No lessons were removed. The specified lesson may not exist in the schedule." << COLOR_RESET << std::endl;
        }
        
    } catch (...) {
        std::cout << "ERROR: Invalid ID format." << std::endl;
    }
}

void System::handleAddCourse() {
    std::cout << "\n=== ADD NEW COURSE ===" << std::endl;
    
    int courseId, credits;
    std::string name, moedA, moedB, lecturer;
    
    std::cout << "Enter Course ID: ";
    std::cin >> courseId;
    std::cin.ignore(); // Clear input buffer
    
    // Check if course ID already exists
    for (const auto& course : courses) {
        if (course.getId() == courseId) {
            std::cout << "ERROR: Course with ID " << courseId << " already exists!" << std::endl;
            return;
        }
    }
    
    std::cout << "Enter Course Name: ";
    std::getline(std::cin, name);
    
    std::cout << "Enter Credits: ";
    std::cin >> credits;
    std::cin.ignore();
    
    std::cout << "Enter Moed A Date (YYYY-MM-DD): ";
    std::getline(std::cin, moedA);
    
    std::cout << "Enter Moed B Date (YYYY-MM-DD): ";
    std::getline(std::cin, moedB);
    
    std::cout << "Enter Lecturer Name: ";
    std::getline(std::cin, lecturer);
    
    // Add the new course
    courses.emplace_back(courseId, name, credits, moedA, moedB, lecturer);
    
    // Auto-save
    saveCourses();
    
    std::cout << "SUCCESS: Added course " << courseId << " - " << name << " (Auto-saved)" << std::endl;
}

void System::handleRemoveCourse(const std::string& courseId_str) {
    try {
        int courseId = std::stoi(courseId_str);
        
        auto it = std::remove_if(courses.begin(), courses.end(), 
            [courseId](const Course& c){ return c.getId() == courseId; });

        if (it != courses.end()) {
            std::string courseName = it->getName();
            courses.erase(it, courses.end());
            
            // Auto-save
            saveCourses();
            
            std::cout << "SUCCESS: Removed course " << courseId << " - " << courseName << " (Auto-saved)" << std::endl;
            std::cout << "WARNING: You may want to remove related lessons manually." << std::endl;
        } else {
            std::cout << "ERROR: Course with ID " << courseId << " not found." << std::endl;
        }
    } catch (...) {
        std::cout << "ERROR: Invalid course ID format." << std::endl;
    }
}

void System::handleAddLesson() {
    std::cout << "\n=== ADD NEW LESSON ===" << std::endl;
    
    int courseId, groupId, startHour, duration;
    std::string type, teacher, day, building, room;
    
    std::cout << "Enter Lesson Type (Lecture/Tutorial/Lab): ";
    std::getline(std::cin, type);
    
    std::cout << "Enter Course ID: ";
    std::cin >> courseId;
    
    std::cout << "Enter Group ID: ";
    std::cin >> groupId;
    std::cin.ignore();
    
    // Check if lesson already exists
    for (const auto& lesson : lessons) {
        if (lesson->getCourseId() == courseId && lesson->getGroupId() == groupId) {
            std::cout << "ERROR: Lesson with Course ID " << courseId 
                      << " and Group ID " << groupId << " already exists!" << std::endl;
            return;
        }
    }
    
    std::cout << "Enter Teacher Name: ";
    std::getline(std::cin, teacher);
    
    std::cout << "Enter Day (Monday/Tuesday/Wednesday/Thursday/Friday/Saturday/Sunday): ";
    std::getline(std::cin, day);
    
    std::cout << "Enter Start Hour (0-23): ";
    std::cin >> startHour;
    
    std::cout << "Enter Duration (hours): ";
    std::cin >> duration;
    std::cin.ignore();
    
    std::cout << "Enter Building: ";
    std::getline(std::cin, building);
    
    std::cout << "Enter Room: ";
    std::getline(std::cin, room);
    
    // Create the appropriate lesson type
    Lesson* newLesson = nullptr;
    int endHour = startHour + duration;
    
    if (type == "Lecture") {
        newLesson = new Lecture(type, courseId, day, startHour, endHour, room, teacher, groupId);
    } else if (type == "Tutorial") {
        newLesson = new Tutorial(type, courseId, day, startHour, endHour, room, teacher, groupId);
    } else if (type == "Lab") {
        newLesson = new Lab(type, courseId, day, startHour, endHour, room, teacher, groupId);
    } else {
        std::cout << "ERROR: Invalid lesson type. Must be Lecture, Tutorial, or Lab." << std::endl;
        return;
    }
    
    // Add to lessons
    lessons.push_back(newLesson);
    
    // Auto-save
    saveLessons();
    
    std::cout << "SUCCESS: Added " << type << " for Course " << courseId 
              << ", Group " << groupId << " (Auto-saved)" << std::endl;
}

void System::handleClear() {
    clearScreen();
    std::cout << std::string(50, '=') << std::endl;
    std::cout << " COURSE MANAGEMENT SYSTEM " << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "Type 'Help' for commands or 'Exit' to quit." << std::endl;
}

void System::handleCheckConflicts(const std::string& scheduleId_str) {
    if (scheduleId_str.empty()) {
        std::cout << "ERROR: Missing schedule ID. Usage: CheckConflicts <schedule_id>" << std::endl;
        return;
    }
    
    try {
        int scheduleId = std::stoi(scheduleId_str);
        Schedule* schedule = nullptr;
        for(auto& s : schedules){
            if(s.getId() == scheduleId){
                schedule = &s;
                break;
            }
        }

        if(schedule){
            std::cout << "\nCONFLICT ANALYSIS FOR SCHEDULE " << scheduleId << ":" << std::endl;
            schedule->printConflicts();
        } else {
            std::cout << "ERROR: Schedule with ID " << scheduleId << " not found." << std::endl;
        }
    } catch (...) {
        std::cout << "ERROR: Invalid schedule ID format." << std::endl;
    }
}

void System::handleFindTimeConflicts() {
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "                    TIME CONFLICT ANALYSIS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    if (schedules.empty()) {
        std::cout << "No schedules available for conflict analysis." << std::endl;
        return;
    }
    
    bool foundAnyConflicts = false;
    
    // Analyze each schedule separately
    for (const auto& schedule : schedules) {
        std::cout << "\n--- ANALYZING SCHEDULE " << schedule.getId() << " ---" << std::endl;
        
        bool hasLessonConflicts = false;
        bool hasExamConflicts = false;
        
        // 1. Check lesson-to-lesson conflicts
        std::vector<std::pair<size_t, size_t>> lessonConflictPairs; // Use size_t for indices
        const auto& lessons = schedule.getLessons();
        
        for (size_t i = 0; i < lessons.size(); i++) {
            for (size_t j = i + 1; j < lessons.size(); j++) {
                if (lessons[i]->getDay() == lessons[j]->getDay()) {
                    int start1 = lessons[i]->getStartHour();
                    int end1 = start1 + lessons[i]->getDuration();
                    int start2 = lessons[j]->getStartHour();
                    int end2 = start2 + lessons[j]->getDuration();
                    
                    if ((start1 < end2) && (start2 < end1)) {
                        lessonConflictPairs.push_back(std::make_pair(i, j));
                        hasLessonConflicts = true;
                    }
                }
            }
        }
        
        // 2. Check exam conflicts (Moed A and Moed B)
        std::vector<std::pair<int, int>> examConflictPairs;
        std::set<int> scheduleCourseIds;
        
        for (const auto& lesson : lessons) {
            scheduleCourseIds.insert(lesson->getCourseId());
        }
        
        std::vector<int> courseList(scheduleCourseIds.begin(), scheduleCourseIds.end());
        
        for (size_t i = 0; i < courseList.size(); i++) {
            for (size_t j = i + 1; j < courseList.size(); j++) {
                const Course* course1 = nullptr;
                const Course* course2 = nullptr;
                
                for (const auto& course : courses) {
                    if (course.getId() == courseList[i]) course1 = &course;
                    if (course.getId() == courseList[j]) course2 = &course;
                }
                
                if (course1 && course2) {
                    // Check Moed A conflicts
                    if (course1->getMoedA() == course2->getMoedA() && !course1->getMoedA().empty()) {
                        examConflictPairs.push_back(std::make_pair(courseList[i], courseList[j]));
                        hasExamConflicts = true;
                    }
                    // Check Moed B conflicts
                    if (course1->getMoedB() == course2->getMoedB() && !course1->getMoedB().empty()) {
                        examConflictPairs.push_back(std::make_pair(courseList[i], courseList[j]));
                        hasExamConflicts = true;
                    }
                }
            }
        }
        
        // Display results for this schedule
        if (!hasLessonConflicts && !hasExamConflicts) {
            std::cout << "  ? NO CONFLICTS DETECTED - This schedule is conflict-free!" << std::endl;
        } else {
            foundAnyConflicts = true;
            
            // Display lesson conflicts
            if (hasLessonConflicts) {
                std::cout << "\n  ?? LESSON TIME CONFLICTS ??" << std::endl;
                for (const auto& conflict : lessonConflictPairs) {
                    size_t i = conflict.first;
                    size_t j = conflict.second;
                    
                    std::cout << "    CONFLICT: Course " << lessons[i]->getCourseId() 
                              << " (" << getCourseName(lessons[i]->getCourseId()) << ")" << std::endl;
                    std::cout << "              vs Course " << lessons[j]->getCourseId() 
                              << " (" << getCourseName(lessons[j]->getCourseId()) << ")" << std::endl;
                    std::cout << "    Day: " << lessons[i]->getDay() << std::endl;
                    
                    int start1 = lessons[i]->getStartHour();
                    int end1 = start1 + lessons[i]->getDuration();
                    int start2 = lessons[j]->getStartHour();
                    int end2 = start2 + lessons[j]->getDuration();
                    
                    std::cout << "    Times: " << (start1 < 10 ? "0" : "") << start1 << ":00-" 
                              << (end1 < 10 ? "0" : "") << end1 << ":00 vs " 
                              << (start2 < 10 ? "0" : "") << start2 << ":00-" 
                              << (end2 < 10 ? "0" : "") << end2 << ":00" << std::endl;
                    
                    std::cout << "    Rooms: " << lessons[i]->getBuilding() << " " << lessons[i]->getRoom() 
                              << " vs " << lessons[j]->getBuilding() << " " << lessons[j]->getRoom() << std::endl;
                    std::cout << std::endl;
                }
            }
            
            // Display exam conflicts
            if (hasExamConflicts) {
                std::cout << "  ?? EXAM DATE CONFLICTS ??" << std::endl;
                for (const auto& conflict : examConflictPairs) {
                    int courseId1 = conflict.first;
                    int courseId2 = conflict.second;
                    
                    const Course* course1 = nullptr;
                    const Course* course2 = nullptr;
                    
                    for (const auto& course : courses) {
                        if (course.getId() == courseId1) course1 = &course;
                        if (course.getId() == courseId2) course2 = &course;
                    }
                    
                    if (course1 && course2) {
                        std::cout << "    EXAM CONFLICT: Course " << courseId1 << " (" << course1->getName() << ")" << std::endl;
                        std::cout << "                   vs Course " << courseId2 << " (" << course2->getName() << ")" << std::endl;
                        
                        if (course1->getMoedA() == course2->getMoedA() && !course1->getMoedA().empty()) {
                            std::cout << "    Moed A Date: " << course1->getMoedA() << std::endl;
                        }
                        if (course1->getMoedB() == course2->getMoedB() && !course1->getMoedB().empty()) {
                            std::cout << "    Moed B Date: " << course1->getMoedB() << std::endl;
                        }
                        std::cout << std::endl;
                    }
                }
            }
        }
    }
    
    std::cout << std::string(80, '-') << std::endl;
    if (!foundAnyConflicts) {
        std::cout << "SUMMARY: All schedules are conflict-free! ?" << std::endl;
    } else {
        std::cout << "SUMMARY: Conflicts detected in one or more schedules." << std::endl;
        std::cout << "RECOMMENDATION: Consider choosing different groups or rescheduling conflicting lessons." << std::endl;
    }
    std::cout << std::string(80, '=') << std::endl;
}

void System::handleAnalyzeCourseWorkload(const std::string& scheduleId_str) {
    if (scheduleId_str.empty()) {
        std::cout << "ERROR: Missing schedule ID. Usage: AnalyzeWorkload <schedule_id>" << std::endl;
        std::cout << "       Or use 'AnalyzeWorkload all' to analyze all schedules." << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "                    COURSE WORKLOAD ANALYSIS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    
    if (scheduleId_str == "all") {
        // Analyze all schedules
        if (schedules.empty()) {
            std::cout << "No schedules available for analysis." << std::endl;
            return;
        }
        
        for (const auto& schedule : schedules) {
            analyzeScheduleWorkload(schedule);
            std::cout << std::string(80, '-') << std::endl;
        }
    } else {
        // Analyze specific schedule
        try {
            int scheduleId = std::stoi(scheduleId_str);
            Schedule* schedule = nullptr;
            
            for (auto& s : schedules) {
                if (s.getId() == scheduleId) {
                    schedule = &s;
                    break;
                }
            }
            
            if (schedule) {
                analyzeScheduleWorkload(*schedule);
            } else {
                std::cout << "ERROR: Schedule with ID " << scheduleId << " not found." << std::endl;
                if (!schedules.empty()) {
                    std::cout << "Available schedule IDs: ";
                    for (size_t i = 0; i < schedules.size(); ++i) {
                        std::cout << schedules[i].getId();
                        if (i < schedules.size() - 1) std::cout << ", ";
                    }
                    std::cout << std::endl;
                }
            }
        } catch (...) {
            std::cout << "ERROR: Invalid schedule ID format." << std::endl;
        }
    }
    
    std::cout << std::string(80, '=') << std::endl;
}

void System::analyzeScheduleWorkload(const Schedule& schedule) const {
    std::cout << "\nWORKLOAD ANALYSIS FOR SCHEDULE " << schedule.getId() << std::endl;
    std::cout << std::string(50, '-') << std::endl;
    
    if (schedule.getLessons().empty()) {
        std::cout << "Schedule is empty - no workload to analyze." << std::endl;
        return;
    }
    
    // Group lessons by course - FIXED: Use non-const Lesson* to match System's lessons
    std::map<int, std::vector<Lesson*>> courseMap;  // FIXED: Changed from const Lesson* to Lesson*
    std::map<int, int> lecHours, tutHours, labHours;
    
    for (const auto& lesson : schedule.getLessons()) {
        int courseId = lesson->getCourseId();
        courseMap[courseId].push_back(lesson.get());  // Now this should work
        
        if (lesson->getType() == "Lecture") {
            lecHours[courseId] += lesson->getDuration();
        } else if (lesson->getType() == "Tutorial") {
            tutHours[courseId] += lesson->getDuration();
        } else if (lesson->getType() == "Lab") {
            labHours[courseId] += lesson->getDuration();
        }
    }
    
    // Calculate totals
    int totalWeeklyHours = 0;
    std::vector<std::pair<int, int>> courseHours; // pair<courseId, totalHours>
    
    std::cout << std::left << std::setw(8) << "Course" 
              << " - " << std::setw(35) << "Course Name" 
              << std::setw(6) << "Lec" 
              << std::setw(6) << "Tut" 
              << std::setw(6) << "Lab" 
              << std::setw(8) << "Total" 
              << "Credits" << std::endl;
    std::cout << std::string(75, '-') << std::endl;
    
    for (const auto& coursePair : courseMap) {
        int courseId = coursePair.first;
        std::string courseName = getCourseName(courseId);
        
        int lecH = lecHours[courseId];
        int tutH = tutHours[courseId];
        int labH = labHours[courseId];
        int totalH = lecH + tutH + labH;
        
        totalWeeklyHours += totalH;
        courseHours.push_back(std::make_pair(courseId, totalH));
        
        // Get course credits
        int credits = 0;
        for (const auto& course : courses) {
            if (course.getId() == courseId) {
                credits = course.getCredits();
                break;
            }
        }
        
        std::cout << std::left << std::setw(8) << courseId 
                  << " - " << (courseName.length() > 34 ? courseName.substr(0, 31) + "..." : courseName)
                  << std::setw(6) << lecH << "h"
                  << std::setw(6) << tutH << "h"
                  << std::setw(6) << labH << "h"
                  << std::setw(8) << totalH << "h"
                  << credits << std::endl;
    }
    
    std::cout << std::string(75, '=') << std::endl;
    
    // Summary statistics
    std::cout << "\nWORKLOAD SUMMARY:" << std::endl;
    std::cout << "• Total Weekly Hours: " << totalWeeklyHours << " hours" << std::endl;
    std::cout << "• Total Semester Hours (12 weeks): " << (totalWeeklyHours * 12) << " hours" << std::endl;
    std::cout << "• Number of Courses: " << courseMap.size() << " courses" << std::endl;
    std::cout << "• Average Hours per Course: " << std::fixed << std::setprecision(1) 
              << (courseMap.empty() ? 0.0 : (double)totalWeeklyHours / courseMap.size()) << " hours/week" << std::endl;
    
    // Course ranking by time commitment
    std::sort(courseHours.begin(), courseHours.end(), 
              [](const std::pair<int, int>& a, const std::pair<int, int>& b) {
                  return a.second > b.second; // Sort by hours descending
              });
    
    std::cout << "\nCOURSE RANKING BY TIME COMMITMENT:" << std::endl;
    for (size_t i = 0; i < courseHours.size(); ++i) {
        int courseId = courseHours[i].first;
        int hours = courseHours[i].second;
        std::string courseName = getCourseName(courseId);
        
        std::cout << "  " << (i + 1) << ". Course " << courseId << " (" 
                  << courseName << ") - " << hours << " hours/week" << std::endl;
    }
    
    // Workload assessment
    std::cout << "\nTEACHING WORKLOAD ASSESSMENT:" << std::endl;
    if (totalWeeklyHours <= 15) {
        std::cout << "  ? LIGHT WORKLOAD - Good balance for other activities" << std::endl;
    } else if (totalWeeklyHours <= 25) {
        std::cout << "  ? STANDARD WORKLOAD - Manageable with some effort" << std::endl;
    } else if (totalWeeklyHours <= 35) {
        std::cout << "  ?? HEAVY WORKLOAD - Challenging, plan accordingly" << std::endl;
    } else {
        std::cout << "  ? VERY HEAVY WORKLOAD - High risk of burnout!" << std::endl;
    }
}

void System::handleAnalyzeTeacherSchedules(const std::string& teacherName) {
    if (teacherName.empty()) {
        std::cout << "ERROR: Missing teacher name. Usage: AnalyzeTeacher <teacher_name>" << std::endl;
        std::cout << "Example: AnalyzeTeacher Dr. Smith" << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(80, '=') << std::endl;
    std::cout << "                 TEACHER SCHEDULE ANALYSIS" << std::endl;
    std::cout << std::string(80, '=') << std::endl;
    std::cout << "Analyzing schedule for: " << teacherName << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    // Find all lessons taught by this teacher - using System's lessons type
    std::vector<Lesson*> teacherLessons;
    
    for (Lesson* lesson : lessons) {
        if (lesson->getTeacherName() == teacherName) {
            teacherLessons.push_back(lesson);
        }
    }
    
    if (teacherLessons.empty()) {
        std::cout << "No lessons found for teacher: " << teacherName << std::endl;
        
        // Suggest similar teacher names
        std::cout << "\nDid you mean one of these teachers?" << std::endl;
        std::set<std::string> allTeachers;
        for (Lesson* lesson : lessons) {
            allTeachers.insert(lesson->getTeacherName());
        }
        
        size_t count = 0;
        for (const auto& teacher : allTeachers) {
            if (teacher.find(teacherName.substr(0, 3)) != std::string::npos || 
                teacherName.find( teacher.substr(0, 3)) != std::string::npos) {
                std::cout << "  • " << teacher << std::endl;
                count++;
                if (count >= 5) break;
            }
        }
        
        if (count == 0) {
            std::cout << "Available teachers:" << std::endl;
            count = 0;
            for (const auto& teacher : allTeachers) {
                std::cout << "  • " << teacher << std::endl;
                count++;
                if (count >= 10) {
                    std::cout << "  ... and " << (allTeachers.size() - count) << " more" << std::endl;
                    break;
                }
            }
        }
        return;
    }
    
    // Group lessons by type and course - FIXED: Use consistent Lesson* types
    std::vector<Lesson*> lectures, tutorials, labs;
    std::map<int, std::vector<Lesson*>> courseMap;  // FIXED: Changed from const Lesson* to Lesson*
    std::map<std::string, int> dayHours;
    
    for (Lesson* lesson : teacherLessons) {
        courseMap[lesson->getCourseId()].push_back(lesson);  // Fixed: removed .get() since lesson is already a raw pointer
        dayHours[lesson->getDay()] += lesson->getDuration();
        
        if (lesson->getType() == "Lecture") {
            lectures.push_back(lesson);
        } else if (lesson->getType() == "Tutorial") {
            tutorials.push_back(lesson);
        } else if (lesson->getType() == "Lab") {
            labs.push_back(lesson);
        }
    }
    
    // Display comprehensive overview
    std::cout << "\nTEACHING SCHEDULE OVERVIEW:" << std::endl;
    std::cout << std::string(60, '-') << std::endl;
    
    // Sort lessons by day and time for better display
    std::sort(teacherLessons.begin(), teacherLessons.end(), 
              [](Lesson* a, Lesson* b) {
                  std::vector<std::string> days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
                  auto dayA = std::find(days.begin(), days.end(), a->getDay()) - days.begin();
                  auto dayB = std::find(days.begin(), days.end(), b->getDay()) - days.begin();
                  if (dayA != dayB) return dayA < dayB;
                  return a->getStartHour() < b->getStartHour();
              });
    
    std::cout << std::left << std::setw(12) << "Day" 
              << std::setw(8) << "Time" 
              << std::setw(8) << "Type" 
              << std::setw(10) << "Course" 
              << std::setw(25) << "Course Name" 
              << std::setw(8) << "Group" 
              << "Location" << std::endl;
    std::cout << std::string(80, '-') << std::endl;
    
    for (Lesson* lesson : teacherLessons) {
        std::string courseName = getCourseName(lesson->getCourseId());
        std::string timeStr = (lesson->getStartHour() < 10 ? "0" : "") + std::to_string(lesson->getStartHour()) + ":00-" +
                             (lesson->getStartHour() + lesson->getDuration() < 10 ? "0" : "") + 
                             std::to_string(lesson->getStartHour() + lesson->getDuration()) + ":00";
        
        std::cout << std::left << std::setw(12) << lesson->getDay()
                  << std::setw(8) << timeStr
                  << std::setw(8) << lesson->getType()
                  << std::setw(10) << lesson->getCourseId()
                  << std::setw(25) << (courseName.length() > 24 ? courseName.substr(0, 21) + "..." : courseName)
                  << std::setw(8) << lesson->getGroupId()
                  << lesson->getBuilding() << " " << lesson->getRoom() << std::endl;
    }
    
    // Teaching statistics
    int totalHours = 0;
    for (Lesson* lesson : teacherLessons) {
        totalHours += lesson->getDuration();
    }
    
    std::cout << "\n" << std::string(60, '=') << std::endl;
    std::cout << "TEACHING STATISTICS:" << std::endl;
    std::cout << "• Total Lessons: " << teacherLessons.size() << " sessions" << std::endl;
    std::cout << "• Total Teaching Hours: " << totalHours << " hours/week" << std::endl;
    std::cout << "• Different Courses: " << courseMap.size() << " courses" << std::endl;
    std::cout << "• Lesson Distribution:" << std::endl;
    std::cout << "  - Lectures: " << lectures.size() << " sessions" << std::endl;
    std::cout << "  - Tutorials: " << tutorials.size() << " sessions" << std::endl;
    std::cout << "  - Labs: " << labs.size() << " sessions" << std::endl;
    
    // Course details
    std::cout << "\nCOURSES TAUGHT:" << std::endl;
    for (const auto& coursePair : courseMap) {
        int courseId = coursePair.first;
        const auto& courseLessons = coursePair.second;
        std::string courseName = getCourseName(courseId);
        
        int courseHours = 0;
        for (Lesson* lesson : courseLessons) {
            courseHours += lesson->getDuration();
        }
        
        std::cout << "• Course " << courseId << " - " << courseName << std::endl;
        std::cout << "  Sessions: " << courseLessons.size() << ", Hours: " << courseHours << "/week" << std::endl;
    }
    
    // Daily workload distribution
    std::cout << "\nDAILY WORKLOAD DISTRIBUTION:" << std::endl;
    std::vector<std::string> days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
    std::string busiestDay = "";
    int maxDayHours = 0;
    
    for (const auto& day : days) {
        int hours = dayHours[day];
        if (hours > 0) {
            std::cout << "• " << std::setw(10) << std::left << day << ": " << hours << " hours" << std::endl;
            if (hours > maxDayHours) {
                maxDayHours = hours;
                busiestDay = day;
            }
        }
    }
    
    if (!busiestDay.empty()) {
        std::cout << "• Busiest Day: " << busiestDay << " (" << maxDayHours << " hours)" << std::endl;
    }
    
    // Workload assessment
    std::cout << "\nTEACHING WORKLOAD ASSESSMENT:" << std::endl;
    if (totalHours <= 8) {
        std::cout << "  ? LIGHT TEACHING LOAD - Good work-life balance" << std::endl;
    } else if (totalHours <= 16) {
        std::cout << "  ? STANDARD TEACHING LOAD - Typical academic workload" << std::endl;
    } else if (totalHours <= 24) {
        std::cout << "  ?? HEAVY TEACHING LOAD - High commitment level" << std::endl;
    } else {
        std::cout << "  ? VERY HEAVY TEACHING LOAD - Consider workload balancing" << std::endl;
    }
}

void System::printWelcomeMessage() {
    std::cout << "\n" << std::string(50, '=') << std::endl;
    std::cout << " WELCOME TO COURSE MANAGEMENT SYSTEM " << std::endl;
    std::cout << std::string(50, '=') << std::endl;
    std::cout << "? AUTO-SAVE ENABLED: All changes saved automatically" << std::endl;
    std::cout << "??  ENHANCED CONFLICT DETECTION: Ask before adding conflicts" << std::endl;
    std::cout << "Type 'Help' for commands or 'Exit' to quit." << std::endl;
}

void System::handleRemoveLesson(const std::string& courseId_str, const std::string& groupId_str) {
    try {
        int courseId = std::stoi(courseId_str);
        int groupId = std::stoi(groupId_str);
        
        auto it = std::remove_if(lessons.begin(), lessons.end(), 
            [courseId, groupId](const Lesson* lesson){ 
                return lesson->getCourseId() == courseId && lesson->getGroupId() == groupId; 
            });

        if (it != lessons.end()) {
            // Delete the lesson objects before removing from vector
            for (auto iter = it; iter != lessons.end(); ++iter) {
                delete *iter;
            }
            lessons.erase(it, lessons.end());
            
            // Auto-save
            saveLessons();
            
            std::cout << "SUCCESS: Removed lesson for Course " << courseId 
                      << ", Group " << groupId << " (Auto-saved)" << std::endl;
        } else {
            std::cout << "ERROR: Lesson with Course ID " << courseId 
                      << " and Group ID " << groupId << " not found." << std::endl;
        }
    } catch (...) {
        std::cout << "ERROR: Invalid ID format." << std::endl;
    }
}

void System::handleHelp() {
	system("cls"); 
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "                    AVAILABLE COMMANDS                    " << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << std::left;
    std::cout << std::setw(35) << "PrintCourse <course_id>" << " - Print course details" << std::endl;
    std::cout << std::setw(35) << "PrintCourses" << " - Print first 10 courses" << std::endl;
    std::cout << std::setw(35) << "More" << " - Print next 10 courses" << std::endl;
    std::cout << std::setw(35) << "PrintSchedule <schedule_id>" << " - Print specific schedule" << std::endl;
    std::cout << std::setw(35) << "PrintSchedules" << " - Print all schedules" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::cout << "                   SCHEDULE MANAGEMENT                    " << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::cout << std::setw(35) << "AddSchedule" << " - Add new empty schedule" << std::endl;
    std::cout << std::setw(35) << "RmSchedule <schedule_id>" << " - Remove schedule" << std::endl;
    std::cout << std::setw(35) << "Add <sched> <course> <group>" << " - Add lesson to schedule (?? LESSON TYPE MENU)" << std::endl;
    std::cout << std::setw(35) << "Rm <sched> <course> <group>" << " - Remove lesson from schedule (??? REMOVAL MENU)" << std::endl;
    std::cout << std::setw(35) << "CheckConflicts <schedule_id>" << " - Check conflicts in schedule" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::cout << "                   DATA MANAGEMENT                       " << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::cout << std::setw(35) << "AddCourse" << " - Add new course (Auto-save)" << std::endl;
    std::cout << std::setw(35) << "RmCourse <course_id>" << " - Remove course (Auto-save)" << std::endl;
    std::cout << std::setw(35) << "AddLesson" << " - Add new lesson (Auto-save)" << std::endl;
    std::cout << std::setw(35) << "RmLesson <course> <group>" << " - Remove lesson (Auto-save)" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::cout << "                      ANALYSIS COMMANDS                   " << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::cout << std::setw(35) << "FindTimeConflicts" << " - Find all time conflicts" << std::endl;
    std::cout << std::setw(35) << "AnalyzeWorkload <schedule_id>" << " - Analyze course workload" << std::endl;
    std::cout << std::setw(35) << "AnalyzeWorkload all" << " - Analyze all schedules" << std::endl;
    std::cout << std::setw(35) << "AnalyzeTeacher <teacher_name>" << " - Analyze teacher schedule" << std::endl;
    std::cout << std::string(70, '-') << std::endl;
    std::cout << std::setw(35) << "Clear" << " - Clear screen" << std::endl;
    std::cout << std::setw(35) << "Help" << " - Show this help" << std::endl;
    std::cout << std::setw(35) << "Exit" << " - Save and exit" << std::endl;
    std::cout << "\n*** ENHANCED LESSON SELECTION ***" << std::endl;
    std::cout << "?? When adding lessons with 'Add <sched> <course> <group>':" << std::endl;
    std::cout << "   • System shows available lesson types (LEC, LAB, TUT)" << std::endl;
    std::cout << "   • Interactive menu to choose which type to add" << std::endl;
    std::cout << "   • Detailed lesson information for each option" << std::endl;
    std::cout << "   • Option to cancel if you change your mind" << std::endl;
    std::cout << "\n*** ENHANCED LESSON REMOVAL ***" << std::endl;
    std::cout << "???  When removing lessons with 'Rm <sched> <course> <group>':" << std::endl;
    std::cout << "   • System shows lessons currently in the schedule" << std::endl;
    std::cout << "   • Interactive menu to choose which type to remove" << std::endl;
    std::cout << "   • Option to remove ALL lesson types at once" << std::endl;
    std::cout << "   • Detailed lesson information and confirmation" << std::endl;
    std::cout << "   • Option to cancel if you change your mind" << std::endl;
    std::cout << "\n*** ENHANCED CONFLICT DETECTION ***" << std::endl;
    std::cout << "? When adding conflicting lessons, you'll get:" << std::endl;
    std::cout << "   • Detailed colored conflict warnings" << std::endl;
    std::cout << "   • Option to force add anyway [Y/N]" << std::endl;
    std::cout << "   • All add/remove operations auto-save data" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
}

