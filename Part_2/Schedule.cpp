#include "Schedule.h"
#include <algorithm>
#include <iostream>
#include <iomanip>
#include <string>
#include <sstream>
#include <fstream>
#include "Lecture.h"
#include "Tutorial.h"
#include "Lab.h"

// Default constructor
Schedule::Schedule() : id(0), studentId(0), courseId(0), semester(""), year(0) {}

// Parameterized constructor (single parameter)
Schedule::Schedule(int scheduleId) : id(scheduleId), studentId(0), courseId(0), semester(""), year(0) {}

// Comprehensive parameterized constructor
Schedule::Schedule(int scheduleId, int studId, int crsId, const std::string& sem, int yr) 
    : id(scheduleId), studentId(studId), courseId(crsId), semester(sem), year(yr) {}

// Copy constructor
Schedule::Schedule(const Schedule& other) 
    : id(other.id), studentId(other.studentId), courseId(other.courseId), 
      semester(other.semester), year(other.year) {
    for (const auto& lesson : other.lessons) {
        lessons.push_back(lesson->clone());
    }
}

// Assignment operator
Schedule& Schedule::operator=(const Schedule& other) {
    if (this != &other) {
        id = other.id;
        studentId = other.studentId;
        courseId = other.courseId;
        semester = other.semester;
        year = other.year;
        lessons.clear();
        for (const auto& lesson : other.lessons) {
            lessons.push_back(lesson->clone());
        }
    }
    return *this;
}

// Getter and setter for ID
int Schedule::getId() const noexcept {
    return id;
}

void Schedule::setId(int newId) {
    id = newId;
}

// Getter and setter for Student ID
int Schedule::getStudentId() const noexcept {
    return studentId;
}

void Schedule::setStudentId(int newStudentId) {
    studentId = newStudentId;
}

// Getter and setter for Course ID
int Schedule::getCourseId() const noexcept {
    return courseId;
}

void Schedule::setCourseId(int newCourseId) {
    courseId = newCourseId;
}

// Getter and setter for Semester
const std::string& Schedule::getSemester() const noexcept {
    return semester;
}

void Schedule::setSemester(const std::string& newSemester) {
    semester = newSemester;
}

// Getter and setter for Year
int Schedule::getYear() const noexcept {
    return year;
}

void Schedule::setYear(int newYear) {
    year = newYear;
}

// Smart pointer version - preferred
void Schedule::addLesson(std::unique_ptr<Lesson> lesson) {
    // Check for conflicts
    for (const auto& existingLesson : lessons) {
        if (existingLesson->getDay() == lesson->getDay()) {
            int start1 = existingLesson->getStartHour();
            int end1 = start1 + existingLesson->getDuration();
            int start2 = lesson->getStartHour();
            int end2 = start2 + lesson->getDuration();

            if ((start1 < end2) && (start2 < end1)) {
                std::cout << "\n" << std::string(50, '=') << std::endl;
                std::cout << "            *** CONFLICT DETECTED ***" << std::endl;
                std::cout << std::string(50, '=') << std::endl;
                std::cout << "Cannot add lesson for Course " << lesson->getCourseId() 
                         << " (Group " << lesson->getGroupId() << ")" << std::endl;
                std::cout << "Conflicts with existing Course " << existingLesson->getCourseId() 
                         << " (Group " << existingLesson->getGroupId() << ")" << std::endl;
                std::cout << "\nTime conflict on " << lesson->getDay() << ":" << std::endl;
                std::cout << "  Existing lesson: " << existingLesson->getTimeRange() << std::endl;
                std::cout << "  New lesson:      " << lesson->getTimeRange() << std::endl;
                std::cout << "\nLESSON NOT ADDED due to scheduling conflict." << std::endl;
                std::cout << std::string(50, '=') << std::endl;
                return;
            }
        }
    }
    
    lessons.push_back(std::move(lesson));
    std::cout << "SUCCESS: Lesson added for Course " << lessons.back()->getCourseId() 
             << " (Group " << lessons.back()->getGroupId() << ") on " << lessons.back()->getDay() 
             << " at " << lessons.back()->getTimeRange() << std::endl;
}

// Force add version with smart pointer
void Schedule::addLessonForce(std::unique_ptr<Lesson> lesson) {
    lessons.push_back(std::move(lesson));
}

// Backward compatibility versions - convert raw pointer to smart pointer
void Schedule::addLesson(Lesson* lesson) {
    if (lesson) {
        addLesson(lesson->clone());
    }
}

void Schedule::addLessonForce(Lesson* lesson) {
    if (lesson) {
        addLessonForce(lesson->clone());
    }
}

// Remove lesson by course, group, and type (specific removal)
void Schedule::removeLesson(int courseId, int groupId, const std::string& type) {
    bool found = false;
    
    auto it = std::remove_if(lessons.begin(), lessons.end(),
        [courseId, groupId, &type](const std::unique_ptr<Lesson>& lesson) {
            return lesson->getCourseId() == courseId && 
                   lesson->getGroupId() == groupId && 
                   lesson->getType() == type;
        });
    
    if (it != lessons.end()) {
        found = true;
        lessons.erase(it, lessons.end());
    }

    if (found) {
        std::cout << "SUCCESS: " << type << " lesson removed for Course " << courseId 
                  << ", Group " << groupId << std::endl;
    } else {
        std::cout << "ERROR: " << type << " lesson not found for Course " << courseId 
                  << ", Group " << groupId << std::endl;
    }
}

// Remove lesson
void Schedule::removeLesson(int courseId, int groupId) {
    bool found = false;
    
    auto it = std::remove_if(lessons.begin(), lessons.end(),
        [courseId, groupId](const std::unique_ptr<Lesson>& lesson) {
            return lesson->getCourseId() == courseId && lesson->getGroupId() == groupId;
        });
    
    if (it != lessons.end()) {
        found = true;
        lessons.erase(it, lessons.end());
    }

    if (found) {
        std::cout << "Lesson(s) removed successfully." << std::endl;
    } else {
        std::cout << "Lesson not found." << std::endl;
    }
}

// Getters for lessons
std::vector<std::unique_ptr<Lesson>>& Schedule::getLessons() {
    return lessons;
}

const std::vector<std::unique_ptr<Lesson>>& Schedule::getLessons() const {
    return lessons;
}

// Check if lesson conflicts with existing lessons
bool Schedule::hasConflict(const Lesson* newLesson) const {
    for (const auto& lesson : lessons) {
        if (lesson->conflictsWith(*newLesson)) {
            return true;
        }
    }
    return false;
}

// Calculate total hours
int Schedule::totalHours() const {
    int total = 0;
    for (const auto& lesson : lessons) {
        total += lesson->getDuration();
    }
    return total;
}

// Print schedule - Updated to meet all requirements with detailed lesson summary
void Schedule::printSchedule() const {
	if (lessons.empty()) {
		std::cout << "Schedule is empty." << std::endl;
		return;
	}

	// ANSI Color codes for different lesson types
	const std::string COLOR_RESET = "\033[0m";
	const std::string COLOR_LECTURE = "\033[1;34m";     // Bright Blue for Lectures
	const std::string COLOR_TUTORIAL = "\033[1;32m";    // Bright Green for Tutorials
	const std::string COLOR_LAB = "\033[1;33m";         // Bright Yellow for Labs
	const std::string COLOR_CONFLICT = "\033[1;31m";    // Bright Red for Conflicts
	const std::string COLOR_HEADER = "\033[1;36m";      // Bright Cyan for Headers

	// Define days of the week
	std::vector<std::string> days = {"Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday"};
	
	// Find the time range (earliest to latest)
	int earliestHour = 24, latestHour = 0;
	for (const auto& lesson : lessons) {
		int startHour = lesson->getStartHour();
		int endHour = startHour + lesson->getDuration();
		if (startHour < earliestHour) earliestHour = startHour;
		if (endHour > latestHour) latestHour = endHour;
	}
	
	// Ensure reasonable bounds (typical academic day)
	if (earliestHour > 8) earliestHour = 8;
	if (latestHour < 18) latestHour = 18;

	// Print schedule header with statistics
	std::cout << "\n" << std::string(150, '=') << std::endl;
	std::cout << COLOR_HEADER << "                                    WEEKLY TIMETABLE - SCHEDULE " << id << COLOR_RESET << std::endl;
	std::cout << std::string(150, '=') << std::endl;

	// Calculate and display statistics
	int lectureCount = 0, tutorialCount = 0, labCount = 0;
	for (const auto& lesson : lessons) {
		if (lesson->getType() == "Lecture") lectureCount++;
		else if (lesson->getType() == "Tutorial") tutorialCount++;
		else if (lesson->getType() == "Lab") labCount++;
	}

	std::cout << "  " << COLOR_LECTURE << "Lectures: " << std::setw(3) << lectureCount << COLOR_RESET
		 << "  |  " << COLOR_TUTORIAL << "Tutorials: " << std::setw(3) << tutorialCount << COLOR_RESET
		 << "  |  " << COLOR_LAB << "Labs: " << std::setw(3) << labCount << COLOR_RESET
		 << "  |  Total Hours: " << std::setw(3) << totalHours() << std::endl;
	std::cout << std::string(150, '-') << std::endl;

	// Print legend with colored symbols/markers for each type
	std::cout << "  " << COLOR_LECTURE << "[LEC] Lectures" << COLOR_RESET 
		 << "   " << COLOR_TUTORIAL << "[TUT] Tutorials" << COLOR_RESET
		 << "   " << COLOR_LAB << "[LAB] Labs" << COLOR_RESET
		 << "   " << COLOR_CONFLICT << "[!!!] Conflicts" << COLOR_RESET << std::endl;
	std::cout << std::string(150, '=') << std::endl;

	// Updated column widths to accommodate more information
	const int timeColWidth = 8;
	const int dayColWidth = 20;  // Increased width to fit course number, lesson type, and classroom

	// Print day headers with color
	std::cout << std::left << COLOR_HEADER << std::setw(timeColWidth) << "Time" << COLOR_RESET;
	for (const std::string& day : days) {
		std::cout << "|" << COLOR_HEADER << std::setw(dayColWidth) << (" " + day) << COLOR_RESET;
	}
	std::cout << "|" << std::endl;

	// Print separator line under headers
	std::cout << std::string(timeColWidth, '-') << "+";
	for (int i = 0; i < 7; i++) {
		std::cout << std::string(dayColWidth, '-');
		if (i < 6) std::cout << "+";
	}
	std::cout << "+" << std::endl;

	// Print each hour row
	for (int hour = earliestHour; hour < latestHour; hour++) {
		std::string timeStr = (hour < 10 ? "0" : "") + std::to_string(hour) + ":00";
		
		std::cout << std::setw(timeColWidth) << timeStr;
		
		for (const std::string& day : days) {
			std::cout << "|";
			
			// Find lessons that occur on this day and time
			std::vector<const Lesson*> lessonsAtTime;
			for (const auto& lesson : lessons) {
				if (lesson->getDay() == day && 
					lesson->getStartHour() <= hour && 
					hour < lesson->getStartHour() + lesson->getDuration()) {
					lessonsAtTime.push_back(lesson.get());
				}
			}
			
			if (!lessonsAtTime.empty()) {
				if (lessonsAtTime.size() > 1) {
					// Handle conflicts - display all conflicting courses
					std::string conflictInfo = "";
					for (size_t i = 0; i < lessonsAtTime.size(); ++i) {
						const Lesson* lesson = lessonsAtTime[i];
						if (i > 0) conflictInfo += "/";
						
						// Format: CourseNumber-Type-Room
						std::string lessonType = lesson->getType().substr(0, 3); // Lecture->Lec, Tutorial->Tut, Lab->Lab
						conflictInfo += std::to_string(lesson->getCourseId()) + "-" + lessonType + "-" + lesson->getRoom();
					}
					
					// Truncate if too long for cell width
					if (conflictInfo.length() > dayColWidth - 2) {
						conflictInfo = conflictInfo.substr(0, dayColWidth - 5) + "...";
					}
					
					std::cout << " " << COLOR_CONFLICT << std::left << std::setw(dayColWidth - 1) << conflictInfo << COLOR_RESET;
				} else {
					const Lesson* lesson = lessonsAtTime[0];
					std::string lessonColor = (lesson->getType() == "Lecture") ? COLOR_LECTURE :
											 (lesson->getType() == "Tutorial") ? COLOR_TUTORIAL : COLOR_LAB;
					
					// Format: CourseNumber-LessonType-Classroom (meets all requirements)
					std::string lessonType = lesson->getType().substr(0, 3); // Lecture->Lec, Tutorial->Tut, Lab->Lab
					std::string lessonInfo = std::to_string(lesson->getCourseId()) + "-" + lessonType + "-" + lesson->getRoom();
					
					// Truncate if too long for cell width
					if (lessonInfo.length() > dayColWidth - 2) {
						lessonInfo = lessonInfo.substr(0, dayColWidth - 5) + "...";
					}
					
					std::cout << " " << lessonColor << std::left << std::setw(dayColWidth - 1) << lessonInfo << COLOR_RESET;
				}
			} else {
				std::cout << " " << std::setw(dayColWidth - 1) << "";
			}
		}
		std::cout << "|" << std::endl;
	}
	
	// Print bottom border
	std::cout << std::string(timeColWidth, '-') << "+";
	for (int i = 0; i < 7; i++) {
		std::cout << std::string(dayColWidth, '-');
		if (i < 6) std::cout << "+";
	}
	std::cout << "+" << std::endl;
	std::cout << std::string(150, '=') << std::endl;

	// ===============================
	// DETAILED LESSON SUMMARY SECTION
	// ===============================
	
	std::cout << COLOR_HEADER << "DETAILED LESSON SUMMARY:" << COLOR_RESET << std::endl;
	std::cout << std::string(150, '=') << std::endl;
	
	// Collect lessons by type and sort by course ID and group
	std::vector<const Lesson*> lectures, tutorials, labs;
	for (const auto& lesson : lessons) {
		if (lesson->getType() == "Lecture") {
			lectures.push_back(lesson.get());
		} else if (lesson->getType() == "Tutorial") {
			tutorials.push_back(lesson.get());
		} else if (lesson->getType() == "Lab") {
			labs.push_back(lesson.get());
		}
	}
	
	// Sort lessons by course ID and group for consistent display
	auto sortLessons = [](const Lesson* a, const Lesson* b) {
		if (a->getCourseId() != b->getCourseId()) return a->getCourseId() < b->getCourseId();
		return a->getGroupId() < b->getGroupId();
	};
	
	std::sort(lectures.begin(), lectures.end(), sortLessons);
	std::sort(tutorials.begin(), tutorials.end(), sortLessons);
	std::sort(labs.begin(), labs.end(), sortLessons);
	
	// Display Lectures
	if (!lectures.empty()) {
		std::cout << COLOR_LECTURE << "[LEC] LECTURES (" << lectures.size() << " total):" << COLOR_RESET << std::endl;
		for (const auto& lesson : lectures) {
			int startHour = lesson->getStartHour();
			int endHour = startHour + lesson->getDuration();
			
			std::cout << "  + Course " << std::setw(3) << lesson->getCourseId() 
					  << " Group " << std::setw(2) << lesson->getGroupId()
					  << " | " << std::setw(9) << std::left << lesson->getDay() 
					  << " " << std::setw(2) << std::right << (startHour < 10 ? "0" : "") << startHour 
					  << ":00-" << std::setw(2) << (endHour < 10 ? "0" : "") << endHour << ":00"
					  << " | " << std::setw(20) << std::left << lesson->getTeacherName()
					  << " | " << std::setw(8) << lesson->getRoom() << std::endl;
		}
		std::cout << std::endl;
	}
	
	// Display Tutorials
	if (!tutorials.empty()) {
		std::cout << COLOR_TUTORIAL << "[TUT] TUTORIALS (" << tutorials.size() << " total):" << COLOR_RESET << std::endl;
		for (const auto& lesson : tutorials) {
			int startHour = lesson->getStartHour();
			int endHour = startHour + lesson->getDuration();
			
			std::cout << "  + Course " << std::setw(3) << lesson->getCourseId() 
					  << " Group " << std::setw(2) << lesson->getGroupId()
					  << " | " << std::setw(9) << std::left << lesson->getDay() 
					  << " " << std::setw(2) << std::right << (startHour < 10 ? "0" : "") << startHour 
					  << ":00-" << std::setw(2) << (endHour < 10 ? "0" : "") << endHour << ":00"
					  << " | " << std::setw(20) << std::left << lesson->getTeacherName()
					  << " | " << std::setw(8) << lesson->getRoom() << std::endl;
		}
		std::cout << std::endl;
	}
	
	// Display Labs
	if (!labs.empty()) {
		std::cout << COLOR_LAB << "[LAB] LABS (" << labs.size() << " total):" << COLOR_RESET << std::endl;
		for (const auto& lesson : labs) {
			int startHour = lesson->getStartHour();
			int endHour = startHour + lesson->getDuration();
			
			std::cout << "  + Course " << std::setw(3) << lesson->getCourseId() 
					  << " Group " << std::setw(2) << lesson->getGroupId()
					  << " | " << std::setw(9) << std::left << lesson->getDay() 
					  << " " << std::setw(2) << std::right << (startHour < 10 ? "0" : "") << startHour 
					  << ":00-" << std::setw(2) << (endHour < 10 ? "0" : "") << endHour << ":00"
					  << " | " << std::setw(20) << std::left << lesson->getTeacherName()
					  << " | " << std::setw(8) << lesson->getRoom() << std::endl;
		}
		std::cout << std::endl;
	}
	
	std::cout << std::string(150, '=') << std::endl;
}

// Print conflicts analysis
void Schedule::printConflicts() const {
    std::vector<std::pair<int, int>> conflictPairs;
    bool hasAnyConflicts = false;
    
    // Check all pairs of lessons for conflicts
    for (size_t i = 0; i < lessons.size(); i++) {
        for (size_t j = i + 1; j < lessons.size(); j++) {
            if (lessons[i]->conflictsWith(*lessons[j])) {
                conflictPairs.push_back(std::make_pair(static_cast<int>(i), static_cast<int>(j)));
                hasAnyConflicts = true;
            }
        }
    }
    
    if (!hasAnyConflicts) {
        std::cout << "\n--- NO CONFLICTS DETECTED ---" << std::endl;
        std::cout << "All lessons in this schedule are properly scheduled without time conflicts." << std::endl;
        return;
    }
    
    std::cout << "\n" << std::string(70, '=') << std::endl;
    std::cout << "                    *** SCHEDULE CONFLICTS ***" << std::endl;
    std::cout << std::string(70, '=') << std::endl;
    std::cout << "Found " << conflictPairs.size() << " conflict(s) in this schedule:" << std::endl;
    
    for (size_t k = 0; k < conflictPairs.size(); k++) {
        int i = conflictPairs[k].first;
        int j = conflictPairs[k].second;
        
        std::cout << "\nCONFLICT #" << (k + 1) << ":" << std::endl;
        std::cout << "  Course " << lessons[i]->getCourseId() << " (Group " << lessons[i]->getGroupId() 
                 << ") vs Course " << lessons[j]->getCourseId() << " (Group " << lessons[j]->getGroupId() << ")" << std::endl;
        std::cout << "  Both scheduled on " << lessons[i]->getDay() << std::endl;
        std::cout << "    Course " << lessons[i]->getCourseId() << ": " << lessons[i]->getTimeRange() << std::endl;
        std::cout << "    Course " << lessons[j]->getCourseId() << ": " << lessons[j]->getTimeRange() << std::endl;
    }
    
    std::cout << "\nRECOMMENDATION: Remove one lesson from each conflicting pair or choose different groups." << std::endl;
    std::cout << std::string(70, '=') << std::endl;
}

// Save to file (simplified for smart pointers)
void Schedule::saveToFile(const std::string& filename) const {
    std::ofstream out(filename);
    if (!out) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    for (const auto& lesson : lessons) {
        out << lesson->getType() << ","
            << lesson->getCourseId() << ","
            << lesson->getGroupId() << ","
            << lesson->getTeacherName() << ","
            << lesson->getDay() << ","
            << lesson->getStartHour() << ","
            << lesson->getDuration() << ","
            << lesson->getBuilding() << ","
            << lesson->getRoom() << std::endl;
    }

    out.close();
    std::cout << "Schedule saved to " << filename << " successfully." << std::endl;
}

// Load from file (updated for smart pointers)
void Schedule::loadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (!in) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    std::string line;
    while (std::getline(in, line)) {
        std::stringstream ss(line);
        std::string type, teacherName, day, building, room;
        int courseId, groupId, startHour, duration;

        std::getline(ss, type, ',');
        ss >> courseId; ss.ignore();
        ss >> groupId; ss.ignore();
        std::getline(ss, teacherName, ',');
        std::getline(ss, day, ',');
        ss >> startHour; ss.ignore();
        ss >> duration; ss.ignore();
        std::getline(ss, building, ',');
        std::getline(ss, room, ',');

        try {
            std::unique_ptr<Lesson> lesson;
            int endHour = startHour + duration;
            
            if (type == "Lecture") {
                lesson = std::make_unique<Lecture>(type, courseId, day, startHour, endHour, room, teacherName, groupId);
            } else if (type == "Tutorial") {
                lesson = std::make_unique<Tutorial>(type, courseId, day, startHour, endHour, room, teacherName, groupId);
            } else if (type == "Lab") {
                lesson = std::make_unique<Lab>(type, courseId, day, startHour, endHour, room, teacherName, groupId);
            }
            
            if (lesson) {
                lessons.push_back(std::move(lesson));
            }
        } catch (const std::exception& e) {
            std::cerr << "Error creating lesson: " << e.what() << std::endl;
        }
    }

    in.close();
    std::cout << "Schedule loaded from " << filename << " successfully." << std::endl;
}

// Clear all lessons from schedule
void Schedule::clearLessons() {
    lessons.clear();
}


































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































































