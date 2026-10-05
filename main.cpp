#include <iostream>
#include <limits>
#include <cstdlib>
#include "Student.h"

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

int readInt(const char* prompt, int minimum, int maximum) {
    int value;
    while (true) {
        std::cout << prompt;
        if (std::cin >> value && value >= minimum && value <= maximum) {
            clearInput();
            return value;
        }
        if (std::cin.eof()) {
            std::cout << "\nInput closed. Exiting PeerLearn.\n";
            std::exit(0);
        }
        std::cout << "Please enter a value from " << minimum << " to " << maximum << ".\n";
        clearInput();
    }
}

void readText(const char* prompt, char* text, int size) {
    std::cout << prompt;
    std::cin.getline(text, size);
}

void registerStudent(StudentManager& manager) {
    char name[60], branch[40], username[30], password[30];
    int id = readInt("Student ID: ", 1, 999999);
    readText("Name: ", name, 60);
    readText("Branch: ", branch, 40);
    int semester = readInt("Semester (1-8): ", 1, 8);
    readText("Username: ", username, 30);
    readText("Password: ", password, 30);

    if (manager.registerStudent(id, name, branch, semester, username, password)) {
        std::cout << "Registration successful. You can now log in.\n";
    } else {
        std::cout << "Registration failed. IDs and usernames must be unique; all fields are required.\n";
    }
}

void manageList(SkillList& list, const char* title) {
    while (true) {
        std::cout << "\n--- " << title << " ---\n1. Add\n2. Remove\n3. Update proficiency\n4. View\n5. Back\n";
        int choice = readInt("Enter choice: ", 1, 5);
        if (choice == 5) return;
        if (choice == 4) { list.display(); continue; }

        char skill[50];
        readText("Skill name: ", skill, 50);
        if (choice == 1) {
            int proficiency = readInt("Proficiency (1 Beginner, 2 Intermediate, 3 Advanced): ", 1, 3);
            std::cout << (list.add(skill, proficiency) ? "Skill added.\n" : "Could not add skill (blank or duplicate).\n");
        } else if (choice == 2) {
            std::cout << (list.remove(skill) ? "Skill removed.\n" : "Skill not found.\n");
        } else {
            int proficiency = readInt("New proficiency (1-3): ", 1, 3);
            std::cout << (list.updateProficiency(skill, proficiency) ? "Skill updated.\n" : "Skill not found.\n");
        }
    }
}

void studentMenu(Student* student) {
    while (true) {
        std::cout << "\n========== PEERLEARN ==========\nWelcome, " << student->getName()
                  << "\n1. My Profile\n2. Manage Skills I Can Teach\n3. Manage Learning Interests\n4. Logout\n";
        int choice = readInt("Enter choice: ", 1, 4);
        if (choice == 1) student->displayProfile();
        else if (choice == 2) manageList(student->getTeachSkills(), "TEACHABLE SKILLS");
        else if (choice == 3) manageList(student->getLearningInterests(), "LEARNING INTERESTS");
        else return;
    }
}

int main() {
    StudentManager manager;
    while (true) {
        std::cout << "\n========================================\n              PEERLEARN\n      College Peer Learning System\n========================================\n"
                  << "1. Register\n2. Login\n3. Exit\n";
        int choice = readInt("Enter choice: ", 1, 3);
        if (choice == 1) {
            registerStudent(manager);
        } else if (choice == 2) {
            char username[30], password[30];
            readText("Username: ", username, 30);
            readText("Password: ", password, 30);
            Student* student = manager.login(username, password);
            if (student) studentMenu(student);
            else std::cout << "Invalid username or password.\n";
        } else {
            std::cout << "Thank you for using PeerLearn.\n";
            return 0;
        }
    }
}
