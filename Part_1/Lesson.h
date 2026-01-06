// (Base Class) תהיה מחלקה בסיסית Lesson מחלקת
//Lab ,  Tutorial , Lecture : וממנה יורשות שלוש מחלקות 

#ifndef LESSON_H
#define LESSON_H

#include <string>
#include <iostream>
using namespace std;


class Lesson {
protected:
	string type;             
	int courseId;           
    string day;             
    int startHour;          
    int endHour;        
    string classroom;       
    string teacherName;     
    int groupNumber;        


public:

   
    Lesson(string type, int courseId, string day, int startHour, int endHour,
         string classroom, string teacherName, int groupNumber);

    
    virtual void print() const;
    
    // Getters
	string getType() const;
    int getCourseId() const;
    string getDay() const;
    int getStartHour() const;
    int getEndHour() const;
    string getClassroom() const;
    string getTeacherName() const;
    int getGroupNumber() const;

    // Setters
    void setType(const string& t);
	void setCourseId(int id);
    void setDay(const string& d);
    void setStartHour(int h);
    void setEndHour(int h);
    void setClassroom(const string& c);
    void setTeacherName(const string& t);
    void setGroupNumber(int g);
   
    friend ostream& operator<<(ostream& os, const Lesson& lesson);

};



#endif