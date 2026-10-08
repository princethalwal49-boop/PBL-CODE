#include "Matching.h"

MatchingSystem::MatchingSystem(StudentGraph& studentGraph) : graph(studentGraph) {}

int MatchingSystem::calculateScore(int proficiency, float averageRating) const {
    // 50 points for possessing the requested skill, 25 for proficiency,
    // and 25 for rating. An unrated student uses neutral 3.0/5.0 rating.
    float ratingForScore = averageRating > 0.0f ? averageRating : 3.0f;
    int proficiencyPoints = (proficiency * 25) / 3;
    int ratingPoints = static_cast<int>(ratingForScore * 5.0f + 0.5f);
    return 50 + proficiencyPoints + ratingPoints;
}

void MatchingSystem::sortByScore(Recommendation recommendations[], int count) const {
    // Bubble sort is intentionally used to demonstrate manual sorting.
    for (int pass = 0; pass < count - 1; ++pass) {
        for (int i = 0; i < count - pass - 1; ++i) {
            if (recommendations[i].score < recommendations[i + 1].score) {
                Recommendation temporary = recommendations[i];
                recommendations[i] = recommendations[i + 1];
                recommendations[i + 1] = temporary;
            }
        }
    }
}

int MatchingSystem::getRecommendations(Student* learner, StudentManager& manager,
                                       const char* requestedSkill, Recommendation results[], int maximumResults) {
    if (!learner || !requestedSkill || !results || maximumResults <= 0) return 0;
    if (!learner->getLearningInterests().contains(requestedSkill)) return -1;

    int resultCount = 0;
    for (int i = 0; i < manager.getCount() && resultCount < maximumResults; ++i) {
        Student* candidate = manager.getStudentAt(i);
        if (candidate == learner) continue;

        int proficiency = candidate->getTeachSkills().getProficiency(requestedSkill);
        if (proficiency == 0) continue;

        results[resultCount].student = candidate;
        results[resultCount].proficiency = proficiency;
        results[resultCount].rating = candidate->getAverageRating();
        results[resultCount].score = calculateScore(proficiency, results[resultCount].rating);
        ++resultCount;
    }

    sortByScore(results, resultCount);
    for (int i = 0; i < resultCount; ++i) {
        graph.addConnection(learner->getId(), results[i].student->getId(), results[i].score);
    }
    return resultCount;
}
