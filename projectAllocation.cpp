#include "projectAllocation.h"

int ProjectAllocation::getMultiplicity(string supervisorid, int projectid)
{
	for (int i = 0; i < _supervisorIDProject.size(); i++)
	{
		if ((_supervisorIDProject.at(i) == supervisorid) && (_projectID.at(i) == projectid))
			return _multiplicity.at(i);
	}
}

int ProjectAllocation::getSupervisionLoad(string supervisorid) 
{
	for (int i = 0; i< _supervisorIDSupervisor.size(); i++)
	{
		if (_supervisorIDSupervisor.at(i) == supervisorid)
			return _supervisionLoad.at(i);
	}
}

bool ProjectAllocation::choiceAlreadyAllocated(string studentid) 
{
	for (int i = 0; i < _studentID.size(); i++)
	{
		if (_studentID.at(i) == studentid)
			return _choiceAlreadyAllocated.at(i);
	}
}

int ProjectAllocation::getStudentsAllocatedProject(int projectid) 
{
	int total = 0;
	for (int i = 0; i < _allocatedChoices.size(); i++)
	{
			if (_allocatedChoices.at(i)==projectid)
			++total;
	}
		return total;
}

int ProjectAllocation::getStudentsAllocatedTotal(string supervisorid) 
{
	int total = 0;
	for (int i = 0; i < _allocatedChoices.size(); i++) {
		for (int j = 0; j < _supervisorIDProject.size(); j++) {
			if ((_supervisorIDProject.at(j) == supervisorid) && (_allocatedChoices.at(i) == _projectID.at(j))) {
				++total;
			}
		}
	}
		return total;
}

vector <int> ProjectAllocation::getAllocatedChoices() 
{
	return _allocatedChoices;
}

string ProjectAllocation::getAllocatedStudents(string supervisorid, int projectid) 
{
	for (int i = 0; i < _supervisorIDProject.size(); i++)
	{
		if ((_supervisorIDProject.at(i) == supervisorid) && (_projectID.at(i) == projectid))
			return _allocatedStudents.at(i);
	}
}

vector <string> ProjectAllocation::getAllocatedStudentID() 
{
	return _allocatedStudentID;
}

int ProjectAllocation::checkChoices(string studentid, int choice1, int counter) 
{
	// ensures it only checks students with the same choice in a higher postion
	int iterateCounter = 0; 

	//counts the number of students with the same choice in a higher postion
	int count = 0;  

	//iterator class uses no i value so this accounts for this
	int choiceCounter = 0;
	
	for (auto itr = _studentID.begin(); itr != _studentID.end(); itr++) {
		if (studentid == *itr){
			++choiceCounter;
			continue;

		}else{

		list<int> choice = _studentsChoices.at(choiceCounter);
		for (auto it = choice.begin(); it != choice.end(); it++) {
			if (iterateCounter == counter) {
				break;
			}
			else if ((choice1 == *it) && (_choiceAlreadyAllocated.at(choiceCounter) == false)) {
				++count;
			}
			++iterateCounter;
		}
		}
		++choiceCounter;
	}
	return count;
}

int ProjectAllocation::getScoreOfAllocation() 
{
	return _scoreOfAllocation;
}

void ProjectAllocation::allocateProjects()
{
	
	for (int i = 0; i < _studentID.size(); i++) {
		list<int> choice = _studentsChoices.at(i);
		int count = 0;
		for (auto it = choice.begin(); it != choice.end(); it++) {
			if (choiceAlreadyAllocated(_studentID.at(i)) == true)
			{
				cout << "Student already allocated " << endl;
				continue;
			}
			else if ((getStudentsAllocatedProject(_projectID.at(*it-1)) >= getMultiplicity(_supervisorIDProject.at(*it-1), _projectID.at(*it - 1)))
				|| (getStudentsAllocatedTotal(_supervisorIDProject.at(*it - 1)) >= getSupervisionLoad(_supervisorIDProject.at(*it - 1)))) {
				++count;

				//if its iterated through all a students choices assigns them zero and updates relevant fields
				if (count == 4) {
					cout << "Allocation taken" << endl;
					_allocatedStudentID.push_back(_studentID.at(i));
					_allocatedChoices.push_back(0);
					_choiceAlreadyAllocated.at(i) = true;
					_scoreOfAllocation += 0;
				}
				continue;
			}
			else if (count != 0) {
				int spaceLeft = getMultiplicity(_supervisorIDProject.at(*it - 1), _projectID.at(*it - 1)) - checkChoices(_studentID.at(i), *it - 1, count);
				
				if (spaceLeft > 0) {
					_allocatedStudentID.push_back(_studentID.at(i));
					_allocatedChoices.push_back(_projectID.at(*it - 1));
					_choiceAlreadyAllocated.at(i) = true;

					switch (count) {
					case 1:_scoreOfAllocation += 3;
						break;

					case 2:_scoreOfAllocation += 2;
						break;

					case 3:_scoreOfAllocation += 1;
						break;
					}
				}
				else if(count < 3){
					//updates count and continues - for next iteration as they haven't reached the end of their choices
					++count;
					continue;
				}
				else {
					//if its iterated through all a students choices assigns them zero and updates relevant fields
					_allocatedStudentID.push_back(_studentID.at(i));
					_allocatedChoices.push_back(0);
					_choiceAlreadyAllocated.at(i) = true;
					_scoreOfAllocation += 0;
				}
			}
			else
			{
				_allocatedStudentID.push_back(_studentID.at(i));
				_allocatedChoices.push_back(_projectID.at(*it-1));
				_choiceAlreadyAllocated.at(i) = true;
				_scoreOfAllocation += 4;
				
			}
		}
	}
}
