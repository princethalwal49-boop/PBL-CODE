#ifndef LINKEDLIST_H
#define LINKEDLIST_H

// A manually implemented singly linked list used for student skills.
struct SkillNode {
    char skillName[50];
    int proficiency; // 1 = Beginner, 2 = Intermediate, 3 = Advanced
    SkillNode* next;
};

class SkillList {
private:
    SkillNode* head;

public:
    SkillList();
    SkillList(const SkillList& other);
    SkillList& operator=(const SkillList& other);
    ~SkillList();

    bool add(const char* skillName, int proficiency);
    bool remove(const char* skillName);
    bool updateProficiency(const char* skillName, int proficiency);
    bool contains(const char* skillName) const;
    int getProficiency(const char* skillName) const;
    bool isEmpty() const;
    void display() const;
    void clear();

private:
    void copyFrom(const SkillList& other);
};

#endif
