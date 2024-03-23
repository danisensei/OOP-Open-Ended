#ifndef COURSES_H
#define COURSES_H

#include <string>
#include <vector>
#include <algorithm> 
#include "Teachers.h"
#include "Students.h"

class Teacher; // Forward declaration
class Student; // Forward declaration

class Course {
private:
    int courseCode;
    std::string courseName;
    Teacher* teacher;
    std::vector<Student*> studentsEnrolled;

public:
    Course(int ID, std::string name, Teacher* t);

    void addStudent(Student* student);
    void removeStudent(Student* student);
    void viewStudents() const;

    int getCourseCode() const;
    std::string getCourseName() const;
    Teacher* getTeacher() const;
    std::vector<Student*> getStudentsEnrolled() const;
    void displayTeacher(const Teacher* cteacher) const;
};

#endif
