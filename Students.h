#pragma once

#include<iostream>
#include<vector>
#include<Course.h>

using namespace std;

class Student
{
    private:
    string studentID;
    string name;
    string email;
    vector<Course> coursesEnrolled;

    public:
    Student(string id, string n, string mail) : studentID(id), name(n), email(mail) {}

    void enrollCourse(Course course){}
    void dropCourse(Course course) {}
    void viewCourses() {
        
    }
  
};