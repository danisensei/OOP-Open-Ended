#include<iostream>
#include<vector>

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
    void viewCourses() {
        
    }
  
};