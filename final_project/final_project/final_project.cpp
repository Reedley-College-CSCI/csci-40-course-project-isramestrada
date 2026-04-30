// CSCI-40 Final Project
// Author: Israel Mosqueda
// Description: Media backlog manager that allows a user to add, remove, and organize names of games and movies

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct MediaItem {
    string title;
    string category;
    int year;
    int rating;
};


void saveToFile(MediaItem library[], int itemCount) {
    ofstream outFile("data.txt");
    if (outFile.is_open()) {
        for (int i = 0; i < itemCount; i++) {
            outFile << library[i].title << endl;
            outFile << library[i].category << endl;
            outFile << library[i].year << endl;
            outFile << library[i].rating << endl;
        }
        outFile.close();
    }
}

void loadFromFile(MediaItem library[], int& itemCount, int MAX_ITEMS) {
    ifstream inFile("data.txt");
    itemCount = 0;
    if (inFile.is_open()) {
        while (itemCount < MAX_ITEMS && getline(inFile, library[itemCount].title)) {
            getline(inFile, library[itemCount].category);
            inFile >> library[itemCount].year;
            inFile >> library[itemCount].rating;
            inFile.ignore();
            itemCount++;
        }
        inFile.close();
    }
}

void displayLibrary(MediaItem library[], int itemCount) {
    cout << "\n--- Current Media Backlog (" << itemCount << "/100) ---" << endl;
    if (itemCount == 0) cout << "Library is empty." << endl;
    for (int i = 0; i < itemCount; i++) {
        cout << i + 1 << ". [" << library[i].category << "] " << library[i].title
            << " (" << library[i].year << ") - Rating: " << library[i].rating << "/10" << endl;
    }
}

void addItem(MediaItem library[], int& itemCount, int MAX_ITEMS) {
    if (itemCount >= MAX_ITEMS) {
        cout << "Error: Library is full!" << endl;
        return;
    }
    cout << "\nEnter Title: ";
    getline(cin >> ws, library[itemCount].title); 
    cout << "Enter Category (Game/Movie): ";
    getline(cin, library[itemCount].category);
    cout << "Enter Release Year: ";
    cin >> library[itemCount].year;
    cout << "Enter Rating (1-10): ";
    cin >> library[itemCount].rating;

    itemCount++;
    cout << "Item added successfully!" << endl;
}

void removeItem(MediaItem library[], int& itemCount) {
    if (itemCount == 0) {
        cout << "Nothing to remove." << endl;
        return;
    }
    int index;
    displayLibrary(library, itemCount);
    cout << "Enter the number of the item to remove: ";
    cin >> index;

    if (index < 1 || index > itemCount) {
        cout << "Invalid selection." << endl;
    }
    else {
        for (int i = index - 1; i < itemCount - 1; i++) {
            library[i] = library[i + 1];
        }
        itemCount--;
        cout << "Item removed." << endl;
    }
}

int main() {
    const int MAX_ITEMS = 100;
    MediaItem library[MAX_ITEMS];
    int itemCount = 0;
    int choice = 0;

    loadFromFile(library, itemCount, MAX_ITEMS);

    while (choice != 4) {
        cout << "\n--- Media Backlog Manager ---" << endl;
        cout << "1. View Library" << endl;
        cout << "2. Add Item" << endl;
        cout << "3. Remove Item" << endl;
        cout << "4. Exit & Save" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: displayLibrary(library, itemCount); break;
        case 2: addItem(library, itemCount, MAX_ITEMS); break;
        case 3: removeItem(library, itemCount); break;
        case 4: saveToFile(library, itemCount); cout << "Saving and exiting..." << endl; break;
        default: cout << "Invalid choice, try again." << endl;
        }
    }

    return 0;
}