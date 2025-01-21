// DSA-Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include "Actor.h"
#include "Movie.h"
#include "Dictionary.h"
#include "DoublyLinkedList.h"
using namespace std;

void displayMainMenu();
void displayAdminMenu();
void displayUserMenu();
void loadDataFromCSV();

int main() {
    Dictionary actors;
    Dictionary movies;
    Dictionary cast;

    loadDataFromCSV(actors, movies, cast);

    int choice;

}

void displayMainMenu() {
    cout << "\n===== Main Menu =====\n";
    cout << "[1] Admin\n";
    cout << "[2] User\n";
    cout << "[0] Exit\n";
    cout << "Choose an option: ";
}

void displayAdminMenu() {
    cout << "\n===== Admin Menu =====\n";
    cout << "[1] Add new actor\n";
    cout << "[2] Add new movie\n";
    cout << "[3] Add an actor to a movie\n";
    cout << "[4] Update actor/movie details\n";
    cout << "[0] Return to Main Menu\n";
    cout << "Choose an option: ";
}

void displayUserMenu() {
    cout << "\n===== User Menu =====\n";
    cout << "[1] Display actors by age\n";
    cout << "[2] Display movies made within the past 3 years\n";
    cout << "[3] Display all movies an actor starred in\n";
    cout << "[4] Display all actors in a movie\n";
    cout << "[5] Display list of all actors that an actor knows\n";
    cout << "[6] Add rating to an actor or movie\n";
    cout << "[7] Get recommendations based on ratings (actor/movie)\n";
    cout << "[0] Return to Main Menu\n";
    cout << "Choose an option: ";
}

// Function to load data from CSV files into the dictionary
void loadDataFromCSV(Dictionary& actors, Dictionary& movies, Dictionary& cast) {
    ifstream actorsFile("actors.csv");
    if (actorsFile.is_open()) {
        string line;
        getline(actorsFile, line);
        while (getline(actorsFile, line)) {
            stringstream ss(line);
            string id, name, birth;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, birth, ',');

            Actor* actor = new Actor(stoi(id), name, stoi(birth));
            actors.add(id, actor);
        }
        actorsFile.close();
    }
    else {
        cerr << "Failed to open actors.csv file." << endl;
    }

    ifstream moviesFile("movies.csv");
    if (moviesFile.is_open()) {
        string line;
        getline(moviesFile, line);
        while (getline(moviesFile, line)) {
            stringstream ss(line);
            string id, title, year;
            getline(ss, id, ',');
            getline(ss, title, ',');
            getline(ss, year, ',');

            Movie* movie = new Movie(stoi(id), title, "", stoi(year));
            movies.add(id, movie);
        }
        moviesFile.close();
    }
    else {
        cerr << "Failed to open movies.csv file." << endl;
    }

    ifstream castFile("cast.csv");
    if (castFile.is_open()) {
        string line;
        getline(castFile, line);
        while (getline(castFile, line)) {
            stringstream ss(line);
            string actorId, movieId;
            getline(ss, actorId, ',');
            getline(ss, movieId, ',');

            string castKey = actorId + "," + movieId;
            cast.add(castKey, nullptr);
        }
        castFile.close();
    }
    else {
        cerr << "Failed to open cast.csv file." << endl;
    }
}