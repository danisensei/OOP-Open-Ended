#pragma once

#include<iostream>
#include<vector>
#include<Course.h>

using namespace std;

class Teacher
{
    private:
        string name;
        string email;
        string teacherID;
        vector<Course> coursestaught;
  
    public:
        Teacher(string id,string n, string mail) : teacherID(id), name(n), email(mail) {}

  void assignCourse (Course course) {
    coursestaught.push_back(course);
  }
  void removeCourse (Course course) {
    for (int i = 0; i < coursestaught.size(); i++) {
      if (coursestaught[i].getCourseCode() == course.getCourseCode()) {
        coursestaught.erase(coursestaught.begin() + i);
        break;
      }
    }
  }
  void viewCourses() {
    for (int i = 0; i < coursestaught.size(); i++) {
      displayCourses(coursestaught[i]);
    }
  } 

  void displayCourses(Course course) {
    cout << "\nCourses Assigned to the Teacher;" << endl;
    for (int i = 0; i < coursestaught.size(); i++)
    {
        cout << "Course #" << i+1 << ":" << endl;
        cout << "";

    }

  }


};