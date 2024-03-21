#include<Course.h>

#include<iostream>
#include<vector>
#include<Teachers.h>
#include<Students.h>

using namespace std;

Course::Course(int ID, string name, Teacher t) : courseCode(ID), courseName(name), teacher(t) {};

//Main Methods To ADD
void Course::addStudent(Student & student)
{
    studentsEnrolled.push_back(student);
}

void Course::removeStudent(Student & student)
{
    studentsEnrolled.erase(find(studentsEnrolled.begin(), studentsEnrolled.end(), student));
}

void Course::viewStudents() const
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

//Additional Course Methods


int Course::getCourseCode() const
{
    return courseCode;
}

string Course::getCourseName() const
{
    return courseName;
}

Teacher Course::getTeacher() const
{
    return teacher;
}

void Course::displayTeacher(const Teacher &cteacher) const
{
    cout << "Teacher Name: " << cteacher.getTeacherName() << endl;
    cout << "Teacher ID: " << cteacher.getTeacherID() << endl;
    cout << "Teacher Email: " << cteacher.getTeacherEmail() << endl;
}
