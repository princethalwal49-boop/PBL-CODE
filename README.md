# PeerLearn

Console-based C++ Data Structures project, built incrementally without STL containers.

## Current milestone: approximately 40%

- Fixed array of student records
- Registration and login
- Profile display
- Manually implemented singly linked lists for teachable skills and learning interests
- Add, remove, update, and display skill operations
- Manually implemented child-sibling skill tree
- Seeded computer-science skill hierarchy with display, search, parent lookup, and insertion
- Manually implemented weighted graph using linked adjacency lists
- Linear student search by ID, name, branch, and teachable skill
- Fixed recommendation array, manual bubble sort, and weighted peer connections
- Matching formula: 50% skill compatibility, 25% proficiency, 25% rating

## Build (Windows / g++)

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp Student.cpp LinkedList.cpp SkillTree.cpp Graph.cpp Matching.cpp -o PeerLearn.exe
.\PeerLearn.exe
```

