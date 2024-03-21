#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>
#include"Course.h"

using namespace std;

class Student
{
private:
    string studentID;
    string name;
    string email;
    vector<Course> coursesEnrolled;

public:
    Student() {}
    Student(string id, string n, string mail);

    void enrollCourse(Course course);
    void dropCourse(Course course);
    void viewCourses();

    void writeToFile(const string& filename) const;
    void readFromFile(const string& filename, const vector<Course>& allCourses);

    string getstudentName() const;
    string getstudentID() const;
    string getstudentEmail() const;

    vector<Course> getCourse();
};
