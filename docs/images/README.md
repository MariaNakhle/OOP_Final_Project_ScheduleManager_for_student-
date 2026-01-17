# Project Documentation - Images Placeholder

This directory contains visual assets for the project documentation.

## Architecture Diagrams

### Part 1 Architecture
The Part 1 architecture diagram illustrates the basic class structure and relationships in the initial implementation.

```
┌─────────────────────────────────────────────────────────────────────┐
│                    PART 1 ARCHITECTURE                               │
│                                                                      │
│   ┌──────────────────┐                                              │
│   │   FileManager    │ ◄── Handles CSV file I/O                     │
│   └────────┬─────────┘                                              │
│            │ loads/saves                                            │
│            ▼                                                         │
│   ┌──────────────────┐         ┌──────────────────┐                │
│   │     Course       │         │    Schedule      │                │
│   ├──────────────────┤         ├──────────────────┤                │
│   │ - id             │         │ - id             │                │
│   │ - name           │         │ - lessons[]      │                │
│   │ - credits        │         └────────┬─────────┘                │
│   │ - lecturer       │                  │                          │
│   │ - moedA/B        │                  │ contains                 │
│   └──────────────────┘                  │                          │
│                                         ▼                          │
│                              ┌──────────────────┐                  │
│                              │  Lesson (ABC)    │                  │
│                              ├──────────────────┤                  │
│                              │ # courseId       │                  │
│                              │ # day            │                  │
│                              │ # startHour      │                  │
│                              │ # endHour        │                  │
│                              │ # classroom      │                  │
│                              │ # teacher        │                  │
│                              │ # groupNumber    │                  │
│                              └────────┬─────────┘                  │
│                                       │                            │
│                  ┌────────────────────┼────────────────────┐       │
│                  │                    │                    │       │
│                  ▼                    ▼                    ▼       │
│         ┌────────────────┐   ┌────────────────┐  ┌────────────────┐│
│         │   Lecture      │   │   Tutorial     │  │      Lab       ││
│         │                │   │                │  │                ││
│         │ + display()    │   │ + display()    │  │ + display()    ││
│         │ + getType()    │   │ + getType()    │  │ + getType()    ││
│         └────────────────┘   └────────────────┘  └────────────────┘│
│                                                                     │
│   ┌──────────────────┐                                             │
│   │ MenuFunctions    │ ◄── User Interface                          │
│   │ TestFunctions    │ ◄── Testing Utilities                       │
│   └──────────────────┘                                             │
└─────────────────────────────────────────────────────────────────────┘
```

### Part 2 Architecture  
The Part 2 architecture shows the enhanced design with the System controller class.

```
┌─────────────────────────────────────────────────────────────────────┐
│                    PART 2 ARCHITECTURE                               │
│                                                                      │
│   ┌──────────────────────────────────────────────────────────────┐  │
│   │                    System Controller                         │  │
│   ├──────────────────────────────────────────────────────────────┤  │
│   │  - courses: vector<Course>                                   │  │
│   │  - lessons: vector<Lesson*>                                  │  │
│   │  - schedules: vector<Schedule>                               │  │
│   ├──────────────────────────────────────────────────────────────┤  │
│   │  + run(): void                                               │  │
│   │  + handleAddSchedule(): void                                 │  │
│   │  + handleRemoveSchedule(id): void                            │  │
│   │  + handleAddLessonToSchedule(...): void                      │  │
│   │  + handleCheckConflicts(id): void                            │  │
│   │  + handleAnalyzeCourseWorkload(id): void                     │  │
│   │  + handleAnalyzeTeacherSchedules(name): void                 │  │
│   │  - loadCourses(): void                                       │  │
│   │  - loadLessons(): void                                       │  │
│   │  - loadSchedules(): void                                     │  │
│   │  - saveSchedules(): void                                     │  │
│   └─────────┬──────────────┬──────────────┬─────────────────────┘  │
│             │              │              │                         │
│             │ manages      │ manages      │ manages                 │
│             ▼              ▼              ▼                         │
│   ┌──────────────┐ ┌──────────────┐ ┌──────────────────┐          │
│   │   Course     │ │   Lesson*    │ │    Schedule      │          │
│   └──────────────┘ └──────┬───────┘ └────────┬─────────┘          │
│                           │                   │                     │
│                           │                   │ contains            │
│                           │                   ▼                     │
│                  ┌────────┴───────┐    ┌──────────────┐            │
│                  │                │    │  Lesson*[]   │            │
│                  ▼                ▼    └──────────────┘            │
│         ┌────────────┐    ┌────────────┐                           │
│         │  Lecture   │    │  Tutorial  │                           │
│         │  Lab       │    │  ...       │                           │
│         └────────────┘    └────────────┘                           │
│                                                                     │
│   ┌──────────────────────────────────────────────────────────────┐ │
│   │                    Tests Module                              │ │
│   ├──────────────────────────────────────────────────────────────┤ │
│   │  + testCourseCreation(): bool                                │ │
│   │  + testLessonCreation(): bool                                │ │
│   │  + testScheduleManagement(): bool                            │ │
│   │  + testConflictDetection(): bool                             │ │
│   │  + runAllTests(): bool                                       │ │
│   └──────────────────────────────────────────────────────────────┘ │
│                                                                     │
└─────────────────────────────────────────────────────────────────────┘
```

## Data Flow Diagram

```
┌───────────┐         ┌───────────┐         ┌───────────┐
│   User    │ ──────> │  System   │ ──────> │   CSV     │
│ Interface │ <────── │Controller │ <────── │  Files    │
└───────────┘         └───────────┘         └───────────┘
      │                     │                     │
      │ Menu Commands       │ Data Operations     │
      │                     │                     │
      ▼                     ▼                     ▼
 ┌─────────┐          ┌──────────┐         ┌──────────┐
 │Display  │          │ Process  │         │  Load/   │
 │Results  │          │ Business │         │  Save    │
 └─────────┘          │  Logic   │         │  Data    │
                      └──────────┘         └──────────┘
```

## Class Relationship Diagram

```
                    uses
   Schedule ─────────────────> Lesson (Abstract)
      │                            △
      │                            │
      │                   ┌────────┼────────┐
      │                   │        │        │
      │               Lecture  Tutorial   Lab
      │
      │ references
      └──────────────────> Course
```

## System Flow - Adding a Lesson

```
┌─────────────────────────────────────────────────────────────┐
│                   Add Lesson Workflow                        │
└─────────────────────────────────────────────────────────────┘

User Input:                System Processing:
   │                             │
   ├─ Schedule ID               │
   ├─ Course ID                 │
   ├─ Lesson Type               │
   │                             │
   └──────────────────> ┌────────────────┐
                        │ Validate Input │
                        └───────┬────────┘
                                │
                       ┌────────▼─────────┐
                       │ Check Course     │
                       │ Exists           │
                       └────────┬─────────┘
                                │
                       ┌────────▼─────────┐
                       │ Check Schedule   │
                       │ Exists           │
                       └────────┬─────────┘
                                │
                       ┌────────▼─────────┐
                       │ Load Lesson from │
                       │ CSV              │
                       └────────┬─────────┘
                                │
                       ┌────────▼─────────┐
                       │ Check for        │
                       │ Conflicts        │
                       └────────┬─────────┘
                                │
                         No     │     Yes
                     ┌──────────┴────────┐
                     │                   │
            ┌────────▼─────────┐  ┌──────▼──────┐
            │ Add to Schedule  │  │Show Warning │
            │ Save to File     │  │Ask Confirm  │
            └────────┬─────────┘  └──────┬──────┘
                     │                   │
                     │              User confirms?
                     │                   │
                     └───────────────────┘
                             │
                    ┌────────▼─────────┐
                    │ Display Success  │
                    │ Message          │
                    └──────────────────┘
```

## Testing Strategy Diagram

```
┌─────────────────────────────────────────────────────────┐
│                 Testing Pyramid                         │
├─────────────────────────────────────────────────────────┤
│                                                         │
│           ┌───────────────────────┐                     │
│           │  Integration Tests    │                     │
│           │  - Complete workflows │                     │
│           │  - Multi-class tests  │                     │
│           └───────────────────────┘                     │
│                                                         │
│       ┌─────────────────────────────────┐               │
│       │        Component Tests          │               │
│       │  - Schedule management          │               │
│       │  - Conflict detection           │               │
│       │  - Workload analysis            │               │
│       └─────────────────────────────────┘               │
│                                                         │
│  ┌──────────────────────────────────────────────┐       │
│  │              Unit Tests                      │       │
│  │  - Course creation/getters/setters          │       │
│  │  - Lesson polymorphism                      │       │
│  │  - Schedule add/remove                      │       │
│  │  - File I/O operations                      │       │
│  └──────────────────────────────────────────────┘       │
│                                                         │
└─────────────────────────────────────────────────────────┘
```

## Notes

- Architecture diagrams are represented in ASCII art for better compatibility
- Visual diagrams can be generated using tools like:
  - PlantUML for UML diagrams
  - draw.io for flowcharts
  - Graphviz for class diagrams
  
- For high-quality PNG/SVG images, consider generating them from the ASCII representations using specialized tools

## Future Enhancements

- Add sequence diagrams for complex operations
- Include state diagrams for schedule lifecycle
- Create entity-relationship diagrams for database design (Part 3)
