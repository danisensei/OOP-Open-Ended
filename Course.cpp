#include <iostream>
#include <algorithm> 
#include "Course.h"
#include "Teachers.h"
#include "Students.h"

Course::Course(int ID, std::string name, Teacher* t) : courseCode(ID), courseName(name), teacher(t) {}

void Course::addStudent(Student* student) {
    studentsEnrolled.push_back(student);
}

void Course::removeStudent(Student* student) {
    studentsEnrolled.erase(std::find(studentsEnrolled.begin(), studentsEnrolled.end(), student));
}

void Course::viewStudents() const {
    std::cout << "Students Enrolled in the Course:" << std::endl;
    int i = 1;
    if(studentsEnrolled.empty()) {
        std::cout << "There are no students enrolled in the course." << std::endl;
    }
    for (const auto &student : studentsEnrolled) {
        std::cout << "Student #" << i << std::endl;
        std::cout << "Student Name: " << student->getStudentName() << std::endl;
        std::cout << "Student ID: " << student->getStudentID() << std::endl;
        std::cout << "Student Email: " << student->getStudentEmail() << std::endl << std::endl;
        i++;
    }
}

int Course::getCourseCode() const {
    return courseCode;
}

std::string Course::getCourseName() const {
    return courseName;
}

Teacher* Course::getTeacher() const {
    return teacher;
}

std::vector<Student*> Course::getStudentsEnrolled() const {
    return studentsEnrolled;
}

void Course::displayTeacher(const Teacher* cteacher) const {
    std::cout << "Teacher Name: " << cteacher->getTeacherName() << std::endl;
    std::cout << "Teacher ID: " << cteacher->getTeacherID() << std::endl;
    std::cout << "Teacher Email: " << cteacher->getTeacherEmail() << std::endl;
}
