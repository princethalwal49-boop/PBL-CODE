#ifndef SKILLTREE_H
#define SKILLTREE_H

// Child-sibling representation: a node has one pointer to its first child and
// one pointer to its next sibling. This allows any number of child skills.
struct SkillTreeNode {
    char name[50];
    SkillTreeNode* firstChild;
    SkillTreeNode* nextSibling;
};

class SkillTree {
private:
    SkillTreeNode* root;

    SkillTreeNode* findNode(SkillTreeNode* node, const char* name) const;
    SkillTreeNode* findParent(SkillTreeNode* node, const char* name) const;
    void displayFrom(SkillTreeNode* node, int depth) const;
    void destroy(SkillTreeNode* node);
    SkillTreeNode* createNode(const char* name);

public:
    SkillTree();
    ~SkillTree();

    void loadDefaultHierarchy();
    bool addSkillOrCategory(const char* parentName, const char* name);
    bool contains(const char* name) const;
    const char* getParentName(const char* name) const;
    void display() const;
};

#endif
