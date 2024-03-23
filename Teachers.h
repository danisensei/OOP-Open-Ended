#ifndef TEACHERS_H
#define TEACHERS_H

#include <string>
#include <vector>
#include <algorithm> 
#include "Course.h"

class Course; // Forward declaration

class Teacher {
private:
    std::string name;
    std::string email;
    int teacherID;
    std::vector<Course*> coursesTaught;

public:
    Teacher(int id, std::string n, std::string mail);

    void assignCourse(Course* course);
    void removeCourse(Course* course);
    void viewCourses() const;

    std::string getTeacherName() const;
    std::string getTeacherEmail() const;
    int getTeacherID() const;
    std::vector<Course*> getCourses() const;
};

#endif
