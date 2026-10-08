#include "Student.h"
#include <iostream>
#include <cstring>
#include <iomanip>

namespace {
void copyText(char* destination, const char* source, int size) {
    std::strncpy(destination, source ? source : "", size - 1);
    destination[size - 1] = '\0';
}
}

Student::Student() : id(0), semester(0), averageRating(0.0f), ratingCount(0) {
    name[0] = branch[0] = username[0] = password[0] = '\0';
}

Student::Student(int studentId, const char* studentName, const char* studentBranch,
                 int studentSemester, const char* user, const char* pass)
    : id(studentId), semester(studentSemester), averageRating(0.0f), ratingCount(0) {
    copyText(name, studentName, 60);
    copyText(branch, studentBranch, 40);
    copyText(username, user, 30);
    copyText(password, pass, 30);
}

int Student::getId() const { return id; }
const char* Student::getName() const { return name; }
const char* Student::getBranch() const { return branch; }
int Student::getSemester() const { return semester; }
const char* Student::getUsername() const { return username; }
bool Student::passwordMatches(const char* pass) const { return std::strcmp(password, pass) == 0; }
float Student::getAverageRating() const { return averageRating; }
int Student::getRatingCount() const { return ratingCount; }
SkillList& Student::getTeachSkills() { return teachSkills; }
SkillList& Student::getLearningInterests() { return learningInterests; }
const SkillList& Student::getTeachSkills() const { return teachSkills; }
const SkillList& Student::getLearningInterests() const { return learningInterests; }

void Student::displayProfile() const {
    std::cout << "\n========== MY PROFILE ==========\n";
    std::cout << "Student ID     : " << id << "\n";
    std::cout << "Name           : " << name << "\n";
    std::cout << "Branch         : " << branch << "\n";
    std::cout << "Semester       : " << semester << "\n";
    std::cout << "Average Rating : " << std::fixed << std::setprecision(1) << averageRating << "\n";
    std::cout << "\nSkills I Can Teach:\n";
    teachSkills.display();
    std::cout << "\nSkills I Want To Learn:\n";
    learningInterests.display();
}

StudentManager::StudentManager() : studentCount(0) {}

bool StudentManager::registerStudent(int id, const char* name, const char* branch, int semester,
                                     const char* username, const char* password) {
    if (studentCount >= MAX_STUDENTS || id <= 0 || semester < 1 || semester > 8 ||
        !name || name[0] == '\0' || !branch || branch[0] == '\0' ||
        !username || username[0] == '\0' || !password || password[0] == '\0' ||
        findById(id) || findByUsername(username)) {
        return false;
    }
    students[studentCount++] = Student(id, name, branch, semester, username, password);
    return true;
}

Student* StudentManager::login(const char* username, const char* password) {
    Student* student = findByUsername(username);
    return student && student->passwordMatches(password) ? student : 0;
}

Student* StudentManager::findById(int id) {
    for (int i = 0; i < studentCount; ++i) {
        if (students[i].getId() == id) return &students[i];
    }
    return 0;
}

Student* StudentManager::findByUsername(const char* username) {
    if (!username) return 0;
    for (int i = 0; i < studentCount; ++i) {
        if (std::strcmp(students[i].getUsername(), username) == 0) return &students[i];
    }
    return 0;
}

Student* StudentManager::getStudentAt(int index) {
    if (index < 0 || index >= studentCount) return 0;
    return &students[index];
}

int StudentManager::getCount() const { return studentCount; }
