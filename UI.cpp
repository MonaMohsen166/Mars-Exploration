#include "UI.h"

void UI::PrintMessage(string msg)
{
	cout << msg;
}

string UI::readInput()
{
	string s;
	cin >> s;
	return s;
}

int UI::getOutPutMode()
{
	int x;
	cout << "Output Modes:\n1-Interactiv\n2-Step-By-Step\n3-Silent\n\nEnter the Mode Number:";
	cin >> x;
	return x;
}

void UI::printDaySummary(int currentDay, PriQueue<Mission*>* waitingEmergency,
	Queue<Mission*>* waitingMountain, Queue<Mission*>* waitingPolar, Queue<Mission*>*inExecutionMissions,
	Queue<Rover*>* inExecutionRovers, Queue<Rover*>*avilableMountainRover, Queue<Rover*>*avilableEmergencyRover,
	Queue<Rover*>*avilablePolarRover, Queue<Rover*>*checkupEmergenceyRover, Queue<Rover*>*checkupMountainRover,
	Queue<Rover*>*checkupPolarRover, Queue<Mission*>*completedMission)
{
	cout << "Current Day:" << currentDay << endl;

	printWaiting(waitingEmergency, waitingMountain, waitingPolar);
	printInExec(inExecutionMissions);
	printAvilableRovers(avilableMountainRover, avilableEmergencyRover, avilablePolarRover);
	printCheckUpRovers(checkupEmergenceyRover, checkupMountainRover, checkupPolarRover);
	printCompleteMissions(completedMission);


}

void UI::printInExec(Queue<Mission*>* inExecutionMissions)
{
	//InExec Print
	cout << "In-Execution Missions/Rovers: ";
	Queue<Mission*> temp;
	Mission* tMission;
	bool first = true;
	cout << "[";
	while (!inExecutionMissions->isEmpty()) {
		inExecutionMissions->dequeue(tMission);
		if (tMission->getMissionType() == 'E') {
			if (!first) { cout << ","; }
			cout << tMission->getId() << "/" << tMission->getRoverId();
			first = false;
		}
		temp.enqueue(tMission);
	}
	cout << "] ";
	while (!temp.isEmpty()) {
		temp.dequeue(tMission);
		inExecutionMissions->enqueue(tMission);
	}
	////////////////////////////////////////////
	first = true;
	cout << "(";
	while (!inExecutionMissions->isEmpty()) {
		inExecutionMissions->dequeue(tMission);
		if (tMission->getMissionType() == 'P') {
			if (!first) { cout << ", "; }
			cout << tMission->getId() << "/" << tMission->getRoverId();
			first = false;
		}
		temp.enqueue(tMission);
	}
	cout << ") ";
	while (!temp.isEmpty()) {
		temp.dequeue(tMission);
		inExecutionMissions->enqueue(tMission);
	}
	////////////////////////////////////////////
	first = true;
	cout << "{";
	while (!inExecutionMissions->isEmpty()) {
		inExecutionMissions->dequeue(tMission);
		if (tMission->getMissionType() == 'M') {
			if (!first) { cout << ", "; }
			cout << tMission->getId() << "/" << tMission->getRoverId();
			first = false;
		}
		temp.enqueue(tMission);
	}
	cout << "} " << endl;
	while (!temp.isEmpty()) {
		temp.dequeue(tMission);
		inExecutionMissions->enqueue(tMission);
	}
}

void UI::printAvilableRovers(Queue<Rover*>* avilableMountainRover, Queue<Rover*>* avilableEmergencyRover, Queue<Rover*>* avilablePolarRover)
{
	cout << "Available Rovers: ";
	Queue<Rover*> temp;
	Rover* tRover;
	bool first = true;
	cout << "[";
	while (!avilableEmergencyRover->isEmpty()) {
		if (!first) { cout << ','; }
		avilableEmergencyRover->dequeue(tRover);
		temp.enqueue(tRover);
		cout << tRover->getID();
		first = false;
	}
	cout << "] ";
	while (!temp.isEmpty()) {
		temp.dequeue(tRover);
		avilableEmergencyRover->enqueue(tRover);
	}
	///////////////////////////////////////////////////
	first = true;
	cout << "(";
	while (!avilablePolarRover->isEmpty()) {
		if (!first) { cout << ','; }
		avilablePolarRover->dequeue(tRover);
		temp.enqueue(tRover);
		cout << tRover->getID();
		first = false;
	}
	cout << ") ";
	while (!temp.isEmpty()) {
		temp.dequeue(tRover);
		avilablePolarRover->enqueue(tRover);
	}
	///////////////////////////////////////////////////
	first = true;
	cout << "{";
	while (!avilableMountainRover->isEmpty()) {
		if (!first) { cout << ','; }
		avilableMountainRover->dequeue(tRover);
		temp.enqueue(tRover);
		cout << tRover->getID();
		first = false;
	}
	cout << "} " << endl;
	while (!temp.isEmpty()) {
		temp.dequeue(tRover);
		avilableMountainRover->enqueue(tRover);
	}
}

void UI::printCompleteMissions(Queue<Mission*>* completedMission)
{
	cout << "Completed Missions: ";
	Queue<Mission*> temp;
	Mission* tMission;
	bool first = true;
	cout << "[";
	while (!completedMission->isEmpty()) {
		completedMission->dequeue(tMission);
		if (tMission->getMissionType() == 'E') {
			if (!first) { cout << ", "; }
			cout << tMission->getId() << "/" << tMission->getRoverId();
			first = false;
		}
		temp.enqueue(tMission);
	}
	cout << "] ";
	while (!temp.isEmpty()) {
		temp.dequeue(tMission);
		completedMission->enqueue(tMission);
	}
	////////////////////////////////////////////
	first = true;
	cout << "(";
	while (!completedMission->isEmpty()) {
		completedMission->dequeue(tMission);
		if (tMission->getMissionType() == 'P') {
			if (!first) { cout << ", "; }
			cout << tMission->getId() << "/" << tMission->getRoverId();
			first = false;
		}
		temp.enqueue(tMission);
	}
	cout << ") ";
	while (!temp.isEmpty()) {
		temp.dequeue(tMission);
		completedMission->enqueue(tMission);
	}
	////////////////////////////////////////////
	first = true;
	cout << "{";
	while (!completedMission->isEmpty()) {
		completedMission->dequeue(tMission);
		if (tMission->getMissionType() == 'M') {
			if (!first) { cout << ", "; }
			cout << tMission->getId() << "/" << tMission->getRoverId();
			first = false;
		}
		temp.enqueue(tMission);
	}
	cout << "} " << endl;
	while (!temp.isEmpty()) {
		temp.dequeue(tMission);
		completedMission->enqueue(tMission);
	}
}

void UI::printCheckUpRovers(Queue<Rover*>* checkupEmergenceyRover, Queue<Rover*>* checkupMountainRover, Queue<Rover*>* checkupPolarRover)
{
	cout << "In-Checkup Rovers: ";
	Queue<Rover*> temp;
	Rover* tRover;
	bool first = true;
	cout << "[";
	while (!checkupEmergenceyRover->isEmpty()) {
		if (!first) { cout << ','; }
		checkupEmergenceyRover->dequeue(tRover);
		temp.enqueue(tRover);
		cout << tRover->getID();
		first = false;
	}
	cout << "] ";
	while (!temp.isEmpty()) {
		temp.dequeue(tRover);
		checkupEmergenceyRover->enqueue(tRover);
	}
	///////////////////////////////////////////////////
	first = true;
	cout << "(";
	while (!checkupPolarRover->isEmpty()) {
		if (!first) { cout << ','; }
		checkupPolarRover->dequeue(tRover);
		temp.enqueue(tRover);
		cout << tRover->getID();
		first = false;
	}
	cout << ") ";
	while (!temp.isEmpty()) {
		temp.dequeue(tRover);
		checkupPolarRover->enqueue(tRover);
	}
	///////////////////////////////////////////////////
	first = true;
	cout << "{";
	while (!checkupMountainRover->isEmpty()) {
		if (!first) { cout << ','; }
		checkupMountainRover->dequeue(tRover);
		temp.enqueue(tRover);
		cout << tRover->getID();
		first = false;
	}
	cout << "} " << endl;
	while (!temp.isEmpty()) {
		temp.dequeue(tRover);
		checkupMountainRover->enqueue(tRover);
	}
}

void UI::printWaiting(PriQueue<Mission*>* waitingEmergency, Queue<Mission*>* waitingMountain, Queue<Mission*>* waitingPolar)
{
	//waiting Print
	cout << "Waiting Missions: ";
	Queue<Mission*> temp;
	Mission* tMission;
	bool first = true;
	cout << "[";
	while (!waitingEmergency->isEmpty()) {
		if (!first) { cout << ','; }
		waitingEmergency->remove(tMission);
		temp.enqueue(tMission);
		cout << tMission->getId();
		first = false;
	}
	cout << "] ";
	while (!temp.isEmpty()) {
		temp.dequeue(tMission);
		waitingEmergency->add(tMission, tMission->getPriority());
	}
	///////////////////////////////////////////////////
	first = true;
	cout << "(";
	while (!waitingPolar->isEmpty()) {
		if (!first) { cout << ','; }
		waitingPolar->dequeue(tMission);
		temp.enqueue(tMission);
		cout << tMission->getId();
		first = false;
	}
	cout << ") ";
	while (!temp.isEmpty()) {
		temp.dequeue(tMission);
		waitingPolar->enqueue(tMission);
	}
	//////////////////////////////////////////////////
	first = true;
	cout << "{";
	while (!waitingMountain->isEmpty()) {
		if (!first) { cout << ','; }
		waitingMountain->dequeue(tMission);
		temp.enqueue(tMission);
		cout << tMission->getId();
		first = false;
	}
	cout << "}" << endl;
	while (!temp.isEmpty()) {
		temp.dequeue(tMission);
		waitingMountain->enqueue(tMission);
	}
}
