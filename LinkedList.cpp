#include "LinkedList.h"
#include <iostream>
#include <cstring>

SkillList::SkillList() : head(0) {}

SkillList::SkillList(const SkillList& other) : head(0) {
    copyFrom(other);
}

SkillList& SkillList::operator=(const SkillList& other) {
    if (this != &other) {
        clear();
        copyFrom(other);
    }
    return *this;
}

SkillList::~SkillList() {
    clear();
}

bool SkillList::add(const char* skillName, int proficiency) {
    if (!skillName || skillName[0] == '\0' || proficiency < 1 || proficiency > 3 || contains(skillName)) {
        return false;
    }

    SkillNode* newNode = new SkillNode;
    std::strncpy(newNode->skillName, skillName, 49);
    newNode->skillName[49] = '\0';
    newNode->proficiency = proficiency;
    newNode->next = 0;

    if (!head) {
        head = newNode;
        return true;
    }

    SkillNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
    return true;
}

bool SkillList::remove(const char* skillName) {
    SkillNode* current = head;
    SkillNode* previous = 0;

    while (current) {
        if (std::strcmp(current->skillName, skillName) == 0) {
            if (previous) {
                previous->next = current->next;
            } else {
                head = current->next;
            }
            delete current;
            return true;
        }
        previous = current;
        current = current->next;
    }
    return false;
}

bool SkillList::updateProficiency(const char* skillName, int proficiency) {
    if (proficiency < 1 || proficiency > 3) {
        return false;
    }
    SkillNode* current = head;
    while (current) {
        if (std::strcmp(current->skillName, skillName) == 0) {
            current->proficiency = proficiency;
            return true;
        }
        current = current->next;
    }
    return false;
}

bool SkillList::contains(const char* skillName) const {
    return getProficiency(skillName) != 0;
}

int SkillList::getProficiency(const char* skillName) const {
    SkillNode* current = head;
    while (current) {
        if (std::strcmp(current->skillName, skillName) == 0) {
            return current->proficiency;
        }
        current = current->next;
    }
    return 0;
}

bool SkillList::isEmpty() const {
    return head == 0;
}

void SkillList::display() const {
    if (!head) {
        std::cout << "None\n";
        return;
    }

    SkillNode* current = head;
    while (current) {
        const char* level = current->proficiency == 1 ? "Beginner" :
                            current->proficiency == 2 ? "Intermediate" : "Advanced";
        std::cout << "- " << current->skillName << " (" << level << ")\n";
        current = current->next;
    }
}

void SkillList::clear() {
    while (head) {
        SkillNode* nodeToDelete = head;
        head = head->next;
        delete nodeToDelete;
    }
}

void SkillList::copyFrom(const SkillList& other) {
    SkillNode* current = other.head;
    while (current) {
        add(current->skillName, current->proficiency);
        current = current->next;
    }
}
