# PeerLearn

Console-based C++ Data Structures project, built incrementally without STL containers.

## Current milestone: Module 1

- Fixed array of student records
- Registration and login
- Profile display
- Manually implemented singly linked lists for teachable skills and learning interests
- Add, remove, update, and display skill operations

## Build (Windows / g++)

```powershell
g++ -std=c++11 -Wall -Wextra -pedantic main.cpp Student.cpp LinkedList.cpp -o PeerLearn.exe
.\PeerLearn.exe
```

The later modules (skill tree, graph and matching, queue, ratings, projects, and persistence) will be added one at a time.
