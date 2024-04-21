#pragma once
#include "Queue.h"
#include "PriQueue.h"
#include "Mission.h"

class Event
{

protected:
	int ID;
	int day;
	PriQueue<Mission*>* waitingEmergencyMissions;
	Queue<Mission*>* waitingPolarMissions;
	Queue<Mission*>* waitingMountainMissions;
	Queue<Mission*>* completeMissions;
	Queue<Mission*>* inExecutionMissions;

public:
	Event(int id, int day , PriQueue<Mission*>* , Queue<Mission*>*, Queue<Mission*>*, Queue<Mission*>*, Queue<Mission*>*);
	Event();
	virtual ~Event();

	int Event::GetID() const;
	int Event::GetDay() const;

	virtual void Execute() = 0;

};