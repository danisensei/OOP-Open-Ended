#include<Course.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

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


void Course::writeToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << courseCode << "," << courseName << "," << teacher.getTeacherID() << "\n";
        for (const auto& student : studentsEnrolled) {
            file << student.getstudentID() << "," << student.getstudentName() << "," << student.getstudentEmail() << "\n";
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for writing\n";
    }   
}

void Course::readFromFile(const string& filename, const vector<Student>& allStudents) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        if (getline(file, line)) {
            stringstream ss(line);
            string courseID;
            getline(ss, courseID, ',');
            getline(ss, courseName, ',');
            string teacherID;
            vector<Teacher> allTeachers; 

            getline(ss, teacherID, ',');


            auto it = find_if(allTeachers.begin(), allTeachers.end(), [teacherID](const Teacher& t) {
                return t.getTeacherID() == teacherID;
            });
            if (it != allTeachers.end()) {
                teacher = *it;
            }

            
            while (getline(file, line)) {
                stringstream ss(line);
                string studentID, studentName, studentEmail;
                getline(ss, studentID, ',');
                getline(ss, studentName, ',');
                getline(ss, studentEmail, ',');

               
                auto it = find_if(allStudents.begin(), allStudents.end(), [studentID](const Student& s) {
                    return s.getstudentID() == studentID;
                });
                if (it != allStudents.end()) {
                    studentsEnrolled.push_back(*it);
                }
            }
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for reading\n";
    }
}


vector<Student> Course::getStudentsEnrolled()
{
    return studentsEnrolled;
}