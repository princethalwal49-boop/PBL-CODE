#ifndef STUDENT_H
#define STUDENT_H

#include "LinkedList.h"

const int MAX_STUDENTS = 100;

class Student {
private:
    int id;
    char name[60];
    char branch[40];
    int semester;
    char username[30];
    char password[30];
    float averageRating;
    int ratingCount;
    SkillList teachSkills;
    SkillList learningInterests;

public:
    Student();
    Student(int studentId, const char* studentName, const char* studentBranch,
            int studentSemester, const char* user, const char* pass);

    int getId() const;
    const char* getName() const;
    const char* getBranch() const;
    int getSemester() const;
    const char* getUsername() const;
    bool passwordMatches(const char* pass) const;
    float getAverageRating() const;
    int getRatingCount() const;

    SkillList& getTeachSkills();
    SkillList& getLearningInterests();
    const SkillList& getTeachSkills() const;
    const SkillList& getLearningInterests() const;
    void displayProfile() const;
};

class StudentManager {
private:
    Student students[MAX_STUDENTS];
    int studentCount;

public:
    StudentManager();
    bool registerStudent(int id, const char* name, const char* branch, int semester,
                         const char* username, const char* password);
    Student* login(const char* username, const char* password);
    Student* findById(int id);
    Student* findByUsername(const char* username);
    Student* getStudentAt(int index);
    int getCount() const;
};

#endif
