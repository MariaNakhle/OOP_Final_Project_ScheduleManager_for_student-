#ifndef LAB_H
#define LAB_H

#include "Lesson.h"
#include <string>
#include <memory>

class Lab : public Lesson {
public:
    // Constructors
    Lab();
    Lab(const std::string& type, int courseId, const std::string& day, 
        int startHour, int endHour, const std::string& classroom, 
        const std::string& teacherName, int groupNumber);

    // Virtual destructor
    virtual ~Lab() = default;
    
    // Copy and move constructors
    Lab(const Lab& other) = default;
    Lab& operator=(const Lab& other) = default;
    Lab(Lab&& other) noexcept = default;
    Lab& operator=(Lab&& other) noexcept = default;

    // Override pure virtual methods
    std::string getType() const override;
    void print() const override;
    std::unique_ptr<Lesson> clone() const override;
    double getWorkloadFactor() const override;

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Lab& lab);
};

#endif // LAB_H