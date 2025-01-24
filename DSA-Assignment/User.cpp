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

    // Populate the temporary dictionary with actors in the specified age range
    for (int key = 0; key < actorDict.getLength(); ++key) { 
        if (actorDict.contains(key)) {
            Actor actor = actorDict.get(key);
            int age = actor.calculateAge();
            if (age >= x && age <= y) {
                tempDict.add(age, actor); // Use age as the key for ordering
            }
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

    for (int key = 0; key < movieDict.getLength(); key++) {
        if (movieDict.contains(key)) {
            int releaseYear = movieDict.get(key).getYearOfRelease();
            if (currentYear - releaseYear <= 3) {
                cout << "Name: " << key << ", Year: " << releaseYear << endl;
            }
        }
    }
}

//Purpose: Display all movies an actor starred in
//Precondition: Actor must exist
//Postcondition: Movies displayed must be in alphabetical order
void User::displayMoviesByActor(Dictionary<int, Actor>& actorDict, const string& actorName) {
    for (int key = 0; key < actorDict.getLength(); key++) {
        if (actorDict.get(key).getName() == actorName) {
            Actor actor = actorDict.get(key);
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
    for (int key = 0; key < movieDict.getLength(); key++) {
        if (movieDict.get(key).getTitle() == movieName) {
            Movie movie = movieDict.get(key);
            movie.getActors();
            return;
        }
    }
    cout << "Movie not found in the dictionary." << endl;
}

/// Purpose: Display a list of all actors that a particular actor knows.
/// Precondition: The actor must exist in the movies.
/// Postcondition: Outputs the names of all actors known to the given actor.
void User::displayActorsKnown(Dictionary<int, Movie>& movieDict, const Actor& actor) {
    Dictionary<string, bool> knownActors;  // Tracks known actors by their names
    Dictionary<string, bool> visitedMovies;  // Tracks movies already processed

    cout << "Actors known by " << actor.getName() << ":" << endl;

    // Step 1: Process all movies the given actor starred in
    for (int movieKey = 0; movieKey < movieDict.getLength(); ++movieKey) {
        if (!movieDict.contains(movieKey)) continue;

        Movie movie = movieDict.get(movieKey);

        // Retrieve the cast of the movie
        DoublyLinkedList<Actor> cast = movie.getActorList();

        // Check if the given actor is in the cast
        bool actorInMovie = false;
        typename DoublyLinkedList<Actor>::Node* currentNode = cast.firstNode; // Access the first node
        while (currentNode != nullptr) {
            if (currentNode->item.getName() == actor.getName()) {
                actorInMovie = true;
                break;
            }
            currentNode = currentNode->next;
        }

        if (!actorInMovie) continue;

        // Mark this movie as visited
        visitedMovies.add(movie.getTitle(), true);

        // Add all other actors in the movie to the knownActors list
        currentNode = cast.firstNode;  // Reset to the start of the list
        while (currentNode != nullptr) {
            const Actor& coActor = currentNode->item;
            if (coActor.getName() != actor.getName() && !knownActors.contains(coActor.getName())) {
                knownActors.add(coActor.getName(), true);
                cout << "- " << coActor.getName() << endl;
            }
            currentNode = currentNode->next;
        }
    }

    // Step 2: Extend the list by processing movies of known actors
    for (int movieKey = 0; movieKey < movieDict.getLength(); ++movieKey) {
        if (!movieDict.contains(movieKey)) continue;

        Movie movie = movieDict.get(movieKey);

        // Skip movies that have already been processed
        if (visitedMovies.contains(movie.getTitle())) continue;

        // Retrieve the cast of the movie
        DoublyLinkedList<Actor> cast = movie.getActorList();

        // Check if any known actor is in the cast
        bool related = false;
        typename DoublyLinkedList<Actor>::Node* currentNode = cast.firstNode; // Access the first node
        while (currentNode != nullptr) {
            if (knownActors.contains(currentNode->item.getName())) {
                related = true;
                break;
            }
            currentNode = currentNode->next;
        }

        if (!related) continue;

        // Add all actors from this related movie to the knownActors list
        currentNode = cast.firstNode;  // Reset to the start of the list
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
