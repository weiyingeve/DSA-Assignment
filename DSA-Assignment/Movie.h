#pragma once
#include <string>;
using namespace std;
#include "DoublyLinkedList.h"

class Actor;

class Movie
{
private:
	int movieId;
	string title;
	string plot;
	int yearOfRelease;
	float totalRatings;
	int noOfVoters;
	static DoublyLinkedList<Actor> actors;


public:
	//default constructor
	Movie();

	//Constructor
	Movie(int movieId, string title, string plot, int yearOfRelease);

	//deconstructor
	~Movie();

	//Purpose: Retrieve the movie's id.
	//Precondition : None.
	//Postcondition : Returns the id of the movie.
	int getMovieId() const;

	//Purpose: Retrieve the movie's title.
	//Precondition: None.
	//Postcondition: Returns the title of the movie.
	string getTitle() const;

	//Purpose: Retreive the movie's plot.
	//Precondition: None.
	//Postcondition: Returns the plot of the movie.
	string getPlot() const;

	//Purpose: Retrieve the movie's year of release.
	//Precondition: None.
	//Postcondition: Returns the year of release of the movie.
	int getYearOfRelease() const;

	//Purpose: Retrieve the movie's cast.
	//Precondition: None.
	//Postcondition: Returns the cast of the movie.
	DoublyLinkedList<Actor> getActorList() const;

	//Purpose: Retrieve the movie's total ratings.
	//Precondition : None.
	//Postcondition : Returns the total ratings of the movie.
	float getTotalRatings() const;

	//Purpose: Retrieve the number of voters of the movie's rating.
	//Precondition : None.
	//Postcondition : Returns the number of voters of the movie's rating.
	int getNoOfVoters() const;

	//Purpose: Calculate the rating of the movie.
	//Precondition: None.
	//Postcondition: Returns the updated rating of the movie.
	float calculateRating() const;

	//Purpose: Updates rating based on user input.
	//Precondition : None.
	//Postcondition : Updates rating for the movie.
	void updateRating();

	//Purpose: Add an actor to the movie's list of actors.
	//Precondition: None.
	//Postcondition: The actor is added to the movie's actor list.
	void addActor(const Actor& actor);

	//Purpose: Retrieve the list of actors in the movie.
	//Precondition: None.
	//Postcondition: Returns a pointer to the head of the actor list.
	void getActors();

	// Purpose: Display details of the movie.
	// Precondition: None.
	// Postcondition: The movie is displayed.
	void print();

	//for comparison reasons
	bool operator<(const Movie& movie);
};

