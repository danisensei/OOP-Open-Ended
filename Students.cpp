#include <iostream>
#include <algorithm> 
#include "Students.h"
#include "Course.h"

Student::Student(int id, std::string n, std::string mail) : studentID(id), name(n), email(mail) {}

void Student::enrollCourse(Course* course) {
    coursesEnrolled.push_back(course);
}
void Student::dropCourse(Course* course) {
    coursesEnrolled.erase(std::find(coursesEnrolled.begin(), coursesEnrolled.end(), course));
}

void Student::viewCourses() const {
    std::cout << "\nCourses Assigned to the Student " << name << ";" << std::endl;
    int i = 1;
    if(coursesEnrolled.empty()) {
        std::cout << "There are no courses assigned to the student." << std::endl;
    }
    for (const auto &course : coursesEnrolled) {
        std::cout << "Course #" << i << ":" << std::endl;
        std::cout << "Course ID: " << course->getCourseCode() << std::endl;
        std::cout << "Course Name: " << course->getCourseName() << std::endl;
        std::cout << "Course Teacher: "; 
        course->displayTeacher(course->getTeacher()); 
        std::cout << "\n";
        i++;
    }
}

std::string Student::getStudentName() const {
    return name;
}

int Student::getStudentID() const {
    return studentID;
}

std::string Student::getStudentEmail() const {
    return email;
}

std::vector<Course*> Student::getCourses() const {
    return coursesEnrolled;
}
