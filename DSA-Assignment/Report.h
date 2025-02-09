#pragma once
using namespace std;
#include <string>
#include "Printable.h"
#include "DoublyLinkedList.h"

class Report : Printable
{
private:
	string type;
	string description;
	int reportId;
	char status;
	DoublyLinkedList<Report> reports;
public:
	//default constructor
	Report();

	//constructor
	Report(int reportId, string type, string description);

	//deconstructor
	~Report();

	//Purpose: Retrieve the report type
	//Precondition : None.
	//Postcondition : Returns the report type
	string getType() const;
	
	//Purpose: Retrieve the report description
	//Precondition : None.
	//Postcondition : Returns the report description
	string getDescription() const;

	//Purpose: Retrieve the reportid
	//Precondition : None.
	//Postcondition : Returns the reportid
	int getReportId() const;

	//Purpose: Update status of the report.
	//Precondition: Report status is currently 'U' (Unresolved)
	//Postcondition: Status is updated to Resolved.
	bool updateStatus();

	//Purpose: Print details of the report.
	//Precondition: None.
	//Postcondition: Displays details of the report.
	void print() const override;

	//for comparison reasons
	bool operator<(const Report& report) const;
};

