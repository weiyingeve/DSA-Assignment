// DSA-Assignment.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <fstream>
#include <sstream>
#include "Actor.h"
#include "Movie.h"
#include "Dictionary.h"
#include "DoublyLinkedList.h"
#include "User.h"
#include "Admin.h"
#include "Report.h"
using namespace std;

void displayMainMenu();
void displayAdminMenu();
void displayUserMenu();
void loadDataFromCSV(Dictionary<int, Actor>& actors, Dictionary<int, Movie>& movies);

int main() {
    Dictionary<int, Actor> actors;
    Dictionary<int, Movie> movies;
    Dictionary<int, Report> reports;

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

                switch (adminChoice) {
                case 0:
                    cout << "Returning to main menu..." << endl;
                    break;
                case 1: // add new actor
                    cout << "Enter actor ID: ";
                    cin >> actorID;
                    cin.ignore(); // Clear buffer
                    cout << "Enter actor name: ";
                    getline(cin, actorName);
                    cout << "Enter year of birth: ";
                    cin >> yob;

                    admin.addActor(Actor(actorID, actorName, yob));
                    break;

                case 2: // add new movie
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

                case 3: // add actor to movie
                    cout << "Enter actor ID: ";
                    cin >> actorID;
                    cout << "Enter movie ID: ";
                    cin >> movieID;

                    admin.addActorToMovie(actorID, movieID);
                    break;

                case 4: // view report 
                    admin.viewReports(reports);
                    break;

                case 5: // resolve issue

                    admin.resolveIssue(reports, actors, movies);
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
                case 1: // display actor by age
                    int min;
                    int max;
                    cout << "Enter min age: " << endl;
                    cin >> min;
                    cout << "Enter max age: " << endl;
                    cin >> max;

                    user.displayActorsByAgeRange(actors, min, max);
                    break;

                case 2: // display movies made within the past 3 years
                    user.displayMoviesPast3Years(movies);;
                    break;

                case 3: // display all movies an actor starred in
                    cout << "Enter name of actor: " << endl;
                    cin >> actorName;
                    user.displayMoviesByActor(actors, actorName);
                    break;

                case 4: // display all actors in a movie
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
                case 6: // report error
                    user.reportError(reports);
                    break;

                case 7: // add rating to actor or movie
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

                case 8: // get reccommendation based on ratings
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
    cout << "[4] View reports\n";
    cout << "[5] Resolve issues\n";
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
	cout << "[6] Report error\n";
    cout << "[7] Add rating to an actor or movie\n";
    cout << "[8] Get recommendations based on ratings (actor/movie)\n";
    cout << "[0] Return to Main Menu\n";
    cout << "Choose an option: ";
}


// Function to load data from CSV files into the dictionary
static void loadDataFromCSV(Dictionary<int, Actor>& actors, Dictionary<int, Movie>& movies) {
	ifstream actorsFile("actors.csv");
	ifstream moviesFile("movies.csv");
	ifstream castFile("cast.csv");

	// Load actors
	if (actorsFile.is_open()) {
		string line;
		getline(actorsFile, line); // Skip header row

		while (getline(actorsFile, line)) {
			stringstream ss(line);
			string id, name, birth;

			getline(ss, id, ',');
			getline(ss, name, ',');
			getline(ss, birth, ',');

			// Validate and add actor
			if (!id.empty() && !birth.empty()) {
				try {
					Actor actor(stoi(id), name, stoi(birth));
					actors.add(stoi(id), actor);
				}
				catch (const invalid_argument&) {
					cerr << "Invalid data in actors.csv: " << line << endl;
				}
			}
			else {
				cerr << "Skipping invalid line in actors.csv: " << line << endl;
			}
		}
		actorsFile.close();
	}
	else {
		cerr << "Failed to open actors.csv file." << endl;
	}

	// Load movies
	if (moviesFile.is_open()) {
		string line;
		getline(moviesFile, line); // Skip header row

		while (getline(moviesFile, line)) {
			stringstream ss(line);
			string id, title, plot, year;

			getline(ss, id, ','); // Read movie ID

			// Handle movie titles with and without quotes
			if (ss.peek() == '"') {  // If the title starts with a quote
				ss.get(); // Consume the opening quote
				getline(ss, title, '"'); // Read until the closing quote
				ss.get(); // Consume the comma after the closing quote
			}
			else {
				getline(ss, title, ','); // Read normal title
            
			}
            getline(ss, plot, ','); // read plot
			getline(ss, year, ','); // Read year

			// Validate and add movie
			if (!id.empty() && !year.empty()) {
				try {
					Movie movie(stoi(id), title, plot, stoi(year));
					movies.add(stoi(id), movie);
				}
				catch (const invalid_argument&) {
					cerr << "Invalid data in movies.csv: " << line << endl;
				}
			}
			else {
				cerr << "Skipping invalid line in movies.csv: " << line << endl;
			}
		}
		moviesFile.close();
	}
	else {
		cerr << "Failed to open movies.csv file." << endl;
	}

	// Load cast relationships
	if (castFile.is_open()) {
		string line;
		getline(castFile, line); // Skip header row

		while (getline(castFile, line)) {
			stringstream ss(line);
			string actorId, movieId;

			getline(ss, actorId, ',');
			getline(ss, movieId, ',');

			if (!actorId.empty() && !movieId.empty()) {
				try {
					int aId = stoi(actorId);
					int mId = stoi(movieId);
					if (actors.contains(aId) && movies.contains(mId)) {
						actors.get(aId).addMovie(movies.get(mId));
						movies.get(mId).addActor(actors.get(aId));
					}
				}
				catch (const invalid_argument&) {
					cerr << "Invalid cast entry: " << line << endl;
				}
			}
			else {
				cerr << "Skipping invalid line in cast.csv: " << line << endl;
			}
		}
		castFile.close();
	}
	else {
		cerr << "Failed to open cast.csv file." << endl;
	}
}
