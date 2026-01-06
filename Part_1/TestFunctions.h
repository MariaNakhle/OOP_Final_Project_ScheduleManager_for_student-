#ifndef TESTFUNCTIONS_H
#define TESTFUNCTIONS_H

#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <cassert>
#include "Course.h"
#include "Schedule.h"
#include "Lecture.h"
#include "Tutorial.h"
#include "Lab.h"
#include "MenuFunctions.h"

using namespace std;

// Test counter for tracking passed tests
extern int totalTests;
extern int passedTests;

// Utility functions for testing
void resetTestCounters();
void printTestSummary();
void assertTrue(bool condition, const string& testName);
void createTestCSVFiles();
void cleanupTestFiles();

// Core class tests
void testCourseClass();
void testLessonClass();
void testScheduleClass();

// Menu function tests
void testMenuFunctions();
void testPrintFunctions();
void testScheduleTableFunctions();
void testAnalysisFunctions();

// File handling tests
void testCSVFileHandling();

// Main test runner
void runAllTests();

#endif