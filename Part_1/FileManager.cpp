#include "FileManager.h"
#include "Lecture.h"
#include "Tutorial.h"
#include "Lab.h"
#include "MenuFunctions.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
using namespace std;

/**
 * Helper function to write course data to output stream
 * Reduces code duplication in save functions
 *  file Output file stream to write to
 *  courses Vector of courses to write
 */
void writeCourseData(ofstream& file, const vector<Course>& courses) {
    for (const Course& c : courses) {
        file << c.getId() << ','
            << c.getName() << ','
            << c.getCredits() << ','
            << c.getMoedA() << ','
            << c.getMoedB() << ','
            << c.getLecturer() << ','
            << c.getSemester() << '\n';
    }
}



// ----------------------------------------------------------
// reading courses from CSV file
// ----------------------------------------------------------
void loadCourses(vector<Course>& courses) {
    try {
		ifstream inFile("courses.csv"); // ifstream to read from courses.csv
        if (!inFile.is_open()) {
            //throw runtime_error("Failed to open courses.csv");
            cout << "Warning: courses.csv not found. Starting with empty course list." << endl;
            return;
        }

        string line;
        getline(inFile, line); // skip header

        while (getline(inFile, line)) {
            stringstream ss(line);
            string idStr, name, creditsStr, moedA, moedB, lecturer, semester;


			getline(ss, idStr, ','); // Read until the first comma 
			getline(ss, name, ','); // Read until the second comma
			getline(ss, creditsStr, ','); // ss is a stringstream object
            getline(ss, moedA, ',');
            getline(ss, moedB, ',');
            getline(ss, lecturer, ',');
            getline(ss, semester, ',');

            // Add validation before calling stoi()
            if (idStr.empty() || creditsStr.empty()) {
                cerr << "Warning: Invalid data in line: " << line << endl;
                continue;
            }

			int id = stoi(idStr); // Convert string to int ==> why ? because id is an integer
            int credits = stoi(creditsStr); // Convert string to int

            courses.emplace_back(id, name, credits, moedA, moedB, lecturer, semester);
        }

        inFile.close();
        cout << "Successfully loaded " << courses.size() << " courses from courses.csv" << endl;

    }
	catch (const exception& e) { // exception  represents an error or exceptional condition that occurs during program execution.
        cerr << "Error in loadCourses: " << e.what() << endl;
    }
}

// ----------------------------------------------------------
// saving courses to CSV file
// ----------------------------------------------------------
 
void saveCourses(const vector<Course>& courses) {
    try {
        // First, try to open the original file directly
		ofstream outFile("courses.csv"); // ofstream to write to courses.csv
        if (outFile.is_open()) {
            // Direct write succeeded
            outFile << "course_id,course_name,credits,exam_date_a,exam_date_b,responsible_lecturer,semester\n";


            writeCourseData(outFile, courses);

            outFile.close();
            cout << "Courses saved successfully to courses.csv" << endl;
            return;
        }

        // If direct write failed, try the temp file approach
        string tempFileName = "courses_temp.csv";
        ofstream tempFile(tempFileName);
        if (!tempFile.is_open()) {
            cerr << "Failed to create temporary file for saving courses" << endl;
            return;
        }

        tempFile << "course_id,course_name,credits,exam_date_a,exam_date_b,responsible_lecturer,semester\n";


        writeCourseData(tempFile, courses);
        tempFile.close();

        // Try to remove the original file first, then rename
        remove("courses.csv");
        if (rename(tempFileName.c_str(), "courses.csv") == 0) {
            cout << "Courses saved successfully to courses.csv" << endl;
        }
        else {
			cerr << "Could not replace courses.csv - file may be in use by another program" << endl; // cerr: it is used to output error messages
            cerr << "Your data has been saved in " << tempFileName << endl;
            cerr << "Please close any programs that have courses.csv open and try option 5 (Save all data) again" << endl;
        }

    }
    catch (const exception& e) {
        cerr << "Error in saveCourses: " << e.what() << endl;
    }
}
// ----------------------------------------------------------
// read (Schedule1.csv ... Schedule6.csv)
// ----------------------------------------------------------
void loadSchedules(vector<Schedule*>& schedules) {
    try {
        ifstream schedulesFile("schedules.csv");
        if (!schedulesFile.is_open()) {
            cout << "Warning: schedules.csv not found. Starting with empty schedule list." << endl;
            return;
        }

        string line;
        bool isFirstLine = true;

        while (getline(schedulesFile, line)) {
            if (line.empty()) continue; // Skip empty lines

            // Remove whitespace
            line.erase(0, line.find_first_not_of(" \t\r\n"));
            line.erase(line.find_last_not_of(" \t\r\n") + 1);

            if (line.empty()) continue;

            // Skip header line if it's the first line and contains text
            if (isFirstLine) {
                isFirstLine = false;
                if (line.find("schedule") != string::npos ||
                    line.find("id") != string::npos ||
                    !isdigit(line[0])) {
                    continue; // Skip header and move to next line
                }
            }

            // Process schedule ID
            try {
				int id = stoi(line);// Convert string to int
                Schedule* sched = new Schedule(id);
                schedules.push_back(sched);

                // Load individual schedule file
                loadIndividualSchedule(sched, id);

            }
            catch (const invalid_argument& e) {
                //cerr << "Warning: Invalid schedule ID: " << line << endl;
                cerr << "Warning: Invalid schedule ID: " << line << " (" << e.what() << ")" << endl;

            }
            catch (const out_of_range& e) {
                //cerr << "Warning: Schedule ID out of range: " << line << endl;
                cerr << "Warning: Schedule ID out of range: " << line << " (" << e.what() << ")" << endl;

            }
        }

        schedulesFile.close();
        cout << "Successfully loaded " << schedules.size() << " schedules" << endl;

    }
    catch (const exception& e) {
        cerr << "Error in loadSchedules: " << e.what() << endl;
    }
}


//  function to load individual schedule
void loadIndividualSchedule(Schedule* sched, int id) {
    string filename = "Schedule" + to_string(id) + ".csv";
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Warning: Cannot open " << filename << endl;
        return;
    }

    string line;
    getline(inFile, line); // skip header

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string courseIdStr, day, startTimeStr, endTimeStr, room, type, groupStr;

        // Change from tab-separated to comma-separated and add group_number
		getline(ss, courseIdStr, ','); // Read until the first comma
		getline(ss, day, ','); // ss? is a stringstream object
        getline(ss, startTimeStr, ',');
        getline(ss, endTimeStr, ',');
        getline(ss, room, ',');
        getline(ss, type, ',');
        getline(ss, groupStr, ',');

        try {
            if (courseIdStr.empty() || startTimeStr.empty() || endTimeStr.empty()) {
                cerr << "Warning: Invalid lesson data in " << filename << ": " << line << endl;
                continue;
            }

            int courseId = stoi(courseIdStr); // Convert course ID from string to int

            // Parse time format using helper function to avoid duplication
            int start = parseTimeToHour(startTimeStr);
            int end = parseTimeToHour(endTimeStr);

            // Get group number or use default value
            int groupNumber = 1;  // default value
            if (!groupStr.empty()) {
                groupNumber = stoi(groupStr);
            }

            // Use existing values from CSV (not dummy values)
            string dummyTeacher = "Unknown";
            string classroom = room;

            Lesson* l = nullptr;
            if (type == "Lecture")
                l = new Lecture(type, courseId, day, start, end, classroom, dummyTeacher, groupNumber);
            else if (type == "Tutorial")
                l = new Tutorial(type, courseId, day, start, end, classroom, dummyTeacher, groupNumber);
            else if (type == "Lab")
                l = new Lab(type, courseId, day, start, end, classroom, dummyTeacher, groupNumber);

            if (l) {
                sched->addLesson(l);
            }
        }
        catch (const exception& e) {
            //cerr << "Warning: Error parsing lesson in " << filename << ": " << line << endl;
            cerr << "Warning: Error parsing lesson in " << filename << ": " << line << " (" << e.what() << ")" << endl;

        }
    }

    inFile.close();
}



// ----------------------------------------------------------
// save (Schedule1.csv עד Schedule6.csv)
// ----------------------------------------------------------

void saveSchedules(const vector<Schedule*>& schedules) {
	try { // try -catch block to handle exceptions
		ofstream schedulesFile("schedules.csv"); // Open schedules.csv for writing  
        if (!schedulesFile.is_open()) {
            // throw an exception if the file cannot be opened
			throw runtime_error("Failed to open schedules.csv for writing"); 
        }
		//loop of all schedules in the vector 
        for (const Schedule* s : schedules) {
            int id = s->getId();
			schedulesFile << id << '\n'; // Write schedule ID to schedules.csv

			// Open individual schedule file for writing
            string filename = "Schedule" + to_string(id) + ".csv";
            ofstream outFile(filename);
            if (!outFile.is_open()) {
                cerr << "Failed to open " << filename << " for writing" << endl;
                continue;
            }

            // Change header to include group_number
            outFile << "course_id,day,start_time,end_time,room,type,group_number\n";
            const vector<Lesson*>& lessons = s->getLessons();
            for (Lesson* l : lessons) {
                if (l == nullptr) {
                    cerr << "Warning: Encountered null Lesson pointer in saveSchedules, skipping." << endl;
                    continue;
                }
                int start = l->getStartHour();
                int end = l->getEndHour();
                string type;

				// dynamic_cast to determine lesson type
                if (dynamic_cast<Lecture*>(l)) type = "Lecture";
                else if (dynamic_cast<Tutorial*>(l)) type = "Tutorial";
                else if (dynamic_cast<Lab*>(l)) type = "Lab";
                else type = "Unknown";

                // Change from tab-separated to comma-separated and add group_number
                outFile << l->getCourseId() << ','
                    << l->getDay() << ','
					<< (start < 10 ? "0" : "") << start << ":00," // Format start time with leading zero
                    << (end < 10 ? "0" : "") << end << ":00,"
                    << l->getClassroom() << ','
                    << type << ','
                    << l->getGroupNumber() << '\n';
            }

            outFile.close();
        }

        schedulesFile.close();
    }
    catch (const exception& e) {
        cerr << "Error in saveSchedules: " << e.what() << endl;
    }
}

// Add these functions to the existing FileManager.cpp

// ----------------------------------------------------------
// ----------------------------------------------------------
// loadLessonsFromFile :How to open one CSV file
//How to read its data. and How to create the right lesson objects.
//How to add them into the lessons vector.
//  but : loadAllLessons
//It knows that we have three different files (lectures.csv, tutorials.csv, labs.csv).
//It calls loadLessonsFromFile three times
//  once per file 
//
void loadAllLessons(vector<Lesson*>& lessons) {
    try {
        // Load from lectures.csv
        loadLessonsFromFile("lectures.csv", "Lecture", lessons);

        // Load from tutorials.csv
        loadLessonsFromFile("tutorials.csv", "Tutorial", lessons);

        // Load from labs.csv
        loadLessonsFromFile("labs.csv", "Lab", lessons);

        cout << "Successfully loaded total of " << lessons.size() << " lessons from all CSV files" << endl;

    }
    catch (const exception& e) {
        cerr << "Error in loadAllLessons: " << e.what() << endl;
    }
}

// ----------------------------------------------------------
// ----------------------------------------------------------
void loadLessonsFromFile(const string& filename, const string& lessonType, vector<Lesson*>& lessons) {
    try {
        ifstream inFile(filename);
        if (!inFile.is_open()) {
            cout << "Warning: " << filename << " not found. Skipping " << lessonType << " loading." << endl;
            return;
        }

        string line;
        getline(inFile, line); // skip header
        int loadedCount = 0;

        while (getline(inFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string typeColumn, courseIdStr, day, startTimeStr, endTimeStr, classroom, teacherName, groupNumberStr;

            // The actual CSV format: type,courseId,day,startTime,endTime,classroom,teacherName,groupNumber
            getline(ss, typeColumn, ',');      // Skip the type column (Lecture/Tutorial/Lab)
            getline(ss, courseIdStr, ',');
            getline(ss, day, ',');
            getline(ss, startTimeStr, ',');
            getline(ss, endTimeStr, ',');
            getline(ss, classroom, ',');
            getline(ss, teacherName, ',');
            getline(ss, groupNumberStr, ',');

            try {
                if (courseIdStr.empty() || startTimeStr.empty() || endTimeStr.empty() || groupNumberStr.empty()) {
                    cerr << "Warning: Invalid " << lessonType << " data in line: " << line << endl;
                    continue;
                }

                int courseId = stoi(courseIdStr);

                // Parse time format using helper function to avoid duplication
                int startHour = parseTimeToHour(startTimeStr);
                int endHour = parseTimeToHour(endTimeStr);

                int groupNumber = stoi(groupNumberStr);

                Lesson* lesson = nullptr;

                if (lessonType == "Lecture") {
                    lesson = new Lecture("Lecture", courseId, day, startHour, endHour, classroom, teacherName, groupNumber);
                }
                else if (lessonType == "Tutorial") {
                    lesson = new Tutorial("Tutorial", courseId, day, startHour, endHour, classroom, teacherName, groupNumber);
                }
                else if (lessonType == "Lab") {
                    lesson = new Lab("Lab", courseId, day, startHour, endHour, classroom, teacherName, groupNumber);
                }

                if (lesson) {
                    lessons.push_back(lesson);
                    loadedCount++;
                }
            }
            catch (const exception& e) {
                cerr << "Warning: Error parsing " << lessonType << " data: " << line << " - " << e.what() << endl;

            }
        }

        inFile.close();
        cout << "Successfully loaded " << loadedCount << " " << lessonType << " lessons from " << filename << endl;

    }
    catch (const exception& e) {
        cerr << "Error loading " << lessonType << " from " << filename << ": " << e.what() << endl;
    }
}

// ----------------------------------------------------------
// ----------------------------------------------------------
void saveAllLessons(const vector<Lesson*>& lessons) {
    try {
        // Separate lessons by type
        vector<Lesson*> lectures, tutorials, labs;

        for (Lesson* lesson : lessons) {
            if (lesson == nullptr) {
                cerr << "Warning: Encountered null Lesson pointer in saveAllLessons, skipping." << endl;
                continue;
            }

            if (dynamic_cast<Lecture*>(lesson)) {
                lectures.push_back(lesson);
            }
            else if (dynamic_cast<Tutorial*>(lesson)) {
                tutorials.push_back(lesson);
            }
            else if (dynamic_cast<Lab*>(lesson)) {
                labs.push_back(lesson);
            }
        }

        // Save lectures.csv
        saveLessonsToFile("lectures.csv", lectures, "Lecture");

        // Save tutorials.csv
        saveLessonsToFile("tutorials.csv", tutorials, "Tutorial");

        // Save labs.csv
        saveLessonsToFile("labs.csv", labs, "Lab");

        cout << "Successfully saved all lessons to separate CSV files" << endl;

    }
    catch (const exception& e) {
        cerr << "Error in saveAllLessons: " << e.what() << endl;
    }
}

//  function to save lessons to specific file
void saveLessonsToFile(const string& filename, const vector<Lesson*>& lessons, const string& lessonType) {
    try {
        ofstream outFile(filename);
        if (!outFile.is_open()) {
            cerr << "Failed to open " << filename << " for writing" << endl;
            return;
        }

        // Write header to match the format: type,course_id,day,start_time,end_time,classroom,teacher_name,group_number
        outFile << "type,course_id,day,start_time,end_time,classroom,teacher_name,group_number\n";

        for (Lesson* lesson : lessons) {
            if (lesson == nullptr) {
                cerr << "Warning: Encountered null Lesson pointer in saveLessonsToFile, skipping." << endl;
                continue;
            }
            outFile << lessonType << ','
                << lesson->getCourseId() << ','
                << lesson->getDay() << ','
                << (lesson->getStartHour() < 10 ? "0" : "") << lesson->getStartHour() << ":00,"
                << (lesson->getEndHour() < 10 ? "0" : "") << lesson->getEndHour() << ":00,"
                << lesson->getClassroom() << ','
                << lesson->getTeacherName() << ','
                << lesson->getGroupNumber() << '\n';
        }

        outFile.close();
        cout << "Saved " << lessons.size() << " " << lessonType << " lessons to " << filename << endl;

    }
    catch (const exception& e) {
       // cerr << "Warning: Error parsing lesson in " << filename << ": " << line << endl;
        cerr << "Error saving " << lessonType << " to " << filename << ": " << e.what() << endl;
    }
}