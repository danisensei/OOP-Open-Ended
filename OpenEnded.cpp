#include<iostream>
#include<vector>
#include<string>
using namespace std;

class Student
{
    private:
    string studentID;
    string name;
    string email;
    vector<string> coursesEnrolled;

    public:
        Student(string id, string n, string mail) : studentID(id), name(n), email(mail) {}

    void enrollaCourse(string course){}
    void dropaCourse(string course) {}
    void viewCourses() {}
  
};

class Teacher
{
    private:
        string name;
        string email;
        string teacherID;
        vector<string> coursestaught;
  
    public:
        Teacher(string id,string n, string mail) : teacherID(id), name(n), email(mail) {}

  void assignCourse (string course) {}
  void removeCourse (string course) {}
  void viewCourses() {} 


};

class courses 
{ 
private: 
public:
};
