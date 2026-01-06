#include "MenuFunctions.h"

// ExamDateTime struct implementation
// -1 indicates invalid hour
// isValid is false if the date is empty or invalid
ExamDateTime::ExamDateTime() : day(""), startHour(-1), endHour(-1), isValid(false), originalDate("") {}

// Helper function to check if string contains '/'
bool containsSlash(const string& str) {
    for (char c : str) {
        if (c == '/') {
            return true;
        }
    }
    return false;
}
 
// Constructor that parses the exam date string
ExamDateTime::ExamDateTime(const string& examDateStr) : isValid(false), originalDate(examDateStr) {
    try {
        // Handle empty or placeholder dates
		//  we use NULL, none, and 0 ==> we assume they are invalid
        if (examDateStr.empty() || examDateStr == "NULL" || examDateStr == "none" || examDateStr == "0") {
            return;
        }

        // Parse date format MM/DD/YYYY 
        // nopes = no postition found
        if (containsSlash(examDateStr)) { // Check if it contains '/'
			// Split the date string into parts
			vector<string> dateParts;// to hold month, day, year parts
			stringstream ss(examDateStr); // Split by '/'
            string part;
            while (getline(ss, part, '/')) {
                dateParts.push_back(part);
            }

            if (dateParts.size() == 3) {
                int month = stoi(dateParts[0]); 
                int day_num = stoi(dateParts[1]);
                int year = stoi(dateParts[2]);

                // Calculate day of week using Zeller's congruence
                // Adjust month and year for Zeller's formula
                if (month < 3) {
                    month += 12;
                    year--;
                }

                int k = year % 100; 
                int j = year / 100;

                int dayOfWeek = (day_num + (13 * (month + 1)) / 5 + k + k / 4 + j / 4 - 2 * j) % 7;

                // Convert to 0=Saturday, 1=Sunday, 2=Monday, etc.
                vector<string> dayNames = { "Saturday", "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday" };

                if (dayOfWeek >= 0 && dayOfWeek < 7) {
                    day = dayNames[dayOfWeek];
                }
                else {
                    day = "Unknown";
                }

                // Default  time assumptions (can be adjusted)
                startHour = 9;  // Most lessons start at 9:00 AM
                endHour = 12;   // 3-hour  duration

                isValid = true;
            }
        }

    }
    catch (const exception&) { 
        // Parsing failed
        isValid = false;
    }
}

void printMenu() {
    cout << "\n===============================================================================\n";
    cout << "1.  PrintCourse <course_id>              - Print course details\n";
    cout << "2.  PrintCourses                         - Print first 10 courses\n";
    cout << "3.  More                                 - Print next 10 courses\n";
    cout << "4.  PrintSchedule <schedule_id>          - Print specific schedule\n";
    cout << "5.  PrintSchedules                       - Print all schedules\n";
    cout << "6.  AddSchedule                          - Add new empty schedule\n";
    cout << "7.  RmSchedule <schedule_id>             - Remove schedule\n";
    cout << "8.  Add <sched> <course> <group>         - Add lesson to schedule\n";
    cout << "9.  Rm <sched> <course> <group>          - Remove lesson from schedule\n";
    cout << "10. Clear                                - Clear screen\n";
    cout << "11. Help                                 - Show this help\n";
    cout << "12. Exit                                 - Save and exit\n";
    cout << "--- ADVANCED ANALYSIS ---\n";
    cout << "13. Find Time Conflicts                  - Detect overlapping lessons & exams\n";
    cout << "14. Course Workload Analysis             - Analyze course lesson distribution\n";
    cout << "15. Teacher Schedule Analysis            - Analyze teacher workload\n";
    cout << "16. Run System Tests                     - Test all functions\n";
    cout << "===============================================================================\n";
    cout << "Enter your choice: ";
}

// Function to clear input buffer after invalid input occurs
// Purpose: Clears the error flags on the cin stream
void clearCin() { 
    //Clears the error flags on the cin stream
    cin.clear();
    // Removes leftover characters from the input buffer
    //cin.ignore(numeric_limits<streamsize>::max(), '\n'); 
    //cin.ignore(10000, '\n');  // Clear up to 10000 characters or until newline
	string dummy; // dummy variable to hold input
    getline(cin, dummy);  // Read and discard everything until newline
}


void showHelp() {
    cout << "\n=== HELP - Command Reference ===\n";
    cout << "1.  PrintCourse <course_id>     - Display details for a specific course\n";
    cout << "2.  PrintCourses                - Show first 10 courses in the system\n";
    cout << "3.  More                        - Show next 10 courses (pagination)\n";
    cout << "4.  PrintSchedule <schedule_id> - Display a specific schedule \n";
    cout << "5.  PrintSchedules              - Show all available schedules\n";
    cout << "6.  AddSchedule                 - Create a new empty schedule\n";
    cout << "7.  RmSchedule <schedule_id>    - Remove a schedule from system\n";
    cout << "8.  Add <sched> <course> <group> - Add lesson to schedule\n";
    cout << "9.  Rm <sched> <course> <group>  - Remove lesson from schedule\n";
    cout << "10. Clear                       - Clear the screen\n";
    cout << "11. Help                        - Show this help menu\n";
    cout << "12. Exit                        - Save all data and exit program\n";
    cout << "\nExamples:\n";
    cout << "  Option 1: Enter course ID like 1000\n";
    cout << "  Option 4: Enter schedule ID like 1\n";
    cout << "  Option 8: Enter schedule ID, course ID, and group number\n";
    cout << "================================\n";
}


// Helper function to check if string contains ':'
bool containsColon(const string& str) {
    for (char c : str) {
        if (c == ':') {
            return true;
        }
    }
    return false;
}


  //Simple helper function to parse time string to hour integer
 //param timeStr The time string in format "HH:MM" or just "HH"
 // return The hour as integer, or 0 if parsing fails
 
int parseTimeToHour(const string& timeStr) {
    if (timeStr.empty()) return 0;

    // Check if time has colon (like "14:30")
    if (containsColon(timeStr)) {
		return stoi(timeStr.substr(0, timeStr.find(':'))); // return hour part before ':'
    }
    else {
        // Just hour number like "14"
        return stoi(timeStr);
    }
}

/**
 * Function to check for time conflicts in a schedule CSV file
 * scheduleId The ID of the schedule to check
 * return true if conflicts found, false otherwise
 */
bool hasCSVScheduleConflicts(int scheduleId) {
    string filename = "Schedule" + to_string(scheduleId) + ".csv";
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        return false; // No file means no conflicts
    }

    // Vector to store all lessons from CSV file
    vector<tuple<string, int, int, int, string, string>> lessons;
	//<day, startHour, endHour, courseId, type, room>
	// tuple format: <day, startHour, endHour, courseId, type, room>
  

    string line;
    getline(inFile, line); // skip header row

    // Read all lessons from CSV file
    while (getline(inFile, line)) {
        if (line.empty()) continue;

		stringstream ss(line); // Create a stringstream to parse the line
        string courseIdStr, day, startTimeStr, endTimeStr, room, type;

        // Parse each field from CSV line
        getline(ss, courseIdStr, ',');
        getline(ss, day, ',');
        getline(ss, startTimeStr, ',');
        getline(ss, endTimeStr, ',');
        getline(ss, room, ',');
        getline(ss, type, ',');

        try {
            if (courseIdStr.empty() || startTimeStr.empty() || endTimeStr.empty()) {
                continue; // Skip empty lines
            }

            int courseId = stoi(courseIdStr);
            int startHour = parseTimeToHour(startTimeStr);
            int endHour = parseTimeToHour(endTimeStr);

            // Make day name start with capital letter
            if (!day.empty()) {
                day[0] = toupper(day[0]);
                for (size_t i = 1; i < day.length(); i++) {
                    day[i] = tolower(day[i]);
                }
            }

            // Store lesson info in tuple
            lessons.push_back(make_tuple(day, startHour, endHour, courseId, type, room));

        } catch (const exception&) {
            continue; // Skip invalid lines
        }
    }
    inFile.close();

    // Check every pair of lessons for time conflicts
    for (size_t i = 0; i < lessons.size(); i++) {
        for (size_t j = i + 1; j < lessons.size(); j++) {
            // Get lesson details from tuples
            string day1 = get<0>(lessons[i]);
            int start1 = get<1>(lessons[i]);
            int end1 = get<2>(lessons[i]);

            string day2 = get<0>(lessons[j]);
            int start2 = get<1>(lessons[j]);
            int end2 = get<2>(lessons[j]);

            // Check if same day and time overlap
            if (day1 == day2 && start1 < end2 && start2 < end1) { 
                return true; // Found a conflict!
            }
        }
    }

    return false; // No conflicts found
}


// Function to print all lessons for a specific course from CSV files
void printAllLessonsFromCSV(int courseId, const vector<Course>& courses) {
    // First show basic course info
    bool courseFound = false;
    for (const Course& c : courses) {
        if (c.getId() == courseId) {
            cout << "\n--- Course Details ---\n";
            cout << c << endl;
            courseFound = true;
            break;
        }
    }

    if (!courseFound) {
        cout << "Course ID " << courseId << " not found.\n";
        return;
    }

    // Read from all three CSV files and display lessons for this course
    vector<string> filenames = { "lectures.csv", "tutorials.csv", "labs.csv" };
    vector<string> lessonTypes = { "Lecture", "Tutorial", "Lab" };

	bool anyLessonsFound = false; // Track if any lessons were found for this course

    for (size_t i = 0; i < filenames.size(); i++) {
        ifstream inFile(filenames[i]);
        if (!inFile.is_open()) {
            cout << "Warning: " << filenames[i] << " not found.\n";
            continue;
        }

        string line;
        getline(inFile, line); // skip header
        bool lessonFoundInFile = false;

        cout << "\n--- " << lessonTypes[i] << " Information for Course " << courseId << " ---\n";

        while (getline(inFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string typeColumn, courseIdStr, day, startTime, endTime, room, teacherName, groupStr;

            // CSV format: type,course_id,day,start_time,end_time,room,teacher_name,group
            getline(ss, typeColumn, ',');
            getline(ss, courseIdStr, ',');
            getline(ss, day, ',');
            getline(ss, startTime, ',');
            getline(ss, endTime, ',');
            getline(ss, room, ',');
            getline(ss, teacherName, ',');
            getline(ss, groupStr, ',');

            try {
                if (!courseIdStr.empty() && stoi(courseIdStr) == courseId) {
                    cout << "Day: " << day << endl;
                    cout << "Time: " << startTime << " - " << endTime << endl;
                    cout << "Room: " << room << endl;
                    cout << "Teacher: " << teacherName << endl;
                    cout << "Group: " << groupStr << endl;
                    cout << "--------------------\n";
                    lessonFoundInFile = true;
                    anyLessonsFound = true;
                }
            }
            catch (const exception&) {
                // Skip invalid lines
                continue;
            }
        }

        if (!lessonFoundInFile) {
            cout << "No " << lessonTypes[i] << " information found for Course " << courseId << ".\n";
        }

        inFile.close();
    }

    if (!anyLessonsFound) {
        cout << "\nNo lesson information found for Course " << courseId << " in any CSV files.\n";
    }
}

// Function to print a specfic schedule table from CSV file
void printScheduleTable(int scheduleId) {
    string filename = "Schedule" + to_string(scheduleId) + ".csv";
	ifstream inFile(filename); // Open the schedule CSV file (read)

    if (!inFile.is_open()) {
        cout << "Schedule " << scheduleId << " CSV file not found.\n";
        cout << "Trying to create a test Schedule" << scheduleId << ".csv file...\n";

        // Create a test file with the data from your image
        if (scheduleId == 2) {
			ofstream testFile(filename); // Open for writing
            if (testFile.is_open()) {
                testFile << "course_id,day,start_time,end_time,room,type,group_number\n";
                testFile << "1004,sunday,10:00,12:00,A201,Lecture,1\n";
                testFile.close();
                cout << "Test file created. Trying to read again...\n";

                // Try to open again
                inFile.open(filename);
                if (!inFile.is_open()) {
                    cout << "Still cannot open " << filename << "\n";
                    return;
                }
            }
            else {
                cout << "Cannot create test file " << filename << "\n";
                return;
            }
        }
        else {
            cout << "Please create " << filename << " manually or use case 8 to add lessons.\n";
            return;
        }
    }

    inFile.close(); // Close and reopen for conflict check

    // CHECK FOR CONFLICTS
    bool hasConflicts = hasCSVScheduleConflicts(scheduleId);
    if (hasConflicts) {
        cout << "\n!!! WARNING: TIME CONFLICTS DETECTED IN SCHEDULE " << scheduleId << " !!!\n";
        cout << "This schedule contains overlapping lessons.\n";
        cout << "You must remove conflicting courses before using this schedule.\n";
        cout << "Use option 9 to remove lessons or option 13 for detailed analysis.\n\n";
    }

    // Reopen file for reading schedule data
    inFile.open(filename);

    // Data structure to hold schedule information - store course details separately
    map<int, map<string, vector<tuple<string, string, string, string>>>> scheduleGrid; // courseId, type, room, group
    vector<string> days = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    string line;
    getline(inFile, line); // skip header

    // Read schedule data
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string courseIdStr, day, startTimeStr, endTimeStr, room, type, groupStr;

        getline(ss, courseIdStr, ',');
        getline(ss, day, ',');
        getline(ss, startTimeStr, ',');
        getline(ss, endTimeStr, ',');
        getline(ss, room, ',');
        getline(ss, type, ',');
        getline(ss, groupStr, ',');

        try {
            if (courseIdStr.empty() || startTimeStr.empty() || endTimeStr.empty()) {
                continue;
            }

			int courseId = stoi(courseIdStr); // Convert course ID from string to int
            int startHour = parseTimeToHour(startTimeStr);
            int endHour = parseTimeToHour(endTimeStr);

            // Get group number
            string groupNumber = "1";  // default
            if (!groupStr.empty()) {
                groupNumber = groupStr;
            }

            // Normalize day name - capitalize first letter, lowercase rest
            if (!day.empty()) {
                day[0] = toupper(day[0]);
                for (size_t i = 1; i < day.length(); i++) {
                    day[i] = tolower(day[i]);
                }
            }

            // Store course details separately for multi-row display
            tuple<string, string, string, string> courseDetails = make_tuple(courseIdStr, type, room, groupNumber);

            // Add lesson to all hours it spans
            for (int hour = startHour; hour < endHour; hour++) {
                scheduleGrid[hour][day].push_back(courseDetails);
            }

        }
        catch (const exception&) {
            continue; // Skip invalid lines
        }
    }
    inFile.close(); 

    // Find time range
    if (scheduleGrid.empty()) {
        cout << "No lessons found in schedule " << scheduleId << ".\n";
        return;
    }

    int minHour = scheduleGrid.begin()->first;
    int maxHour = scheduleGrid.rbegin()->first;

    cout << "========== SCHEDULE " << scheduleId << " ==========\n";

    // Print table header with increased spacing
    cout << setw(8) << "Time"; // 
    for (const string& day : days) {
        cout << setw(14) << day;  // Increased from 10 to 14
    }
    cout << "\n";

    cout << string(8 + days.size() * 14, '-') << "\n";  // Updated line length

    // Print table rows - 4 rows per time slot
    for (int hour = minHour; hour <= maxHour; hour++) {
        // Row 1: Time and Course IDs
        cout << setw(6) << hour << ":00";
        for (const string& day : days) {
            string cellContent = "";
            if (scheduleGrid[hour].count(day) > 0) {
                for (size_t i = 0; i < scheduleGrid[hour][day].size(); i++) {
                    if (i > 0) cellContent += " | ";
                    cellContent += "C:" + get<0>(scheduleGrid[hour][day][i]);
                }
            }
            cout << setw(14) << cellContent;  // Increased from 10 to 14
        }
        cout << "\n";

        // Row 2: Lesson Types
        cout << setw(8) << "";
        for (const string& day : days) {
            string cellContent = "";
            if (scheduleGrid[hour].count(day) > 0) {
                for (size_t i = 0; i < scheduleGrid[hour][day].size(); i++) {
                    if (i > 0) cellContent += " | ";
                    string type = get<1>(scheduleGrid[hour][day][i]);
                    if (type == "Lecture") cellContent += "Lec";
                    else if (type == "Tutorial") cellContent += "Tut";
                    else if (type == "Lab") cellContent += "Lab";
                    else cellContent += type;
                }
            }
            cout << setw(14) << cellContent;  // Increased from 10 to 14
        }
        cout << "\n";

        // Row 3: Rooms
        cout << setw(8) << "";
        for (const string& day : days) {
            string cellContent = "";
            if (scheduleGrid[hour].count(day) > 0) {
                for (size_t i = 0; i < scheduleGrid[hour][day].size(); i++) {
                    if (i > 0) cellContent += " | ";
                    string room = get<2>(scheduleGrid[hour][day][i]);
                    if (room.length() > 12) room = room.substr(0, 10) + "..";  // Adjusted for wider columns
                    cellContent += room;
                }
            }
            cout << setw(14) << cellContent;  // Increased from 10 to 14
        }
        cout << "\n";

        // Row 4: Groups
        cout << setw(8) << "";
        for (const string& day : days) {
            string cellContent = "";
            if (scheduleGrid[hour].count(day) > 0) {
                for (size_t i = 0; i < scheduleGrid[hour][day].size(); i++) {
                    if (i > 0) cellContent += " | ";
                    cellContent += "G" + get<3>(scheduleGrid[hour][day][i]);
                }
            }
            cout << setw(14) << cellContent;  // Increased from 10 to 14
        }
        cout << "\n";

        // Empty line between time slots for clarity
        if (hour < maxHour) {
            cout << "\n";
        }
    }
}

void printScheduleTableClean(int scheduleId) {
    string filename = "Schedule" + to_string(scheduleId) + ".csv";
    ifstream inFile(filename);

    if (!inFile.is_open()) {
        cout << "Schedule " << scheduleId << " CSV file not found.\n";
        return;
    }
    inFile.close(); // Close for conflict check

    // CHECK FOR CONFLICTS
    bool hasConflicts = hasCSVScheduleConflicts(scheduleId);
    if (hasConflicts) {
        cout << "\n!!! WARNING: SCHEDULE " << scheduleId << " HAS TIME CONFLICTS !!!\n";
        cout << "Remove conflicting courses before using this schedule.\n\n";
    }

    // Reopen file for reading schedule data
    inFile.open(filename);

    // Data structure to hold schedule information - store course details separately
    map<int, map<string, vector<tuple<string, string, string, string>>>> scheduleGrid; // courseId, type, room, group
    vector<string> days = { "Sunday", "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday" };

    string line;
    getline(inFile, line); // skip header

    // Read schedule data
    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string courseIdStr, day, startTimeStr, endTimeStr, room, type, groupStr;

        getline(ss, courseIdStr, ',');
        getline(ss, day, ',');
        getline(ss, startTimeStr, ',');
        getline(ss, endTimeStr, ',');
        getline(ss, room, ',');
        getline(ss, type, ',');
        getline(ss, groupStr, ',');

        try {
            if (courseIdStr.empty() || startTimeStr.empty() || endTimeStr.empty()) {
                continue;
            }

            int courseId = stoi(courseIdStr);
            int startHour = parseTimeToHour(startTimeStr);
            int endHour = parseTimeToHour(endTimeStr);

            // Get group number
            string groupNumber = "1";  // default
            if (!groupStr.empty()) {
                groupNumber = groupStr;
            }

            // Normalize day name - capitalize first letter, lowercase rest
            if (!day.empty()) {
                day[0] = toupper(day[0]);
                for (size_t i = 1; i < day.length(); i++) {
                    day[i] = tolower(day[i]);
                }
            }

            // Store course details separately for multi-row display
            tuple<string, string, string, string> courseDetails = make_tuple(courseIdStr, type, room, groupNumber);

            // Add lesson to all hours it spans
            for (int hour = startHour; hour < endHour; hour++) {
                scheduleGrid[hour][day].push_back(courseDetails);
            }

        }
        catch (const exception&) {
            continue; // Skip invalid lines
        }
    }
    inFile.close();

    // Find time range
    if (scheduleGrid.empty()) {
        cout << "No lessons found in schedule " << scheduleId << ".\n";
        return;
    }

    int minHour = scheduleGrid.begin()->first;
    int maxHour = scheduleGrid.rbegin()->first;

    // Print table header with increased spacing
	cout << setw(8) << "Time"; // sapce between time and day names
    for (const string& day : days) {
		cout << setw(14) << day;  // space between day names
    }
    cout << "\n";

	cout << string(8 + days.size() * 14, '-') << "\n";  // Updated line length of header

    // Print table rows - 4 rows per time slot
    for (int hour = minHour; hour <= maxHour; hour++) {
       
        // Row 1: Time and Course IDs
		cout << setw(6) << hour << ":00"; // space between hour and course IDs
        for (const string& day : days) {
            string cellContent = "";
            if (scheduleGrid[hour].count(day) > 0) {
                for (size_t i = 0; i < scheduleGrid[hour][day].size(); i++) {
                    if (i > 0) cellContent += " | ";
                    cellContent += "C:" + get<0>(scheduleGrid[hour][day][i]);
                }
            }
            cout << setw(14) << cellContent;  // Increased from 10 to 14
        }
        cout << "\n";

        // Row 2: Lesson Types
        cout << setw(8) << "";
        for (const string& day : days) {
            string cellContent = "";
            if (scheduleGrid[hour].count(day) > 0) {
                for (size_t i = 0; i < scheduleGrid[hour][day].size(); i++) {
                    if (i > 0) cellContent += " | ";
                    string type = get<1>(scheduleGrid[hour][day][i]);
                    if (type == "Lecture") cellContent += "Lec";
                    else if (type == "Tutorial") cellContent += "Tut";
                    else if (type == "Lab") cellContent += "Lab";
                    else cellContent += type;
                }
            }
            cout << setw(14) << cellContent;  // Increased from 10 to 14
        }
        cout << "\n";

        // Row 3: Rooms
        cout << setw(8) << "";
        for (const string& day : days) {
            string cellContent = "";
            if (scheduleGrid[hour].count(day) > 0) {
                for (size_t i = 0; i < scheduleGrid[hour][day].size(); i++) {
                    if (i > 0) cellContent += " | ";
                    string room = get<2>(scheduleGrid[hour][day][i]);
                    if (room.length() > 12) room = room.substr(0, 10) + "..";  // Adjusted for wider columns
                    cellContent += room;
                }
            }
            cout << setw(14) << cellContent;  // Increased from 10 to 14
        }
        cout << "\n";

        // Row 4: Groups
        cout << setw(8) << ""; 
        for (const string& day : days) {
            string cellContent = "";
            if (scheduleGrid[hour].count(day) > 0) {
                for (size_t i = 0; i < scheduleGrid[hour][day].size(); i++) {
                    if (i > 0) cellContent += " | ";
                    cellContent += "G" + get<3>(scheduleGrid[hour][day][i]);
                }
            }
            cout << setw(14) << cellContent;  // Increased from 10 to 14
        }
        cout << "\n";

        // Empty line between time slots for clarity
        if (hour < maxHour) {
            cout << "\n";
        }
    }
}

// New function to get lesson details from CSV and let user choose group
bool addLessonFromCSV(int courseId, int lessonChoice, const vector<Course>& courses, Schedule* target) {
    // First show basic course info
    bool courseFound = false;
    for (const Course& c : courses) {
        if (c.getId() == courseId) {
            cout << "\n--- Course Information ---\n";
            cout << "Course ID: " << c.getId() << endl;
            cout << "Course Name: " << c.getName() << endl;
            cout << "Credits: " << c.getCredits() << endl;
            cout << "Lecturer: " << c.getLecturer() << endl;
            cout << "Semester: " << c.getSemester() << endl;
            courseFound = true;
            break;
        }
    }

    if (!courseFound) {
        cout << "Course ID " << courseId << " not found.\n";
        return false;
    }

    // Determine lesson type name and filename
    string lessonType;
    string filename;
    if (lessonChoice == 1) {
        lessonType = "Lecture";
        filename = "lectures.csv";
    }
    else if (lessonChoice == 2) {
        lessonType = "Tutorial";
        filename = "tutorials.csv";
    }
    else if (lessonChoice == 3) {
        lessonType = "Lab";
        filename = "labs.csv";
    }
    else {
        cout << "Invalid lesson type.\n";
        return false;
    }

    cout << "\n--- " << lessonType << " Information for Course " << courseId << " ---\n";

    // Try to read from the specific lesson type CSV file
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Warning: " << filename << " not found. No specific " << lessonType << " information available.\n";
        return false;
    }

    string line;
    getline(inFile, line); // skip header

    // Store all matching lessons with their details
    vector<tuple<int, string, string, string, string, string, int>> availableLessons; // group, day, start, end, room, teacher, groupNum

    while (getline(inFile, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        string typeColumn, courseIdStr, day, startTime, endTime, room, teacher, groupStr;

        // CSV format: type,course_id,day,start_time,end_time,room,teacher_name,group
        getline(ss, typeColumn, ',');
        getline(ss, courseIdStr, ',');
        getline(ss, day, ',');
        getline(ss, startTime, ',');
        getline(ss, endTime, ',');
        getline(ss, room, ',');
        getline(ss, teacher, ',');
        getline(ss, groupStr, ',');

        try {
            if (!courseIdStr.empty() && stoi(courseIdStr) == courseId) {
                int groupNumber = stoi(groupStr);

                cout << "Day: " << day << endl;
                cout << "Time: " << startTime << " - " << endTime << endl;
                cout << "Room: " << room << endl;
                cout << "Teacher: " << teacher << endl;
                cout << "Group Number: " << groupNumber << endl;
                cout << "--------------------\n";

                // Store lesson details
                availableLessons.push_back(make_tuple(groupNumber, day, startTime, endTime, room, teacher, groupNumber));
            }
        }
        catch (const exception&) {
            // Skip invalid lines
            continue;
        }
    }
    inFile.close();

    if (availableLessons.empty()) {
        cout << "No " << lessonType << " information found for Course " << courseId << " in " << filename << ".\n";
        return false;
    }

    // Let user choose which group
    cout << "\nSelect which group to add to schedule:\n";
    for (size_t i = 0; i < availableLessons.size(); i++) {
        cout << (i + 1) << " - Group " << get<0>(availableLessons[i])
            << " (" << get<1>(availableLessons[i]) << " " << get<2>(availableLessons[i])
            << "-" << get<3>(availableLessons[i]) << " in " << get<4>(availableLessons[i]) << ")\n";
    }

    cout << "Enter choice (1-" << availableLessons.size() << "): ";
    int choice;
    cin >> choice;
    clearCin();

    if (choice < 1 || choice > static_cast<int>(availableLessons.size())) {
        cout << "Invalid choice.\n";
        return false;
    }

    // Get selected lesson details
    tuple<int, string, string, string, string, string, int> selectedLesson = availableLessons[choice - 1];
    string day = get<1>(selectedLesson);
    string startTimeStr = get<2>(selectedLesson);
    string endTimeStr = get<3>(selectedLesson);
    string classroom = get<4>(selectedLesson);
    string teacher = get<5>(selectedLesson);
    int groupNumber = get<6>(selectedLesson);

    // Parse time strings to integers using helper function
    int startHour = parseTimeToHour(startTimeStr);
    int endHour = parseTimeToHour(endTimeStr);

    // Create the lesson with proper type strings
    Lesson* lesson = nullptr;
    if (lessonChoice == 1) {
        lesson = new Lecture("Lecture", courseId, day, startHour, endHour, classroom, teacher, groupNumber);
    }
    else if (lessonChoice == 2) {
        lesson = new Tutorial("Tutorial", courseId, day, startHour, endHour, classroom, teacher, groupNumber);
    }
    else if (lessonChoice == 3) {
        lesson = new Lab("Lab", courseId, day, startHour, endHour, classroom, teacher, groupNumber);
    }

    if (lesson) {
        target->addLesson(lesson);
        return true;
    }

    return false;
}

// ===== OPERATION 1: Find Time Conflicts (Lessons and Exams only) =====
void findTimeConflicts(const vector<Schedule*>& schedules, const vector<Course>& courses) {
    cout << "\n=== TIME CONFLICTS ANALYSIS (Lessons + Exams) ===\n";

    bool foundAnyConflict = false;

    for (const Schedule* schedule : schedules) {
        cout << "\n--- Schedule " << schedule->getId() << " ---\n";

        const vector<Lesson*>& lessons = schedule->getLessons();
        vector<pair<Lesson*, Lesson*>> lessonConflicts;
        vector<tuple<string, string, string, string, string, string>> examToExamConflicts; // course1 name, exam1 type, exam1 date, course2 name, exam2 type, exam2 date

        // PART 1: Check lesson-to-lesson conflicts
        for (size_t i = 0; i < lessons.size(); i++) {
            for (size_t j = i + 1; j < lessons.size(); j++) {
                Lesson* lesson1 = lessons[i];
                Lesson* lesson2 = lessons[j];

                // Check if lessons are on the same day
                if (lesson1->getDay() == lesson2->getDay()) {
                    // Check time overlap
                    int start1 = lesson1->getStartHour();
                    int end1 = lesson1->getEndHour();
                    int start2 = lesson2->getStartHour();
                    int end2 = lesson2->getEndHour();

                    // Check if times overlap: (start1 < end2) && (start2 < end1)
                    if (start1 < end2 && start2 < end1) {
                        lessonConflicts.push_back(make_pair(lesson1, lesson2));
                        foundAnyConflict = true;
                    }
                }
            }
        }

        // PART 2: Check exam-to-exam conflicts for courses in the same schedule
        set<int> scheduleCourses;
        for (const Lesson* lesson : lessons) {
            scheduleCourses.insert(lesson->getCourseId());
        }

        vector<int> courseList(scheduleCourses.begin(), scheduleCourses.end());
        for (size_t i = 0; i < courseList.size(); i++) {
            for (size_t j = i + 1; j < courseList.size(); j++) {
                const Course* course1 = nullptr;
                const Course* course2 = nullptr;

                // Find course objects
                for (const Course& c : courses) {
                    if (c.getId() == courseList[i]) course1 = &c;
                    if (c.getId() == courseList[j]) course2 = &c;
                }

                if (course1 && course2) {
                    // Check all exam combinations - ONLY COMPARE EXACT DATES
                    vector<pair<string, string>> examPairs1 = {
                        {course1->getMoedA(), "Moed A"},
                        {course1->getMoedB(), "Moed B"}
                    };
                    vector<pair<string, string>> examPairs2 = {
                        {course2->getMoedA(), "Moed A"},
                        {course2->getMoedB(), "Moed B"}
                    };

                    for (const pair<string, string>& exam1 : examPairs1) {
                        for (const pair<string, string>& exam2 : examPairs2) {
                            // Skip empty or invalid dates
                            if (exam1.first.empty() || exam2.first.empty() ||
                                exam1.first == "TBD" || exam2.first == "TBD" ||
                                exam1.first == "N/A" || exam2.first == "N/A" ||
                                exam1.first == "0" || exam2.first == "0") {
                                continue;
                            }

                            // ONLY CHECK IF EXACT DATES MATCH (not days of week)
                            if (exam1.first == exam2.first) {
                                examToExamConflicts.push_back(make_tuple(
                                    course1->getName(), exam1.second, exam1.first,
                                    course2->getName(), exam2.second, exam2.first
                                ));
                                foundAnyConflict = true;
                            }
                        }
                    }
                }
            }
        }

        // Display results
        if (lessonConflicts.empty() && examToExamConflicts.empty()) {
            cout << " No time conflicts found.\n";
        }
        else {
            // Display lesson-to-lesson conflicts
            if (!lessonConflicts.empty()) {
                cout << " Found " << lessonConflicts.size() << " lesson-to-lesson conflicts:\n";
                for (const pair<Lesson*, Lesson* >& conflict : lessonConflicts) {
                    cout << "  LESSON-LESSON CONFLICT:\n";
                    cout << "    1. Course " << conflict.first->getCourseId()
                        << " (" << conflict.first->getType() << ") "
                        << conflict.first->getDay() << " "
                        << conflict.first->getStartHour() << ":00-"
                        << conflict.first->getEndHour() << ":00 "
                        << conflict.first->getClassroom() << "\n";
                    cout << "    2. Course " << conflict.second->getCourseId()
                        << " (" << conflict.second->getType() << ") "
                        << conflict.second->getDay() << " "
                        << conflict.second->getStartHour() << ":00-"
                        << conflict.second->getEndHour() << ":00 "
                        << conflict.second->getClassroom() << "\n";
                    cout << "  ---\n";
                }
            }

            // Display exam-to-exam conflicts
            if (!examToExamConflicts.empty()) {
                cout << " Found " << examToExamConflicts.size() << " exam-to-exam conflicts:\n";
                for (const tuple < string, string, string, string, string, string>& conflict : examToExamConflicts) {
                    string course1Name = get<0>(conflict);
                    string exam1Type = get<1>(conflict);
                    string exam1Date = get<2>(conflict);
                    string course2Name = get<3>(conflict);
                    string exam2Type = get<4>(conflict);
                    string exam2Date = get<5>(conflict);

                    ExamDateTime exam1Info(exam1Date);
                    ExamDateTime exam2Info(exam2Date);

                    cout << "  EXAM-EXAM CONFLICT:\n";
                    cout << "    1. " << course1Name << " " << exam1Type
                        << " on " << exam1Info.day << " " << exam1Date
                        << " (estimated " << exam1Info.startHour << ":00-" << exam1Info.endHour << ":00)\n";
                    cout << "    2. " << course2Name << " " << exam2Type
                        << " on " << exam2Info.day << " " << exam2Date
                        << " (estimated " << exam2Info.startHour << ":00-" << exam2Info.endHour << ":00)\n";
                    cout << "  ---\n";
                }
            }

            // Add warning message when conflicts are found
            cout << "\n  WARNING: Schedule conflicts detected!\n";
            cout << "   You must modify your schedule to resolve these conflicts.\n";
            cout << "   Consider changing course groups or exam dates.\n";
        }
    }

    if (!foundAnyConflict) {
        cout << "\n No time conflicts found in any schedule!\n";
        cout << "   All schedules are conflict-free.\n";
    }
}

// Simple sorting function for courses by total hours - student style
bool compareCoursesByHours(const pair<int, tuple<int, int, int, int>>& a, const pair<int, tuple<int, int, int, int>>& b) {
    // Compare total hours (first element of tuple)
    return get<0>(a.second) > get<0>(b.second);
}

// ===== OPERATION 2: Course Workload Analysis (Per Schedule) =====
void analyzeCourseWorkload(const vector<Schedule*>& schedules, const vector<Course>& courses) {
    cout << "\n=== COURSE WORKLOAD ANALYSIS ===\n";

    // First, check for Schedule CSV files and analyze each one separately
    bool foundAnySchedule = false;

    for (int scheduleId = 1; scheduleId <= 100; scheduleId++) { // Check reasonable range
        string filename = "Schedule" + to_string(scheduleId) + ".csv";
        ifstream inFile(filename);

        if (!inFile.is_open()) {
            continue; // Skip non-existent files
        }

        foundAnySchedule = true;
        cout << "\n==========================================\n";
        cout << "SCHEDULE " << scheduleId << " ANALYSIS\n";
        cout << "==========================================\n";

        // Map to store course statistics for this schedule: courseId -> {totalHours, lectureHours, tutorialHours, labHours}
        map<int, tuple<int, int, int, int>> courseStats;

        string line;
        getline(inFile, line); // skip header

        // Read schedule data
        while (getline(inFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string courseIdStr, day, startTimeStr, endTimeStr, room, type;

            // CSV format: course_id,day,start_time,end_time,room,type
            getline(ss, courseIdStr, ',');
            getline(ss, day, ',');
            getline(ss, startTimeStr, ',');
            getline(ss, endTimeStr, ',');
            getline(ss, room, ',');
            getline(ss, type, ',');

            try {
                if (courseIdStr.empty() || startTimeStr.empty() || endTimeStr.empty()) {
                    continue;
                }

                int courseId = stoi(courseIdStr);
                // Parse time format "HH:MM" to hour integer using helper function
                int startHour = parseTimeToHour(startTimeStr);
                int endHour = parseTimeToHour(endTimeStr);

                int duration = endHour - startHour;

                // Initialize course if not exists
                if (courseStats.find(courseId) == courseStats.end()) {
                    courseStats[courseId] = make_tuple(0, 0, 0, 0);
                }

                tuple<int, int, int, int>& stats = courseStats[courseId];
                get<0>(stats) += duration; // Add to total hours

                if (type == "Lecture") {
                    get<1>(stats) += duration; // Add lecture hours
                }
                else if (type == "Tutorial") {
                    get<2>(stats) += duration; // Add tutorial hours
                }
                else if (type == "Lab") {
                    get<3>(stats) += duration; // Add lab hours
                }

            }
            catch (const exception&) {
                continue; // Skip invalid lines
            }
        }
        inFile.close();

        // Display results for this schedule
        if (courseStats.empty()) {
            cout << "No lessons found in Schedule" << scheduleId << ".csv\n";
            continue;
        }

        // Sort courses by total hours (descending) - using simple function instead of lambda
        vector<pair<int, tuple<int, int, int, int>>> sortedCourses(courseStats.begin(), courseStats.end());
        sort(sortedCourses.begin(), sortedCourses.end(), compareCoursesByHours);

        cout << setw(8) << "Course" << setw(20) << "Name" << setw(8) << "Hours"
            << setw(6) << "Lec" << setw(6) << "Tut" << setw(6) << "Lab" << "\n";
        cout << string(54, '-') << "\n";

        int totalWeeklyHours = 0;
        int totalCoursesWithLessons = 0;

        for (const pair<int, tuple<int, int, int, int>>& entry : sortedCourses) {
            int courseId = entry.first;
            int totalHours = get<0>(entry.second);
            int lectureHours = get<1>(entry.second);
            int tutorialHours = get<2>(entry.second);
            int labHours = get<3>(entry.second);

            // Find course name
            string courseName = "Unknown";
            for (const Course& course : courses) {
                if (course.getId() == courseId) {
                    courseName = course.getName();
                    if (courseName.length() > 18) {
                        courseName = courseName.substr(0, 15) + "...";
                    }
                    break;
                }
            }

            if (totalHours > 0) { // Only show courses with scheduled lessons
                cout << setw(8) << courseId << setw(20) << courseName << setw(8) << totalHours
                    << setw(6) << lectureHours << setw(6) << tutorialHours << setw(6) << labHours << "\n";

                totalWeeklyHours += totalHours;
                totalCoursesWithLessons++;
            }
        }

        // Calculate semester totals (12 weeks) for this schedule
        int totalSemesterHours = totalWeeklyHours * 12;

        cout << "\n--- Schedule " << scheduleId << " Summary ---\n";
        cout << "Total courses with scheduled lessons: " << totalCoursesWithLessons << "\n";
        cout << "Total hours learning per week: " << totalWeeklyHours << " hours\n";
        cout << "Total hours for 1 semester (12 weeks): " << totalSemesterHours << " hours\n";
        cout << "Average hours per course per week: " << (totalCoursesWithLessons > 0 ?
            static_cast<double>(totalWeeklyHours) / totalCoursesWithLessons : 0) << " hours\n";
    }

    if (!foundAnySchedule) {
        cout << "No Schedule CSV files found.\n";
        cout << "Please ensure you have Schedule1.csv, Schedule2.csv, etc. in your project directory.\n";
    }
}

// Simple sorting function for teacher lessons - student style
bool compareTeacherLessons(const tuple<int, string, string, string, string, string, string>& a, 
                          const tuple<int, string, string, string, string, string, string>& b) {
    // First compare by course ID
    if (get<0>(a) != get<0>(b)) {
        return get<0>(a) < get<0>(b);
    }
    // Then by lesson type
    return get<1>(a) < get<1>(b);
}

// Simple function to find busiest day - student style
string findBusiestDay(const map<string, int>& dayCount) {
    string busiestDay = "";
    int maxLessons = 0;
    
    // Simple loop to find the day with most lessons
    for (const pair<string, int>& entry : dayCount) {
        if (entry.second > maxLessons) {
            maxLessons = entry.second;
            busiestDay = entry.first;
        }
    }
    
    return busiestDay + " (" + to_string(maxLessons) + " lessons)";
}

// ===== OPERATION 3: Teacher Schedule Analysis (Enhanced) =====
void analyzeTeacherSchedules(const vector<Schedule*>& schedules, const vector<Course>& courses) {
    cout << "\n=== TEACHER SCHEDULE ANALYSIS ===\n";

    // Ask user for teacher name
    string teacherName;
    cout << "Enter teacher name: ";
    getline(cin, teacherName);

    if (teacherName.empty()) {
        cout << "No teacher name provided.\n";
        return;
    }

    cout << "\nSearching for lessons taught by: " << teacherName << "\n";
    cout << "==========================================\n";

    // Structure to store teacher's lessons: {courseId, lessonType, day, startTime, endTime, room, group}
    vector<tuple<int, string, string, string, string, string, string>> teacherLessons;

    // Search in all three CSV files
    vector<string> filenames = { "lectures.csv", "tutorials.csv", "labs.csv" };
    vector<string> lessonTypes = { "Lecture", "Tutorial", "Lab" };

    for (size_t i = 0; i < filenames.size(); i++) {
        ifstream inFile(filenames[i]);
        if (!inFile.is_open()) {
            cout << "Warning: " << filenames[i] << " not found.\n";
            continue;
        }

        string line;
        getline(inFile, line); // skip header

        while (getline(inFile, line)) {
            if (line.empty()) continue;

            stringstream ss(line);
            string typeColumn, courseIdStr, day, startTime, endTime, room, teacher, groupStr;

            // CSV format: type,course_id,day,start_time,end_time,room,teacher_name,group
            getline(ss, typeColumn, ',');
            getline(ss, courseIdStr, ',');
            getline(ss, day, ',');
            getline(ss, startTime, ',');
            getline(ss, endTime, ',');
            getline(ss, room, ',');
            getline(ss, teacher, ',');
            getline(ss, groupStr, ',');

            try {
                // Check if this lesson is taught by the specified teacher
                if (!teacher.empty() && teacher == teacherName) {
                    int courseId = stoi(courseIdStr);

                    // Store lesson information
                    teacherLessons.push_back(make_tuple(
                        courseId,
                        lessonTypes[i],
                        day,
                        startTime,
                        endTime,
                        room,
                        groupStr
                    ));
                }
            }
            catch (const exception&) {
                // Skip invalid lines
                continue;
            }
        }
        inFile.close();
    }

    // Display results
    if (teacherLessons.empty()) {
        cout << "No lessons found for teacher: " << teacherName << "\n";
        cout << "Please check the spelling and try again.\n";
        return;
    }

    // Sort lessons by course ID and then by lesson type - using simple function instead of lambda
    sort(teacherLessons.begin(), teacherLessons.end(), compareTeacherLessons);

    cout << "\n--- Lessons taught by " << teacherName << " ---\n";
    cout << setw(8) << "Course" << setw(25) << "Course Name" << setw(10) << "Type"
        << setw(10) << "Day" << setw(12) << "Time" << setw(8) << "Room" << setw(8) << "Group" << "\n";
    cout << string(91, '-') << "\n";

    int totalLessons = 0;
    int totalHours = 0;
    map<string, int> lessonTypeCount;
    map<int, string> courseIdToName;

    // Create a map of course IDs to course names
    for (const Course& course : courses) {
        courseIdToName[course.getId()] = course.getName();
    }

    for (const tuple<int, string, string, string, string, string, string>& lesson : teacherLessons) {
        int courseId = get<0>(lesson);
        string lessonType = get<1>(lesson);
        string day = get<2>(lesson);
        string startTime = get<3>(lesson);
        string endTime = get<4>(lesson);
        string room = get<5>(lesson);
        string group = get<6>(lesson);

        // Find course name
        string courseName = "Unknown Course";
        if (courseIdToName.find(courseId) != courseIdToName.end()) {
            courseName = courseIdToName[courseId];
            if (courseName.length() > 23) {
                courseName = courseName.substr(0, 20) + "...";
            }
        }

        // Calculate lesson duration
        int duration = 0;
        try {
            int startHour = parseTimeToHour(startTime);
            int endHour = parseTimeToHour(endTime);
            duration = endHour - startHour;
            totalHours += duration;
        }
        catch (const exception&) {
            duration = 0;
        }

        string timeSlot = startTime + "-" + endTime;

        cout << setw(8) << courseId << setw(25) << courseName << setw(10) << lessonType
            << setw(10) << day << setw(12) << timeSlot << setw(8) << room << setw(8) << group << "\n";

        totalLessons++;
        lessonTypeCount[lessonType]++;
    }

    // Summary statistics
    cout << "\n--- Summary for " << teacherName << " ---\n";
    cout << "Total lessons: " << totalLessons << "\n";
    cout << "Total teaching hours per week: " << totalHours << " hours\n";
    cout << "Lesson breakdown:\n";
    for (const pair<string, int>& entry : lessonTypeCount) {
        cout << "  " << entry.first << ": " << entry.second << " lessons\n";
    }

    // Find unique courses
    set<int> uniqueCourses;
    for (const tuple<int, string, string, string, string, string, string>& lesson : teacherLessons) {
        uniqueCourses.insert(get<0>(lesson));
    }
    cout << "Number of different courses: " << uniqueCourses.size() << "\n";

    // Find busiest day using simple function instead of max_element with lambda
    map<string, int> dayCount;
    for (const tuple<int, string, string, string, string, string, string>& lesson : teacherLessons) {
        dayCount[get<2>(lesson)]++;
    }

    if (!dayCount.empty()) {
        cout << "Busiest day: " << findBusiestDay(dayCount) << "\n";
    }
}

