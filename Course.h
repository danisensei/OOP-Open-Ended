#pragma once

#include<iostream>
#include<vector>
#include<Teachers.h>
#include<Students.h>

using namespace std;

class Course 
{ 
private: 
    int courseCode;
    string courseName;
    Teacher teacher;
    vector<Student> studentsEnrolled; 

public:
    Course();

    int getCourseCode()
    {
        return courseCode;
    }

};
