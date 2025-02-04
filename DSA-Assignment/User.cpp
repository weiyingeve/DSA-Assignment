#include "User.h"
#include <iostream>
#include <algorithm>
#include <ctime>

using namespace std;

//Constructor
User::User(const string username, const int userId)
    : username(username), userId(userId) {}

//deconstructor
User::~User() {}

//Purpose: Retrieve the username of the user.
//Precondition: None.
//Postcondition: Returns the username of the user.
string User::getUsername() const {
    return username;
}

//Purpose: Retrieve the id of the user.
//Precondition: None.
//Postcondition: Returns the user id.
int User::getUserId() const {
    return userId;
}

//Purpose: Display (in ascending order of age) the actors with age between x and y (entered by user)
//Precondition: x and y entered must be a valid number (y>x)
//Postcondition: Actors displayed must be in ascending order
void User::displayActorsByAgeRange(Dictionary<int, Actor>& actorDict, int x, int y) {
    if (x >= y) {
        cout << "Invalid age range: y must be greater than x." << endl;
    }

    Dictionary<int, Actor> tempDict; 
    DoublyLinkedList<Actor*> actorList = actorDict.getAllItems();
    // Populate the temporary dictionary with actors in the specified age range
    for (int i = 0; i < actorList.getLength(); i++) { 
        Actor actor = actorDict.get(i);
        int age = actor.calculateAge();
        if (age >= x && age <= y) {
            tempDict.add(age, actor); // Use age as the key for ordering
        }
    }

    cout << "Actors between ages " << x << " and " << y << ":" << endl;

    // Display actors in ascending order of age
    for (int age = x; age <= y; ++age) {
        if (tempDict.contains(age)) {
            Actor actor = tempDict.get(age);
            cout << "ID: " << actor.getActorId() << ", Name: " << actor.getName() << ", Age: " << age << endl;
        }
    }
}

//Purpose: Display movies made within the past 3 years 
//Precondition: None
//Postcondition: Movies displayed in ascending order of year
void User::displayMoviesPast3Years(Dictionary<int, Movie>& movieDict) {
    int currentYear = 2025; 

    cout << "Movies released in the past 3 years:" << endl;

    DoublyLinkedList<Movie*> movieList = movieDict.getAllItems();
    for (int i = 0; i < movieList.getLength(); i++) {
        int releaseYear = movieDict.get(i).getYearOfRelease();
        if (currentYear - releaseYear <= 3) {
            cout << "Title: " << movieDict.get(i).getTitle() << ", Year: " << releaseYear << endl;
        }
    }
}

//Purpose: Display all movies an actor starred in
//Precondition: Actor must exist
//Postcondition: Movies displayed must be in alphabetical order
void User::displayMoviesByActor(Dictionary<int, Actor>& actorDict, const string& actorName) {
    DoublyLinkedList<Actor*> actorList = actorDict.getAllItems();
    for (int i = 0; i < actorList.getLength(); i++) {
        if (actorDict.get(i).getName() == actorName) {
            cout << "Movies " << actorName << " acted in: " << endl;
            Actor actor = actorDict.get(i);
            actor.getMovies();
            return;
        }
    }
    cout << "Actor not found in the dictionary." << endl;
    
}

//Purpose: Display actors in a movie
//Precondition: Movie must exist
//Postcondition: Actor displayed must be in alphebetical order
void User::displayActorsByMovie(Dictionary<int, Movie>& movieDict, const string& movieName) {
    DoublyLinkedList<Movie*> movieList = movieDict.getAllItems();
    for (int i = 0; i < movieList.getLength(); i++) {
        if (movieDict.get(i).getTitle() == movieName) {
            cout << "Actors in " << movieName << ": " << endl;
            movieDict.get(i).getActors();
            return;
        }
    }
    cout << "Movie not found in the dictionary." << endl;
}

/// Purpose: Display a list of all actors that a particular actor knows.
/// Precondition: The actor must exist in the movies.
/// Postcondition: Outputs the names of all actors known to the given actor. 
void User::displayActorsKnown(Dictionary<int, Movie>& movieDict, const Actor& actor) {
    Dictionary<string, bool> knownActors; 
    Dictionary<string, bool> visitedMovies;

    cout << "Actors known by " << actor.getName() << ":" << endl;

    // Step 1: Process all movies the given actor starred in
    DoublyLinkedList<Movie*> movieList = movieDict.getAllItems();
    for (int movieKey = 0; movieKey < movieList.getLength(); ++movieKey) {
        Movie movie = movieDict.get(movieKey);

        DoublyLinkedList<Actor> cast = movie.getActorList();

        bool actorInMovie = false;
        typename DoublyLinkedList<Actor>::Node* currentNode = cast.firstNode; 
        while (currentNode != nullptr) {
            if (currentNode->item.getName() == actor.getName()) {
                actorInMovie = true;
                break;
            }
            currentNode = currentNode->next;
        }

        if (!actorInMovie) continue;

        
        visitedMovies.add(movie.getTitle(), true);

        
        currentNode = cast.firstNode;  
        while (currentNode != nullptr) {
            const Actor& coActor = currentNode->item;
            if (coActor.getName() != actor.getName() && !knownActors.contains(coActor.getName())) {
                knownActors.add(coActor.getName(), true);
                cout << "- " << coActor.getName() << endl;
            }
            currentNode = currentNode->next;
        }
    }

    for (int movieKey = 0; movieKey < movieDict.getLength(); ++movieKey) {
        if (!movieDict.contains(movieKey)) continue;

        Movie movie = movieDict.get(movieKey);

        if (visitedMovies.contains(movie.getTitle())) continue;

        DoublyLinkedList<Actor> cast = movie.getActorList();

        bool related = false;
        typename DoublyLinkedList<Actor>::Node* currentNode = cast.firstNode;
        while (currentNode != nullptr) {
            if (knownActors.contains(currentNode->item.getName())) {
                related = true;
                break;
            }
            currentNode = currentNode->next;
        }

        if (!related) continue;

        currentNode = cast.firstNode;
        while (currentNode != nullptr) {
            const Actor& coActor = currentNode->item;
            if (!knownActors.contains(coActor.getName())) {
                knownActors.add(coActor.getName(), true);
                cout << "- " << coActor.getName() << endl;
            }
            currentNode = currentNode->next;
        }
    }
}

//Purpose: Report an error for an actor or movie.
//Precondition: Actor or Movie must exist.
//Postcondition: Creates new report.
void User::reportError(Dictionary<int, Report> reportDict) {
    string type, description;
    int reportId;
    cout << "Enter type of report: ";
    cin >> type;
    cout << "Enter description of report (include id of actor or movie): ";
    cin >> description;
    //generate report Id
    reportId = reportDict.getLength() + 1;
    Report Report(reportId, type, description);
    cout << "Report created successfully. Report details: " << endl;
    Report.print();
    reportDict.add(reportId, Report);
}

//Purpose: Add a new rating for a specific actor.
//Precondition: Actor exists in the Dictionary.
//Postcondition: Updates rating for the actor.
void User::addActorRating(Dictionary<int, Actor>& actorDict, const string& actorName) {
    for (int key = 0; key < actorDict.getLength(); key++) {
        if (actorDict.get(key).getName() == actorName) {
            Actor actor = actorDict.get(key);
            actor.updateRating();
            return;
        }
    }
    cout << "Actor not found in the dictionary." << endl;
}

//Purpose: Add a new rating for a specific movie.
//Precondition: Movie exists in the Dictionary.
//Postcondition: Updates rating for the movie.
void User::addMovieRating(Dictionary<int, Movie>& movieDict, const string& movieName) {
    for (int key = 0; key < movieDict.getLength(); key++) {
        if (movieDict.get(key).getTitle() == movieName) {
            Movie movie = movieDict.get(key);
            movie.updateRating();
            return;
        }
    }
    cout << "Movie not found in the dictionary." << endl;
}

//Purpose: Get recommendations of a movie by ranking.
//Precondition: movieDict not empty.
//Postcondition: Displays movies by ranking in descending order.
void User::getRecommendationsByRanking(Dictionary<int, Movie>& movieDict) {
    DoublyLinkedList<Movie*> movieList = movieDict.getAllItems();

	// Step 2: Sort the DoublyLinkedList by ranking in descending order
    int size = movieList.getLength();
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - i - 1; j++) {
            Movie* movie1 = movieList.get(j);
            Movie* movie2 = movieList.get(j + 1);

            if (movie1->calculateRating() < movie2->calculateRating()) {
                // Swap using public set method
                movieList.set(j, movie2);
                movieList.set(j + 1, movie1);
            }
        }
    }

	cout << "Recommended Movies by Ranking:" << endl;
	movieList.print();
}