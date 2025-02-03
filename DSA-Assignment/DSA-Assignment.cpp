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
#include "User.h"
#include "Admin.h"
using namespace std;

void displayMainMenu();
void displayAdminMenu();
void displayUserMenu();
void loadDataFromCSV(Dictionary<int, Actor>& actors, Dictionary<int, Movie>& movies);

int main() {
    Dictionary<int, Actor> actors;
    Dictionary<int, Movie> movies;

    loadDataFromCSV(actors, movies);
    Admin admin("Rena", 1);
    User user("Isabelle", 1);
    while (true) {
        int mainChoice;
        displayMainMenu();
        cin >> mainChoice;

        if (mainChoice == 0) {
            cout << "Exiting the program. Goodbye!" << endl;
            break;
        }

        if (mainChoice == 1) { // Admin Menu
            string actorName, movieTitle, type, plot;
            int actorID, movieID, yearOfRelease, yob, adminChoice;

            while (true) {
                displayAdminMenu();
                cin >> adminChoice;

                if (adminChoice == 0) {
                    cout << "Returning to main menu..." << endl;
                    break;
                }

                switch (adminChoice) {
                case 1:
                    cout << "Enter actor ID: ";
                    cin >> actorID;
                    cin.ignore(); // Clear buffer
                    cout << "Enter actor name: ";
                    getline(cin, actorName);
                    cout << "Enter year of birth: ";
                    cin >> yob;

                    admin.addActor(Actor(actorID, actorName, yob));
                    break;

                case 2:
                    cout << "Enter movie ID: ";
                    cin >> movieID;
                    cin.ignore();
                    cout << "Enter movie title: ";
                    getline(cin, movieTitle);
                    cout << "Enter year of release: ";
                    cin >> yearOfRelease;
                    cin.ignore();
                    cout << "Enter movie type: ";
                    getline(cin, type);
                    cout << "Enter plot: ";
                    getline(cin, plot);

                    admin.addMovie(Movie(movieID, movieTitle, plot, yearOfRelease));
                    break;

                case 3:
                    cout << "Enter actor ID: ";
                    cin >> actorID;
                    cout << "Enter movie ID: ";
                    cin >> movieID;

                    admin.addActorToMovie(actorID, movieID);
                    break;

                default:
                    cout << "Invalid choice. Please try again." << endl;
                }
            }
        }

        if (mainChoice == 2) { // User Menu
            int userChoice;
            string actorName, movieName, choice;

            while (true) {
                displayUserMenu();
                cin >> userChoice;

                if (userChoice == 0) {
                    cout << "Returning to main menu..." << endl;
                    break;
                }

                switch (userChoice) {
                case 1:
                    int min;
                    int max;
                    cout << "Enter min age: " << endl;
                    cin >> min;
                    cout << "Enter max age: " << endl;
                    cin >> max;

                    user.displayActorsByAgeRange(actors, min, max);
                    break;

                case 2:
                    user.displayMoviesPast3Years(movies);;
                    break;

                case 3:
                    cout << "Enter name of actor: " << endl;
                    cin >> actorName;
                    user.displayMoviesByActor(actors, actorName);
                    break;
                case 4:
                    cout << "Enter movie title: " << endl;
                    cin >> movieName;

                    user.displayActorsByMovie(movies, movieName);
                    break;
                case 5: // display actors actor knows
                    int actorID;
                    cout << "Enter actor id: " << endl;
                    cin >> actorID;
                    if (actors.contains(actorID)) {
                        user.displayActorsKnown(movies, actors.get(actorID));
                    }
                    else {
                        cout << "Actor not found" << endl;
                        break;
                case 6: // add rating to actor or movie
                    cout << "Add rating to [actor/movie]? " << endl;
                    cin >> choice;
                    if (choice == "actor" || choice == "Actor") {
                        string actorName;
                        cout << "Enter name of actor: " << endl;
                        cin >> actorName;
                        user.addActorRating(actors, actorName);
                    }
                    else if (choice == "movie" || choice == "Movie") {
                        string movieTitle;
                        cout << "Enter movie title: " << endl;
                        cin >> movieTitle;
                        user.addMovieRating(movies, movieTitle);
                    }
                    else {
                        cout << "Invalid input. Please enter [actor/movie]" << endl;
                    }
                    break;
                case 7: // get reccommendation based on ratings
                    user.getRecommendationsByRanking(movies);
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    }
                }
            }
        }

        return 0;
    }
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
static void loadDataFromCSV(Dictionary<int, Actor>& actors, Dictionary<int, Movie>& movies) {
    ifstream actorsFile("actors.csv");
    ifstream moviesFile("movies.csv");
    ifstream castFile("cast.csv");
    if (actorsFile.is_open()) {
        string line;
        getline(actorsFile, line);
        while (getline(actorsFile, line)) {
            stringstream ss(line);
            string id, name, birth;
            getline(ss, id, ',');
            getline(ss, name, ',');
            getline(ss, birth, ',');

            Actor actor = Actor(stoi(id), name, stoi(birth));
            actors.add(stoi(id), actor);
        }
        actorsFile.close();
    }
    else {
        cerr << "Failed to open actors.csv file." << endl;
    }

    if (moviesFile.is_open()) {
        string line;
        getline(moviesFile, line);
        while (getline(moviesFile, line)) {
            stringstream ss(line);
            string id, title, year;
            getline(ss, id, ',');
            getline(ss, title, ',');
            getline(ss, year, ',');

            Movie movie = Movie(stoi(id), title, "", stoi(year));
            movies.add(stoi(id), movie);
        }
        moviesFile.close();
    }
    else {
        cerr << "Failed to open movies.csv file." << endl;
    }

    if (castFile.is_open()) {
        string line;
        getline(castFile, line);
        while (getline(castFile, line)) {
            stringstream ss(line);
            string actorId, movieId;
            getline(ss, actorId, ',');
            getline(ss, movieId, ',');

            int aId = stoi(actorId);
            int mId = stoi(movieId);

            if (actors.contains(aId) && movies.contains(mId)) {
                actors.get(aId).addMovie(movies.get(mId));
                movies.get(mId).addActor(actors.get(aId));
            }
        }
        castFile.close();
    }
    else {
        cerr << "Failed to open cast.csv file." << endl;
    }
}