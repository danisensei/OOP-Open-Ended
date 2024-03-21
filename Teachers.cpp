#include "Teachers.h"

#include<iostream>
#include<string>
#include<vector>
#include<fstream>
#include<algorithm>
#include"Course.h"

Teacher::Teacher(string id, string n, string mail) : teacherID(id), name(n), email(mail) {}

void Teacher::assignCourse(Course course) {
    coursestaught.push_back(course);
}

void Teacher::removeCourse(Course course) {
    coursestaught.erase(find(coursestaught.begin(), coursestaught.end(), course));
}

void Teacher::viewCourses() {
    cout << "\nCourses Assigned to the Teacher " << name << ";" << endl;
    int i = 1;
    for (const auto &course : coursestaught)
    {
        cout << "Course #" << i << ":" << endl;
        cout << "Course ID: " << course.getCourseCode() << endl;
        cout << "Course Name: " << course.getCourseName() << endl;
        cout << "Course Enrolled Student: "; course.viewStudents(); cout << "\n";
        i++;

    }
}

void Teacher::writeToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << teacherID << "," << name << "," << email << "\n";
        for (const auto& course : coursestaught) {
            file << course.getCourseCode() << "," << course.getCourseName() << "\n";
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for writing\n";
    }
}

void Teacher::readFromFile(const string& filename, const vector<Course>& allCourses) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        if (getline(file, line)) {
            stringstream ss(line);
            getline(ss, teacherID, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');

            while (getline(file, line)) {
                stringstream ss(line);
                string courseCode, courseName;
                getline(ss, courseCode, ',');
                getline(ss, courseName, ',');

                auto it = find_if(allCourses.begin(), allCourses.end(), [courseCode](const Course& c) {
                    return c.getCourseCode() == stoi(courseCode);
                });
                if (it != allCourses.end()) {
                    coursestaught.push_back(*it);
                }
            }
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for reading\n";
    }
}

string Teacher::getTeacherName() const {
    return name;
}

string Teacher::getTeacherEmail() const {
    return email;
}

string Teacher::getTeacherID() const {
    return teacherID;
}

vector<Course> Teacher::getCourse() {
    return coursestaught;
}
