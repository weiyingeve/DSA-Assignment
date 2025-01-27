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
static void loadDataFromCSV(Dictionary<int, Actor>& actors, Dictionary<int, Movie>& movies, Dictionary<string, void*>& cast);

int main() {
    Dictionary<int, Actor> actors;
    Dictionary<int, Movie> movies;
    Dictionary<string, void*> cast;

    loadDataFromCSV(actors, movies, cast);
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

        else if (mainChoice == 1) {
            int adminChoice;
            displayAdminMenu();
        }
        switch (mainChoice) { // Main menu
        case 1: // Admin menu
            while (true) {
                int adminChoice;
                displayAdminMenu();
                cin >> adminChoice;
                if (adminChoice == 0) {
                    cout << "Exiting the program. Goodbye!" << endl;
                    break;
                }

                switch (adminChoice) {
                case 1: // add new actor
                    string actorName;
                    int actorID;
                    int yob;
                    cout << "Enter actor ID: " << endl;
                    cin >> actorID;
                    cout << "Enter name of actor: " << endl;
                    cin >> actorName;
                    cout << "Enter year of birth of actor: " << endl;
                    cin >> yob;

                    Actor newActor(actorID, actorName, yob);
                    admin.addActor(newActor);
                    break;

                case 2: // add new movie
                    string movieTitle;
                    int movieID;
                    string plot;
                    int yearOfRelease;
                    cout << "Enter movie ID " << endl;
                    cin >> movieID;
                    cout << "Enter movie title: " << endl;
                    cin >> movieTitle;
                    cout << "Enter movie plot: " << endl;
                    cin >> plot;
                    cout << "Enter year of release: " << endl;
                    cin >> yearOfRelease;

                    Movie newMovie(movieID, movieTitle, plot, yearOfRelease);
                    admin.addMovie(newMovie);
                    break;

                case 3: // add actor to a movie
                    int movieID;
                    int actorID;
                    cout << "Enter movie ID: " << endl;
                    cin >> movieID;
                    cout << "Enter actor ID: " << endl;
                    cin >> actorID;

                    admin.addActorToMovie(movieID, actorID);
                    break;

                case 4: // update actor/movie details
                    string type;
                    cout << "Update [actor / movie] details: ";
                    cin >> type;
                    if (type == "Actor" || type == "actor") {
                        int actorId, birthYear;
                        string name;
                        cout << "Enter Actor ID to update: " << endl;
                        cin >> actorId;
                        cout << "Enter New Actor Name: " << endl;
                        cin >> name;
                        cout << "Enter New Actor Birth Year: " << endl;
                        cin >> birthYear;

                        Actor updatedActor(actorId, name, birthYear);
                        admin.updateDetails(type, actorId, updatedActor);
                    }
                    else if (type == "Movie" || type == "movie") {
                        int movieId, year;
                        string title;
                        cout << "Enter Movie ID to update: " << endl;
                        cin >> movieId;
                        cout << "Enter New Movie Title: " << endl;
                        cin >> title;
                        cout << "Enter New Movie Release Year: " << endl;
                        cin >> year;

                        Movie updatedMovie(movieId, title, "", year);
                        admin.updateDetails(type, movieId, updatedMovie);
                    }
                    else {
                        cout << "Invalid type entered. Please enter [actor/movie]" << endl;
                    }
                    break;
                case 5: // return to main menu 
                    break;

                default:
                    cout << "Invalid choice. Try again." << endl;
                    break;
                }
            }
            break;

        case 2: // User menu
            while (true) {
                int userChoice;
                displayUserMenu();
                cin >> userChoice;
                if (userChoice == 0) {
                    cout << "Exiting the program. Goodbye!" << endl;
                    break;
                } 
                switch (userChoice) {
                case 1: // display actors by age
                    int min;
                    int max;
                    cout << "Enter min age: " << endl;
                    cin >> min;
                    cout << "Enter max age: " << endl;
                    cin >> max;

                    user.displayActorsByAgeRange(actors, min, max);
                    break;
                case 2: // display movies made in the past 3 years
                    user.displayMoviesPast3Years(movies);
                    break;
                case 3: // display movies the actor starred in
                    string actorName;
                    cout << "Enter name of actor: " << endl;
                    cin >> actorName;
                    user.displayMoviesByActor(actors, actorName);
                    break;
                case 4: // display all actors in the movie
                    string movieName;
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
                    } else {
                        cout << "Actor not found" << endl;
                    break;
                case 6: // add rating to actor or movie
                    cout << "Add rating to [actor/movie]? " << endl;
                    string choice;
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
                    break;
                case 8: // return to main menu
                    break;
                }
            }
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
static void loadDataFromCSV(Dictionary<int, Actor>& actors, Dictionary<int, Movie>& movies, Dictionary<string, void*>& cast) {
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

            Actor actor = Actor(stoi(id), name, stoi(birth));
            actors.add(stoi(id), actor);
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

            Movie movie = Movie(stoi(id), title, "", stoi(year));
            movies.add(stoi(id), movie);
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