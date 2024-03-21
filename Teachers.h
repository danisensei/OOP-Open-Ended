#pragma once

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include"Course.h"

using namespace std;

class Teacher
{
private:
    string name;
    string email;
    string teacherID;
    vector<Course> coursestaught;

public:
    Teacher() {}
    Teacher(string id, string n, string mail);

    void assignCourse(Course course);
    void removeCourse(Course course);
    void viewCourses();

    void writeToFile(const string& filename) const;
    void readFromFile(const string& filename, const vector<Course>& allCourses);

    string getTeacherName() const;
    string getTeacherEmail() const;
    string getTeacherID() const;
    vector<Course> getCourse();
};
