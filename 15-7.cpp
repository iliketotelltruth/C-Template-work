#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <iomanip>

using namespace std;

template <class T>
T getMax(T a, T b) {
    return (a > b) ? a : b;
}

template <class T>
T getMin(T a, T b) {
    return (a < b) ? a : b;
}

struct Student {
    string id;
    string name;
    int score;
};

void addStudent(vector<Student>& students);
void listAllStudents(const vector<Student>& students);
void sortByScore(vector<Student>& students);
void searchById(const vector<Student>& students);
void showStatistics(const vector<Student>& students);

int main() {
    vector<Student> students;
    int choice;

    do {
        cout << "\n Student Grade Management System\n";
        cout << "1. Add student\n";
        cout << "2. List all students\n";
        cout << "3. Sort by score\n";
        cout << "4. Search by id\n";
        cout << "5. Show statistics\n";
        cout << "0. Exit\n";

        if (!(cin >> choice)) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Invalid input. Please enter a number.\n";
            continue;
        }

        switch (choice) {
        case 1: addStudent(students); break;
        case 2: listAllStudents(students); break;
        case 3: sortByScore(students); break;
        case 4: searchById(students); break;
        case 5: showStatistics(students); break;
        case 0: cout << "Exiting program...\n"; break;
        default: cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 0);

    return 0;
}
// add student
void addStudent(vector<Student>& students) {
    Student newStudent;
    cout << "Enter ID: ";
    cin >> newStudent.id;
    // check if same id.
    for (const auto& s : students) {
        if (s.id == newStudent.id) {
            cout << "Error: Student ID already exists! Rejecting new entry.\n";
            return;
        }
    }
    cout << "Enter Name: ";
    cin.ignore();
    getline(cin, newStudent.name);
    cout << "Enter Score: ";
    cin >> newStudent.score;
    students.push_back(newStudent);
    cout << "Student added successfully.\n";
}
// show all student.
void listAllStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No students in the system.\n";
        return;
    }
    cout << "\n" << left << setw(15) << "ID" << setw(20) << "Name" << "Score\n";
    cout << string(45, '-') << "\n";
    for (const auto& s : students) {
        cout << left << setw(15) << s.id << setw(20) << s.name << s.score << "\n";
    }
}
// soft by score
void sortByScore(vector<Student>& students) {
    if (students.empty()) {
        cout << "No students to sort.\n";
        return;
    }
    sort(students.begin(), students.end(), [](const Student& a, const Student& b) {
        return a.score > b.score;
        });
    cout << "Students sorted by score (descending).\n";
    listAllStudents(students);
}
// search student
void searchById(const vector<Student>& students) {
    string searchId;
    cout << "Enter ID to search: ";
    cin >> searchId;
    for (const auto& s : students) {
        if (s.id == searchId) {
            cout << "Student found: " << s.id << " | " << s.name << " | Score: " << s.score << "\n";
            return;
        }
    }
    cout << "Student not found.\n";
}
//Statistics score
void showStatistics(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No data available for statistics.\n";
        return;
    }
    int maxScore = students[0].score;
    int minScore = students[0].score;
    int totalScore = 0;
    int passCount = 0;
    int failCount = 0;
    for (const auto& s : students) {
        // use tamplate function to find max and min score
        maxScore = getMax(maxScore, s.score);
        minScore = getMin(minScore, s.score);
        totalScore += s.score;
        if (s.score >= 60) {
            passCount++;
        }
        else {
            failCount++;
        }
    }
    double average = static_cast<double>(totalScore) / students.size();
    cout << "\n--- Statistics ---\n";
    cout << "Class Average: " << fixed << setprecision(2) << average << "\n";
    cout << "Highest Score: " << maxScore << "\n";
    cout << "Lowest Score:  " << minScore << "\n";
    cout << "Passed (>=60): " << passCount << "\n";
    cout << "Failed (<60):  " << failCount << "\n";
}