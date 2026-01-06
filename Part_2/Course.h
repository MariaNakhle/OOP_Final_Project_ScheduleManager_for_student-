#ifndef COURSE_H
#define COURSE_H

#include <string>
#include <iostream>
#include <stdexcept>

class Course {
private:
    int id;
    std::string name;
    int credits;
    std::string moedA;
    std::string moedB;
    std::string lecturer;

    // Input validation helper methods
    void validateId(int courseId) const;
    void validateCredits(int courseCredits) const;
    void validateName(const std::string& courseName) const;

public:
    // Constructors
    Course();
    Course(int id, const std::string& name, int credits, 
           const std::string& moedA, const std::string& moedB, 
           const std::string& lecturer);
    
    // Copy constructor and assignment operator (Rule of 3/5)
    Course(const Course& other) = default;
    Course& operator=(const Course& other) = default;
    
    // Move constructor and assignment operator (C++11)
    Course(Course&& other) noexcept = default;
    Course& operator=(Course&& other) noexcept = default;
    
    // Destructor
    ~Course() = default;

    // Const getters
    int getId() const noexcept;
    const std::string& getName() const noexcept;
    int getCredits() const noexcept;
    const std::string& getMoedA() const noexcept;
    const std::string& getMoedB() const noexcept;
    const std::string& getLecturer() const noexcept;

    // Setters with validation
    void setName(const std::string& newName);
    void setCredits(int newCredits);
    void setMoedA(const std::string& date);
    void setMoedB(const std::string& date);
    void setLecturer(const std::string& name);

    // Utility methods
    bool isValid() const noexcept;
    std::string toString() const;
    
    // Comparison operators
    bool operator==(const Course& other) const noexcept;
    bool operator!=(const Course& other) const noexcept;
    bool operator<(const Course& other) const noexcept; // For sorting by ID
    
    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Course& course);
};

#endif // COURSE_H