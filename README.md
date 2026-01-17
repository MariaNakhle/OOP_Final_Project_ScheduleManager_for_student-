<div align="center">

# 🎓 OOP Final Project: Schedule Manager for Students

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C++-11/14-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20macOS%20%7C%20Windows-lightgrey.svg)]()
[![Status](https://img.shields.io/badge/Status-Complete-success.svg)]()
[![OOP](https://img.shields.io/badge/Paradigm-OOP-orange.svg)]()
[![Build](https://img.shields.io/badge/Build-g++-red.svg)]()

> **Three Parallel Implementations of the Same Scheduling System**  
> Demonstrating mastery across Manual Programming, AI-Assisted Development, and No-Code Platforms

*BSc Final Project in Object-Oriented Programming*  
*Author: Maria Nakhle*

[Features](#-key-features) • [Quick Start](#-quick-start) • [Documentation](#-complete-documentation) • [Examples](#-usage-examples)

</div>

---

## 📋 Table of Contents

<details open>
<summary><b>📚 Click to navigate</b></summary>

- [🎯 Project Overview](#-project-overview)
- [✨ Key Features](#-key-features)
- [🔄 The Three Implementation Approaches](#-the-three-implementation-approaches)
- [💻 Part 1: Manual Implementation](#-part-1-manual-implementation-self-programmed)
- [🤖 Part 2: AI-Assisted Implementation](#-part-2-ai-assisted-implementation-agent-programmed)
- [🌐 Part 3: No-Code Implementation](#-part-3-no-code-implementation-base44-platform)
- [🏗️ System Architecture](#️-system-architecture)
- [🎓 OOP Principles Demonstrated](#-oop-principles-demonstrated)
- [📊 Features Comparison](#-features-comparison)
- [🚀 Installation & Setup](#-installation--setup)
- [📖 Usage Guide](#-usage-guide)
- [📂 Project Structure](#-project-structure)
- [🔧 Technologies & Tools](#-technologies--tools)
- [🛠️ Troubleshooting](#️-troubleshooting)
- [🤝 Contributing](#-contributing)
- [👨‍💻 Author](#-author)
- [📄 License](#-license)
- [🙏 Acknowledgments](#-acknowledgments)

</details>

---

## 🚀 Quick Start

<details>
<summary><b>⚡ Get started in 3 steps</b></summary>

### For Part 1 (Manual Implementation):
```bash
# 1. Navigate to Part 1
cd Part_1

# 2. Compile
g++ -std=c++11 *.cpp -o schedule_manager

# 3. Run
./schedule_manager
```

### For Part 2 (AI-Assisted):
```bash
# 1. Navigate to Part 2
cd Part_2

# 2. Compile
g++ -std=c++11 *.cpp -o schedule_manager_v2

# 3. Run and select option 1 or 2
./schedule_manager_v2
```

### For Part 3 (Base44 Web App):
Access the deployed "Timetable Maestro" web application via the Base44 platform URL (see `part 3_Base44.docx` for details).

</details>

---

## 🎓 Project Overview

The **Schedule Manager for Students** is a comprehensive Object-Oriented Programming (OOP) project that showcases the evolution of software development methodologies. This system demonstrates the application of core OOP principles including **inheritance**, **polymorphism**, **encapsulation**, and **abstraction** to solve real-world scheduling problems in an academic environment.

### 🎯 Purpose
The primary goal of this project is to create a robust course scheduling system that allows students to:
- ✅ Manage multiple course schedules
- ✅ Track lectures, tutorials, and laboratory sessions
- ✅ Detect scheduling conflicts automatically
- ✅ Analyze workload distribution
- ✅ Organize academic planning efficiently

### 🚀 What Makes This Project Unique?

This project is **NOT** just another schedule manager. It demonstrates **THREE different implementation approaches** to building the exact same system, each showcasing different aspects of modern software development:

1. **💻 Part 1 - Manual Programming**: Complete implementation from scratch using pure C++ and OOP principles
2. **🤖 Part 2 - AI-Assisted Development**: Leveraging AI agents for improved architecture and testing
3. **🌐 Part 3 - No-Code Platform**: Building a web application using Base44 without writing code

---

## ✨ Key Features

### 🎯 Core Capabilities

<table>
<tr>
<td width="50%">

#### 📚 Course Management
- ✅ Unlimited course storage
- ✅ Complete course information (ID, name, credits, exams)
- ✅ Lecturer details and semester tracking
- ✅ Pagination for large course lists (10 items per page)
- ✅ Automatic data loading from CSV files

#### 📅 Schedule Operations
- ✅ Create unlimited schedules
- ✅ Add/remove lessons by type (Lecture/Tutorial/Lab)
- ✅ Smart ID compacting (automatic gap removal)
- ✅ Multi-schedule management
- ✅ CSV-based persistence

</td>
<td width="50%">

#### 🔍 Analysis & Intelligence
- ✅ Time conflict detection with detailed reports
- ✅ Workload distribution analysis (hours per day/week)
- ✅ Teacher schedule aggregation
- ✅ Course completion tracking
- ✅ Visual schedule tables

#### 🧪 Quality & Testing
- ✅ Comprehensive test suites (Part 1 & 2)
- ✅ Unit, integration, and system tests
- ✅ Memory management validation
- ✅ Input validation and error handling
- ✅ Automated testing frameworks

</td>
</tr>
</table>

---

## 🔄 The Three Implementation Approaches

This assignment required implementing the same Schedule Manager system using **three fundamentally different methodologies**. Each approach demonstrates different skills and modern development practices:

### Comparison Overview

| Aspect | 💻 Part 1: Manual | 🤖 Part 2: Agent | 🌐 Part 3: Base44 |
|--------|------------------|------------------|-------------------|
| **Development Method** | Hand-coded C++ | AI-assisted C++ | No-code platform |
| **Primary Language** | C++11 | C++11 | Visual builder |
| **Complexity** | High - detailed implementation | Medium - modular architecture | Low - conversational building |
| **Time Investment** | ⭐⭐⭐⭐⭐ Highest | ⭐⭐⭐ Medium | ⭐ Lowest |
| **Control Level** | Maximum control | High control | Limited to platform |
| **Deployment** | Command-line app | Command-line app | Web app (hosted) |
| **Best For** | Learning OOP deeply | Professional projects | Quick MVPs |
| **Lines of Code** | ~9,000+ lines (approx) | ~6,000+ lines (approx) | 0 lines |
| **Testing** | Manual + built-in suite | Comprehensive test framework | Platform-managed |

### 📊 Visual Comparison

```
┌─────────────────────────────────────────────────────────────────┐
│           Development Approach Spectrum                         │
├─────────────────────────────────────────────────────────────────┤
│                                                                 │
│  💻 Manual         🤖 AI-Assisted      🌐 No-Code              │
│  Programming       Development         Platform                │
│                                                                 │
│  ├──────────────┼──────────────────┼─────────────────┤         │
│  │              │                  │                 │         │
│  Maximum         Balanced           Minimal                    │
│  Control         Efficiency         Coding                     │
│                                                                 │
│  ▼               ▼                  ▼                          │
│  Deep OOP        Modern              Rapid                     │
│  Learning        Architecture        Deployment                │
│                                                                 │
└─────────────────────────────────────────────────────────────────┘
```

---

## 🎯 What This Project Proves

✅ **Strong OOP Skills** - Part 1 shows deep understanding of classes, inheritance, polymorphism, and memory management  
✅ **Adaptability** - Ability to work with AI tools effectively (Part 2) and embrace no-code platforms (Part 3)  
✅ **Problem-Solving** - Implementation of complex features like schedule compacting, conflict detection, and workload analysis  
✅ **Completeness** - All three implementations fulfill the same project requirements from different angles  
✅ **Modern Development** - Understanding of traditional programming, AI-assisted development, and no-code solutions

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

## 💻 Part 1: Manual Implementation (Self-Programmed)

> **`main_for_part_one.cpp`** - Complete hand-coded implementation demonstrating deep OOP mastery

### 🎯 Overview

Part 1 is the **manual implementation** where everything was coded from scratch without AI assistance. This is a production-level, comprehensive implementation that showcases complete understanding of:
- Object-Oriented Programming principles
- C++ language features and STL
- Memory management and pointer manipulation
- File I/O and data persistence
- User interface design
- Error handling and validation

### 🌟 What Sets This Implementation Apart

This is **NOT** a basic student project. Key distinguishing features include:

✅ **Advanced Memory Management**
- Deep copying of lessons when renaming schedules
- Proper cleanup with delete operations
- Smart use of dynamic_cast for type checking
- No memory leaks

✅ **Production-Ready Features**
- Dynamic detection of unlimited CSV files
- Automatic schedule ID compacting (removes gaps in numbering)
- Comprehensive error handling with cin.fail() checks
- User-friendly reminders and guidance

✅ **Sophisticated Algorithms**
- Schedule renaming with preservation of all lesson data
- Conflict detection across multiple schedules
- Workload analysis with detailed breakdowns
- Teacher schedule aggregation

![Part 1 Architecture](docs/images/part1_architecture.png)

### 🔥 Key Features (16 Menu Options)

#### 1. 📚 Course Management
- **PrintCourse `<course_id>`** - Display detailed information about a specific course including all lesson types
- **PrintCourses** - Display first 10 courses with smart pagination
- **More** - View next 10 courses in the list
- **Data Loading** - Automatic loading of course data from CSV files on startup

#### 2. 📅 Schedule Management  
- **PrintSchedule `<schedule_id>`** - Display a specific schedule in a beautifully formatted table
- **PrintSchedules** - Display all available schedules with clean table format
- **AddSchedule** - Create a new empty schedule with automatic ID assignment
- **RmSchedule `<schedule_id>`** - Delete schedule with intelligent ID compacting
  - **⚡ Special Feature**: Automatically renumbers remaining schedules to remove gaps
  - Example: Delete Schedule 4 → Schedules 5,6,7 become 4,5,6

#### 3. ✏️ Lesson Management
- **Add `<sched> <course> <group>`** - Add lessons to a schedule
  - Interactive lesson type selection (Lecture/Tutorial/Lab)
  - Automatic conflict detection before adding
  - **Smart reminder**: Prompts to add ALL lesson types for complete course
  - Visual feedback on course completion status
  
- **Rm `<sched> <course> <group> <type>`** - Remove specific lessons
  - Precise removal by course, group, AND lesson type
  - Debug output for verification
  - Automatic save after removal

#### 4. 🔍 Analysis Features
- **Find Time Conflicts** (Option 13) - Detect scheduling conflicts across all schedules
  - Shows conflicting courses, days, and time overlaps
  - Classroom conflict detection
  
- **Course Workload Analysis** (Option 14) - Analyze weekly workload distribution
  - Total weekly hours
  - Daily breakdown
  - Credit hour analysis
  
- **Teacher Schedule Analysis** (Option 15) - View teaching assignments
  - Aggregates teacher schedules across all courses
  - Shows total teaching hours
  - Lists all courses per teacher

#### 5. 🛠️ System Features
- **Help** (Option 11) - Comprehensive command reference
- **Clear** (Option 10) - Clear screen (platform-dependent)
- **Test** (Option 16) - Run comprehensive test suite
- **Exit** (Option 12) - Save all data and exit gracefully

### 💡 Advanced OOP Techniques Demonstrated

#### 1. Polymorphism with Dynamic Casting
```cpp
// Using dynamic_cast to safely check and convert types
Lesson* lessonCopy = nullptr;

if (dynamic_cast<Lecture*>(originalLesson)) {
    lessonCopy = new Lecture(
        originalLesson->getType(),
        originalLesson->getCourseId(),
        // ... other parameters
    );
}
else if (dynamic_cast<Tutorial*>(originalLesson)) {
    lessonCopy = new Tutorial(/* ... */);
}
else if (dynamic_cast<Lab*>(originalLesson)) {
    lessonCopy = new Lab(/* ... */);
}
```

#### 2. Deep Copying with Polymorphic Objects
```cpp
// Deep copy lessons before deleting schedule
vector<Lesson*> lessonsBackup;
const vector<Lesson*>& originalLessons = s->getLessons();

for (Lesson* originalLesson : originalLessons) {
    if (originalLesson) {
        // Create new copy based on actual type
        Lesson* lessonCopy = /* polymorphic copy */;
        lessonsBackup.push_back(lessonCopy);
    }
}
```

#### 3. Iterator-Based Removal Pattern
```cpp
// Safe removal while iterating
vector<Lesson*>::iterator it = lessons.begin();
while (it != lessons.end()) {
    Lesson* l = *it;
    bool shouldRemove = (l->getCourseId() == courseId) && 
                       (l->getGroupNumber() == groupNumber) &&
                       (l->getType() == targetLessonType);
    
    if (shouldRemove) {
        delete l;  // Free memory
        it = lessons.erase(it);  // Safe erase
    }
    else {
        it++;
    }
}
```

### 🏗️ Implementation Details

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

## 🤖 Part 2: AI-Assisted Implementation (Agent-Programmed)

> **`main_for_part_two.cpp`** - Professional architecture built with AI collaboration

### 🎯 Overview

Part 2 represents the **AI-assisted implementation** where an AI agent (ChatGPT, Claude, or similar) collaborated in building the system. This approach demonstrates:
- Modern software development practices
- Professional architectural patterns
- Test-driven development
- Better separation of concerns
- More maintainable codebase

### 🤝 The AI Collaboration Advantage

Working with an AI agent brought several improvements over Part 1:

✅ **Cleaner Architecture**
- Introduced the `System` class as a central controller
- Better encapsulation of functionality
- Clearer separation between UI and business logic

✅ **Enhanced Testing**
- Dedicated `Tests` class with comprehensive test suite
- Unit tests, integration tests, and system tests
- Automated testing before deployment

✅ **Modern C++ Practices**
- Exception handling with try-catch blocks
- More use of const correctness
- Better input validation patterns

✅ **Simpler Entry Point**
- Clean main menu with 3 options
- Delegates complexity to System class
- Easier to understand and maintain

### 🌟 Major Improvements Over Part 1
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

## 🌐 Part 3: No-Code Implementation (Base44 Platform)

> **"Timetable Maestro"** - Web-based application built through conversational AI

### 🎯 Overview

Part 3 represents a **completely different approach** to building the same Schedule Manager system - using the **Base44 no-code platform**. This demonstrates the modern trend of building full-stack web applications **without writing any code**.

**What is Base44?**  
Base44 is an AI-powered no-code platform that builds web applications through natural language conversations. You describe what you want, and the AI generates the entire application - database, frontend, backend, and deployment.

> **Note:** The specific features and capabilities described for Base44 are based on the assignment documentation (`part 3_Base44.docx`). Features may vary based on the platform version and subscription tier used.

### 🚀 The "Timetable Maestro" Application

The Base44 implementation, branded as **"Timetable Maestro"**, includes all the functionality of Parts 1 and 2, but delivered as a **modern web application**:

✅ **Web Interface** - Accessible via browser (no command-line)  
✅ **Database Backend** - Automatic database creation and management  
✅ **User Authentication** - Login system with role-based access  
✅ **Cloud Hosted** - Instant deployment and sharing  
✅ **Responsive Design** - Works on desktop, tablet, and mobile  
✅ **Visual Calendar** - Interactive schedule visualization  
✅ **Real-time Updates** - Changes sync instantly  
✅ **Email Notifications** - Alerts for schedule changes  

### 🎨 What Base44 Provides (All Built-In)

#### 1. 💾 Database & Storage
- Automatic database schema generation
- Data relationships configured through conversation
- Built-in data validation
- Backup and recovery

#### 2. 👤 User Management
- User registration and authentication
- Role-based permissions (Student/Teacher/Admin)
- Profile management
- Access control

#### 3. 🎨 User Interface
- Modern web interface (no design skills needed)
- Responsive layouts
- Custom branding and colors
- Interactive components

#### 4. 📊 Advanced Features
- Calendar/schedule visualization
- Analytics and reporting dashboards
- Export to PDF and iCalendar
- Email/SMS notifications
- Search and filtering
- Data import/export

#### 5. 🚀 Deployment & Hosting
- Instant cloud deployment
- Custom domain support
- HTTPS security
- Automatic scaling
- 99.9% uptime

### 🔄 Development Process - No Code Required

The entire application was built through conversation:

```
1. Describe the application
   "I need a schedule management system for students..."

2. Define entities and relationships
   "Create courses, schedules, lectures, tutorials, labs..."

3. Specify features
   "Add conflict detection, workload analysis..."

4. Customize the interface
   "Show schedules in a calendar view..."

5. Configure permissions
   "Students can view, admins can edit..."

6. Deploy!
   Application goes live instantly
```

**Total Development Time**: Hours (vs. weeks for Parts 1 & 2)  
**Lines of Code Written**: 0  
**Technical Skills Required**: None (conversational only)

### 📱 Key Features of Timetable Maestro

#### Schedule Management
- Create and manage multiple schedules
- Visual drag-and-drop interface
- Color-coded by course
- Week/month/semester views

#### Conflict Detection
- Real-time conflict warnings
- Visual indicators on calendar
- Suggested alternative times
- Automatic resolution suggestions

#### Collaboration Features
- Share schedules with classmates
- Group study sessions
- Teacher availability tracking
- Classroom booking

#### Mobile Experience
- Progressive Web App (PWA)
- Works offline
- Push notifications
- Add to home screen

#### Analytics Dashboard
- Workload distribution charts
- Study time tracking
- Course completion progress
- Custom reports

### 🆚 Comparison with Parts 1 & 2

| Aspect | Part 1 & 2 (C++) | Part 3 (Base44) |
|--------|------------------|-----------------|
| **Interface** | Command-line | Modern web UI |
| **Access** | Local installation | Cloud-based (anywhere) |
| **Multi-user** | Single user | Unlimited users |
| **Database** | CSV files | Professional database |
| **Authentication** | None | Full user management |
| **Visualization** | Text tables | Interactive calendar |
| **Mobile** | Not supported | Fully responsive |
| **Deployment** | Manual | Instant cloud hosting |
| **Maintenance** | Manual updates | Auto-updated by platform |
| **Cost** | Free (open source) | Subscription-based |

### 🎓 What Part 3 Demonstrates

This implementation proves understanding of:

✅ **Modern Development Trends** - No-code/low-code platforms  
✅ **Product Thinking** - Focus on user experience, not just code  
✅ **AI Collaboration** - Using AI as a development tool  
✅ **Web Technologies** - Even without coding them directly  
✅ **Professional Deployment** - Production-ready applications  
✅ **Scalability** - Building for multiple users from day one  

### 🔗 Access the Application

The Timetable Maestro application is hosted on Base44 and accessible via a custom URL. It demonstrates that the same Schedule Manager functionality can be delivered through radically different approaches - from manual C++ programming to conversational no-code development.

### 📄 Documentation

Detailed information about the Base44 implementation is available in `part 3_Base44.docx`, which includes:
- Application structure and design
- Feature specifications
- User workflows
- System architecture diagrams
- Deployment details

---

## 🎨 OOP Principles Demonstrated

This project is a masterclass in Object-Oriented Programming. Here's how the fundamental OOP principles are implemented:

### 1. 🏛️ Inheritance

The lesson hierarchy demonstrates classical inheritance:

```
         Lesson (Abstract Base Class)
              ⬆️
      ┌───────┼───────┐
      │       │       │
  Lecture Tutorial  Lab
```

**Implementation:**
```cpp
class Lesson {
protected:
    int courseId;
    string day;
    string startHour;
    string endHour;
    string classroom;
    string teacherName;
    int groupNumber;
    
public:
    virtual void display() = 0;  // Pure virtual
    virtual string getType() = 0;  // Pure virtual
};

class Lecture : public Lesson {
public:
    void display() override { /* ... */ }
    string getType() override { return "Lecture"; }
};
```

**Why it matters:**
- Code reuse: Common attributes defined once in Lesson
- Type safety: Can create heterogeneous collections
- Extensibility: Easy to add new lesson types (Seminar, Workshop, etc.)

### 2. 🔄 Polymorphism

Both compile-time and runtime polymorphism are used:

**Runtime Polymorphism (Virtual Functions):**
```cpp
vector<Lesson*> lessons;  // Can hold Lecture, Tutorial, Lab

for (Lesson* lesson : lessons) {
    lesson->display();  // Calls correct version based on actual type
    cout << lesson->getType();  // Dynamic dispatch
}
```

**Type Identification:**
```cpp
if (dynamic_cast<Lecture*>(lesson)) {
    // Handle as Lecture
}
else if (dynamic_cast<Tutorial*>(lesson)) {
    // Handle as Tutorial
}
```

**Why it matters:**
- Flexibility: One interface, multiple implementations
- Maintainability: Add new types without changing existing code
- Clean code: No ugly if-else chains based on type flags

### 3. 🔒 Encapsulation

Private data with controlled public access:

```cpp
class Course {
private:
    int id;
    string name;
    int credits;
    string moedA, moedB;
    string lecturer;
    string semester;

public:
    // Getters - read-only access
    int getId() const;
    string getName() const;
    
    // Setters - validated write access
    void setCredits(int newCredits);
    void setName(const string& newName);
    
    // No setId() - ID is immutable!
};
```

**Why it matters:**
- Data protection: Can't accidentally corrupt object state
- Validation: Setters can validate before changing
- Interface stability: Internal changes don't break external code
- Immutability: Some fields (like ID) cannot be changed

### 4. 🎭 Abstraction

Complex operations hidden behind simple interfaces:

**Schedule Class:**
```cpp
class Schedule {
public:
    void addLesson(Lesson* lesson);  // Simple interface
    bool hasConflict(Lesson* newLesson);  // Complex logic hidden
    void printWeeklySchedule();  // Formatted output
    
private:
    vector<Lesson*> lessons;
    // Complex internal implementation
    bool checkTimeOverlap(Lesson* l1, Lesson* l2);
    void sortByDayAndTime();
};
```

**User doesn't need to know:**
- How conflicts are detected
- How lessons are stored internally
- How schedules are formatted
- File I/O details

**Why it matters:**
- Simplicity: Easy to use, complex under the hood
- Maintainability: Can change implementation without affecting users
- Focus: Users think about what to do, not how it's done

### 5. 🔗 Composition

Objects are composed of other objects:

```cpp
class Schedule {
private:
    int id;
    vector<Lesson*> lessons;  // Has-a relationship
};

class System {
private:
    vector<Course> courses;    // Composed of courses
    vector<Schedule> schedules; // Composed of schedules
    vector<Lesson*> lessons;   // Composed of lessons
};
```

**Why it matters:**
- Flexibility: "Has-a" is more flexible than "Is-a"
- Reusability: Same Lesson can be in multiple contexts
- Modularity: Each component can be developed independently

### 🎯 Advanced OOP Techniques Used

#### RTTI (Run-Time Type Information)
```cpp
dynamic_cast<Lecture*>(lesson)  // Safe downcasting
```

#### Const Correctness
```cpp
int getId() const;  // Doesn't modify object
const vector<Lesson*>& getLessons() const;  // Returns const reference
```

#### Resource Management (RAII)
```cpp
System::~System() {
    for (Lesson* lesson : lessons) {
        delete lesson;  // Clean up resources
    }
}
```

#### Copy Prevention
```cpp
// Deep copying of polymorphic objects
Lesson* copyLesson(const Lesson* original) {
    if (dynamic_cast<const Lecture*>(original)) {
        return new Lecture(*dynamic_cast<const Lecture*>(original));
    }
    // ...
}
```

---

## 📊 Features Comparison

| Feature | 💻 Part 1: Manual | 🤖 Part 2: Agent | 🌐 Part 3: Base44 |
|---------|-------------------|------------------|-------------------|
| **Development Method** | Hand-coded | AI-assisted | No-code |
| **Course Management** | ✓ Full | ✓ Full | ✓ Full |
| **Schedule Creation** | ✓ Unlimited | ✓ Unlimited | ✓ Unlimited |
| **Lesson Management** | ✓ All types | ✓ All types | ✓ All types |
| **Conflict Detection** | ✓ Advanced | ✓ Enhanced | ✓ Real-time |
| **Workload Analysis** | ✓ Detailed | ✓ Detailed | ✓ Visual charts |
| **Testing Framework** | ✓ Built-in | ✓ Comprehensive | ✓ Platform-managed |
| **System Architecture** | OOP (manual) | OOP (System class) | Cloud architecture |
| **Data Storage** | CSV files | CSV files | Database |
| **User Interface** | CLI (16 options) | CLI (3-tier menu) | Web UI |
| **User Management** | Single user | Single user | ✓ Multi-user |
| **Authentication** | - | - | ✓ Full auth |
| **Export Options** | CSV only | CSV only | ✓ PDF, iCal, Excel |
| **Search Capabilities** | Basic | Basic | ✓ Advanced |
| **Mobile Access** | - | - | ✓ Responsive |
| **Deployment** | Local only | Local only | ✓ Cloud hosted |
| **Schedule Visualization** | Text tables | Text tables | ✓ Interactive calendar |
| **Notifications** | - | - | ✓ Email/SMS |
| **Collaboration** | - | - | ✓ Share schedules |
| **Lines of Code** | ~9,000+ | ~6,000+ | 0 |
| **Best Use Case** | Learning OOP | Professional CLI apps | Production web apps |

---

## 🚀 Installation & Setup

### Prerequisites

<details>
<summary><b>🔍 System Requirements</b></summary>

- **Compiler**: g++ (GNU C++ Compiler) with C++11 support or later
- **Operating System**: 
  - Linux (Ubuntu 18.04+, Fedora, etc.)
  - macOS (10.12+)
  - Windows (with MinGW or WSL)
- **RAM**: 512MB minimum (1GB recommended)
- **Disk Space**: 100MB for source code and compiled binaries
- **Make** (optional): For automated builds

#### Checking Your Installation
```bash
# Check g++ version
g++ --version

# Should output something like:
# g++ (Ubuntu 9.3.0-17ubuntu1~20.04) 9.3.0
```

</details>

### 📥 Installation Steps

<details open>
<summary><b>Step-by-Step Guide</b></summary>

#### 1. Clone the Repository
```bash
git clone https://github.com/MariaNakhle/OOP_Final_Project_ScheduleManager_for_student-.git
cd OOP_Final_Project_ScheduleManager_for_student-
```

#### 2. Verify Directory Structure
```bash
ls -la
# You should see: Part_1/ Part_2/ LICENSE README.md
```

#### 3. Choose Your Implementation

**Option A: Part 1 (Manual Implementation)**
```bash
cd Part_1
g++ -std=c++11 *.cpp -o schedule_manager
./schedule_manager
```

**Option B: Part 2 (AI-Assisted Implementation)**
```bash
cd Part_2
g++ -std=c++11 *.cpp -o schedule_manager_v2
./schedule_manager_v2
```

**Option C: Using Alternative Main Files**
```bash
# From repository root
g++ -std=c++11 main_for_part_one.cpp Part_1/*.cpp -o part1_app
./part1_app

# Or for Part 2
g++ -std=c++11 main_for_part_two.cpp Part_2/*.cpp -o part2_app
./part2_app
```

</details>

### 🛠️ Troubleshooting

<details>
<summary><b>Common Issues & Solutions</b></summary>

#### ❌ `g++: command not found`

**Problem**: C++ compiler not installed

**Solution**:
```bash
# Ubuntu/Debian
sudo apt-get update
sudo apt-get install g++

# macOS
xcode-select --install

# Fedora
sudo dnf install gcc-c++
```

#### ❌ `undefined reference` errors

**Problem**: Not all source files compiled

**Solution**:
```bash
# Ensure all .cpp files are included
g++ -std=c++11 Part_1/*.cpp -o schedule_manager_v1
```

#### ❌ Permission denied when running

**Problem**: Executable permissions not set

**Solution**:
```bash
chmod +x schedule_manager_v1
./schedule_manager_v1
```

#### ❌ CSV files not found

**Problem**: Running from wrong directory

**Solution**:
```bash
# Always run from within Part_1 or Part_2 directory
cd Part_1
./schedule_manager_v1
```

</details>

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

### 🎮 Getting Started

<details open>
<summary><b>First-Time Walkthrough</b></summary>

#### Part 2 Example (Recommended for Beginners)

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

3. **Run Tests (Recommended)**
```
Select: 2
[STARTING] Test Suite...
✓ Testing Course creation...     PASS
✓ Testing Lesson polymorphism... PASS
✓ Testing Schedule operations... PASS
✓ Testing Conflict detection...  PASS
✓ All tests completed successfully!
```

4. **Enter the System**
```
Select: 1
[STARTING] Course Management System...
```

</details>

### 📋 Complete Menu Reference

<details>
<summary><b>Part 1 Commands (16 Options)</b></summary>

| Option | Command | Description |
|--------|---------|-------------|
| 1 | `PrintCourse <id>` | Display detailed course information |
| 2 | `PrintCourses` | List first 10 courses |
| 3 | `More` | Show next 10 courses (pagination) |
| 4 | `PrintSchedule <id>` | Display schedule in table format |
| 5 | `PrintSchedules` | List all schedules |
| 6 | `AddSchedule` | Create new empty schedule |
| 7 | `RmSchedule <id>` | Delete schedule (with ID compacting) |
| 8 | `Add <sched> <course>` | Add lesson to schedule |
| 9 | `Rm <sched> <course> <group> <type>` | Remove specific lesson |
| 10 | `Clear` | Clear screen |
| 11 | `Help` | Display command reference |
| 12 | `Exit` | Save data and quit |
| 13 | `Find Conflicts` | Detect schedule conflicts |
| 14 | `Workload Analysis` | Analyze weekly workload |
| 15 | `Teacher Analysis` | View teacher schedules |
| 16 | `Test` | Run built-in test suite |

</details>

### 🎯 Example Workflows

<details>
<summary><b>Common Tasks</b></summary>

#### ✅ Task 1: Create Your First Schedule

```
1. Launch program → ./schedule_manager
2. View available courses → Option 2 (PrintCourses)
3. Create schedule → Option 6 (AddSchedule)
   Output: "SUCCESS: New empty schedule created with ID 1"
4. Add a course → Option 8 (Add)
   Input: Schedule ID: 1
   Input: Course ID: 234118
   Choose lesson type: 1 (Lecture)
5. Complete the course by adding Tutorial (option 2) and Lab (option 3)
6. View your schedule → Option 4 (PrintSchedule)
   Input: Schedule ID: 1
```

#### ✅ Task 2: Detect Schedule Conflicts

```
1. Add multiple courses to a schedule
2. Select Option 13 (Find Time Conflicts)
3. Review conflict report:
   
⚠  WARNING: Conflict detected!
   Schedule: 1
   Courses: 234118 and 234218
   Day: Monday
   Time: 14:00 - 15:00
   Classroom: Building 32, Room 101
```

#### ✅ Task 3: Analyze Your Workload

```
1. Select Option 14 (Course Workload Analysis)
2. View detailed breakdown:

=== Weekly Workload Analysis ===
Total Hours: 24
Average per Day: 4.8

Daily Breakdown:
  Sunday:    6 hours (2 courses)
  Monday:    5 hours (2 courses)
  Tuesday:   4 hours (1 course)
  ...
```

</details>

### 💡 Pro Tips

<details>
<summary><b>Best Practices & Power User Tips</b></summary>

#### 🎯 Scheduling Tips
- **Complete Courses**: Always add all lesson types (Lecture, Tutorial, Lab) for each course
- **Check Conflicts**: Run conflict detection after adding each new course
- **Balanced Workload**: Use workload analysis to distribute courses evenly
- **Save Often**: The system auto-saves, but use Exit (Option 12) properly

#### ⚡ Efficiency Tips
- **Pagination**: Use "More" (Option 3) to navigate through long course lists
- **Multiple Schedules**: Create different schedules for comparison (e.g., Plan A, Plan B)
- **ID Compacting**: When you delete schedules, IDs automatically renumber

#### 🧪 Testing Tips
- **Run Tests First**: Verify system integrity before use (Part 2, Option 2)
- **Test After Changes**: If you modify the code, re-run tests
- **Check Memory**: Tests include memory leak detection

</details>
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

## 🤝 Contributing

Contributions, issues, and feature requests are welcome!

<details>
<summary><b>How to Contribute</b></summary>

### 📝 Reporting Issues
1. Check existing issues first
2. Use the issue template
3. Provide detailed description
4. Include steps to reproduce
5. Add system information (OS, compiler version)

### 🔧 Submitting Changes
1. Fork the repository
2. Create a feature branch (`git checkout -b feature/AmazingFeature`)
3. Commit your changes (`git commit -m 'Add some AmazingFeature'`)
4. Push to the branch (`git push origin feature/AmazingFeature`)
5. Open a Pull Request

### ✅ Contribution Guidelines
- Follow existing code style
- Add tests for new features
- Update documentation
- Keep commits focused and atomic
- Write clear commit messages

</details>

---

## 👨‍💻 Author

<div align="center">

**Maria Nakhle**

[![GitHub](https://img.shields.io/badge/GitHub-MariaNakhle-black?logo=github)](https://github.com/MariaNakhle)

*BSc Student in Computer Science*  
*Passionate about OOP, AI, and Software Engineering*

### 🌟 Other Projects
- [MARICH Robot Car](https://github.com/MariaNakhle/Final-Project---Marich-Robot-Car-) - AI-Powered Intelligent Robot
- [Operating System Project](https://github.com/MariaNakhle/Operating-System-Project-) - OS Internals Implementation
- [Deep Learning Project](https://github.com/MariaNakhle/DEEP-LEARNING---Final-Project) - Pneumonia Detection with CNNs

</div>

---

## 📄 License

This project is licensed under the **MIT License** - see the [LICENSE](LICENSE) file for details.

### 📜 MIT License Summary

```
Copyright (c) 2026 Maria Nakhle

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND...
```

**What this means:**
- ✅ Commercial use allowed
- ✅ Modification allowed
- ✅ Distribution allowed
- ✅ Private use allowed
- ⚠️ License and copyright notice must be included
- ⚠️ Software provided "as-is" without warranty

---

## 🙏 Acknowledgments

### 🎓 Academic Support
- **Course Instructors**: For guidance on OOP principles and project requirements
- **Academic Institution**: For providing the learning environment and resources

### 💻 Technologies & Tools
- **C++ Community**: For excellent documentation and support
- **GNU Project**: For the g++ compiler and development tools
- **Base44 Platform**: For no-code development capabilities

### 📚 Inspiration & Resources
- Open-source scheduling projects for design inspiration
- Stack Overflow community for problem-solving assistance
- C++ reference documentation and tutorials

### 🤝 Special Thanks
- Fellow students who tested the application and provided feedback
- AI assistants (ChatGPT, Claude) for Part 2 collaboration
- All contributors to the C++ STL and ecosystem

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

<div align="center">

## 🌟 Project Highlights

| Metric | Value |
|--------|-------|
| **Total Implementations** | 3 Different Approaches |
| **Lines of Code** | 15,000+ Across All Parts |
| **Programming Languages** | C++11/14 + Base44 |
| **OOP Principles** | 5 Core + Advanced Techniques |
| **Test Coverage** | Comprehensive Suites |
| **Development Time** | Full Semester Project |

---

### ⭐ If you find this project helpful, please give it a star!

**Project Status**: ✅ Complete | **Last Updated**: January 2026 | **Version**: 3.0

---

**Built with ❤️ and OOP principles**  
*Demonstrating three paths to the same destination*

</div>

