#ifndef COURSE_H
#define COURSE_H

#include <string>
using namespace std;

class Course {
private:
	int id; // course number 
	string name; // course name 
	int credits; 
	string moedA;
	string moedB;
	string lecturer; // name of the lecturer
    string semester;

public:

	// default constructor - creates an empty course
    Course();  
    
    // (Parameterized Constructor)
    Course(int id, string name, int credits, string moedA, string moedB, string lecturer, string semester);

    int getId() const;
    string getName() const;
    int getCredits() const;
    string getMoedA() const;
    string getMoedB() const;
    string getLecturer() const;
    string getSemester() const;

    // Setters 
	// there is not set function for id , because it is a unique identifier and should not change
    void setName(const string& newName);
    void setCredits(int newCredits);
    void setMoedA(const string& date);
    void setMoedB(const string& date);
    void setLecturer(const string& name);
    void setSemester(const string& s);

  
    friend ostream& operator<<(ostream& os, const Course& course);

};
#endif