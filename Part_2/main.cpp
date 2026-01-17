#include <iostream>
#include <stdexcept>
#include <string>
#include "System.h"
#include "Tests.h"

void printMainMenu() {
    std::cout << "\n=== COURSE MANAGEMENT SYSTEM ===" << std::endl;
    std::cout << "1. Run Course Management System" << std::endl;
    std::cout << "2. Run Test Suite" << std::endl;
    std::cout << "3. Exit" << std::endl;
    std::cout << "Choose an option (1-3): ";
}

int main() {
    try {
        int choice;
        do {
            printMainMenu();
            std::cin >> choice;
            std::cin.ignore(); // Clear the input buffer
            
            switch (choice) {
                case 1: {
                    std::cout << "\n[STARTING] Course Management System..." << std::endl;
                    System courseSystem;
                    courseSystem.run();
                    break;
                }
                case 2: {
                    std::cout << "\n[STARTING] Test Suite..." << std::endl;
                    bool allTestsPassed = Tests::runAllTests();
                    if (allTestsPassed) {
                        std::cout << "\n? All tests completed successfully!" << std::endl;
                    } else {
                        std::cout << "\n? Some tests failed. Please check the output above." << std::endl;
                    }
                    std::cout << "\nPress Enter to continue...";
                    std::cin.get();
                    break;
                }
                case 3:
                    std::cout << "Goodbye!" << std::endl;
                    break;
                default:
                    std::cout << "Invalid choice. Please try again." << std::endl;
                    break;
            }
        } while (choice != 3);
        
    } catch (const std::exception& e) {
        std::cerr << "FATAL ERROR: " << e.what() << std::endl;
        return 1;
    }
    return 0;
}