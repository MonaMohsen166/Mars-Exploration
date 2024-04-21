#include "Event.h"

Event::Event(int id, int d, PriQueue<Mission*>*wem, Queue<Mission*>* wpm, Queue<Mission*>* wmm, Queue<Mission*>* cm, Queue<Mission*>*ixm)
{
	ID = id;
	day = d;
	waitingEmergencyMissions = wem;
	waitingPolarMissions = wpm;
	waitingMountainMissions = wmm;
	completeMissions = cm;
	inExecutionMissions = ixm;
}

Event::Event()
{
}

Event::~Event()
{
}

int Event::GetID() const
{
	return ID;
}

int Event::GetDay() const
{
	return day;
}