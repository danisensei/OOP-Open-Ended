#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>
#include "Teachers.h"
#include "Students.h"
#include "Course.h"

using namespace std;

// Function declarations
void loadData(vector<Teacher*>& teachers, vector<Student*>& students, vector<Course*>& courses);
void saveData(const vector<Teacher*>& teachers, const vector<Student*>& students, const vector<Course*>& courses);
void loadTeachers(vector<Teacher*>& teachers, vector<Course*>& courses);
void loadStudents(vector<Student*>& students, vector<Course*>& courses);
void loadCourses(vector<Course*>& courses, const vector<Teacher*>& teachers, const vector<Student*>& students);
void saveTeachers(const vector<Teacher*>& teachers);
void saveStudents(const vector<Student*>& students);
void saveCourses(const vector<Course*>& courses);
Teacher* findTeacher(const vector<Teacher*>& teachers, const int& teacherID);
Student* findStudent(const vector<Student*>& students, const int& studentID);
void displayHeader(const string& title);
void displayFooter();
void addTeacher(vector<Teacher*>& teachers, vector<Course*>& courses);
void addStudent(vector<Student*>& students);
void addCourse(vector<Course*>& courses, const vector<Teacher*>& teachers);
void enrollStudent(vector<Student*>& students, const vector<Course*>& courses);
void adminScreen(vector<Student*>& students,vector<Teacher*>& teachers, vector<Course*>& courses);
void teacherLogin(const vector<Teacher*>& teachers);
void studentLogin(const vector<Student*>& students);
Course* findCourse(const vector<Course*>& courses, int courseId);

int main() {
    vector<Teacher*> teachers;
    vector<Student*> students;
    vector<Course*> courses;

    // Load data from files
    loadData(teachers, students, courses);

    int choice;
    do {
        displayHeader("Login");
        cout << "1. Admin" << endl;
        cout << "2. Teacher" << endl;
        cout << "3. Student" << endl;
        cout << "4. Exit" << endl;
        cout << "Enter your choice: ";
        while(true)
        {
            if(cin >> choice)
            {
                if(choice == 1)
                {
                    adminScreen(students, teachers, courses);
                    break;
                }
                else if(choice == 2)
                {
                    teacherLogin(teachers);
                    break;
                }
                else if(choice == 3)
                {
                    studentLogin(students);
                    break;
                }
                else if(choice == 4)
                {
                    displayFooter();
                    cout << "Exiting..." << endl;
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    cout << "Enter your choice: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
    } while (choice != 4);
    // Save data to files before exiting
    saveData(teachers, students, courses);

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

// Implementations

void loadData(vector<Teacher*>& teachers, vector<Student*>& students, vector<Course*>& courses) {
    loadTeachers(teachers, courses);
    loadStudents(students, courses);
    loadCourses(courses, teachers, students);
}

void saveData(const vector<Teacher*>& teachers, const vector<Student*>& students, const vector<Course*>& courses) {
    saveCourses(courses);
    saveTeachers(teachers);
    saveStudents(students);
}

void loadTeachers(vector<Teacher*>& teachers, vector<Course*>& courses) {
    ifstream file("teachers.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open teachers file for reading." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string id, name, email;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');

        if(!(id == "")) {
            int id_teacher = stoi(id);
            Teacher* teacher = new Teacher(id_teacher, name, email);
        
            // Load the courses taught by this teacher
            string courseId;
            while (getline(ss, courseId, ',')) {
                Course* course = findCourse(courses, stoi(courseId));
                if (course != nullptr) {
                    teacher->assignCourse(course);
                }
            }

            teachers.push_back(teacher);
        }
    }
    file.close();
}

void loadStudents(vector<Student*>& students, vector<Course*>& courses) {
    ifstream file("students.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open students file for reading." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {

        stringstream ss(line);
        string id, name, email;
        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, email, ',');

        if (!(id == "")){
            
            Student* student = new Student(stoi(id), name, email);
            
            // Load the courses enrolled by this student
            string courseId;
            while (getline(ss, courseId, ',')) {
                Course* course = findCourse(courses, stoi(courseId));
                if (course != nullptr) {
                    student->enrollCourse(course);
                }
            }

            students.push_back(student);

        }
    }
    file.close();
}

void saveCourses(const vector<Course*>& courses) {
    ofstream file("courses.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open courses file for writing." << endl;
        return;
    }

    for (const auto& course : courses) {
        file << course->getCourseCode() << "," << course->getCourseName() << "," << course->getTeacher()->getTeacherID();

        // Save the students enrolled in this course
        const auto& students = course->getStudentsEnrolled();
        for (const auto& student : students) {
            file << "," << student->getStudentID();
        }

        file << endl;
    }
    file.close();
}

void loadCourses(vector<Course*>& courses, const vector<Teacher*>& teachers, const vector<Student*>& students) {
    ifstream file("courses.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open courses file for reading." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string code_str;
        string name;
        string teacherID_str;

        getline(ss, code_str, ',');
        getline(ss, name, ',');
        getline(ss, teacherID_str, ',');

        int teacherID = stoi(teacherID_str);

        Teacher* teacher = findTeacher(teachers, teacherID);
        if (teacher == nullptr) {
            cerr << "Error: Teacher with ID " << teacherID << " not found for course " << code_str << endl;
            continue;
        }

        Course* course = new Course(stoi(code_str), name, teacher);

        string studentID_str;
        while (getline(ss, studentID_str, ',')) {
            int studentID = stoi(studentID_str);
            Student* student = findStudent(students, studentID);
            if (student != nullptr) {
                course->addStudent(student);
            }
        }

        courses.push_back(course);
    }
    file.close();
}

Course* findCourse(const vector<Course*>& courses, int courseId) {
    for (const auto& course : courses) {
        if (course->getCourseCode() == courseId) {
            return course;
        }
    }
    return nullptr;
}

void saveTeachers(const vector<Teacher*>& teachers) {
    ofstream file("teachers.txt", ios::trunc); // Truncate the file to clear previous data
    if (!file.is_open()) {
        cerr << "Error: Unable to open teachers file for writing." << endl;
        return;
    }

    for (const auto& teacher : teachers) {
        file << teacher->getTeacherID() << "," << teacher->getTeacherName() << "," << teacher->getTeacherEmail();

        // Save the courses taught by this teacher
        for (const auto& course : teacher->getCourses()) {
            file << "," << course->getCourseCode();
        }

        file << endl;
    }
    file.close();
}

void saveStudents(const vector<Student*>& students) {
    ofstream file("students.txt", ios::trunc); // Truncate the file to clear previous data
    if (!file.is_open()) {
        cerr << "Error: Unable to open students file for writing." << endl;
        return;
    }

    for (const auto& student : students) {
        file << student->getStudentID() << "," << student->getStudentName() << "," << student->getStudentEmail();

        // Save the courses enrolled by this student
        for (const auto& course : student->getCourses()) {
            file << "," << course->getCourseCode();
        }

        file << endl;
    }
    file.close();
}

Teacher* findTeacher(const vector<Teacher*>& teachers, const int& teacherID) {
    for (const auto& teacher : teachers) {
        if (teacher->getTeacherID() == teacherID) {
            return teacher;
        }
    }
    return nullptr;
}

Student* findStudent(const vector<Student*>& students, const int& studentID) {
    for (const auto& student : students) {
        if (student->getStudentID() == studentID) {
            return student;
        }
    }
    return nullptr;
}

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

void addTeacher(vector<Teacher*>& teachers, vector<Course*>& courses) {
    int id;
    string name, email;
    cout << "Enter Teacher ID: ";
    while(true) {
        cin >> id;
        if(cin.fail()) {
            cout << "Invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
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
    int id;
    string name, email;
    cout << "Enter Student ID: ";
    while(true) {
        cin >> id;
        if(cin.fail()) {
            cout << "Invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
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
    int teacherID;
    cout << "Enter Course Code: ";
    while(true) {
        cin >> code;
        if(cin.fail()) {
            cout << "Invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    cout << "Enter Course Name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter Teacher ID for the Course: ";
    while(true) {
        cin >> teacherID;
        if(cin.fail()) {
            cout << "Invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    auto it = find_if(teachers.begin(), teachers.end(), [teacherID](const Teacher* t) {
        return t->getTeacherID() == teacherID;
    });

    if (it != teachers.end()) {
        Course* newCourse = new Course(code, name, *it);
        courses.push_back(newCourse);
        (*it)->assignCourse(newCourse);
        cout << "Course added successfully!" << endl;
    } else {
        cout << "Teacher with ID " << teacherID << " not found. Course not added." << endl;
    }
}

void enrollStudent(vector<Student*>& students, const vector<Course*>& courses) {
    int studentID;
    int courseCode;
    cout << "Enter Student ID: ";
    while(true) {
        cin >> studentID;
        if(cin.fail()) {
            cout << "Invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }
    cout << "Enter Course Code to Enroll: ";
    while(true) {
        cin >> courseCode;
        if(cin.fail()) {
            cout << "Invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    auto studentIt = find_if(students.begin(), students.end(), [studentID](const Student* s) {
        return s->getStudentID() == studentID;
    });

    if (studentIt != students.end()) {
        auto courseIt = find_if(courses.begin(), courses.end(), [courseCode](const Course* c) {
            return c->getCourseCode() == courseCode;
        });

        if (courseIt != courses.end()) {
            (*studentIt)->enrollCourse(*courseIt);
            cout << "Student enrolled in the course successfully" << endl;
        } else {
            cout << "Course with code " << courseCode << " not found. Enrollment failed." << endl;
        }
    } else {
        cout << "Student with ID " << studentID << " not found. Enrollment failed." << endl;
    }
}

void adminScreen(vector<Student*>& students,vector<Teacher*>& teachers, vector<Course*>& courses) {
    displayHeader("ADMIN");
    cout << "1. Register Teacher" << endl;
    cout << "2. Register Student" << endl;
    cout << "3. Register Course" << endl;
    cout << "4. Enroll Student in Course" << endl;
    cout << "5. View Teachers and Courses" << endl;
    cout << "6. View Students and Courses" << endl;
    cout << "7. Go Back" << endl;
    cout << "Enter your choice: ";
    int choice;
    while(true)
        {
            if(cin >> choice)
            {
                if(choice == 1)
                {
                    addTeacher(teachers, courses);
                    break;
                }
                else if(choice == 2)
                {
                    addStudent(students);
                    break;
                }
                else if(choice == 3)
                {
                    addCourse(courses, teachers);
                    break;
                }
                else if(choice == 4)
                {
                    enrollStudent(students, courses);
                    break;
                }
                else if(choice == 5)
                {
                    displayHeader("TEACHERS AND COURSES");
                    for (const auto& teacher : teachers) {
                        teacher->viewCourses();
                    }
                    break;
                }
                else if(choice == 6)
                {
                    displayHeader("STUDENTS AND COURSES");
                    for (const auto& student : students) {
                        student->viewCourses();
                    }
                    break;
                }
                else if(choice == 7)
                {
                    break;
                }
                else
                {
                    cout << "Invalid choice. Please enter a valid option." << endl;
                    cout << "Enter your choice: ";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                }
            }
        }
    
}

void teacherLogin(const vector<Teacher*>& teachers) {
    displayHeader("TEACHER LOGIN");
    cout << "Enter your Teacher ID: ";
    int teacherID;
    while (true) {
        cin >> teacherID;
        if (cin.fail()) {
            cout << "Invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    Teacher* teacher = findTeacher(teachers, teacherID);
    if (teacher != nullptr) {
        cout << "Login Successful!" << endl;
        cout << "Welcome " << teacher->getTeacherName() << "!" << endl;
        teacher->viewCourses();
    } else {
        cout << "Login Failed! Teacher ID not found." << endl;
    }
}

void studentLogin(const vector<Student*>& students) {
    displayHeader("STUDENT LOGIN");
    cout << "Enter your Student ID: ";
    int studentID;
    while (true) {
        cin >> studentID;
        if (cin.fail()) {
            cout << "Invalid input. Please try again: ";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        } else {
            break;
        }
    }

    Student* student = findStudent(students, studentID);
    if (student != nullptr) {
        cout << "Login Successful!" << endl;
        cout << "Welcome " << student->getStudentName() << "!" << endl;
        student->viewCourses();
    } else {
        cout << "Login Failed! Student ID not found." << endl;
    }
}
