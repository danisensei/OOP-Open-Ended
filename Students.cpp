#include<Students.h>

#include<iostream>
#include<vector>
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
