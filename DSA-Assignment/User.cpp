#include "User.h"
#include "Movie.h"
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

// Purpose: Display (in ascending order of age) the actors with age between x and y (entered by user)
// Precondition: x and y entered must be a valid number (y > x)
// Postcondition: Actors displayed must be in ascending order
void User::displayActorsByAgeRange(Dictionary<int, Actor>& actorDict, int x, int y) {
    // Validate age range
    if (x >= y) {
        cout << "Invalid age range: y must be greater than x." << endl;
        return;
    }

    // Temporary dictionary to store actors filtered by age
    Dictionary<int, DoublyLinkedList<Actor*>> tempDict;

    // Get all actors and filter them by age range
    DoublyLinkedList<Actor*> actorList = actorDict.getAllItems();
    for (int i = 0; i < actorList.getLength(); i++) {
        Actor* actor = actorList.get(i);
        if (actor == nullptr) continue;

        int age = actor->calculateAge();
        if (age >= x && age <= y) {
            if (!tempDict.contains(age)) {
                DoublyLinkedList<Actor*> ageList;
                ageList.add(actor);
                tempDict.add(age, ageList);
            }
            else {
                tempDict.get(age).add(actor);
            }
        }
    }

    // Display actors in ascending order of age and name
    cout << "Actors between ages " << x << " and " << y << ":" << endl;

    for (int age = x; age <= y; age++) {
        if (tempDict.contains(age)) {
            DoublyLinkedList<Actor*>& ageActorList = tempDict.get(age);

            for (int i = 0; i < ageActorList.getLength(); i++) {
                Actor* actor = ageActorList.get(i);
                cout << "ID: " << actor->getActorId()
                    << ", Name: " << actor->getName()
                    << ", Age: " << age << endl;
            }
        }
    }
}

//Purpose: Display movies made within the past 3 years 
//Precondition: None
//Postcondition: Movies displayed in ascending order of year
void User::displayMoviesPast3Years(Dictionary<int, Movie>& movieDict) {
    int currentYear = 2025;
    Dictionary<int, DoublyLinkedList<Movie*>> sortedMovies;

    cout << "Movies released in the past 3 years:" << endl;

    // Get all movies and sort them by release year
    DoublyLinkedList<Movie*> movieList = movieDict.getAllItems();

    for (int i = 0; i < movieList.getLength(); i++) {
        Movie* movie = movieList.get(i);
        if (movie == nullptr) continue;

        int releaseYear = movie->getYearOfRelease();
        if (currentYear - releaseYear <= 3) {
            if (!sortedMovies.contains(releaseYear)) {
                sortedMovies.add(releaseYear, DoublyLinkedList<Movie*>());
            }
            sortedMovies.get(releaseYear).add(movie);
        }
    }

    // Sort and display movies in ascending order of year
    DoublyLinkedList<int> sortedYears;
    for (int i = currentYear - 3; i <= currentYear; i++) {
        if (sortedMovies.contains(i)) {
            sortedYears.add(i);
        }
    }

    for (int i = 0; i < sortedYears.getLength(); i++) {
        int year = sortedYears.get(i);
        DoublyLinkedList<Movie*>& movies = sortedMovies.get(year);

        for (int j = 0; j < movies.getLength(); j++) {
            Movie* movie = movies.get(j);
            cout << "Title: " << movie->getTitle() << ", Year: " << year << endl;
        }
    }
}


//Purpose: Display all movies an actor starred in
//Precondition: Actor must exist
//Postcondition: Movies displayed must be in alphabetical order
void User::displayMoviesByActor(Dictionary<int, Actor>& actorDict, const int& actorId) {
    if (actorDict.contains(actorId)) {
        Actor actor = actorDict.get(actorId);
        cout << "Movies " << actor.getName() << " acted in: " << endl;
        actor.getMovies();
        return;
    }
    cout << "Actor not found in the dictionary." << endl;

}


//Purpose: Display actors in a movie
//Precondition: Movie must exist
//Postcondition: Actor displayed must be in alphebetical order
void User::displayActorsByMovie(Dictionary<int, Movie>& movieDict, const int& movieId) {
    if (movieDict.contains(movieId)) {
        Movie movie = movieDict.get(movieId);
        cout << "Actors in " << movie.getTitle() << ": " << endl;
        movie.getActors();
        return;
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
    auto movieNode = movieList.getFirstNode();  // Use getFirstNode()

    while (movieNode != nullptr) {
        Movie* movie = movieNode->item;

        // Check if actor starred in the movie
        DoublyLinkedList<Actor> cast = movie->getActorList();
        bool actorInMovie = false;

        typename DoublyLinkedList<Actor>::Node* actorNode = cast.getFirstNode();  // Use getFirstNode()
        while (actorNode != nullptr) {
            if (actorNode->item.getName() == actor.getName()) {
                actorInMovie = true;
                break;
            }
            actorNode = actorNode->next;
        }

        if (!actorInMovie) {
            movieNode = movieNode->next;
            continue;
        }

        // Mark movie as visited
        visitedMovies.add(movie->getTitle(), true);

        // Collect co-actors from the movie
        actorNode = cast.getFirstNode();  // Use getFirstNode()
        while (actorNode != nullptr) {
            const Actor& coActor = actorNode->item;
            if (coActor.getName() != actor.getName() && !knownActors.contains(coActor.getName())) {
                knownActors.add(coActor.getName(), true);
                cout << "- " << coActor.getName() << endl;
            }
            actorNode = actorNode->next;
        }

        movieNode = movieNode->next;
    }

    // Step 2: Find second-degree connections
    movieNode = movieList.getFirstNode();  // Use getFirstNode()
    while (movieNode != nullptr) {
        Movie* movie = movieNode->item;
        if (visitedMovies.contains(movie->getTitle())) {
            movieNode = movieNode->next;
            continue;
        }

        // Check if any known actor is in this movie
        DoublyLinkedList<Actor> cast = movie->getActorList();
        bool related = false;

        typename DoublyLinkedList<Actor>::Node* actorNode = cast.getFirstNode();  // Use getFirstNode()
        while (actorNode != nullptr) {
            if (knownActors.contains(actorNode->item.getName())) {
                related = true;
                break;
            }
            actorNode = actorNode->next;
        }

        if (!related) {
            movieNode = movieNode->next;
            continue;
        }

        // Add new actors from the movie
        actorNode = cast.getFirstNode();  // Use getFirstNode()
        while (actorNode != nullptr) {
            const Actor& coActor = actorNode->item;
            if (!knownActors.contains(coActor.getName())) {
                knownActors.add(coActor.getName(), true);
                cout << "- " << coActor.getName() << endl;
            }
            actorNode = actorNode->next;
        }

        movieNode = movieNode->next;
    }
}


//Purpose: Report an error for an actor or movie.
//Precondition: Actor or Movie must exist.
//Postcondition: Creates new report.
void User::reportError(Dictionary<int, Report>& reportDict) {
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
void User::addActorRating(Dictionary<int, Actor>& actorDict, const int& actorId) {
    if (actorDict.contains(actorId)) {
        Actor* actor = &actorDict.get(actorId);
        actor->updateRating();
        return;
    }
    cout << "Actor not found in the dictionary." << endl;
}

//Purpose: Add a new rating for a specific movie.
//Precondition: Movie exists in the Dictionary.
//Postcondition: Updates rating for the movie.
void User::addMovieRating(Dictionary<int, Movie>& movieDict, const int& movieId) {
    if (movieDict.contains(movieId)) {
        Movie* movie = &movieDict.get(movieId);
        movie->updateRating();
        return;
    }
    cout << "Movie not found in the dictionary." << endl;
}

// Purpose: Get recommendations of an actor by ranking.
// Precondition: actorDict is not empty.
// Postcondition: Displays top 5 actors by ranking in descending order.
void User::getActorRecommendationsByRanking(Dictionary<int, Actor>& actorDict) {
    DoublyLinkedList<Actor*> actorList = actorDict.getAllItems();

    if (actorList.isEmpty()) {
        cout << "No actors available for recommendations." << endl;
        return;
    }

    // Ensure sorting function does NOT modify data
    actorList.sortDescending([](Actor* a, Actor* b) {
        return a->calculateRating() > b->calculateRating();
        });

    // Display top 5 actors only
    cout << "Top 5 Recommended Actors by Ranking:" << endl;
    for (int i = 0; i < min(5, actorList.getLength()); i++) {
        Actor* actor = actorList.get(i);
        cout << actor->getName() << " - Rating: " << actor->calculateRating() << "/5" << endl;
    }
}


// Purpose: Get recommendations of a movie by ranking.
// Precondition: movieDict is not empty.
// Postcondition: Displays top 5 movies by ranking in descending order.
void User::getMovieRecommendationsByRanking(Dictionary<int, Movie>& movieDict) {
    DoublyLinkedList<Movie*> movieList = movieDict.getAllItems();

    if (movieList.isEmpty()) {
        cout << "No movies available for recommendations." << endl;
        return;
    }

    // Sort in descending order based on rating
    movieList.sortDescending([](Movie* a, Movie* b) {
        return a->calculateRating() > b->calculateRating();
    });

    // Display top 5 movies
    cout << "Top 5 Recommended Movies by Ranking:" << endl;
    int count = 0;
    for (int i = 0; i < movieList.getLength() && count < 5; i++) {
        Movie* movie = movieList.get(i);
        cout << movie->getTitle() << " - Rating: " << movie->calculateRating() << "/5" << endl;
        count++;
    }
}

