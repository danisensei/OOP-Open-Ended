#pragma once

#include<iostream>
#include<vector>
#include<fstream>
#include<algorithm>


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
    Course();
    Course(int ID, string name, Teacher t);

    void addStudent(Student & student);
    void removeStudent(Student & student);
    void viewStudents() const;

    void writeToFile(const string& filename) const;
    void readFromFile(const string& filename, const vector<Student>& allStudents);

    int getCourseCode() const;
    string getCourseName() const;
    Teacher getTeacher() const;
    vector<Student> getStudentsEnrolled();

    void displayTeacher(const Teacher &cteacher) const;
};
