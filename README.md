# OOP Final Project: Schedule Manager for Students

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)

## 📋 Table of Contents
- [Project Overview](#project-overview)
- [Academic Context](#academic-context)
- [Project Architecture](#project-architecture)
- [Part 1: Basic Schedule Management System](#part-1-basic-schedule-management-system)
- [Part 2: Enhanced System with Improved Architecture](#part-2-enhanced-system-with-improved-architecture)
- [Part 3: Advanced Features and Optimizations](#part-3-advanced-features-and-optimizations)
- [Features Comparison](#features-comparison)
- [Installation & Compilation](#installation--compilation)
- [Usage Guide](#usage-guide)
- [Project Structure](#project-structure)
- [Technologies Used](#technologies-used)
- [Contributors](#contributors)
- [License](#license)

---

## 🎓 Project Overview

The **Schedule Manager for Students** is a comprehensive Object-Oriented Programming (OOP) project developed as a final assignment. This system demonstrates the application of core OOP principles including inheritance, polymorphism, encapsulation, and abstraction to solve real-world scheduling problems in an academic environment.

### Purpose
The primary goal of this project is to create a robust course scheduling system that allows students to:
- Manage multiple course schedules
- Track lectures, tutorials, and laboratory sessions
- Detect scheduling conflicts
- Analyze workload distribution
- Organize academic planning efficiently

The project is divided into **three progressive parts**, each building upon the previous with increasing complexity and sophistication.

---

## 🎯 Academic Context

This project was developed as the final assignment for an Object-Oriented Programming course. It demonstrates:

- **Design Patterns**: Implementation of proper class hierarchies and relationships
- **Data Persistence**: File I/O operations for saving and loading schedules
- **Error Handling**: Robust input validation and exception management
- **Testing**: Comprehensive test suites for quality assurance
- **Code Organization**: Modular design with separation of concerns

### Learning Objectives
1. Apply OOP principles to a complex, real-world problem
2. Design and implement class hierarchies using inheritance
3. Utilize polymorphism for flexible and extensible code
4. Implement file-based data persistence
5. Create user-friendly command-line interfaces
6. Develop comprehensive testing strategies

---

## 🏗️ Project Architecture

The system uses a hierarchical class structure based on OOP principles:

```
┌─────────────────────────────────────────────────────────┐
│                    Course Management                     │
│  ┌──────────┐         ┌──────────┐                      │
│  │  Course  │◄────────┤ Schedule │                      │
│  └──────────┘         └────┬─────┘                      │
│                            │                             │
│                            │ contains                    │
│                            ▼                             │
│                   ┌────────────────┐                     │
│                   │  Lesson (ABC)  │                     │
│                   └────────┬───────┘                     │
│                            │                             │
│              ┌─────────────┼─────────────┐               │
│              ▼             ▼             ▼               │
│         ┌─────────┐  ┌──────────┐  ┌──────┐             │
│         │ Lecture │  │ Tutorial │  │ Lab  │             │
│         └─────────┘  └──────────┘  └──────┘             │
└─────────────────────────────────────────────────────────┘
```

### Core Classes

#### Lesson (Abstract Base Class)
The parent class for all lesson types, providing common attributes:
- Course ID
- Day of the week
- Start and end hours
- Classroom location
- Teacher name
- Group number

#### Derived Classes
- **Lecture**: Represents theoretical course sessions
- **Tutorial**: Represents practice and problem-solving sessions
- **Lab**: Represents hands-on laboratory work

#### Course
Represents an academic course with:
- Course ID and name
- Credit hours
- Exam dates (Moed A, Moed B)
- Lecturer information
- Semester details

#### Schedule
Manages a collection of lessons:
- Schedule ID
- List of lessons
- Conflict detection
- Workload analysis

---

## 📚 Part 1: Basic Schedule Management System

### Overview
Part 1 establishes the foundation of the schedule management system with essential features for course and schedule handling.

![Part 1 Architecture](docs/images/part1_architecture.png)

### Key Features

#### 1. Course Management
- **Print Course** (`PrintCourse <course_id>`): Display detailed information about a specific course including all lesson types
- **Print Courses** (`PrintCourses`): Display first 10 courses with pagination support
- **More** (`More`): View next 10 courses in the list
- **Data Loading**: Automatic loading of course data from CSV files on startup

#### 2. Schedule Management
- **Print Schedule** (`PrintSchedule <schedule_id>`): Display a specific schedule in a formatted table view
- **Print Schedules** (`PrintSchedules`): Display all available schedules
- **Add Schedule** (`AddSchedule`): Create a new empty schedule with automatic ID assignment
- **Remove Schedule** (`RmSchedule <schedule_id>`): Delete a schedule and compact IDs to remove gaps

#### 3. Lesson Management
- **Add Lesson** (`Add <sched> <course> <group>`): Add lessons (Lecture/Tutorial/Lab) to a schedule
  - Interactive selection of lesson type
  - Automatic conflict detection
  - Visual feedback on course completion
- **Remove Lesson** (`Rm <sched> <course> <group> <type>`): Remove specific lessons from a schedule

#### 4. Analysis Features
- **Find Time Conflicts**: Detect scheduling conflicts across all schedules
- **Course Workload Analysis**: Analyze weekly workload distribution
- **Teacher Schedule Analysis**: View teaching assignments across schedules

#### 5. System Features
- **Help** (`Help`): Display comprehensive command reference
- **Clear** (`Clear`): Clear screen (platform-dependent)
- **Exit** (`Exit`): Save all data and exit the program

### Implementation Details

#### File Structure (Part 1)
```
Part_1/
├── Course.h/cpp           # Course class definition and implementation
├── Lesson.h/cpp           # Abstract Lesson base class
├── Lecture.h/cpp          # Lecture derived class
├── Tutorial.h/cpp         # Tutorial derived class
├── Lab.h/cpp              # Lab derived class
├── Schedule.h/cpp         # Schedule management
├── FileManager.h/cpp      # CSV file operations
├── MenuFunctions.h/cpp    # User interface and menu handling
├── TestFunctions.h/cpp    # Testing utilities
└── main.cpp               # Program entry point
```

#### Data Persistence
Part 1 uses CSV files for data storage:
- **courses.csv**: Course information
- **schedules.csv**: Schedule index
- **Schedule[ID].csv**: Individual schedule data
- **Lecture.csv**, **Tutorial.csv**, **Lab.csv**: Lesson data organized by type

### Example Workflow

```
1. Launch the program
2. Select option 2: PrintCourses (view available courses)
3. Select option 6: AddSchedule (create your schedule)
4. Select option 8: Add <sched> <course> (add courses to your schedule)
   - Choose lesson type (Lecture/Tutorial/Lab)
   - Repeat for all lesson types to complete the course
5. Select option 4: PrintSchedule (view your completed schedule)
6. Select option 13: Find Time Conflicts (check for conflicts)
7. Select option 12: Exit (save and exit)
```

### Code Example: Adding a Lesson

```cpp
// Example: Adding a lecture to Schedule 1 for Course 101
cout << "Enter Schedule ID: "; // Input: 1
cout << "Enter Course ID: ";   // Input: 101
cout << "Choose lesson type:\n";
cout << "1 - Lecture\n";
cout << "2 - Tutorial\n"; 
cout << "3 - Lab\n";
cout << "Enter choice: ";      // Input: 1

// System adds the lecture and provides feedback
```

---

## 🚀 Part 2: Enhanced System with Improved Architecture

### Overview
Part 2 represents a significant architectural improvement with a cleaner design, better separation of concerns, and comprehensive testing.

![Part 2 Architecture](docs/images/part2_architecture.png)

### Major Improvements

#### 1. System Class Architecture
The introduction of the `System` class provides centralized management:
- **Unified Interface**: Single point of control for all operations
- **Better Encapsulation**: Private data members with controlled access
- **Enhanced Menu System**: More intuitive user interface
- **Improved Error Handling**: Comprehensive input validation

#### 2. Comprehensive Testing Framework
Part 2 includes a robust testing suite (`Tests.h/cpp`):

```cpp
class Tests {
public:
    // Course Management Tests
    static bool testCourseCreation();
    static bool testCourseGetters();
    static bool testCourseSetters();
    
    // Lesson Tests
    static bool testLessonCreation();
    static bool testLessonPolymorphism();
    
    // Schedule Tests
    static bool testScheduleCreation();
    static bool testAddLessonToSchedule();
    static bool testRemoveLessonFromSchedule();
    static bool testConflictDetection();
    
    // Integration Tests
    static bool testCompleteWorkflow();
    
    // Run all tests
    static bool runAllTests();
};
```

#### 3. Main Menu System
Part 2 features a two-tiered menu:

```
=== COURSE MANAGEMENT SYSTEM ===
1. Run Course Management System
2. Run Test Suite
3. Exit
```

The Course Management System submenu includes all features from Part 1 plus additional enhancements.

#### 4. Enhanced Features

##### Improved Schedule Display
- Clean table format with column alignment
- Visual separators for better readability
- Detailed schedule information display

##### Better Conflict Detection
```cpp
void handleCheckConflicts(const string& scheduleId) {
    // Advanced conflict detection algorithm
    // Reports conflicts with specific details:
    // - Conflicting lessons
    // - Time overlap details
    // - Affected courses
}
```

##### Workload Analysis
```cpp
void handleAnalyzeCourseWorkload(const string& scheduleId) {
    // Calculates:
    // - Total weekly hours
    // - Hours per day breakdown
    // - Course distribution
    // - Credit hour analysis
}
```

### Implementation Details

#### File Structure (Part 2)
```
Part_2/
├── Course.h/cpp                    # Enhanced course class
├── Lesson.h/cpp                    # Improved lesson base class
├── Lecture.h/cpp                   # Lecture implementation
├── Tutorial.h/cpp                  # Tutorial implementation
├── Lab.h/cpp                       # Lab implementation
├── Schedule.h/cpp                  # Enhanced schedule management
├── System.h/cpp                    # System controller (NEW)
├── Tests.h/cpp                     # Comprehensive test suite (NEW)
├── main.cpp                        # Simplified entry point
└── TEST_SCHEDULE_MANAGEMENT.md     # Testing documentation
```

#### Key Architectural Changes

**Before (Part 1)**: Direct manipulation of data structures in main.cpp
```cpp
// Part 1 approach
vector<Course> courses;
vector<Schedule*> schedules;
// Direct operations on vectors
```

**After (Part 2)**: Encapsulated system with controlled access
```cpp
// Part 2 approach
System courseSystem;
courseSystem.run();
// All operations through System interface
```

### Testing Strategy

Part 2 implements systematic testing:

1. **Unit Tests**: Individual class functionality
2. **Integration Tests**: Multi-class interactions
3. **System Tests**: Complete workflow scenarios
4. **Regression Tests**: Ensure changes don't break existing features

#### Running Tests

```bash
# Compile Part 2
g++ -std=c++11 Part_2/*.cpp -o schedule_manager_v2

# Run the program
./schedule_manager_v2

# Select option 2: Run Test Suite
```

### Code Quality Improvements

#### Memory Management
```cpp
// Improved destructor implementation
System::~System() {
    // Clean up dynamically allocated lessons
    for (Lesson* lesson : lessons) {
        delete lesson;
    }
    lessons.clear();
}
```

#### Input Validation
```cpp
int System::getIntInput(const string& prompt) {
    int value;
    while (true) {
        cout << prompt;
        if (cin >> value) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return value;
        }
        cout << "Invalid input. Please enter a number.\n";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}
```

---

## ⭐ Part 3: Advanced Features and Optimizations

### Overview
Part 3 builds upon the solid foundation of Parts 1 and 2, introducing advanced features, optimizations, and real-world enhancements documented in `part 3_Base44.docx`.

### Planned Enhancements

#### 1. Database Integration
- Transition from CSV to database backend
- Support for SQLite or MySQL
- Improved query performance
- Better data integrity

#### 2. Advanced Search Capabilities
```
Features:
- Multi-criteria search
- Fuzzy matching for course names
- Filter by time slots
- Filter by teacher
- Filter by classroom availability
```

#### 3. Export and Reporting
- **PDF Export**: Generate printable schedules
- **iCalendar Format**: Export to calendar applications
- **Statistics Reports**: Detailed analytics
- **Visual Charts**: Workload distribution graphs

#### 4. User Preferences
```cpp
class UserPreferences {
    - Preferred time slots
    - Blocked time periods
    - Maximum daily hours
    - Preferred course types
    - Campus preferences
};
```

#### 5. Schedule Optimization
```
Algorithms:
- Minimize gaps between classes
- Balance workload across days
- Optimize classroom assignments
- Reduce cross-campus travel
```

#### 6. Multi-User Support
- User authentication
- Personal schedule management
- Shared schedules (study groups)
- Role-based access (student/admin/teacher)

#### 7. Web Interface (Future)
```
Technology Stack:
- Backend: REST API (C++ or migration to modern framework)
- Frontend: React/Vue.js
- Database: PostgreSQL
- Authentication: JWT
```

### Implementation Roadmap

```
Phase 1 (Completed): ✓ Part 1 - Basic functionality
Phase 2 (Completed): ✓ Part 2 - Enhanced architecture
Phase 3 (Current):    ⚡ Advanced features
Phase 4 (Future):     🌐 Web-based system
```

---

## 📊 Features Comparison

| Feature | Part 1 | Part 2 | Part 3 (Planned) |
|---------|--------|--------|------------------|
| Course Management | ✓ | ✓ | ✓ |
| Schedule Creation | ✓ | ✓ | ✓ |
| Lesson Management | ✓ | ✓ | ✓ |
| Conflict Detection | ✓ | ✓ Enhanced | ✓ Advanced |
| Workload Analysis | ✓ Basic | ✓ Detailed | ✓ Visual |
| Testing Framework | ✓ Basic | ✓ Comprehensive | ✓ Automated |
| System Architecture | Procedural | OOP | Enhanced OOP |
| File Format | CSV | CSV | Database |
| User Interface | CLI | Enhanced CLI | CLI + Web |
| Export Options | - | - | ✓ PDF/iCal |
| Search Capabilities | Basic | Basic | ✓ Advanced |
| Multi-User | - | - | ✓ Planned |
| Schedule Optimization | - | - | ✓ Planned |

---

## 💻 Installation & Compilation

### Prerequisites
- **Compiler**: g++ (GNU C++ Compiler) with C++11 support or later
- **Operating System**: Linux, macOS, or Windows (with MinGW)
- **Make** (optional): For automated builds

### Compilation Instructions

#### Part 1: Basic System

```bash
# Navigate to Part 1 directory
cd Part_1

# Compile all source files
g++ -std=c++11 *.cpp -o schedule_manager_v1

# Run the program
./schedule_manager_v1
```

#### Part 2: Enhanced System

```bash
# Navigate to Part 2 directory
cd Part_2

# Compile all source files
g++ -std=c++11 *.cpp -o schedule_manager_v2

# Run the program
./schedule_manager_v2
```

#### Alternative: Using Main Files

```bash
# From repository root

# Compile Part 1 using main_for_part_one.cpp
g++ -std=c++11 main_for_part_one.cpp Part_1/*.cpp -o part1_app

# Compile Part 2 using main_for_part_two.cpp
g++ -std=c++11 main_for_part_two.cpp Part_2/*.cpp -o part2_app
```

### Troubleshooting

#### Common Issues

**Issue**: `undefined reference` errors
```bash
# Solution: Ensure all .cpp files are included
g++ -std=c++11 Part_1/*.cpp -o schedule_manager_v1
```

**Issue**: Permission denied when running
```bash
# Solution: Make executable
chmod +x schedule_manager_v1
./schedule_manager_v1
```

**Issue**: CSV files not found
```bash
# Solution: Run from the correct directory where CSV files are located
cd Part_1  # or Part_2
./schedule_manager_v1
```

---

## 📖 Usage Guide

### Getting Started

#### First Time Setup (Part 2 Example)

1. **Launch the program**
```bash
./schedule_manager_v2
```

2. **Main Menu**
```
=== COURSE MANAGEMENT SYSTEM ===
1. Run Course Management System
2. Run Test Suite
3. Exit
Choose an option (1-3):
```

3. **Run Tests (Recommended First Time)**
```
Select: 2
[STARTING] Test Suite...
Running all tests...
✓ All tests completed successfully!
```

4. **Enter the System**
```
Select: 1
[STARTING] Course Management System...
```

### Basic Operations

#### Creating Your First Schedule

```
Step 1: View available courses
Menu > PrintCourses (Option 2)

Step 2: Create a new schedule  
Menu > AddSchedule (Option 6)
Output: "SUCCESS: New empty schedule created with ID 1"

Step 3: Add a course to your schedule
Menu > Add <sched> <course> (Option 8)
Input: Schedule ID: 1
Input: Course ID: 234118
Choose lesson type:
1 - Lecture
2 - Tutorial
3 - Lab
Input: 1 (for Lecture)

Step 4: Complete the course (add Tutorial and Lab)
Repeat Step 3 with options 2 and 3

Step 5: View your schedule
Menu > PrintSchedule <schedule_id> (Option 4)
Input: Schedule ID: 1
```

#### Schedule Display Example

```
==========================================
Schedule 1:
==========================================
+--------+---------+---------+---------+
| Day    | Start   | End     | Course  |
+--------+---------+---------+---------+
| Sunday | 10:00   | 13:00   | 234118  |
| Monday | 14:00   | 16:00   | 234118  |
| Tuesday| 09:00   | 12:00   | 234218  |
+--------+---------+---------+---------+
```

### Advanced Operations

#### Conflict Detection

```
Menu > Find Time Conflicts (Option 13)

Output Example:
⚠ WARNING: Conflict detected!
Schedule: 1
Courses: 234118 and 234218
Day: Monday
Time: 14:00 - 15:00
Classroom: Building 32, Room 101
```

#### Workload Analysis

```
Menu > Course Workload Analysis (Option 14)

Output Example:
=== Weekly Workload Analysis ===
Total Hours: 24
Average per Day: 4.8

Daily Breakdown:
Sunday:    6 hours
Monday:    5 hours
Tuesday:   4 hours
Wednesday: 5 hours
Thursday:  4 hours
```

#### Teacher Schedule

```
Menu > Teacher Schedule Analysis (Option 15)

Output Example:
=== Dr. Smith's Schedule ===
Total Teaching Hours: 18

Courses:
- 234118 Introduction to CS (6 hours)
- 234218 Data Structures (6 hours)
- 234319 Algorithms (6 hours)
```

### Menu Reference

#### Part 1 & Part 2 Common Commands

| Option | Command | Description |
|--------|---------|-------------|
| 1 | PrintCourse | Display course details |
| 2 | PrintCourses | List first 10 courses |
| 3 | More | Show next 10 courses |
| 4 | PrintSchedule | Display schedule table |
| 5 | PrintSchedules | List all schedules |
| 6 | AddSchedule | Create new schedule |
| 7 | RmSchedule | Remove schedule |
| 8 | Add | Add lesson to schedule |
| 9 | Rm | Remove lesson from schedule |
| 10 | Clear | Clear screen |
| 11 | Help | Display help |
| 12 | Exit | Save and exit |
| 13 | Conflicts | Find time conflicts |
| 14 | Workload | Analyze course workload |
| 15 | Teacher | Analyze teacher schedule |
| 16 | Test | Run test suite (Part 1) |

---

## 📁 Project Structure

### Complete Directory Layout

```
OOP_Final_Project_ScheduleManager_for_student-/
│
├── Part_1/                          # Part 1: Basic System
│   ├── Course.h                     # Course class interface
│   ├── Course.cpp                   # Course class implementation
│   ├── Lesson.h                     # Lesson abstract base class
│   ├── Lesson.cpp                   # Lesson implementation
│   ├── Lecture.h                    # Lecture derived class
│   ├── Lecture.cpp
│   ├── Tutorial.h                   # Tutorial derived class
│   ├── Tutorial.cpp
│   ├── Lab.h                        # Lab derived class
│   ├── Lab.cpp
│   ├── Schedule.h                   # Schedule management
│   ├── Schedule.cpp
│   ├── FileManager.h                # File I/O operations
│   ├── FileManager.cpp
│   ├── MenuFunctions.h              # UI and menu handling
│   ├── MenuFunctions.cpp
│   ├── TestFunctions.h              # Testing utilities
│   ├── TestFunctions.cpp
│   └── main.cpp                     # Program entry point
│
├── Part_2/                          # Part 2: Enhanced System
│   ├── Course.h                     # Enhanced course class
│   ├── Course.cpp
│   ├── Lesson.h                     # Improved lesson hierarchy
│   ├── Lesson.cpp
│   ├── Lecture.h
│   ├── Lecture.cpp
│   ├── Tutorial.h
│   ├── Tutorial.cpp
│   ├── Lab.h
│   ├── Lab.cpp
│   ├── Schedule.h                   # Enhanced schedule
│   ├── Schedule.cpp
│   ├── System.h                     # System controller (NEW)
│   ├── System.cpp
│   ├── Tests.h                      # Test framework (NEW)
│   ├── Tests.cpp
│   ├── main.cpp                     # Simplified entry point
│   └── TEST_SCHEDULE_MANAGEMENT.md  # Testing documentation
│
├── main_for_part_one.cpp            # Alternative Part 1 entry
├── main_for_part_two.cpp            # Alternative Part 2 entry
├── final assignment.pdf             # Project requirements
├── part 3_Base44.docx              # Part 3 documentation
├── OOP-Final-Project-ScheduleManager-for-student-.zip
├── README.md                        # This file
└── LICENSE                          # MIT License

```

### Class Diagram

```
┌─────────────────────────────────────────────────────────────────┐
│                         System (Part 2)                         │
├─────────────────────────────────────────────────────────────────┤
│ - courses: vector<Course>                                       │
│ - lessons: vector<Lesson*>                                      │
│ - schedules: vector<Schedule>                                   │
├─────────────────────────────────────────────────────────────────┤
│ + run(): void                                                   │
│ + handleAddSchedule(): void                                     │
│ + handleAddCourse(): void                                       │
│ + handleCheckConflicts(): void                                  │
└──────────────────────────┬──────────────────────────────────────┘
                           │ manages
                           ▼
         ┌─────────────────────────────────────┐
         │            Schedule                 │
         ├─────────────────────────────────────┤
         │ - id: int                           │
         │ - lessons: vector<Lesson*>          │
         ├─────────────────────────────────────┤
         │ + addLesson(Lesson*): void          │
         │ + removeLesson(...): void           │
         │ + hasConflict(...): bool            │
         └────────────┬────────────────────────┘
                      │ contains
                      ▼
         ┌─────────────────────────────────────┐
         │        Lesson (Abstract)            │
         ├─────────────────────────────────────┤
         │ # courseId: int                     │
         │ # day: string                       │
         │ # startHour: string                 │
         │ # endHour: string                   │
         │ # classroom: string                 │
         │ # teacherName: string               │
         │ # groupNumber: int                  │
         ├─────────────────────────────────────┤
         │ + display(): void = 0 (pure)        │
         │ + getType(): string = 0 (pure)      │
         └──────┬──────────┬──────────┬─────────┘
                │          │          │
       ┌────────▼───┐  ┌───▼────┐  ┌─▼────┐
       │  Lecture   │  │Tutorial│  │ Lab  │
       └────────────┘  └────────┘  └──────┘
```

---

## 🛠️ Technologies Used

### Programming Languages
- **C++11/14**: Core implementation language
- Object-Oriented Programming paradigms

### Development Tools
- **g++**: GNU C++ Compiler
- **Git**: Version control
- **GitHub**: Repository hosting

### Libraries & Standards
- **Standard Template Library (STL)**:
  - `<vector>`: Dynamic arrays for data storage
  - `<string>`: String manipulation
  - `<fstream>`: File I/O operations
  - `<iostream>`: Input/Output streams
  - `<algorithm>`: Sorting and searching algorithms
  - `<map>`: Key-value pair storage
  - `<set>`: Unique element storage

### File Formats
- **CSV (Comma-Separated Values)**: Data persistence
- **TXT**: Configuration files
- **MD (Markdown)**: Documentation

### Design Patterns
- **Inheritance**: Lesson class hierarchy
- **Polymorphism**: Virtual functions for lesson types
- **Encapsulation**: Private data with public interfaces
- **Factory Pattern**: Object creation methods

---

## 👥 Contributors

### Development Team
- **Project Lead**: Responsible for system architecture and implementation
- **Course Instructor**: Academic guidance and requirements specification

### Acknowledgments
This project was developed as part of the Object-Oriented Programming course curriculum. Special thanks to:
- Course instructors for guidance and feedback
- Classmates for testing and suggestions
- Academic institution for providing the learning environment

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

### MIT License Summary

```
Copyright (c) 2025 Schedule Manager Project Contributors

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
```

**What this means:**
- ✓ Commercial use allowed
- ✓ Modification allowed
- ✓ Distribution allowed
- ✓ Private use allowed
- ⚠ License and copyright notice must be included
- ⚠ Software is provided "as-is" without warranty

---

## 📞 Contact & Support

### Reporting Issues
If you encounter any bugs or issues:
1. Check existing issues in the repository
2. Create a new issue with:
   - Detailed description
   - Steps to reproduce
   - Expected vs actual behavior
   - System information (OS, compiler version)

### Contributing
Contributions are welcome! Please:
1. Fork the repository
2. Create a feature branch
3. Make your changes
4. Submit a pull request with detailed description

### Questions
For questions about the project:
- Open a discussion in the repository
- Contact the project maintainers
- Refer to the project documentation

---

## 🎓 Academic Integrity Notice

This project is shared as a reference and learning resource. If you are a student:

⚠️ **Important**: Using this code for your own academic assignments without proper attribution may violate your institution's academic integrity policies. 

**Recommended Use**:
- Study the implementation techniques
- Understand the design patterns
- Learn from the code structure
- Use as inspiration for your own projects
- **Always write your own code** for academic submissions

---

## 🚀 Future Enhancements

### Short-term Goals
- [ ] Implement database backend (SQLite)
- [ ] Add PDF export functionality
- [ ] Enhance search capabilities
- [ ] Improve error messages
- [ ] Add data validation

### Long-term Vision
- [ ] Web-based interface
- [ ] Mobile application
- [ ] Cloud synchronization
- [ ] Machine learning for schedule optimization
- [ ] Integration with university systems
- [ ] Real-time collaboration features

---

## 📚 Additional Resources

### Documentation
- [C++ Reference](https://en.cppreference.com/)
- [STL Documentation](https://www.cplusplus.com/reference/stl/)
- [OOP Principles Guide](https://www.tutorialspoint.com/cplusplus/cpp_object_oriented.htm)

### Related Projects
- University course scheduling systems
- Time management applications
- Academic planning tools

### Learning Materials
- Object-Oriented Design and Patterns
- Data Structures and Algorithms in C++
- Software Engineering Best Practices

---

**Last Updated**: January 2025  
**Version**: 2.0  
**Project Status**: Active Development

---

<div align="center">

### ⭐ Star this repository if you find it helpful!

Made with ❤️ for students by students

</div>
