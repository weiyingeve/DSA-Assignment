#pragma once
#include <string>
#include "DoublyLinkedList.h"
#include "Dictionary.h"
#include "Movie.h"
#include "Actor.h"
using namespace std;
class User
{
private:
	string username;
	int userId;

	DoublyLinkedList<Movie> favoriteMovies;
	DoublyLinkedList<Actor> favoriteActors;
public:
	//Constructor
	User(const string username, const int userId);

	//deconstructor
	~User();

	//Purpose: Retrieve the username of the user.
	//Precondition: None.
	//Postcondition: Returns the username of the user.
	string getUsername() const;

	//Purpose: Retrieve the id of the user.
	//Precondition: None.
	//Postcondition: Returns the user id.
	int getUserId() const;

	//Purpose: Display (in ascending order of age) the actors with age between x and y (entered by user)
	//Precondition: x and y entered must be a valid number (y>x)
	//Postcondition: Actors displayed must be in ascending order
	void displayActorsByAgeRange(Dictionary<int, Actor>& actorDict, int x, int y);

	//Purpose: Display movies made within the past 3 years 
	//Precondition: None
	//Postcondition: Movies displayed in ascending order of year
	void displayMoviesPast3Years(Dictionary<int, Movie>& movieDict);

	//Purpose: Display all movies an actor starred in
	//Precondition: Actor must exist
	//Postcondition: Movies displayed must be in alphabetical order
	void displayMoviesByActor(Dictionary<int, Actor>& actorDict, const string& actorName);
	
	//Purpose: Display actors in a movie
	//Precondition: Movie must exist
	//Postcondition: Actor displayed must be in alphebetical order
	void displayActorsByMovie(Dictionary<int, Movie>& movieDict, const string& movieName);

	//Purpose: Display a list of all actors that a particular actor knows.
	//Precondition: Actor must exist
	//Postcondition: Displays connections between actors.
	void displayActorsKnown(Dictionary<int, Movie>& movieDict, const Actor& actor);

	//Purpose: Report an error for an actor or movie.
	//Precondition: Actor or Movie must exist.
	//Postcondition: Creates new report.
	void reportError();

	//Purpose: Add a new rating for a specific actor.
	//Precondition: Actor exists in the Dictionary.
	//Postcondition: Updates rating for the actor.
	void addActorRating(Dictionary<int, Actor>& actorDict, const string& actorName);

	//Purpose: Add a new rating for a specific movie.
	//Precondition: Movie exists in the Dictionary.
	//Postcondition: Updates rating for the movie.
	void addMovieRating(Dictionary<int, Movie>& movieDict, const string& movieName);

    //Purpose: Get recommendations of a movie by ranking.
    //Precondition: movieDict not empty.
    //Postcondition: Displays movies by ranking in descending order.
	void getRecommendationsByRanking(Dictionary<int, Movie>& movieDict);
};

