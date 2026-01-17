#ifndef TUTORIAL_H
#define TUTORIAL_H

#include "Lesson.h"
#include <string>
#include <memory>

class Tutorial : public Lesson {
public:
    // Constructors
    Tutorial();
    Tutorial(const std::string& type, int courseId, const std::string& day, 
             int startHour, int endHour, const std::string& classroom, 
             const std::string& teacherName, int groupNumber);

    // Virtual destructor
    virtual ~Tutorial() = default;
    
    // Copy and move constructors
    Tutorial(const Tutorial& other) = default;
    Tutorial& operator=(const Tutorial& other) = default;
    Tutorial(Tutorial&& other) noexcept = default;
    Tutorial& operator=(Tutorial&& other) noexcept = default;

    // Override pure virtual methods
    std::string getType() const override;
    void print() const override;
    std::unique_ptr<Lesson> clone() const override;
    double getWorkloadFactor() const override;

    // Stream operator
    friend std::ostream& operator<<(std::ostream& os, const Tutorial& tutorial);
};

#endif // TUTORIAL_H
