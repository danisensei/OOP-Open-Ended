#include<iostream>
#include<vector>

using namespace std;

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