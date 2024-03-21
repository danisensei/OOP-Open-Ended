#pragma once

#include<iostream>
#include<vector>

using namespace std;

class Course;
class Student
{
    private:
    string studentID;
    string name;
    string email;
    vector<Course> coursesEnrolled;

    public:
    Student(){}
    Student(string id, string n, string mail);

   //Main Methods To ADD
    void enrollCourse(Course course){}
    void dropCourse(Course course) {}
    void viewCourses() {}

//________________________________________________________________????????

    void writeToFile(const string& filename) const{}
    void readFromFile(const string& filename, const vector<Course>& allCourses) {}
//Additional Course Methods
    
    string getstudentName() const {}
    string getstudentID() const {}
    string getstudentEmail() const {}

    vector<Course> getCourse(){}
  
};