#include "Course.h"
#include "Teachers.h"
#include "Students.h"

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

using namespace std;

void displayHeader(const string& title) {
    cout << "----------------------------------------------" << endl;
    cout << "           UNIVERSITY MANAGEMENT SYSTEM       " << endl;
    cout << "----------------------------------------------" << endl;
    cout << "                 " << title << "                  " << endl;
    cout << "----------------------------------------------" << endl;
}

void displayFooter() {
    cout << "----------------------------------------------" << endl;
    cout << "           THANK YOU FOR USING UM SYSTEM       " << endl;
    cout << "----------------------------------------------" << endl;
}

void addTeacher(vector<Teacher>& teachers) {
    string id, name, email;
    cout << "Enter Teacher ID: ";
    cin >> id;
    cout << "Enter Teacher Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Teacher Email: ";
    cin >> email;
    Teacher newTeacher(id, name, email);
    teachers.push_back(newTeacher);
    cout << "Teacher added successfully!" << endl;
}

void addStudent(vector<Student>& students) {
    string id, name, email;
    cout << "Enter Student ID: ";
    cin >> id;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Student Email: ";
    cin >> email;
    Student newStudent(id, name, email);
    students.push_back(newStudent);
    cout << "Student added successfully!" << endl;
}

void addCourse(vector<Course>& courses, const vector<Teacher>& teachers) {
    int code;
    string name;
    string teacherID;
    cout << "Enter Course Code: ";
    cin >> code;
    cout << "Enter Course Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Teacher ID for the Course: ";
    cin >> teacherID;

    auto it = find_if(teachers.begin(), teachers.end(), [teacherID](const Teacher& t) {
        return t.getTeacherID() == teacherID;
    });

    if (it != teachers.end()) {
        Course newCourse(code, name, *it);
        courses.push_back(newCourse);
        cout << "Course added successfully!" << endl;
    } else {
        cout << "Teacher with ID " << teacherID << " not found. Course not added." << endl;
    }
}

void enrollStudent(vector<Student>& students, const vector<Course>& courses) {
    string studentID;
    int courseCode;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cout << "Enter Course Code to Enroll: ";
    cin >> courseCode;

    auto studentIt = find_if(students.begin(), students.end(), [studentID](const Student& s) {
        return s.getstudentID() == studentID;
    });

    if (studentIt != students.end()) {
        auto courseIt = find_if(courses.begin(), courses.end(), [courseCode](const Course& c) {
            return c.getCourseCode() == courseCode;
        });

        if (courseIt != courses.end()) {
            studentIt->enrollCourse(*courseIt);
            cout << "Student enrolled in the course successfully!" << endl;
        } else {
            cout << "Course with code " << courseCode << " not found. Enrollment failed." << endl;
        }
    } else {
        cout << "Student with ID " << studentID << " not found. Enrollment failed." << endl;
    }
}

int main() {
    vector<Teacher> teachers;
    vector<Student> students;
    vector<Course> courses;

    for (auto& teacher : teachers) {
        teacher.readFromFile("teacher.txt", teacher.getCourse());
    }

    for (auto& student : students) {
        student.readFromFile("student.txt", student.getCourse());
    }

    for (auto& course : courses) {
        course.readFromFile("course.txt", course.getStudentsEnrolled());
    }

    int choice;
    do {
        displayHeader("MAIN MENU");
        cout << "1. Add Teacher" << endl;
        cout << "2. Add Student" << endl;
        cout << "3. Add Course" << endl;
        cout << "4. Enroll Student in Course" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTeacher(teachers);
                break;
            case 2:
                addStudent(students);
                break;
            case 3:
                addCourse(courses, teachers);
                break;
            case 4:
                enrollStudent(students, courses);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }

        displayFooter();
    } while (choice != 5);

    for (const auto& student : students) {
        student.writeToFile("student.txt");
    }

    for (const auto& teacher : teachers) {
        teacher.writeToFile("teacher.txt");
    }

    for (const auto& course : courses) {
        course.writeToFile("course.txt");
    }

    return 0;
}
