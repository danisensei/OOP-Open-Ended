#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include "Course.h"
#include "Teacher.h"
#include "Student.h"
void displaySeparator();
using namespace std;

// function to display a separator line
void displaySeparator() {
    cout << "----------------------------------------" << endl;
}

int main() {
    cout << "Welcome to University Management System!" << endl;
    displaySeparator();

    // create sample data for demonstration
    Teacher teacher1("T1", "Sir Race ist", "iamracist@gmail.com");
    Teacher teacher2("T2", "Engr Waleed", "engrwaleed000@hotmail.com");

    Student student1("S1", "Daniyal", "malikdaniyal526@example.com");
    Student student2("S2", "Jibran", "mchips2000@example.com");

    Course course1(101, "Introduction to OOP", teacher1);
    Course course2(102, "OOP Lab", teacher2);

    // enroll students in courses
    student1.enrollCourse(course1);
    student2.enrollCourse(course1);
    student2.enrollCourse(course2);

    // assign courses to teachers
    teacher1.assignCourse(course1);
    teacher2.assignCourse(course2);

    // display courses for each teacher
    cout << "Courses assigned to teachers:" << endl;
    displaySeparator();
    cout << "Teacher: " << teacher1.getTeacherName() << endl;
    teacher1.viewCourses();
    displaySeparator();
    cout << "Teacher: " << teacher2.getTeacherName() << endl;
    teacher2.viewCourses();
    displaySeparator();

    // display courses for each student
    cout << "Courses enrolled by students:" << endl;
    displaySeparator();
    cout << "Student: " << student1.getstudentName() << endl;
    student1.viewCourses();
    displaySeparator();
    cout << "Student: " << student2.getstudentName() << endl;
    student2.viewCourses();
    displaySeparator();

    // write data to files
    teacher1.writeToFile("teacher1.txt");
    teacher2.writeToFile("teacher2.txt");
    student1.writeToFile("student1.txt");
    student2.writeToFile("student2.txt");

    cout << "Data written to files successfully!" << endl;
    displaySeparator();

    // read data from files
    vector<Teacher> allTeachers;
    vector<Student> allStudents;
    vector<Course> allCourses;

    // populate allTeachers, allStudents, allCourses with data from files
    // read data for teachers
    Teacher teacher3;
    teacher3.readFromFile("teacher1.txt", allCourses);
    allTeachers.push_back(teacher3);

    Teacher teacher4;
    teacher4.readFromFile("teacher2.txt", allCourses);
    allTeachers.push_back(teacher4);

    // read data for students
    Student student3;
    student3.readFromFile("student1.txt", allCourses);
    allStudents.push_back(student3);

    Student student4;
    student4.readFromFile("student2.txt", allCourses);
    allStudents.push_back(student4);

    cout << "Data read from files successfully!" << endl;
    displaySeparator();

    // display courses for each teacher and student after reading from files
    cout << "Courses assigned to teachers after reading from files:" << endl;
    displaySeparator();
    for (const auto& teacher : allTeachers) {
        cout << "Teacher: " << teacher.getTeacherName() << endl;
        teacher.viewCourses();
        displaySeparator();
    }

    cout << "Courses enrolled by students after reading from files:" << endl;
    displaySeparator();
    for (const auto& student : allStudents) {
        cout << "Student: " << student.getstudentName() << endl;
        student.viewCourses();
        displaySeparator();
    }

    return 0;
}
