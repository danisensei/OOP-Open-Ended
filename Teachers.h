#pragma once

#include<iostream>
#include<string>
#include<vector>


using namespace std;

class Course;
class Teacher
{
  private:
        string name;
        string email;
        string teacherID;
        vector<Course> coursestaught;
  
  public:
        Teacher() {}
        Teacher(string id,string n, string mail);

   //Main Methods To ADD
  void assignCourse (Course course) {}

  void removeCourse (Course course) {}

  void viewCourses() {}

//________________________________________________________________????????

  void writeToFile(const string& filename) const {}
  void readFromFile(const string& filename, const vector<Course>& allCourses) {}
//Additional Course Methods
    
  
  string getTeacherName() const{}

  string getTeacherEmail() const{}

  string getTeacherID() const{}

  vector<Course> getCourse(){}
};