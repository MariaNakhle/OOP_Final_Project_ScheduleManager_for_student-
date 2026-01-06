# 🎓 OOP Final Project: Schedule Manager for Students

[![License: MIT](https://img.shields.io/badge/License-MIT-yellow.svg)](https://opensource.org/licenses/MIT)
[![C++](https://img.shields.io/badge/C++-11-blue.svg)](https://isocpp.org/)
[![Status](https://img.shields.io/badge/Status-Complete-success.svg)]()
[![OOP](https://img.shields.io/badge/Paradigm-OOP-orange.svg)]()

> **Three Different Approaches to Building the Same System**  
> This project demonstrates mastery of software development through three distinct implementation methodologies: **Manual Programming**, **AI-Assisted Development**, and **No-Code Platform**.

---

## 📋 Table of Contents
- [Project Overview](#project-overview)
- [The Three Implementation Approaches](#the-three-implementation-approaches)
- [Academic Context](#academic-context)
- [Project Architecture](#project-architecture)
- [Part 1: Manual Implementation (Self-Programmed)](#part-1-manual-implementation-self-programmed)
- [Part 2: AI-Assisted Implementation (Agent-Programmed)](#part-2-ai-assisted-implementation-agent-programmed)
- [Part 3: No-Code Implementation (Base44 Platform)](#part-3-no-code-implementation-base44-platform)
- [Features Comparison](#features-comparison)
- [OOP Principles Demonstrated](#oop-principles-demonstrated)
- [Installation & Compilation](#installation--compilation)
- [Usage Guide](#usage-guide)
- [Project Structure](#project-structure)
- [Technologies Used](#technologies-used)
- [Contributors](#contributors)
- [License](#license)

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
