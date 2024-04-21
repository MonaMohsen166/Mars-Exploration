#include <iostream>
#include "Mission.h"
#include "Rover.h"
using namespace std;

class UI {
public:
	void PrintMessage(string msg);
	string readInput();
	int getOutPutMode();
	void printDaySummary(int currentDay, PriQueue<Mission*> *waitingEmergency,
		Queue<Mission*> *waitingMountain, Queue<Mission*> *waitingPolar, Queue<Mission*>*inExecutionMissions,
		Queue<Rover*>* inExecutionRovers, Queue<Rover*>*avilableMountainRover, Queue<Rover*>*avilableEmergencyRover,
		Queue<Rover*>*avilablePolarRover, Queue<Rover*>*checkupEmergenceyRover, Queue<Rover*>*checkupMountainRover,
		Queue<Rover*>*checkupPolarRover, Queue<Mission*>*completedMission);
	void printWaiting(PriQueue<Mission*> *waitingEmergency, Queue<Mission*> *waitingMountain, Queue<Mission*> *waitingPolar);
	void printInExec(Queue<Mission*>*inExecutionMissions);
	void printAvilableRovers(Queue<Rover*>*avilableMountainRover, Queue<Rover*>*avilableEmergencyRover, Queue<Rover*>*avilablePolarRover);
	void printCheckUpRovers(Queue<Rover*>*checkupEmergenceyRover, Queue<Rover*>*checkupMountainRover, Queue<Rover*>*checkupPolarRover);
	void printCompleteMissions(Queue<Mission*>*completedMission);

};