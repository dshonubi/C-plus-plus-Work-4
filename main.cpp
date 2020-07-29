#include "projectAllocation.h"
#include <sstream>
#include <cstddef>

int main(int argc, char* argv[]) {
	
	for (int i = 0; i < argc; i++) {
		cout << argv[1] << "i" << endl;
	}
	ProjectAllocation p;
	if (argc > 3) {
		
		//reads in staff file
		for (int i = 0; i < argc; i++) {
			string j = argv[i];
			if (j== "staff.txt") {
				string reader;
				ifstream file("staff.txt");
				if (file.is_open())
				{
					while (getline(file, reader))
					{

						string supervisorid;
						int supervisionLoad;
						stringstream ss(reader);
						ss >> supervisorid >> supervisionLoad;
						p.supervisor(supervisorid, supervisionLoad);
					}
					file.close();
				}
				else {
					cout << "Unable to open file";
				}
			}
		}

		//reads in projects file
		for (int i = 0; i < argc; i++) {
			string j = argv[i];
			if (j == "projects.txt") {
				string reader1;
				ifstream file1("projects.txt");
				if (file1.is_open())
				{
					while (getline(file1, reader1))
					{
						int projectid;
						string supervisorid;
						int multiplicity;
						string projectTitle;
						stringstream ss(reader1);
						ss >> projectid >> supervisorid >> multiplicity;
						string strings = ss.str();

						//project name needs to be split differently otherwise it only retrieves the elements before the first space
						for (int i = 0; i < 3; i++) {
							size_t begin = strings.find_first_of(" ");
							strings = strings.substr(begin + 1, strings.length());
						}

						projectTitle = strings;
						p.project(projectid, supervisorid, multiplicity, projectTitle);
					}
					file1.close();
				}
				else {
					cout << "Unable to open file";
				}
			}
		}

		//reads in students file
		for (int i = 0; i < argc; i++) {
			string j = argv[i];
			if (j == "students.txt") {
				string reader2;
				ifstream file2("students.txt");
				if (file2.is_open())
				{
					while (getline(file2, reader2))
					{
						string studentid;
						int choice1;
						int choice2;
						int choice3;
						int choice4;
						stringstream ss(reader2);
						ss >> studentid >> choice1 >> choice2 >> choice3 >> choice4;
						p.student(studentid, choice1, choice2, choice3, choice4);
					}
					file2.close();
				}
				else {
					cout << "Unable to open file";
				}
			}
		}
	}

		p.allocateProjects();

		ofstream writer("alloc.txt");
		if (writer.is_open())
		{
			for (int i = 0; i < p.getAllocatedChoices().size(); i++) {
				writer << p.getAllocatedStudentID().at(i) << " " << p.getAllocatedChoices().at(i) << endl;
			}
			writer << p.getScoreOfAllocation() << endl;
			writer.close();
		}
		else cout << "Unable to open file";
	}
