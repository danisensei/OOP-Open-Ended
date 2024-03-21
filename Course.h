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
    Course(int ID, string name, Teacher t) : courseCode(ID), courseName(name), teacher(t) {};

    int getCourseCode() const
    {
        return courseCode;
    }

    string getCourseName() const
    {
        return courseName;
    }

    Teacher getTeacher() const
    {
        return teacher;
    }

    void displayTeacher(const Teacher &cteacher) const
    {
        cout << "Teacher Name: " << cteacher.getTeacherName() << endl;
        cout << "Teacher ID: " << cteacher.getTeacherID() << endl;
        cout << "Teacher Email: " << cteacher.getTeacherEmail() << endl;
    }
    
    vector<Student> getStudentsEnrolled() const
    {
        return studentsEnrolled;
    }

    void addStudent(Student & student)
    {
        studentsEnrolled.push_back(student);
    }

    void removeStudent(Student & student)
    {
        studentsEnrolled.erase(find(studentsEnrolled.begin(), studentsEnrolled.end(), student));
    }

    //Main Methods To ADD
    void viewStudents() const
    {
        cout << "Students Enrolled in the Course:" << endl;
        int i = 1;
        for (const auto &student : studentsEnrolled)
        {
            cout << "Student #" << i << endl;
            cout << "Student Name: " << student.getstudentName() << endl;
            cout << "Student ID: " << student.getstudentID() << endl;
            cout << "Student Email: " << student.getstudentEmail() << endl << endl;
            i++;
        }
    }
};


