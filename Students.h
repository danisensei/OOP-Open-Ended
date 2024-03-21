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

    void enrollCourse(Course course){
        coursesEnrolled.push_back(course);
    }
    void dropCourse(Course course) {
        coursesEnrolled.erase(find(coursesEnrolled.begin(), coursesEnrolled.end(), course));
    }
    void viewCourses() {
        
    }

    string getstudentName() const {
         return name;
    }

    string getstudentID() const {
        return studentID;
    }

    string getstudentEmail() const {
        return email;
    }
  
};