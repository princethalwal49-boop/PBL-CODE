#include <iostream>
#include <limits>
#include <cstdlib>
#include <cstring>
#include <iomanip>
#include "Student.h"
#include "SkillTree.h"
#include "Graph.h"
#include "Matching.h"

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

void registerStudent(StudentManager& manager, StudentGraph& graph) {
    char name[60], branch[40], username[30], password[30];
    int id = readInt("Student ID: ", 1, 999999);
    readText("Name: ", name, 60);
    readText("Branch: ", branch, 40);
    int semester = readInt("Semester (1-8): ", 1, 8);
    readText("Username: ", username, 30);
    readText("Password: ", password, 30);

    if (manager.registerStudent(id, name, branch, semester, username, password)) {
        graph.addStudent(id);
        std::cout << "Registration successful. You can now log in.\n";
    } else {
        std::cout << "Registration failed. IDs and usernames must be unique; all fields are required.\n";
    }
}

const char* proficiencyName(int proficiency) {
    if (proficiency == 1) return "Beginner";
    if (proficiency == 2) return "Intermediate";
    return "Advanced";
}

void displayStudentSummary(const Student* student) {
    std::cout << "ID: " << student->getId() << " | " << student->getName()
              << " | " << student->getBranch() << " | Semester " << student->getSemester() << "\n";
}

void findStudentMenu(StudentManager& manager) {
    std::cout << "\n--- FIND A STUDENT ---\n1. By ID\n2. By name\n3. By branch\n4. By teachable skill\n";
    int choice = readInt("Enter choice: ", 1, 4);
    int matches = 0;

    if (choice == 1) {
        int id = readInt("Student ID: ", 1, 999999);
        Student* student = manager.findById(id);
        if (student) {
            displayStudentSummary(student);
            return;
        }
    } else {
        char term[60];
        readText(choice == 2 ? "Name: " : choice == 3 ? "Branch: " : "Skill: ", term, 60);
        for (int i = 0; i < manager.getCount(); ++i) {
            Student* student = manager.getStudentAt(i);
            bool matched = (choice == 2 && std::strcmp(student->getName(), term) == 0) ||
                           (choice == 3 && std::strcmp(student->getBranch(), term) == 0) ||
                           (choice == 4 && student->getTeachSkills().contains(term));
            if (matched) {
                displayStudentSummary(student);
                ++matches;
            }
        }
        if (matches > 0) return;
    }
    std::cout << "No matching student found.\n";
}

void recommendationMenu(Student* learner, StudentManager& manager, const SkillTree& skillTree,
                        MatchingSystem& matchingSystem) {
    char skill[50];
    std::cout << "\nYour learning interests:\n";
    learner->getLearningInterests().display();
    readText("Skill required: ", skill, 50);

    if (!skillTree.contains(skill)) {
        std::cout << "That skill is not in the skill hierarchy. Add it there first.\n";
        return;
    }

    Recommendation recommendations[MAX_STUDENTS];
    int count = matchingSystem.getRecommendations(learner, manager, skill, recommendations, MAX_STUDENTS);
    if (count == -1) {
        std::cout << "Add '" << skill << "' to your learning interests before requesting recommendations.\n";
        return;
    }
    if (count == 0) {
        std::cout << "No peers currently teach '" << skill << "'.\n";
        return;
    }

    std::cout << "\n========== PEER RECOMMENDATIONS ==========\nSkill Required: " << skill << "\n";
    for (int i = 0; i < count; ++i) {
        std::cout << "\n" << i + 1 << ". " << recommendations[i].student->getName()
                  << " (ID: " << recommendations[i].student->getId() << ")\n"
                  << "   Skill Level : " << proficiencyName(recommendations[i].proficiency) << "\n"
                  << "   Rating      : ";
        if (recommendations[i].rating == 0.0f) std::cout << "Not rated (neutral score used)\n";
        else std::cout << std::fixed << std::setprecision(1) << recommendations[i].rating << "\n";
        std::cout << "   Match Score : " << recommendations[i].score << "%\n";
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

void skillTreeMenu(SkillTree& skillTree) {
    while (true) {
        std::cout << "\n--- SKILL HIERARCHY ---\n1. Display hierarchy\n2. Search skill/category\n3. Add skill/category\n4. Back\n";
        int choice = readInt("Enter choice: ", 1, 4);
        if (choice == 4) return;
        if (choice == 1) {
            skillTree.display();
        } else if (choice == 2) {
            char name[50];
            readText("Skill/category to search: ", name, 50);
            const char* parent = skillTree.getParentName(name);
            if (skillTree.contains(name)) {
                std::cout << '"' << name << '"' << " found";
                if (parent) std::cout << " under '" << parent << "'";
                std::cout << ".\n";
            } else {
                std::cout << "Skill/category not found.\n";
            }
        } else {
            char parent[50], name[50];
            readText("Parent category: ", parent, 50);
            readText("New skill/category: ", name, 50);
            std::cout << (skillTree.addSkillOrCategory(parent, name)
                ? "Skill/category added to the hierarchy.\n"
                : "Could not add it. Check the parent name and avoid duplicates.\n");
        }
    }
}

void studentMenu(Student* student, StudentManager& manager, SkillTree& skillTree,
                 StudentGraph& graph, MatchingSystem& matchingSystem) {
    while (true) {
        std::cout << "\n========== PEERLEARN ==========\nWelcome, " << student->getName()
                  << "\n1. My Profile\n2. Manage Skills I Can Teach\n3. Manage Learning Interests\n4. Skill Hierarchy\n5. Find a Student\n6. Get Recommendations\n7. My Connections\n8. Logout\n";
        int choice = readInt("Enter choice: ", 1, 8);
        if (choice == 1) student->displayProfile();
        else if (choice == 2) manageList(student->getTeachSkills(), "TEACHABLE SKILLS");
        else if (choice == 3) manageList(student->getLearningInterests(), "LEARNING INTERESTS");
        else if (choice == 4) skillTreeMenu(skillTree);
        else if (choice == 5) findStudentMenu(manager);
        else if (choice == 6) recommendationMenu(student, manager, skillTree, matchingSystem);
        else if (choice == 7) graph.displayConnections(student->getId());
        else return;
    }
}

int main() {
    StudentManager manager;
    SkillTree skillTree;
    StudentGraph graph;
    MatchingSystem matchingSystem(graph);
    skillTree.loadDefaultHierarchy();
    while (true) {
        std::cout << "\n========================================\n              PEERLEARN\n      College Peer Learning System\n========================================\n"
                  << "1. Register\n2. Login\n3. Exit\n";
        int choice = readInt("Enter choice: ", 1, 3);
        if (choice == 1) {
            registerStudent(manager, graph);
        } else if (choice == 2) {
            char username[30], password[30];
            readText("Username: ", username, 30);
            readText("Password: ", password, 30);
            Student* student = manager.login(username, password);
            if (student) studentMenu(student, manager, skillTree, graph, matchingSystem);
            else std::cout << "Invalid username or password.\n";
        } else {
            std::cout << "Thank you for using PeerLearn.\n";
            return 0;
        }
    }
}
