#ifndef TESTS_H
#define TESTS_H

#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <cassert>

// Include all the classes we want to test
#include "Course.h"
#include "Lesson.h"
#include "Lecture.h"
#include "Tutorial.h"
#include "Lab.h"
#include "Schedule.h"
#include "System.h"

/**
 * @brief Test framework class for the Course Management System
 * 
 * This class provides a comprehensive testing framework for all components
 * of the course management system including courses, lessons, schedules, and system operations.
 */
class Tests {
private:
    static int totalTests;
    static int passedTests;
    static int failedTests;
    
    // ANSI color codes for enhanced output
    static const std::string COLOR_RESET;
    static const std::string COLOR_GREEN;
    static const std::string COLOR_RED;
    static const std::string COLOR_YELLOW;
    static const std::string COLOR_BLUE;
    static const std::string COLOR_CYAN;
    static const std::string COLOR_BOLD;

    // Helper methods for test framework
    static void printTestHeader(const std::string& testName);
    static void printTestResult(bool passed, const std::string& testName, const std::string& errorMessage = "");
    static bool runTest(bool condition, const std::string& testName, const std::string& errorMessage = "");
    static bool assertEqual(int expected, int actual, const std::string& message);
    static bool assertEqual(const std::string& expected, const std::string& actual, const std::string& message);
    static bool assertEqual(double expected, double actual, const std::string& message, double tolerance = 0.001);
    static bool assertTrue(bool condition, const std::string& message);
    static bool assertFalse(bool condition, const std::string& message);
    static bool assertNotNull(void* ptr, const std::string& message);
    static bool assertNull(void* ptr, const std::string& message);

public:
    /**
     * @brief Run all tests in the test suite
     * @return true if all tests pass, false otherwise
     */
    static bool runAllTests();

    // Course class tests
    static bool testCourseConstructors();
    static bool testCourseGettersSetters();
    static bool testCourseValidation();
    static bool testCourseComparison();
    static bool testCourseUtilityMethods();

    // Lesson hierarchy tests
    static bool testLessonCreation();
    static bool testLessonGettersSetters();
    static bool testLessonValidation();
    static bool testLessonTimeConflicts();
    static bool testLessonComparison();
    static bool testLessonCloning();

    // Lecture class tests
    static bool testLectureSpecific();
    static bool testLectureWorkloadFactor();
    static bool testLecturePolymorphism();

    // Tutorial class tests
    static bool testTutorialSpecific();
    static bool testTutorialWorkloadFactor();
    static bool testTutorialPolymorphism();

    // Lab class tests
    static bool testLabSpecific();
    static bool testLabWorkloadFactor();
    static bool testLabPolymorphism();

    // Schedule class tests
    static bool testScheduleConstructors();
    static bool testScheduleAddRemoveLessons();
    static bool testScheduleConflictDetection();
    static bool testScheduleGettersSetters();
    static bool testScheduleUtilityMethods();

    // System class tests
    static bool testSystemInitialization();
    static bool testSystemDataLoading();
    static bool testSystemScheduleManagement();
    static bool testSystemLessonFinding();
    static bool testSystemFileOperations();

    // Integration tests
    static bool testCompleteWorkflow();
    static bool testErrorHandling();
    static bool testMemoryManagement();

    // Performance tests
    static bool testPerformance();

    // Utility methods
    static void printTestSummary();
    static void resetTestCounters();
};

#endif // TESTS_H