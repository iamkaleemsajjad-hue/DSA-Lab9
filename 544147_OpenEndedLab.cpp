/*
    Name    : Muhammad Kaleem Sajjad
    CMS ID  : 544147
    Section : BSCS15E
    Course  : CS: Data Structures and Algorithms
    Lab     : Open Ended Lab: Student Help Desk

    Design:
    Used a singly linked list to store student records because insertion
    at the tail and sequential search both fit naturally, and we don't
    need random access or sorted order here.
    Used a queue (linked list based) for help requests so the desk
    serves students in FIFO order, first come first served.

    Complexity:
    Add student    : O(n) we walk to the tail to check duplicates and append
    Search student : O(n) linear scan through the list
*/

#include <iostream>
#include <string>
using namespace std;

// Student linked list node
struct Student {
    int roll;
    string name;
    Student* next;
};

// Help request queue node
struct Request {
    int roll;
    Request* next;
};

// Global head of the student list
Student* head = NULL;

// Front and rear pointers for the help request queue
Request* frontReq = NULL;
Request* rearReq  = NULL;

// Find a student by roll number, returns NULL if not found
Student* findStudent(int roll) {
    Student* temp = head;
    while (temp != NULL) {
        if (temp->roll == roll)
            return temp;
        temp = temp->next;
    }
    return NULL;
}

// Add a new student to the end of the linked list
void addStudent() {
    int roll;
    string name;

    cout << "Enter roll number: ";
    cin >> roll;

    // Duplicate check
    if (findStudent(roll) != NULL) {
        cout << "Roll number already exists. Try a different one." << endl;
        return;
    }

    cout << "Enter name: ";
    cin.ignore();
    getline(cin, name);

    // Create the new node
    Student* s = new Student;
    s->roll = roll;
    s->name = name;
    s->next = NULL;

    // Append to the end of the list
    if (head == NULL) {
        head = s;
    } else {
        Student* temp = head;
        while (temp->next != NULL)
            temp = temp->next;
        temp->next = s;
    }

    cout << "Student added successfully." << endl;
}

// Search for a student by roll number and print their info
void searchStudent() {
    int roll;
    cout << "Enter roll number to search: ";
    cin >> roll;

    Student* s = findStudent(roll);
    if (s == NULL) {
        cout << "Student not found." << endl;
    } else {
        cout << "Found: Roll " << s->roll << "  Name: " << s->name << endl;
    }
}

// Display all students currently in the list
void displayStudents() {
    if (head == NULL) {
        cout << "No students registered yet." << endl;
        return;
    }

    cout << "Student List:" << endl;
    Student* temp = head;
    int count = 1;
    while (temp != NULL) {
        cout << count << ". Roll: " << temp->roll << "  Name: " << temp->name << endl;
        temp = temp->next;
        count++;
    }
}

// Add a help request for a registered student (enqueue)
void addRequest() {
    int roll;
    cout << "Enter roll number for help request: ";
    cin >> roll;

    // Only registered students can submit requests
    if (findStudent(roll) == NULL) {
        cout << "Student not registered. Request rejected." << endl;
        return;
    }

    Request* r = new Request;
    r->roll = roll;
    r->next = NULL;

    // Enqueue at the rear
    if (rearReq == NULL) {
        frontReq = r;
        rearReq  = r;
    } else {
        rearReq->next = r;
        rearReq = r;
    }

    cout << "Help request added for roll " << roll << "." << endl;
}

// Serve (dequeue) the earliest help request
void serveRequest() {
    if (frontReq == NULL) {
        cout << "No pending help requests." << endl;
        return;
    }

    Request* r = frontReq;
    Student* s = findStudent(r->roll);

    cout << "Serving: Roll " << s->roll << "  Name: " << s->name << endl;

    // Dequeue from the front
    frontReq = frontReq->next;
    if (frontReq == NULL)
        rearReq = NULL;

    delete r;
}

// Display all pending help requests without removing them
void displayRequests() {
    if (frontReq == NULL) {
        cout << "No pending help requests." << endl;
        return;
    }

    cout << "Pending Requests (FIFO order):" << endl;
    Request* temp = frontReq;
    int pos = 1;
    while (temp != NULL) {
        Student* s = findStudent(temp->roll);
        cout << pos << ". Roll: " << temp->roll << "  Name: " << s->name << endl;
        temp = temp->next;
        pos++;
    }
}

// Free all dynamically allocated memory before exit
void freeMemory() {
    // Clear the student linked list
    while (head != NULL) {
        Student* temp = head;
        head = head->next;
        delete temp;
    }

    // Clear the request queue
    while (frontReq != NULL) {
        Request* temp = frontReq;
        frontReq = frontReq->next;
        delete temp;
    }
    rearReq = NULL;
}

int main() {
    int choice;

    cout << "Student Help Desk" << endl;

    do {
        cout << "\n1. Add student" << endl;
        cout << "2. Search student" << endl;
        cout << "3. Display all students" << endl;
        cout << "4. Add help request" << endl;
        cout << "5. Serve next help request" << endl;
        cout << "6. View pending requests" << endl;
        cout << "7. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            addStudent();
        } else if (choice == 2) {
            searchStudent();
        } else if (choice == 3) {
            displayStudents();
        } else if (choice == 4) {
            addRequest();
        } else if (choice == 5) {
            serveRequest();
        } else if (choice == 6) {
            displayRequests();
        } else if (choice == 7) {
            cout << "Exiting. Goodbye!" << endl;
        } else {
            cout << "Invalid choice. Enter 1 to 7." << endl;
        }

    } while (choice != 7);

    // Release all heap memory before program ends
    freeMemory();

    return 0;
}
