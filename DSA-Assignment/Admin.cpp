#include "Admin.h"
#include <iostream>
using namespace std;

//Constructor
Admin::Admin(string name, int adminId)
	: name(name), adminId(adminId){}

//Deconstructor
Admin::~Admin() {};

//Purpose: Retrieve the username of the user.
//Precondition: None.
//Postcondition: Returns the username of the user.
string Admin::getName() const 
{
	return name;
};

//Purpose: Retrieve the id of the user.
//Precondition: None.
//Postcondition: Returns the user id.
int Admin::getAdminId() const {
	return adminId;
};

//Purpose: Add a new actor to the dictionary
//Precondition: Actor must not exist already
//Postcondition: Adds actor to dictionary
void Admin::addActor(const Actor actor, Dictionary<int, Actor>& actors) {
    actors.add(actor.getActorId(), actor);
    cout << "Actor " << actor.getName() << " added successfully." << endl;
}

//Purpose: Add a new movie to the dictionary
//Precondition: Movie must not exist already
//Postcondition: Adds movie to dictionary
void Admin::addMovie(const Movie movie, Dictionary<int, Movie>& movies) {
    movies.add(movie.getMovieId(), movie);
    cout << "Movie " << movie.getTitle() << " added successfully." << endl;
}

//Purpose: Add/link actor to a movie
//Precondition: Movie exists, Actor exists
//Postcondition: Actor is added to an existing movie
void Admin::addActorToMovie(const int& actorId, const int& movieId, Dictionary<int, Actor>& actors, Dictionary<int, Movie>& movies) {
    if (!actors.contains(actorId)) {
        cout << "Actor does not exist!" << endl;
        return;
    }
    if (!movies.contains(movieId)) {
        cout << "Movie does not exist!" << endl;
        return;
    }
    Movie movie = movies.get(movieId);
    Actor actor = actors.get(actorId);
    movie.addActor(actor); 
    movies.add(movieId, movie);
    cout << "Actor " << actor.getName() << " added to movie " << movie.getTitle() << " successfully." << endl;
}

//Purpose: Update movie details
//Precondition: Movie exists 
//Postcondition:Movie details are updated
void Admin::updateDetails(const int& key,const Movie& newValue, Dictionary<int, Movie>& movies) {
    if (movies.contains(key)) {
        movies.add(key, newValue);
        cout << "Movie details updated successfully." << endl;
    }
    else {
        cout << "Movie does not exist." << endl;
    }
}

//Purpose: Update actor details
//Precondition: actor exists 
//Postcondition: actor details are updated
void Admin::updateDetails(const int& key, const Actor& newValue, Dictionary<int, Actor>& actors) {
    if (actors.contains(key)) {
        actors.add(key, newValue);
        cout << "Actor details updated successfully." << endl;
    }
    else {
        cout << "Actor does not exist." << endl;
    }
}

//Purpose: View list of reports made by users.
//Precondition: none
//Postcondition: Display all unresolved reports.
void Admin::viewReports(Dictionary<int, Report>& reportDict) {
    cout << "==== Reports ====" << endl;

    bool hasReports = false;
    for (int key = 0; key <= reportDict.getLength(); key++) { 
        if (reportDict.contains(key)) {
            Report report = reportDict.get(key);
            report.print();
            hasReports = true;
        }
    }

    if (!hasReports) {
        cout << "No Reports Found" << endl;
    }
}

//Purpose: Resolves a report made by a user.
//Precondition: Report exists.
//Postcondition: Updates details based on the report, updates status of report.
void Admin::resolveIssue(Dictionary<int, Report>& reportDict, Dictionary<int, Actor>& actorDict, Dictionary<int, Movie>& movieDict) {
    viewReports(reportDict);

    int reportId;
    cout << "Enter reportId of report you would like to resolve: ";
    cin >> reportId;

    // ✅ Directly check if report exists
    if (!reportDict.contains(reportId)) {
        cout << "Report does not exist. Please try again." << endl;
        return;
    }

    reportDict.get(reportId).print();

    string type;
    cout << "Update actor / movie: ";
    cin >> type;

    int keyOfValue;
    if (type == "movie" || type == "Movie") {
        cout << "Enter id of movie: ";
        cin >> keyOfValue;

        // ✅ Directly check if movie exists
        if (!movieDict.contains(keyOfValue)) {
            cout << "Movie ID does not exist. Please try again." << endl;
            return;
        }

        Movie toUpdate = movieDict.get(keyOfValue);
        toUpdate.print();

        string title, plot, year;
        cin.ignore(); // ✅ Ignore leftover newline
        cout << "Enter new title (leave blank if no changes needed): ";
        getline(cin, title);
        cout << "Enter new plot (leave blank if no changes needed): ";
        getline(cin, plot);
        cout << "Enter new year of release (leave blank if no changes needed): ";
        getline(cin, year);

        if (title.empty()) title = toUpdate.getTitle();
        if (plot.empty()) plot = toUpdate.getPlot();

        int newYear = toUpdate.getYearOfRelease();
        if (!year.empty()) {
            try {
                newYear = stoi(year);
            }
            catch (const invalid_argument&) {
                cout << "Invalid year entered. Keeping existing value." << endl;
            }
        }

        Movie updatedMovie(keyOfValue, title, plot, newYear);
        updateDetails(keyOfValue, updatedMovie, movieDict);
        reportDict.get(reportId).updateStatus();

        cout << "Movie details updated successfully." << endl;
        return;

    }
    else if (type == "actor" || type == "Actor") {
        cout << "Enter id of Actor: ";
        cin >> keyOfValue;

        // ✅ Directly check if actor exists
        if (!actorDict.contains(keyOfValue)) {
            cout << "Actor ID does not exist. Please try again." << endl;
            return;
        }

        Actor toUpdate = actorDict.get(keyOfValue);
        toUpdate.print();

        string name, year;
        cin.ignore(); // ✅ Ignore leftover newline
        cout << "Enter new name (leave blank if no changes needed): ";
        getline(cin, name);
        cout << "Enter new year of birth (leave blank if no changes needed): ";
        getline(cin, year);

        if (name.empty()) name = toUpdate.getName();

        int yearOfBirth = toUpdate.getYearOfBirth();
        if (!year.empty()) {
            try {
                yearOfBirth = stoi(year);
            }
            catch (const invalid_argument&) {
                cout << "Invalid year entered. Keeping existing value." << endl;
            }
        }

        Actor updatedActor(keyOfValue, name, yearOfBirth);
        updateDetails(keyOfValue, updatedActor, actorDict);
        reportDict.get(reportId).updateStatus();

        cout << "Actor details updated successfully." << endl;
        return;

    }
    else {
        cout << "Invalid type. Please try again." << endl;
        return;
    }
}