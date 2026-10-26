// Giovanni Jackson
// CS 300 Project Two - ABCU Advising Assistance Program
// Implements the vector and merge-sort design recommended in Project One.
// Input format: course number, course title, optional prerequisite numbers.
// Blank prerequisite columns in the supplied CSV mean no prerequisite.

#include <cctype>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct Course {
    string courseNumber;
    string courseTitle;
    vector<string> prerequisites;
};

// Remove surrounding whitespace, including Windows carriage returns.
string Trim(const string& text) {
    const size_t first = text.find_first_not_of(" \t\r\n");
    if (first == string::npos) {
        return "";
    }
    const size_t last = text.find_last_not_of(" \t\r\n");
    return text.substr(first, last - first + 1);
}

string Uppercase(string text) {
    for (char& character : text) {
        character = static_cast<char>(toupper(
            static_cast<unsigned char>(character)));
    }
    return text;
}

// The supplied file uses unquoted comma-separated fields.
// Keep empty columns so required fields can be checked separately.
vector<string> SplitFields(const string& line) {
    vector<string> fields;
    size_t start = 0;
    size_t comma = line.find(',');
    while (comma != string::npos) {
        fields.push_back(Trim(line.substr(start, comma - start)));
        start = comma + 1;
        comma = line.find(',', start);
    }
    fields.push_back(Trim(line.substr(start)));
    return fields;
}

// Linear lookup matches the vector design from Project One.
const Course* FindCourse(const vector<Course>& courses, const string& number) {
    for (const Course& course : courses) {
        if (course.courseNumber == number) {
            return &course;
        }
    }
    return nullptr;
}

// Validate a temporary catalog before replacing any previously loaded data.
bool LoadCourses(const string& filename, vector<Course>& courses) {
    ifstream input(filename);
    if (!input.is_open()) {
        cout << "Error: Could not open file: " << filename << '\n';
        return false;
    }

    vector<Course> pending;
    string line;
    size_t lineNumber = 0;
    while (getline(input, line)) {
        ++lineNumber;
        // Accept an optional UTF-8 byte-order mark on the first line.
        if (lineNumber == 1 && line.compare(0, 3, "\xEF\xBB\xBF") == 0) {
            line.erase(0, 3);
        }
        if (Trim(line).empty()) {
            continue;
        }
        const vector<string> fields = SplitFields(line);
        if (fields.size() < 2 || fields[0].empty() || fields[1].empty()) {
            cout << "Error: Missing course number or title on line "
                 << lineNumber << ".\n";
            return false;
        }

        Course course;
        course.courseNumber = Uppercase(fields[0]);
        course.courseTitle = fields[1];
        if (FindCourse(pending, course.courseNumber) != nullptr) {
            cout << "Error: Duplicate course " << course.courseNumber
                 << " on line " << lineNumber << ".\n";
            return false;
        }
        for (size_t index = 2; index < fields.size(); ++index) {
            // Supplied CSV pads unused prerequisite columns with blanks.
            if (!fields[index].empty()) {
                course.prerequisites.push_back(Uppercase(fields[index]));
            }
        }
        pending.push_back(course);
    }
    if (input.bad()) {
        cout << "Error: Could not finish reading the course file.\n";
        return false;
    }
    if (pending.empty()) {
        cout << "Error: The file contains no courses.\n";
        return false;
    }

    // Validate after reading all rows so prerequisites may appear later.
    for (const Course& course : pending) {
        for (const string& prerequisite : course.prerequisites) {
            if (FindCourse(pending, prerequisite) == nullptr) {
                cout << "Error: Invalid prerequisite " << prerequisite
                     << " for " << course.courseNumber << ".\n";
                return false;
            }
        }
    }
    courses.swap(pending);
    cout << "Courses loaded successfully: " << courses.size() << ".\n";
    return true;
}

// Merge sorted halves in the half-open range [begin, end).
void MergeSort(vector<Course>& courses, vector<Course>& buffer,
               size_t begin, size_t end) {
    if (end - begin < 2) {
        return;
    }
    const size_t middle = begin + (end - begin) / 2;
    MergeSort(courses, buffer, begin, middle);
    MergeSort(courses, buffer, middle, end);
    size_t left = begin;
    size_t right = middle;
    size_t destination = begin;
    while (left < middle && right < end) {
        if (courses[left].courseNumber <= courses[right].courseNumber) {
            buffer[destination++] = courses[left++];
        } else {
            buffer[destination++] = courses[right++];
        }
    }
    while (left < middle) {
        buffer[destination++] = courses[left++];
    }
    while (right < end) {
        buffer[destination++] = courses[right++];
    }
    for (size_t index = begin; index < end; ++index) {
        courses[index] = buffer[index];
    }
}

void PrintCourseList(vector<Course>& courses) {
    vector<Course> buffer(courses.size());
    MergeSort(courses, buffer, 0, courses.size());
    cout << "Here is a sample schedule:\n\n";
    for (const Course& course : courses) {
        cout << course.courseNumber << ", " << course.courseTitle << '\n';
    }
}

void PrintCourse(const vector<Course>& courses, const string& number) {
    const Course* course = FindCourse(courses, Uppercase(Trim(number)));
    if (course == nullptr) {
        cout << "Course not found.\n";
        return;
    }
    cout << course->courseNumber << ", " << course->courseTitle << '\n';
    if (course->prerequisites.empty()) {
        cout << "Prerequisites: None\n";
        return;
    }
    // Include prerequisite titles as required by the project directions.
    cout << "Prerequisites:\n";
    for (const string& numberRequired : course->prerequisites) {
        const Course* required = FindCourse(courses, numberRequired);
        if (required != nullptr) {
            cout << required->courseNumber << ", "
                 << required->courseTitle << '\n';
        } else {
            cout << "Error: Prerequisite course not found: "
                 << numberRequired << '\n';
        }
    }
}

int main() {
    vector<Course> courses;
    string choice;
    cout << "Welcome to the course planner.\n";
    while (true) {
        cout << "\n1. Load Data Structure.\n"
             << "2. Print Course List.\n"
             << "3. Print Course.\n"
             << "9. Exit\n\n"
             << "What would you like to do? ";
        // Reading text avoids stream failure on nonnumeric menu input.
        if (!getline(cin, choice)) {
            break;
        }
        choice = Trim(choice);
        if (choice == "9") {
            break;
        }
        if (choice == "1") {
            string filename;
            cout << "Enter the course data filename: ";
            if (!getline(cin, filename)) {
                break;
            }
            LoadCourses(Trim(filename), courses);
        } else if (choice == "2" || choice == "3") {
            if (courses.empty()) {
                cout << "Please load course data first.\n";
            } else if (choice == "2") {
                PrintCourseList(courses);
            } else {
                string number;
                cout << "What course do you want to know about? ";
                if (!getline(cin, number)) {
                    break;
                }
                PrintCourse(courses, number);
            }
        } else {
            cout << (choice.empty() ? "Blank input" : choice)
                 << " is not a valid option.\n";
        }
    }
    cout << "Thank you for using the course planner!\n";
    return 0;
}
