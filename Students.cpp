#include<Students.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>

#include<Course.h>

using namespace std;

void Student::enrollCourse(Course course) {
    coursesEnrolled.push_back(course);
}
void Student::dropCourse(Course course) {
    coursesEnrolled.erase(find(coursesEnrolled.begin(), coursesEnrolled.end(), course));
}
void Student::viewCourses() {
    cout << "\nCourses Assigned to the Student " << name << ";" << endl;
    int i = 1;
    for (const auto &course : coursesEnrolled)
    {
        cout << "Course #" << i << ":" << endl;
        cout << "Course ID: " << course.getCourseCode() << endl;
        cout << "Course Name: " << course.getCourseName() << endl;
        cout << "Course Teacher: "; course.displayTeacher(course.getTeacher()); cout << "\n";
        i++;

    }

} 

//________________________________________________________________????????


void Student::writeToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << studentID << "," << name << "," << email << "\n";
        for (const auto& course : coursesEnrolled) {
            file << course.getCourseCode() << "," << course.getCourseName() << "\n";
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for writing\n";
    }
}

void Student::readFromFile(const string& filename, const vector<Course>& allCourses) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        if (getline(file, line)) {
            stringstream ss(line);
            getline(ss, studentID, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');

            // Read enrolled courses
            while (getline(file, line)) {
                stringstream ss(line);
                string courseCode, courseName;
                getline(ss, courseCode, ',');
                getline(ss, courseName, ',');

                // Find the course object corresponding to courseCode
                // Assuming you have a vector of all courses available
                auto it = find_if(allCourses.begin(), allCourses.end(), [courseCode](const Course& c) {
                    return c.getCourseCode() == stoi(courseCode);
                });
                if (it != allCourses.end()) {
                    coursesEnrolled.push_back(*it);
                }
            }
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for reading\n";
    }
}

//Additional Course Methods


string Student::getstudentName() const {
        return name;
}

string Student::getstudentID() const {
    return studentID;
}

string Student::getstudentEmail() const {
    return email;
}

