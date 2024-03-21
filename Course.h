#pragma once

#include<iostream>
#include<vector>


using namespace std;

class Teacher;
class Student;
class Course 
{ 
private: 
    int courseCode;
    string courseName;
    Teacher teacher;
    vector<Student> studentsEnrolled; 

public:
    Course() {};
    Course(int ID, string name, Teacher t) : courseCode(ID), courseName(name), teacher(t) {};

    //Main Methods To ADD
    void addStudent(Student & student)
    {
        studentsEnrolled.push_back(student);
    }

    void removeStudent(Student & student)
    {
        studentsEnrolled.erase(find(studentsEnrolled.begin(), studentsEnrolled.end(), student));
    }

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
//________________________________________________________________????????

    void writeToFile(const string& filename) const {}
    void readFromFile(const string& filename, const vector<Student>& allStudents) {}

//Additional Course Methods
    
    
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

    vector<Student> getStudentsEnrolled() {}

    void displayTeacher(const Teacher &cteacher) const
    {
        cout << "Teacher Name: " << cteacher.getTeacherName() << endl;
        cout << "Teacher ID: " << cteacher.getTeacherID() << endl;
        cout << "Teacher Email: " << cteacher.getTeacherEmail() << endl;
    }
};


