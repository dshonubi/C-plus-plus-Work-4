#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <list> 
#include <iterator>
using namespace std;

class ProjectAllocation {
public:
	//method for incoming student file data
	void student(string studentID, int choice1, int choice2, int choice3, int choice4) 
	{ 
		_studentChoiceOrder.clear();
		_studentID.push_back(studentID);
		_studentChoiceOrder.push_back(choice1);
		_studentChoiceOrder.push_back(choice2);
		_studentChoiceOrder.push_back(choice3);
		_studentChoiceOrder.push_back(choice4);
		_studentsChoices.push_back(_studentChoiceOrder);
		_choiceAlreadyAllocated.push_back(false);
	}

	//method for incoming supervisor file data
	void supervisor(string supervisorID,int supervisorLoad)
	{ 
		_supervisorIDSupervisor.push_back(supervisorID);
		_supervisionLoad.push_back(supervisorLoad);
	}

	//method for incoming projects file data
	void project(int projectID, string supervisorID, int multiplicity, string projectTitle)
	{ 
		_projectID.push_back(projectID);
		_supervisorIDProject.push_back(supervisorID);
		_multiplicity.push_back(multiplicity);
		_projectTitle.push_back(projectTitle);
	}

	// method to allocate all projects
	void allocateProjects();

	//getters
	
	int getMultiplicity(string supervisorid, int projectid);
	int getScoreOfAllocation();
	int getStudentsAllocatedProject(int projectid);

	//compares projects that may have the same choice in a higher position
	int checkChoices(string studentid, int choice, int counter);
	int getStudentsAllocatedTotal(string supervisorid);
	vector <int> getAllocatedChoices();
	string getAllocatedStudents(string supervisorid, int projectid);
	bool choiceAlreadyAllocated(string studentid);
	int getSupervisionLoad(string supervisorid);
	vector <string> getAllocatedStudentID();

private:

	vector <int> _supervisionLoad;
	vector <int> _multiplicity;
	int _scoreOfAllocation = 0;
	vector <bool> _choiceAlreadyAllocated;
	vector <int> _projectID;
	vector <list<int>> _studentsChoices;
	vector <int> _allocatedChoices;
	vector <string> _projectTitle;
	vector <string> _supervisorIDProject;
	vector <string> _supervisorIDSupervisor;
	vector <string> _supervisor;
	vector <string> _studentID;
	vector <string> _allocatedStudentID;
	vector <string> _allocatedStudents;
	list <int> _studentChoiceOrder;
};