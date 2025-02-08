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
    static Dictionary<int, Actor> actors;
    static Dictionary<int, Movie> movies;
    static Dictionary<int, Report> reports;

    loadDataFromCSV(actors, movies);
    Admin admin("Rena", 1);
    User user("Isabelle", 1);


    bool mainMenuActive = true;
    while (mainMenuActive) {
        int mainChoice;
        displayMainMenu();
        cin >> mainChoice;

        if (mainChoice == 0) {
            cout << "Exiting the program. Goodbye!" << endl;
            mainMenuActive = false;
            break;
        }

        if (mainChoice == 1) { // Admin Menu
            string actorName, movieTitle, type, plot;
            int actorID, movieID, yearOfRelease, yob, adminChoice;

            bool adminMenuActive = true;
            while (adminMenuActive) {
                displayAdminMenu();
                cin >> adminChoice;

                switch (adminChoice) {
                case 0:
                    cout << "Returning to main menu..." << endl;
                    adminMenuActive = false;
                    break;
                case 1: // add new actor
                    cout << "Enter actor ID: ";
                    cin >> actorID;

                    if (actors.contains(actorID)) {
                        cout << "Actor already exists!" << endl;
                        break;
                    }

                    cin.ignore(); // Clear buffer
                    cout << "Enter actor name: ";
                    getline(cin, actorName);
                    cout << "Enter year of birth: ";
                    cin >> yob;

                    admin.addActor(Actor(actorID, actorName, yob), actors);
                    break;

                case 2: // add new movie
                    cout << "Enter movie ID: ";
                    cin >> movieID;

                    if (movies.contains(movieID)) {
                        cout << "Movie already exists!" << endl;
                        break;
                    }

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

                    admin.addMovie(Movie(movieID, movieTitle, plot, yearOfRelease), movies);
                    break;

                case 3: // add actor to movie
                    cout << "Enter actor ID: ";
                    cin >> actorID;
                    if (!actors.contains(actorID)) {
                        cout << "Error: Actor ID " << actorID << " not found!" << endl;
                        break;
                    }

                    cout << "Enter movie ID: ";
                    cin >> movieID;

                    if (!movies.contains(movieID)) {
                        cout << "Error: Movie ID " << movieID << " not found!" << endl;
                        break;
                    }

                    admin.addActorToMovie(actorID, movieID, actors, movies);
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
            int userChoice, actorId, movieId, reportId;
            string choice, type, description;
            bool userMenuActive = true;
            while (userMenuActive) {
                displayUserMenu();
                cin >> userChoice;
                
                switch (userChoice) {
                case 0:
                    cout << "Returning to main menu..." << endl;
                    userMenuActive = false;
                    break;
                case 1: // display actor by age
                    int min;
                    int max;
                    cout << "Enter min age: ";
                    cin >> min;
                    cout << "Enter max age: ";
                    cin >> max;

                    user.displayActorsByAgeRange(actors, min, max);
                    break;

                case 2: // display movies made within the past 3 years
                    user.displayMoviesPast3Years(movies);;
                    break;

                case 3: // display all movies an actor starred in
                    cout << "Enter actor id: " << endl;
                    cin >> actorId;
                    user.displayMoviesByActor(actors, actorId);
                    break;

                case 4: // display all actors in a movie
                    cout << "Enter movie id: " << endl;
                    cin >> movieId;

                    user.displayActorsByMovie(movies, movieId);
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
                    cin.ignore();

                    cout << "Enter type of report: ";
                    getline(cin, type);
                    cout << "Enter description of report (include id of actor or movie): ";
                    getline(cin, description);

                    //generate report Id
                    reportId = reports.getLength() + 1;
                    user.reportError(Report(reportId, type, description), reports);
                    break;

                case 7: // add rating to actor or movie
                    cout << "Add rating to [actor/movie]? " << endl;
                    cin >> choice;
                    if (choice == "actor" || choice == "Actor") {
                        int actorId;
                        cout << "Enter actorId: " << endl;
                        cin >> actorId;
                        user.addActorRating(actors, actorId);
                    }
                    else if (choice == "movie" || choice == "Movie") {
                        int movieId;
                        cout << "Enter movie id: " << endl;
                        cin >> movieId;
                        user.addMovieRating(movies, movieId);
                    }
                    else {
                        cout << "Invalid input. Please enter [actor/movie]" << endl;
                    }
                    break;

                case 8: // get reccommendation based on actor ratings
                    user.getActorRecommendationsByRanking(actors);
                    break;

                case 9: // get reccommendation based on movie ratings
                    user.getMovieRecommendationsByRanking(movies);
                    break;
                default:
                    cout << "Invalid choice. Please try again." << endl;
                    }
                }
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
    cout << "[8] Get recommendations based on actor ratings\n";
    cout << "[9] Get recommendations based on movie ratings\n";
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
