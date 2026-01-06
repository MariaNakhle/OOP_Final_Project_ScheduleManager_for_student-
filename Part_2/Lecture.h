#ifndef LECTURE_H
#define LECTURE_H

#include "Lesson.h"
#include <string>
#include <iostream>
#include <memory>

class Lecture : public Lesson {
public:
    // Constructors
    Lecture();
    Lecture(const std::string& type, int courseId, const std::string& day, 
            int startHour, int endHour, const std::string& classroom, 
            const std::string& teacherName, int groupNumber);

    // Virtual destructor
    virtual ~Lecture() = default;
    
    // Copy and move constructors
    Lecture(const Lecture& other) = default;
    Lecture& operator=(const Lecture& other) = default;
    Lecture(Lecture&& other) noexcept = default;
    Lecture& operator=(Lecture&& other) noexcept = default;

    // Override pure virtual methods
    std::string getType() const override;
    void print() const override;
    std::unique_ptr<Lesson> clone() const override;
    double getWorkloadFactor() const override;

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Lecture& lecture);
};

#endif // LECTURE_H
