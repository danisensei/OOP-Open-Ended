#ifndef STUDENTS_H
#define STUDENTS_H

#include <string>
#include <vector>
#include <algorithm> 
#include "Course.h"

class Course; // Forward declaration

class Student {
private:
    int studentID;
    std::string name;
    std::string email;
    std::vector<Course*> coursesEnrolled;

public:
    Student(int id, std::string n, std::string mail);

    void enrollCourse(Course* course);
    void dropCourse(Course* course);
    void viewCourses() const;

    std::string getStudentName() const;
    int getStudentID() const;
    std::string getStudentEmail() const;
    std::vector<Course*> getCourses() const;
};

#endif
