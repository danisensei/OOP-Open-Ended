#include<Teachers.h>

#include<iostream>
#include<vector>
#include<Course.h>

using namespace std;

Teacher::Teacher(string id,string n, string mail) : teacherID(id), name(n), email(mail) {}

//Main Methods To ADD
void Teacher::assignCourse (Course course) {
coursestaught.push_back(course);
}

void Teacher::removeCourse (Course course) {
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

//________________________________________________________________????????

//Additional Course Methods


string Teacher::getTeacherName() const{
return name;
}

string Teacher::getTeacherEmail() const{
return email;
}

string Teacher::getTeacherID() const{
return teacherID;
}
