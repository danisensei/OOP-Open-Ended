#include <iostream>
#include <algorithm> 
#include "Teachers.h"
#include "Course.h"

using namespace std;

Teacher::Teacher(int id, std::string n, std::string mail) : teacherID(id), name(n), email(mail) {}

void Teacher::assignCourse(Course* course) {
    coursesTaught.push_back(course);
}

void Teacher::removeCourse(Course* course) {
    coursesTaught.erase(std::find(coursesTaught.begin(), coursesTaught.end(), course));
}

void Teacher::viewCourses() const {
    cout << "\nCourses Assigned to the Teacher " << name << ";" << endl;
    int i = 1;
    if(coursesTaught.empty()) {
        cout << "There are no courses assigned to the teacher." << endl;
    }
    for (const auto &course : coursesTaught) {
        cout << "Course #" << i << ":" << endl;
        cout << "Course ID: " << course->getCourseCode() << endl;
        cout << "Course Name: " << course->getCourseName() << endl;
        course->viewStudents();
        cout << "\n";
        i++;
    }
}

std::string Teacher::getTeacherName() const {
    return name;
}

std::string Teacher::getTeacherEmail() const {
    return email;
}

int Teacher::getTeacherID() const {
    return teacherID;
}

std::vector<Course*> Teacher::getCourses() const {
    return coursesTaught;
}
