#pragma once
using namespace std;
#include <string>
class Report
{
private:
	string type;
	string description;
	int reportId;
	char status;
public:
	//default constructor
	Report();

	//constructor
	Report(int reportId, string type, string description);

	//deconstructor
	~Report();

	//Purpose: Update status of the report.
	//Precondition: Report status is currently 'U' (Unresolved)
	//Postcondition: Status is updated to Resolved.
	bool updateStatus();

	//Purpose: Print details of the report.
	//Precondition: None.
	//Postcondition: Displays details of the report.
	void print();
};

