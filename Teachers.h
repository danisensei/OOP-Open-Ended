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
    coursestaught.erase(find(coursestaught.begin(), coursestaught.end(), course));
  }

  void viewCourses() {
    for (int i = 0; i < coursestaught.size(); i++) {
      displayCourses(coursestaught[i]);
    }
  } 

  void displayCourses(Course course) {
    cout << "\nCourses Assigned to the Teacher;" << endl;
    int i = 1;
    for (const auto &course : coursestaught)
    {
        cout << "Course #" << i << ":" << endl;
        cout << "Course ID: " << course.getCourseCode() << endl;
        cout << "Course Name: " << course.getCourseName() << endl;
        cout << "Course Teacher: "; course.displayTeacher(course.getTeacher()); cout << "\n";
        cout << "Course Enrolled Student: "; course.viewStudents(); cout << "\n";
        i++;

    }

  }


  
  string getTeacherName() const{
    return name;
  }

  string getTeacherEmail() const{
    return email;
  }

  string getTeacherID() const{
    return teacherID;
  }


};