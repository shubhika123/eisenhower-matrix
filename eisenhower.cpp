#include <iostream>
#include <vector>
#include <string>
#include <queue>
#include <iomanip>
using namespace std;

// Task structure
struct Task {
    string name;
    bool urgent;
    bool important;
};

// Comparator for priority queue
struct Compare {
    int priority(const Task& t) const {
        if (t.important && t.urgent) return 4;             // highest
        if (!t.important && t.urgent) return 3;
        if (t.important && !t.urgent) return 2;
        return 1;                                          // lowest
    }

    bool operator()(const Task& a, const Task& b) const {
        return priority(a) < priority(b);
    }
};



// Function to print a quadrant
void printQuadrant(const vector<Task>& q) {
    if (q.empty()) {
        cout << "  (No tasks)" << endl;
        return;
    }
    for (auto& t : q) {
        cout << "  - " << t.name << endl;
    }
}

int main() {
    vector<Task> tasks;
    vector<Task> q1, q2, q3, q4;

    int n;
    cout << "\nEnter number of tasks: ";
    cin >> n;
    cin.ignore();

    for (int i = 0; i < n; i++) {
        Task t;
        cout << "\nEnter task name: ";
        getline(cin, t.name);

        cout << "Is it important? (1 yes / 0 no): ";
        cin >> t.important;

        cout << "Is it urgent? (1 yes / 0 no): ";
        cin >> t.urgent;

        cin.ignore();

        tasks.push_back(t);

        if (t.important && t.urgent) q1.push_back(t);
        else if (t.important && !t.urgent) q2.push_back(t);
        else if (!t.important && t.urgent) q3.push_back(t);
        else q4.push_back(t);
    }

    priority_queue<Task, vector<Task>, Compare> pq;
    for (auto& t : tasks) pq.push(t);

cout << "\n=============================================\n";
cout << "            EISENHOWER MATRIX\n";
cout << "=============================================\n\n";

auto printRow = [](const vector<Task>& left, const vector<Task>& right) {
    size_t maxLen = max(left.size(), right.size());
    for (size_t i = 0; i < maxLen; i++) {
        cout << "| ";

        if (i < left.size()) {
            cout << "- " << left[i].name;
            cout << string(28 - min((int)left[i].name.size(), 28), ' ');
        } else {
            cout << string(30, ' ');
        }

        cout << "| ";

        if (i < right.size()) {
            cout << "- " << right[i].name;
            cout << string(28 - min((int)right[i].name.size(), 28), ' ');
        } else {
            cout << string(30, ' ');
        }

        cout << "|\n";
    }
};

cout << "------------------------------------------------------------\n";
cout << "| Important & Urgent           | Important & Not Urgent       |\n";
cout << "------------------------------------------------------------\n";
printRow(q1, q2);

cout << "------------------------------------------------------------\n";
cout << "| Not Important & Urgent       | Not Important & Not Urgent   |\n";
cout << "------------------------------------------------------------\n";
printRow(q3, q4);

cout << "------------------------------------------------------------\n";


    cout << "\n\n=============================================\n";
    cout << "   RECOMMENDED PRIORITY ORDER (Top to Bottom)\n";
    cout << "=============================================\n";

    int order = 1;
    while (!pq.empty()) {
        Task t = pq.top();
        pq.pop();
        cout << order++ << ". " << t.name << "   (Important: " 
                << t.important << ", Urgent: " << t.urgent << ")\n";
    }

    cout << endl;
    return 0;
}