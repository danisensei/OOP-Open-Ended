#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

// Forward declarations
class Teacher;
class Student;
class Course;

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
void addTeacher(vector<Teacher*>& teachers);
void addStudent(vector<Student*>& students);
void addCourse(vector<Course*>& courses, const vector<Teacher*>& teachers);
void enrollStudent(vector<Student*>& students, const vector<Course*>& courses);
void adminScreen(vector<Student*>& students,vector<Teacher*>& teachers, vector<Course*>& courses);
void teacherLogin(const vector<Teacher*>& teachers);
void studentLogin(const vector<Student*>& students);
Course* findCourse(const vector<Course*>& courses, int courseId);


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
    void readFromFile(const string& filename, const vector<Student*>& allStudents) const; // Added const qualifier

    int getCourseCode() const;
    string getCourseName() const;
    Teacher* getTeacher() const;
    vector<Student*> getStudentsEnrolled() const; // Added const qualifier
    // Added const qualifier for displayTeacher method
    void displayTeacher(const Teacher* cteacher) const;
};

// Teacher class declaration
class Teacher
{
private:
    string name;
    string email;
    int teacherID;
    vector<Course*> coursestaught;

public:
    Teacher() {}
    Teacher(int id, string n, string mail);

    void assignCourse(Course* course);
    void removeCourse(Course* course);
    void viewCourses() const; // Added const qualifier

    void writeToFile(const string& filename) const;
    void readFromFile(const string& filename, const vector<Course*>& allCourses) const; // Added const qualifier

    string getTeacherName() const;
    string getTeacherEmail() const;
    int getTeacherID() const;
    vector<Course*> getCourse() const; // Added const qualifier
};

// Student class declaration
class Student
{
private:
    int studentID;
    string name;
    string email;
    vector<Course*> coursesEnrolled;

public:
    Student() {}
    Student(int id, string n, string mail);

    void enrollCourse(Course* course);
    void dropCourse(Course* course);
    void viewCourses() const; // Added const qualifier

    void writeToFile(const string& filename) const;
    void readFromFile(const string& filename, const vector<Course*>& allCourses) const; // Added const qualifier

    string getstudentName() const;
    int getstudentID() const;
    string getstudentEmail() const;

    vector<Course*> getCourse() const; // Added const qualifier
};

// Implementations

void loadData(vector<Teacher*>& teachers, vector<Student*>& students, vector<Course*>& courses) {
    loadCourses(courses, teachers, students);
    loadTeachers(teachers, courses);
    loadStudents(students, courses);
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

        Teacher* teacher = new Teacher(stoi(id), name, email);
        
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
        const auto& students = course->getStudentsEnrolled();
        for (const auto& student : students) {
            file << "," << student->getstudentID();
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
        int code;
        string name;
        int teacherID; // Change teacherID to teacherName
        ss >> code;
        getline(ss, name, ',');
        ss >> teacherID; // Read teacherName instead of teacherID

        Teacher* teacher = nullptr;
        for (const auto& t : teachers) {
            if (t->getTeacherID() == teacherID) {
                teacher = t;
                break;
            }
        }
        if (teacher == nullptr) {
            cerr << "Error: Teacher with ID " << teacherID << " not found for course " << code << endl;
            continue;
        }

        Course* course = new Course(code, name, teacher);

        while (getline(ss, line, ',')) {
            Student* student = findStudent(students, stoi(line));
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
    ofstream file("teachers.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open teachers file for writing." << endl;
        return;
    }

    for (const auto& teacher : teachers) {
        file << teacher->getTeacherID() << "," << teacher->getTeacherName() << "," << teacher->getTeacherEmail();

        // Save the courses taught by this teacher
        for (const auto& course : teacher->getCourse()) {
            file << "," << course->getCourseCode();
        }

        file << endl;
    }
    file.close();
}

void saveStudents(const vector<Student*>& students) {
    ofstream file("students.txt");
    if (!file.is_open()) {
        cerr << "Error: Unable to open students file for writing." << endl;
        return;
    }

    for (const auto& student : students) {
        file << student->getstudentID() << "," << student->getstudentName() << "," << student->getstudentEmail();

        // Save the courses enrolled by this student
        for (const auto& course : student->getCourse()) {
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
        if (student->getstudentID() == studentID) {
            return student;
        }
    }
    return nullptr;
}

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
                    addTeacher(teachers);
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
        cout << "Welcome " << student->getstudentName() << "!" << endl;
        student->viewCourses();
    } else {
        cout << "Login Failed! Student ID not found." << endl;
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
    if(studentsEnrolled.empty()) {
        cout << "There are no students enrolled in the course." << endl;
    }
    
    for (const auto &student : studentsEnrolled)
    {
        cout << "Student #" << i << endl;
        cout << "Student Name: " << student->getstudentName() << endl;
        cout << "Student ID: " << student->getstudentID() << endl;
        cout << "Student Email: " << student->getstudentEmail() << endl << endl;
        i++;
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

vector<Student*> Course::getStudentsEnrolled() const {
    return studentsEnrolled;
}

void Course::displayTeacher(const Teacher* cteacher) const {
    cout << "Teacher Name: " << cteacher->getTeacherName() << endl;
    cout << "Teacher ID: " << cteacher->getTeacherID() << endl;
    cout << "Teacher Email: " << cteacher->getTeacherEmail() << endl;
}

// Teacher method implementations
Teacher::Teacher(int id, string n, string mail) : teacherID(id), name(n), email(mail) {}

void Teacher::assignCourse(Course* course) {
    coursestaught.push_back(course);
}

void Teacher::removeCourse(Course* course) {
    coursestaught.erase(find(coursestaught.begin(), coursestaught.end(), course));
}

void Teacher::viewCourses() const {
    cout << "\nCourses Assigned to the Teacher " << name << ";" << endl;
    int i = 1;
    if(coursestaught.empty()) {
        cout << "There are no courses assigned to the teacher." << endl;
    }
    for (const auto &course : coursestaught)
    {
        cout << "Course #" << i << ":" << endl;
        cout << "Course ID: " << course->getCourseCode() << endl;
        cout << "Course Name: " << course->getCourseName() << endl;
        course->viewStudents(); cout << "\n";
        i++;

    }
}

string Teacher::getTeacherName() const {
    return name;
}

string Teacher::getTeacherEmail() const {
    return email;
}

int Teacher::getTeacherID() const {
    return teacherID;
}

vector<Course*> Teacher::getCourse() const {
    return coursestaught;
}

// Student method implementations
Student::Student(int id, string n, string mail) : studentID(id), name(n), email(mail) {}

void Student::enrollCourse(Course* course) {
    coursesEnrolled.push_back(course);
}

void Student::dropCourse(Course* course) {
    coursesEnrolled.erase(find(coursesEnrolled.begin(), coursesEnrolled.end(), course));
}

void Student::viewCourses() const {
    cout << "\nCourses Assigned to the Student " << name << ";" << endl;
    int i = 1;
    if(coursesEnrolled.empty()) {
        cout << "There are no courses assigned to the student." << endl;
    }
    for (const auto &course : coursesEnrolled)
    {
        cout << "Course #" << i << ":" << endl;
        cout << "Course ID: " << course->getCourseCode() << endl;
        cout << "Course Name: " << course->getCourseName() << endl;
        cout << "Course Teacher: "; course->displayTeacher(course->getTeacher()); cout << "\n";
        i++;
    }
}

string Student::getstudentName() const {
    return name;
}

int Student::getstudentID() const {
    return studentID;
}

string Student::getstudentEmail() const {
    return email;
}

vector<Course*> Student::getCourse() const {
    return coursesEnrolled;
}

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
