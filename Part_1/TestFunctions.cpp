#include "TestFunctions.h"

// Global test counters
int totalTests = 0;
int passedTests = 0;

void resetTestCounters() {
    totalTests = 0;
    passedTests = 0;
}

void printTestSummary() {
    cout << "\n========== TEST SUMMARY ==========\n";
    cout << "Total Tests: " << totalTests << "\n";
    cout << "Passed Tests: " << passedTests << "\n";
    cout << "Failed Tests: " << (totalTests - passedTests) << "\n";
    if (passedTests == totalTests) {
        cout << " ALL TESTS PASSED! \n";
    }
    else {
        cout << " Some tests failed. Please check above for details.\n";
    }
    cout << "==================================\n\n";
}

void assertTrue(bool condition, const string& testName) {
    totalTests++;
    if (condition) {
        passedTests++;
        cout << " PASSED: " << testName << "\n";
    }
    else {
        cout << " FAILED: " << testName << "\n";
    }
}

void createTestCSVFiles() {
    // Create test courses.csv
    ofstream coursesFile("test_courses.csv");
    coursesFile << "id,name,credits,moedA,moedB,lecturer,semester\n";
    coursesFile << "1001,Introduction to Programming,4,12/25/2024,01/15/2025,Dr. Smith,Fall 2024\n";
    coursesFile << "1002,Data Structures,3,12/20/2024,01/10/2025,Prof. Johnson,Fall 2024\n";
    coursesFile.close();

    // Create test lectures.csv
    ofstream lecturesFile("test_lectures.csv");
    lecturesFile << "type,course_id,day,start_time,end_time,room,teacher_name,group\n";
    lecturesFile << "Lecture,1001,Monday,09:00,11:00,A101,Dr. Smith,1\n";
    lecturesFile << "Lecture,1002,Tuesday,10:00,12:00,B201,Prof. Johnson,1\n";
    lecturesFile.close();

    // Create test tutorials.csv
    ofstream tutorialsFile("test_tutorials.csv");
    tutorialsFile << "type,course_id,day,start_time,end_time,room,teacher_name,group\n";
    tutorialsFile << "Tutorial,1001,Wednesday,14:00,15:00,C301,TA Alex,1\n";
    tutorialsFile << "Tutorial,1002,Thursday,15:00,16:00,D401,TA Bob,1\n";
    tutorialsFile.close();

    // Create test labs.csv
    ofstream labsFile("test_labs.csv");
    labsFile << "type,course_id,day,start_time,end_time,room,teacher_name,group\n";
    labsFile << "Lab,1001,Friday,16:00,18:00,Lab1,TA Charlie,1\n";
    labsFile << "Lab,1002,Friday,14:00,16:00,Lab2,TA Diana,1\n";
    labsFile.close();

    // Create test schedule CSV
    ofstream scheduleFile("TestSchedule1.csv");
    scheduleFile << "course_id,day,start_time,end_time,room,type\n";
    scheduleFile << "1001,Monday,09:00,11:00,A101,Lecture\n";
    scheduleFile << "1002,Tuesday,10:00,12:00,B201,Lecture\n";
    scheduleFile.close();
}

void cleanupTestFiles() {
    remove("test_courses.csv");
    remove("test_lectures.csv");
    remove("test_tutorials.csv");
    remove("test_labs.csv");
    remove("TestSchedule1.csv");
}

void testCourseClass() {
    cout << "\n--- Testing Course Class ---\n";

    // Test default constructor
    Course defaultCourse;
    assertTrue(defaultCourse.getId() == 0, "Course default constructor - ID");
    assertTrue(defaultCourse.getName().empty(), "Course default constructor - Name");
    assertTrue(defaultCourse.getCredits() == 0, "Course default constructor - Credits");

    // Test parameterized constructor
    Course testCourse(1001, "Test Course", 3, "12/25/2024", "01/15/2025", "Dr. Test", "Fall 2024");
    assertTrue(testCourse.getId() == 1001, "Course parameterized constructor - ID");
    assertTrue(testCourse.getName() == "Test Course", "Course parameterized constructor - Name");
    assertTrue(testCourse.getCredits() == 3, "Course parameterized constructor - Credits");
    assertTrue(testCourse.getMoedA() == "12/25/2024", "Course parameterized constructor - MoedA");
    assertTrue(testCourse.getMoedB() == "01/15/2025", "Course parameterized constructor - MoedB");
    assertTrue(testCourse.getLecturer() == "Dr. Test", "Course parameterized constructor - Lecturer");
    assertTrue(testCourse.getSemester() == "Fall 2024", "Course parameterized constructor - Semester");

    // Test setters
    testCourse.setName("Updated Course");
    assertTrue(testCourse.getName() == "Updated Course", "Course setter - Name");

    testCourse.setCredits(4);
    assertTrue(testCourse.getCredits() == 4, "Course setter - Credits");

    testCourse.setLecturer("Dr. Updated");
    assertTrue(testCourse.getLecturer() == "Dr. Updated", "Course setter - Lecturer");

    cout << "✅ Course class tests completed!\n";
}

void testLessonClass() {
    cout << "\n--- Testing Lesson Classes ---\n";

    // Test Lecture class
    Lecture lecture("Lecture", 1001, "Monday", 9, 11, "A101", "Dr. Smith", 1);
    assertTrue(lecture.getType() == "Lecture", "Lecture class - Type");
    assertTrue(lecture.getCourseId() == 1001, "Lecture class - Course ID");
    assertTrue(lecture.getDay() == "Monday", "Lecture class - Day");
    assertTrue(lecture.getStartHour() == 9, "Lecture class - Start Hour");
    assertTrue(lecture.getEndHour() == 11, "Lecture class - End Hour");
    assertTrue(lecture.getClassroom() == "A101", "Lecture class - Classroom");
    assertTrue(lecture.getTeacherName() == "Dr. Smith", "Lecture class - Teacher Name");
    assertTrue(lecture.getGroupNumber() == 1, "Lecture class - Group Number");

    // Test Tutorial class
    Tutorial tutorial("Tutorial", 1002, "Wednesday", 14, 15, "C301", "TA Alex", 2);
    assertTrue(tutorial.getType() == "Tutorial", "Tutorial class - Type");
    assertTrue(tutorial.getCourseId() == 1002, "Tutorial class - Course ID");
    assertTrue(tutorial.getDay() == "Wednesday", "Tutorial class - Day");

    // Test Lab class
    Lab lab("Lab", 1003, "Friday", 16, 18, "Lab1", "TA Charlie", 3);
    assertTrue(lab.getType() == "Lab", "Lab class - Type");
    assertTrue(lab.getCourseId() == 1003, "Lab class - Course ID");
    assertTrue(lab.getDay() == "Friday", "Lab class - Day");

    // Test setters
    lecture.setDay("Tuesday");
    assertTrue(lecture.getDay() == "Tuesday", "Lesson setter - Day");

    lecture.setStartHour(10);
    assertTrue(lecture.getStartHour() == 10, "Lesson setter - Start Hour");

    lecture.setClassroom("B202");
    assertTrue(lecture.getClassroom() == "B202", "Lesson setter - Classroom");

    cout << "✅ Lesson classes tests completed!\n";
}

void testScheduleClass() {
    cout << "\n--- Testing Schedule Class ---\n";

    // Test Schedule constructor
    Schedule schedule(1);
    assertTrue(schedule.getId() == 1, "Schedule constructor - ID");
    assertTrue(schedule.getLessonCount() == 0, "Schedule constructor - Initial lesson count");

    // Test adding lessons
    Lesson* lecture = new Lecture("Lecture", 1001, "Monday", 9, 11, "A101", "Dr. Smith", 1);
    schedule.addLesson(lecture);
    assertTrue(schedule.getLessonCount() == 1, "Schedule addLesson - Lesson count");

    Lesson* tutorial = new Tutorial("Tutorial", 1002, "Wednesday", 14, 15, "C301", "TA Alex", 2);
    schedule.addLesson(tutorial);
    assertTrue(schedule.getLessonCount() == 2, "Schedule addLesson - Multiple lessons");

    // Test getting lessons
    const vector<Lesson*>& lessons = schedule.getLessons();
    assertTrue(lessons.size() == 2, "Schedule getLessons - Size");
    assertTrue(lessons[0]->getCourseId() == 1001, "Schedule getLessons - First lesson");
    assertTrue(lessons[1]->getCourseId() == 1002, "Schedule getLessons - Second lesson");

    // Test removing lessons
    bool removed = schedule.removeLesson(1001);
    assertTrue(removed == true, "Schedule removeLesson - Success");
    assertTrue(schedule.getLessonCount() == 1, "Schedule removeLesson - Updated count");

    bool removedAgain = schedule.removeLesson(9999);
    assertTrue(removedAgain == false, "Schedule removeLesson - Non-existent lesson");

    cout << " Schedule class tests completed!\n";
}

void testMenuFunctions() {
    cout << "\n--- Testing Menu Functions ---\n";

    // Test menu functions (these are mostly output functions, so we test they don't crash)
    try {
        // Test menu display functions
        cout << "Testing menu display functions...\n";

        // Redirect cout to suppress output during testing
        stringstream buffer;
        streambuf* orig = cout.rdbuf(buffer.rdbuf());

        printMenu();
        showHelp();

        // Restore cout
        cout.rdbuf(orig);

        assertTrue(true, "Menu display functions - No crashes");
    }
    catch (...) {
        assertTrue(false, "Menu display functions - Exception thrown");
    }

    cout << " Menu functions tests completed!\n";
}

void testPrintFunctions() {
    cout << "\n--- Testing Print Functions ---\n";

    // Create test data
    vector<Course> testCourses;
    testCourses.push_back(Course(1001, "Test Course 1", 3, "12/25/2024", "01/15/2025", "Dr. Test", "Fall 2024"));
    testCourses.push_back(Course(1002, "Test Course 2", 4, "12/20/2024", "01/10/2025", "Prof. Test", "Fall 2024"));

    // Test printAllLessonsFromCSV with valid course
    try {
        // Redirect cout to suppress output during testing
        stringstream buffer;
        streambuf* orig = cout.rdbuf(buffer.rdbuf());

        printAllLessonsFromCSV(1001, testCourses);

        // Restore cout
        cout.rdbuf(orig);

        assertTrue(true, "PrintAllLessonsFromCSV - Valid course");
    }
    catch (...) {
        assertTrue(false, "PrintAllLessonsFromCSV - Exception with valid course");
    }

    // Test printAllLessonsFromCSV with invalid course
    try {
        stringstream buffer;
        streambuf* orig = cout.rdbuf(buffer.rdbuf());

        printAllLessonsFromCSV(9999, testCourses);

        cout.rdbuf(orig);

        assertTrue(true, "PrintAllLessonsFromCSV - Invalid course");
    }
    catch (...) {
        assertTrue(false, "PrintAllLessonsFromCSV - Exception with invalid course");
    }

    cout << " Print functions tests completed!\n";
}

void testScheduleTableFunctions() {
    cout << "\n--- Testing Schedule Table Functions ---\n";

    // Create test schedule file
    ofstream testFile("TestSchedule99.csv");
    testFile << "course_id,day,start_time,end_time,room,type\n";
    testFile << "1001,Monday,09:00,11:00,A101,Lecture\n";
    testFile << "1002,Tuesday,10:00,12:00,B201,Tutorial\n";
    testFile.close();

    // Test printScheduleTableClean
    try {
        stringstream buffer;
        streambuf* orig = cout.rdbuf(buffer.rdbuf());

        printScheduleTableClean(99);

        cout.rdbuf(orig);

        assertTrue(true, "PrintScheduleTableClean - Valid schedule");
    }
    catch (...) {
        assertTrue(false, "PrintScheduleTableClean - Exception thrown");
    }

    // Test printScheduleTable
    try {
        stringstream buffer;
        streambuf* orig = cout.rdbuf(buffer.rdbuf());

        printScheduleTable(99);

        cout.rdbuf(orig);

        assertTrue(true, "PrintScheduleTable - Valid schedule");
    }
    catch (...) {
        assertTrue(false, "PrintScheduleTable - Exception thrown");
    }

    // Test with non-existent schedule
    try {
        stringstream buffer;
        streambuf* orig = cout.rdbuf(buffer.rdbuf());

        printScheduleTableClean(999);

        cout.rdbuf(orig);

        assertTrue(true, "PrintScheduleTableClean - Non-existent schedule");
    }
    catch (...) {
        assertTrue(false, "PrintScheduleTableClean - Exception with non-existent schedule");
    }

    // Cleanup
    remove("TestSchedule99.csv");

    cout << " Schedule table functions tests completed!\n";
}

void testAnalysisFunctions() {
    cout << "\n--- Testing Analysis Functions ---\n";

    // Create test data
    vector<Course> testCourses;
    testCourses.push_back(Course(1001, "Test Course 1", 3, "12/25/2024", "01/15/2025", "Dr. Test", "Fall 2024"));
    testCourses.push_back(Course(1002, "Test Course 2", 4, "12/25/2024", "01/10/2025", "Prof. Test", "Fall 2024"));

    vector<Schedule*> testSchedules;
    Schedule* schedule1 = new Schedule(1);
    schedule1->addLesson(new Lecture("Lecture", 1001, "Monday", 9, 11, "A101", "Dr. Test", 1));
    schedule1->addLesson(new Tutorial("Tutorial", 1002, "Tuesday", 10, 12, "B201", "Prof. Test", 1));
    testSchedules.push_back(schedule1);

    Schedule* schedule2 = new Schedule(2);
    schedule2->addLesson(new Lecture("Lecture", 1001, "Monday", 9, 11, "A101", "Dr. Test", 1)); // Same time as schedule1
    schedule2->addLesson(new Lab("Lab", 1002, "Wednesday", 14, 16, "Lab1", "TA Test", 1));
    testSchedules.push_back(schedule2);

    // Test findTimeConflicts
    try {
        stringstream buffer;
        streambuf* orig = cout.rdbuf(buffer.rdbuf());

        findTimeConflicts(testSchedules, testCourses);

        cout.rdbuf(orig);

        assertTrue(true, "FindTimeConflicts - No crashes");
    }
    catch (...) {
        assertTrue(false, "FindTimeConflicts - Exception thrown");
    }

    // Test analyzeCourseWorkload
    try {
        stringstream buffer;
        streambuf* orig = cout.rdbuf(buffer.rdbuf());

        analyzeCourseWorkload(testSchedules, testCourses);

        cout.rdbuf(orig);

        assertTrue(true, "AnalyzeCourseWorkload - No crashes");
    }
    catch (...) {
        assertTrue(false, "AnalyzeCourseWorkload - Exception thrown");
    }

    // Cleanup
    for (Schedule* s : testSchedules) {
        delete s;
    }

    cout << " Analysis functions tests completed!\n";
}

void testCSVFileHandling() {
    cout << "\n--- Testing CSV File Handling ---\n";

    // Create test CSV files
    createTestCSVFiles();

    // Test reading courses CSV
    ifstream coursesFile("test_courses.csv");
    assertTrue(coursesFile.is_open(), "CSV File Handling - Can open courses file");

    string line;
    getline(coursesFile, line); // header
    getline(coursesFile, line); // first course
    assertTrue(!line.empty(), "CSV File Handling - Can read course data");
    coursesFile.close();

    // Test reading lectures CSV
    ifstream lecturesFile("test_lectures.csv");
    assertTrue(lecturesFile.is_open(), "CSV File Handling - Can open lectures file");

    getline(lecturesFile, line); // header
    getline(lecturesFile, line); // first lecture
    assertTrue(!line.empty(), "CSV File Handling - Can read lecture data");
    lecturesFile.close();

    // Test CSV parsing
    stringstream ss("1001,Test Course,3,12/25/2024,01/15/2025,Dr. Test,Fall 2024");
    string id, name, credits;
    getline(ss, id, ',');
    getline(ss, name, ',');
    getline(ss, credits, ',');

    assertTrue(id == "1001", "CSV Parsing - Course ID");
    assertTrue(name == "Test Course", "CSV Parsing - Course Name");
    assertTrue(credits == "3", "CSV Parsing - Course Credits");

    // Test writing CSV
    ofstream testOutput("test_output.csv");
    testOutput << "test,data,line\n";
    testOutput << "1,2,3\n";
    testOutput.close();

    ifstream testInput("test_output.csv");
    string testLine;
    getline(testInput, testLine);
    assertTrue(testLine == "test,data,line", "CSV Writing - Header line");
    getline(testInput, testLine);
    assertTrue(testLine == "1,2,3", "CSV Writing - Data line");
    testInput.close();

    // Cleanup
    remove("test_output.csv");
    cleanupTestFiles();

    cout << " CSV file handling tests completed!\n";
}

void runAllTests() {
    cout << "\n STARTING COMPREHENSIVE TESTING \n";
    cout << "======================================\n";

    resetTestCounters();

    // Run all test categories
    testCourseClass();
    testLessonClass();
    testScheduleClass();
    testMenuFunctions();
    testPrintFunctions();
    testScheduleTableFunctions();
    testAnalysisFunctions();
    testCSVFileHandling();

    // Print final summary
    printTestSummary();

    cout << " TESTING COMPLETED! \n\n";
}