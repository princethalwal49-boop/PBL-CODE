#include "SkillTree.h"
#include <iostream>
#include <cstring>

SkillTree::SkillTree() : root(0) {}

SkillTree::~SkillTree() {
    destroy(root);
}

SkillTreeNode* SkillTree::createNode(const char* name) {
    if (!name || name[0] == '\0') return 0;
    SkillTreeNode* node = new SkillTreeNode;
    std::strncpy(node->name, name, 49);
    node->name[49] = '\0';
    node->firstChild = 0;
    node->nextSibling = 0;
    return node;
}

void SkillTree::destroy(SkillTreeNode* node) {
    if (!node) return;
    destroy(node->firstChild);
    destroy(node->nextSibling);
    delete node;
}

SkillTreeNode* SkillTree::findNode(SkillTreeNode* node, const char* name) const {
    if (!node || !name) return 0;
    if (std::strcmp(node->name, name) == 0) return node;

    SkillTreeNode* found = findNode(node->firstChild, name);
    return found ? found : findNode(node->nextSibling, name);
}

SkillTreeNode* SkillTree::findParent(SkillTreeNode* node, const char* name) const {
    if (!node) return 0;

    SkillTreeNode* child = node->firstChild;
    while (child) {
        if (std::strcmp(child->name, name) == 0) return node;
        SkillTreeNode* parent = findParent(child, name);
        if (parent) return parent;
        child = child->nextSibling;
    }
    return 0;
}

bool SkillTree::addSkillOrCategory(const char* parentName, const char* name) {
    if (!parentName || !name || name[0] == '\0' || contains(name)) return false;

    // The first item inserted becomes the root category.
    if (!root) {
        if (parentName[0] != '\0') return false;
        root = createNode(name);
        return root != 0;
    }

    SkillTreeNode* parent = findNode(root, parentName);
    if (!parent) return false;

    SkillTreeNode* newNode = createNode(name);
    if (!newNode) return false;

    if (!parent->firstChild) {
        parent->firstChild = newNode;
    } else {
        SkillTreeNode* sibling = parent->firstChild;
        while (sibling->nextSibling) sibling = sibling->nextSibling;
        sibling->nextSibling = newNode;
    }
    return true;
}

bool SkillTree::contains(const char* name) const {
    return findNode(root, name) != 0;
}

const char* SkillTree::getParentName(const char* name) const {
    if (!root || !name || std::strcmp(root->name, name) == 0) return 0;
    SkillTreeNode* parent = findParent(root, name);
    return parent ? parent->name : 0;
}

void SkillTree::displayFrom(SkillTreeNode* node, int depth) const {
    while (node) {
        for (int i = 0; i < depth; ++i) std::cout << "  ";
        std::cout << (depth == 0 ? "" : "+-- ") << node->name << "\n";
        displayFrom(node->firstChild, depth + 1);
        node = node->nextSibling;
    }
}

void SkillTree::display() const {
    if (!root) {
        std::cout << "The skill hierarchy is empty.\n";
        return;
    }
    std::cout << "\n========== SKILL HIERARCHY ==========\n";
    displayFrom(root, 0);
}

void SkillTree::loadDefaultHierarchy() {
    if (root) return;

    addSkillOrCategory("", "Computer Science");
    addSkillOrCategory("Computer Science", "Programming");
    addSkillOrCategory("Programming", "C++");
    addSkillOrCategory("Programming", "Python");
    addSkillOrCategory("Programming", "Java");
    addSkillOrCategory("Computer Science", "Data Structures");
    addSkillOrCategory("Data Structures", "Array");
    addSkillOrCategory("Data Structures", "Linked List");
    addSkillOrCategory("Data Structures", "Stack");
    addSkillOrCategory("Data Structures", "Queue");
    addSkillOrCategory("Data Structures", "Tree");
    addSkillOrCategory("Data Structures", "Graph");
    addSkillOrCategory("Computer Science", "Database");
    addSkillOrCategory("Database", "SQL");
    addSkillOrCategory("Database", "MySQL");
}
