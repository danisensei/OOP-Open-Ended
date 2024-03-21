#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <algorithm>
#include <sstream>

using namespace std;

// Forward declarations
class Teacher;
class Student;
class Course;

// Function declarations
void displayHeader(const string& title);
void displayFooter();
void addTeacher(vector<Teacher*>& teachers);
void addStudent(vector<Student*>& students);
void addCourse(vector<Course*>& courses, const vector<Teacher*>& teachers);
void enrollStudent(vector<Student*>& students, const vector<Course*>& courses);

// Course class declaration
class Course
{
private:
    int courseCode;
    string courseName;
    Teacher* teacher;
    vector<Student*> studentsEnrolled;

public:
    Course();
    Course(int ID, string name, Teacher* t);

    void addStudent(Student* student);
    void removeStudent(Student* student);
    void viewStudents() const;

    void writeToFile(const string& filename) const;
    void readFromFile(const string& filename, const vector<Student*>& allStudents);

    int getCourseCode() const;
    string getCourseName() const;
    Teacher* getTeacher() const;
    vector<Student*> getStudentsEnrolled();

    void displayTeacher(const Teacher* cteacher) const;
};

// Teacher class declaration
class Teacher
{
private:
    string name;
    string email;
    string teacherID;
    vector<Course*> coursestaught;

public:
    Teacher() {}
    Teacher(string id, string n, string mail);

    void assignCourse(Course* course);
    void removeCourse(Course* course);
    void viewCourses();

    void writeToFile(const string& filename) const;
    void readFromFile(const string& filename, const vector<Course*>& allCourses);

    string getTeacherName() const;
    string getTeacherEmail() const;
    string getTeacherID() const;
    vector<Course*> getCourse();
};

// Student class declaration
class Student
{
private:
    string studentID;
    string name;
    string email;
    vector<Course*> coursesEnrolled;

public:
    Student() {}
    Student(string id, string n, string mail);

    void enrollCourse(Course* course);
    void dropCourse(Course* course);
    void viewCourses();

    void writeToFile(const string& filename) const;
    void readFromFile(const string& filename, const vector<Course*>& allCourses);

    string getstudentName() const;
    string getstudentID() const;
    string getstudentEmail() const;

    vector<Course*> getCourse();
};

// Function definitions
void displayHeader(const string& title) {
    cout << "----------------------------------------------" << endl;
    cout << "           UNIVERSITY MANAGEMENT SYSTEM       " << endl;
    cout << "----------------------------------------------" << endl;
    cout << "                 " << title << "                  " << endl;
    cout << "----------------------------------------------" << endl;
}

void displayFooter() {
    cout << "----------------------------------------------" << endl;
    cout << "           THANK YOU FOR USING UM SYSTEM       " << endl;
    cout << "----------------------------------------------" << endl;
}

void addTeacher(vector<Teacher*>& teachers) {
    string id, name, email;
    cout << "Enter Teacher ID: ";
    cin >> id;
    cout << "Enter Teacher Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Teacher Email: ";
    cin >> email;
    Teacher* newTeacher = new Teacher(id, name, email);
    teachers.push_back(newTeacher);
    cout << "Teacher added successfully!" << endl;
}

void addStudent(vector<Student*>& students) {
    string id, name, email;
    cout << "Enter Student ID: ";
    cin >> id;
    cout << "Enter Student Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Student Email: ";
    cin >> email;
    Student* newStudent = new Student(id, name, email);
    students.push_back(newStudent);
    cout << "Student added successfully!" << endl;
}

void addCourse(vector<Course*>& courses, const vector<Teacher*>& teachers) {
    int code;
    string name;
    string teacherID;
    cout << "Enter Course Code: ";
    cin >> code;
    cout << "Enter Course Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Teacher ID for the Course: ";
    cin >> teacherID;

    auto it = find_if(teachers.begin(), teachers.end(), [teacherID](const Teacher* t) {
        return t->getTeacherID() == teacherID;
    });

    if (it != teachers.end()) {
        Course* newCourse = new Course(code, name, *it);
        courses.push_back(newCourse);
        cout << "Course added successfully!" << endl;
    } else {
        cout << "Teacher with ID " << teacherID << " not found. Course not added." << endl;
    }
}

void enrollStudent(vector<Student*>& students, const vector<Course*>& courses) {
    string studentID;
    int courseCode;
    cout << "Enter Student ID: ";
    cin >> studentID;
    cout << "Enter Course Code to Enroll: ";
    cin >> courseCode;

    auto studentIt = find_if(students.begin(), students.end(), [studentID](const Student* s) {
        return s->getstudentID() == studentID;
    });

    if (studentIt != students.end()) {
        auto courseIt = find_if(courses.begin(), courses.end(), [courseCode](const Course* c) {
            return c->getCourseCode() == courseCode;
        });

        if (courseIt != courses.end()) {
            (*studentIt)->enrollCourse(*courseIt);
            cout << "Student enrolled in the course successfully!" << endl;
        } else {
            cout << "Course with code " << courseCode << " not found. Enrollment failed." << endl;
        }
    } else {
        cout << "Student with ID " << studentID << " not found. Enrollment failed." << endl;
    }
}

// Course method implementations
Course::Course() {}

Course::Course(int ID, string name, Teacher* t) : courseCode(ID), courseName(name), teacher(t) {}

void Course::addStudent(Student* student) {
    studentsEnrolled.push_back(student);
}

void Course::removeStudent(Student* student) {
    studentsEnrolled.erase(find(studentsEnrolled.begin(), studentsEnrolled.end(), student));
}

void Course::viewStudents() const {
    cout << "Students Enrolled in the Course:" << endl;
    int i = 1;
    for (const auto &student : studentsEnrolled)
    {
        cout << "Student #" << i << endl;
        cout << "Student Name: " << student->getstudentName() << endl;
        cout << "Student ID: " << student->getstudentID() << endl;
        cout << "Student Email: " << student->getstudentEmail() << endl << endl;
        i++;
    }
}

void Course::writeToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << courseCode << "," << courseName << "," << teacher->getTeacherID() << "\n";
        for (const auto& student : studentsEnrolled) {
            file << student->getstudentID() << "," << student->getstudentName() << "," << student->getstudentEmail() << "\n";
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for writing\n";
    }   
}

void Course::readFromFile(const string& filename, const vector<Student*>& allStudents) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        if (getline(file, line)) {
            stringstream ss(line);
            string courseID;
            getline(ss, courseID, ',');
            getline(ss, courseName, ',');
            string teacherID;
            vector<Teacher*> allTeachers; 

            getline(ss, teacherID, ',');


            auto it = find_if(allTeachers.begin(), allTeachers.end(), [teacherID](const Teacher* t) {
                return t->getTeacherID() == teacherID;
            });
            if (it != allTeachers.end()) {
                teacher = *it;
            }

            
            while (getline(file, line)) {
                stringstream ss(line);
                string studentID, studentName, studentEmail;
                getline(ss, studentID, ',');
                getline(ss, studentName, ',');
                getline(ss, studentEmail, ',');

               
                auto it = find_if(allStudents.begin(), allStudents.end(), [studentID](const Student* s) {
                    return s->getstudentID() == studentID;
                });
                if (it != allStudents.end()) {
                    studentsEnrolled.push_back(*it);
                }
            }
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for reading\n";
    }
}

int Course::getCourseCode() const {
    return courseCode;
}

string Course::getCourseName() const {
    return courseName;
}

Teacher* Course::getTeacher() const {
    return teacher;
}

void Course::displayTeacher(const Teacher* cteacher) const {
    cout << "Teacher Name: " << cteacher->getTeacherName() << endl;
    cout << "Teacher ID: " << cteacher->getTeacherID() << endl;
    cout << "Teacher Email: " << cteacher->getTeacherEmail() << endl;
}

vector<Student*> Course::getStudentsEnrolled() {
    return studentsEnrolled;
}

// Teacher method implementations
Teacher::Teacher(string id, string n, string mail) : teacherID(id), name(n), email(mail) {}

void Teacher::assignCourse(Course* course) {
    coursestaught.push_back(course);
}

void Teacher::removeCourse(Course* course) {
    coursestaught.erase(find(coursestaught.begin(), coursestaught.end(), course));
}

void Teacher::viewCourses() {
    cout << "\nCourses Assigned to the Teacher " << name << ";" << endl;
    int i = 1;
    for (const auto &course : coursestaught)
    {
        cout << "Course #" << i << ":" << endl;
        cout << "Course ID: " << course->getCourseCode() << endl;
        cout << "Course Name: " << course->getCourseName() << endl;
        cout << "Course Enrolled Student: "; course->viewStudents(); cout << "\n";
        i++;

    }
}

void Teacher::writeToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << teacherID << "," << name << "," << email << "\n";
        for (const auto& course : coursestaught) {
            file << course->getCourseCode() << "," << course->getCourseName() << "\n";
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for writing\n";
    }
}

void Teacher::readFromFile(const string& filename, const vector<Course*>& allCourses) {
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

                auto it = find_if(allCourses.begin(), allCourses.end(), [courseCode](const Course* c) {
                    return c->getCourseCode() == stoi(courseCode);
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

vector<Course*> Teacher::getCourse() {
    return coursestaught;
}

// Student method implementations
Student::Student(string id, string n, string mail) : studentID(id), name(n), email(mail) {}

void Student::enrollCourse(Course* course) {
    coursesEnrolled.push_back(course);
}

void Student::dropCourse(Course* course) {
    coursesEnrolled.erase(find(coursesEnrolled.begin(), coursesEnrolled.end(), course));
}

void Student::viewCourses() {
    cout << "\nCourses Assigned to the Student " << name << ";" << endl;
    int i = 1;
    for (const auto &course : coursesEnrolled)
    {
        cout << "Course #" << i << ":" << endl;
        cout << "Course ID: " << course->getCourseCode() << endl;
        cout << "Course Name: " << course->getCourseName() << endl;
        cout << "Course Teacher: "; course->displayTeacher(course->getTeacher()); cout << "\n";
        i++;
    }
}

void Student::writeToFile(const string& filename) const {
    ofstream file(filename);
    if (file.is_open()) {
        file << studentID << "," << name << "," << email << "\n";
        for (const auto& course : coursesEnrolled) {
            file << course->getCourseCode() << "," << course->getCourseName() << "\n";
        }
        file.close();
    } else {
        cerr << "Error: Unable to open file for writing\n";
    }
}

void Student::readFromFile(const string& filename, const vector<Course*>& allCourses) {
    ifstream file(filename);
    if (file.is_open()) {
        string line;
        if (getline(file, line)) {
            stringstream ss(line);
            getline(ss, studentID, ',');
            getline(ss, name, ',');
            getline(ss, email, ',');

            while (getline(file, line)) {
                stringstream ss(line);
                string courseCode, courseName;
                getline(ss, courseCode, ',');
                getline(ss, courseName, ',');

                auto it = find_if(allCourses.begin(), allCourses.end(), [courseCode](const Course* c) {
                    return c->getCourseCode() == stoi(courseCode);
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

string Student::getstudentName() const {
    return name;
}

string Student::getstudentID() const {
    return studentID;
}

string Student::getstudentEmail() const {
    return email;
}

vector<Course*> Student::getCourse() {
    return coursesEnrolled;
}

int main() {
    vector<Teacher*> teachers;
    vector<Student*> students;
    vector<Course*> courses;

    int choice;
    do {
        displayHeader("MAIN MENU");
        cout << "1. Add Teacher" << endl;
        cout << "2. Add Student" << endl;
        cout << "3. Add Course" << endl;
        cout << "4. Enroll Student in Course" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addTeacher(teachers);
                break;
            case 2:
                addStudent(students);
                break;
            case 3:
                addCourse(courses, teachers);
                break;
            case 4:
                enrollStudent(students, courses);
                break;
            case 5:
                cout << "Exiting..." << endl;
                break;
            default:
                cout << "Invalid choice. Please enter a valid option." << endl;
        }

        displayFooter();
    } while (choice != 5);

    for (const auto& student : students) {
        student->writeToFile("student.txt");
    }

    for (const auto& teacher : teachers) {
        teacher->writeToFile("teacher.txt");
    }

    for (const auto& course : courses) {
        course->writeToFile("course.txt");
    }

    // Free memory
    for (auto teacher : teachers) {
        delete teacher;
    }

    for (auto student : students) {
        delete student;
    }

    for (auto course : courses) {
        delete course;
    }

    return 0;
}
