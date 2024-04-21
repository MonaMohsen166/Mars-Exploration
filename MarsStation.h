#pragma once

#include <chrono>
#include <thread>
#include "Queue.h"
#include "PriQueue.h"
#include "Stack.h"
#include "Mission.h"
#include "Rover.h"
#include "UI.h"
#include<fstream>
#include "Event.h"
#include "FormulationEvent.h"
#include "CancelEvent.h"
#include "PrompteEvent.h"

class MarsStation
{
private:
	UI* ui;

	Queue<Event*> allEvents;
	PriQueue<Mission*> waitingEmergencyMissions;
	Queue<Mission*> waitingPolarMissions;
	Queue<Mission*> waitingMountainMissions;
	Queue<Mission*> completeMissions;
	
	Queue<Mission*> inExecutionMissions;
	Queue<Rover*> inExecutionRover;
	Queue<Rover*> availableEmergencyRovers;
	Queue<Rover*> availableMountainRovers;
	Queue<Rover*> availablePolarRovers;
	Queue<Rover*> checkupEmergencyRovers;
	Queue<Rover*> checkupMountainRovers;
	Queue<Rover*> checkupPolarRovers;


public:
	int currentDay;
	MarsStation();
	void run();
	void loadFile();
	void writeOutPutFile();
	void interactiveMode();
	void stepByStepMode();
	void silentMode();
	void excuteEvents();
	void assignMissionsToRovers();
	void completingMissions();
	void mountainAutomaticallyPromoted();
	void RoversCheckup();
};

