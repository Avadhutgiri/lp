#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_BOXES = 100;

vector<int> boxCapacity; // Capacity of each box
vector<int> originalBoxCapacity; // Original box capacities for resetting
vector<int> itemSize; // Sizes of items
vector<string> itemName; // Names of items
int numBoxes, numItems;

void resetBoxes() {
    boxCapacity = originalBoxCapacity;
}

// First Fit algorithm 
void firstFit() {
    vector<int> allocation(numItems, -1);

    for (int i = 0; i < numItems; ++i) {
        for (int j = 0; j < numBoxes; j++) {
            if (boxCapacity[j] >= itemSize[i]) {
                allocation[i] = j;
                boxCapacity[j] -= itemSize[i]; // Reduce box capacity after allocation
                break;
            }
        }
    }

    cout << "\nItem Name\tItem Size\tBox No.\n";
    for (int i = 0; i < numItems; i++) {
        cout << itemName[i] << "\t\t" << itemSize[i] << "\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1;
        } else {
            cout << "Not Allocated";
        }
        cout << endl;
    }

    // resetBoxes();
} 

void bestFit() {
    vector<int> allocation(numItems, -1);

    for (int i = 0; i < numItems; i++) {
        int bestIdx = -1;
        for (int j = 0; j < numBoxes; j++) {
            if (boxCapacity[j] >= itemSize[i]) {
                if (bestIdx == -1 || boxCapacity[bestIdx] > boxCapacity[j]) {
                    bestIdx = j;
                }
            }
        }
        if (bestIdx != -1) {
            allocation[i] = bestIdx;
            boxCapacity[bestIdx] -= itemSize[i];
        }
    }

    cout << "\nItem Name\tItem Size\tBox No.\n";
    for (int i = 0; i < numItems; i++) {
        cout << itemName[i] << "\t\t" << itemSize[i] << "\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1;
        } else {
            cout << "Not Allocated";
        }
        cout << endl;
    }

    // resetBoxes();
}  

void worstFit() {
    vector<int> allocation(numItems, -1);

    for (int i = 0; i < numItems; i++) {
        int wstIdx = -1;
        for (int j = 0; j < numBoxes; j++) {
            if (boxCapacity[j] >= itemSize[i]) {
                if (wstIdx == -1 || boxCapacity[wstIdx] < boxCapacity[j]) {
                    wstIdx = j;
                }
            }
        }

        if (wstIdx != -1) {
            allocation[i] = wstIdx;
            boxCapacity[wstIdx] -= itemSize[i];
        }
    }

    cout << "\nItem Name\tItem Size\tBox No.\n";
    for (int i = 0; i < numItems; i++) {
        cout << itemName[i] << "\t\t" << itemSize[i] << "\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1;
        } else {
            cout << "Not Allocated";
        }
        cout << endl;
    }

    // resetBoxes();
} 

void nextFit() {
    vector<int> allocation(numItems, -1);
    int j = 0;

    for (int i = 0; i < numItems; i++) {
        int start = j;
        while (true) {
            if (boxCapacity[j] >= itemSize[i]) {
                allocation[i] = j;
                boxCapacity[j] -= itemSize[i];
                break;
            }
            j = (j + 1) % numBoxes;
            if (j == start) break;
        }
    }

    cout << "\nItem Name\tItem Size\tBox No.\n";
    for (int i = 0; i < numItems; i++) {
        cout << itemName[i] << "\t\t" << itemSize[i] << "\t\t";
        if (allocation[i] != -1) {
            cout << allocation[i] + 1;
        } else {
            cout << "Not Allocated";
        }
        cout << endl;
    }

    // resetBoxes();
}

void loadData() {
    cout << "Enter the number of boxes: ";
    cin >> numBoxes;
    boxCapacity.resize(numBoxes);
    originalBoxCapacity.resize(numBoxes);

    cout << "Enter the capacities of the boxes: ";
    for (int i = 0; i < numBoxes; ++i) {
        cin >> boxCapacity[i];
        originalBoxCapacity[i] = boxCapacity[i];
    }

    cout << "Enter the number of items: ";
    cin >> numItems;
    itemSize.resize(numItems);
    itemName.resize(numItems);

    cout << "Enter the names of the items and thier sizes: ";
    for (int i = 0; i < numItems; ++i) {
        cin >> itemName[i];
        cin >> itemSize[i];
    }

}

int main() {
    int choice;

    loadData();

    do {
        cout << "\n1. First Fit\n2. Best Fit\n3. Worst Fit\n4. Next Fit\n0. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: firstFit(); break;
            case 2: bestFit(); break;
            case 3: worstFit(); break;
            case 4: nextFit(); break;
            case 0: cout << "Exiting...\n"; break;
            default: cout << "Invalid choice. Please enter a number between 0 and 4.\n"; break;
        }
    } while (choice != 0);

    return 0;
}
