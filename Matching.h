#ifndef MATCHING_H
#define MATCHING_H

#include "Student.h"
#include "Graph.h"

struct Recommendation {
    Student* student;
    int proficiency;
    float rating;
    int score;
};

class MatchingSystem {
private:
    StudentGraph& graph;
    int calculateScore(int proficiency, float averageRating) const;
    void sortByScore(Recommendation recommendations[], int count) const;

public:
    MatchingSystem(StudentGraph& studentGraph);

    // Returns -1 if the requested skill is not listed as a learning interest.
    int getRecommendations(Student* learner, StudentManager& manager,
                           const char* requestedSkill, Recommendation results[], int maximumResults);
};

#endif
