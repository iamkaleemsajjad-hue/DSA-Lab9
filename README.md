# Student Help Desk: Open Ended Lab

**Name:** Muhammad Kaleem Sajjad  
**CMS ID:** 544147  
**Section:** BSCS15E  
**Course:** CS: Data Structures and Algorithms  

## What it does

A simple C++ console app for a student help desk. You can register students, search them by roll number, and manage help requests in a queue.

## Data Structures Used

* **Singly Linked List**: stores student records (roll number and name)
* **Queue (linked list based)**: manages help requests in FIFO order

## Menu Options

1. Add student
2. Search student by roll number
3. Display all students
4. Add a help request
5. Serve the next help request
6. View all pending requests
7. Exit

## How to Compile and Run

```bash
g++ -std=c++11 -o helpdesk 544147_OpenEndedLab.cpp
./helpdesk
```

Or open in VS Code and hit **Run**.

## Notes

* Duplicate roll numbers are rejected
* Only registered students can submit help requests
* All heap memory is freed before exit
