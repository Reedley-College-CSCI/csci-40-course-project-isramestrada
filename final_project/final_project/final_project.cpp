// CSCI-40 Final Project
// Author: Israel Mosqueda
// Description: Media backlog manager to organize games and movies.

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

// function to save data to txt file
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
        cout << "Data saved to text file" << endl;
    }
    else {
        cout << "Error opening file." << endl; 
    }
}

// Function to load data from txt file to array
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
        cout << "Data successfully loaded. Items found: " << itemCount << endl;
    }
    else {
        cout << "No existing data found / empty." << endl;
    }
}

int main() {
    const int MAX_ITEMS = 100;
    MediaItem library[MAX_ITEMS];
    int itemCount = 0;

    loadFromFile(library, itemCount, MAX_ITEMS);

    // This adds a test item only if there's room
    if (itemCount < MAX_ITEMS) {
        library[itemCount] = { "Elden Ring", "Game", 2022, 10 };
        itemCount++;
    }

    saveToFile(library, itemCount);

    cout << "Check your project folder for data.txt!" << endl;
    return 0;
}