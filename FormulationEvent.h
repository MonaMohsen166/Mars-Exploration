#pragma once
#include"Event.h"
#include"Mission.h"

class FormulationEvent :public Event
{
private:
	char missionType;
	int targetLocation;
	int missionDuration;
	int significance;
	int autoP;
public:
	using Event::Event;
	FormulationEvent(int id,int a, int d, char mt, int tl, int dur, int sign, PriQueue<Mission*>* wem, Queue<Mission*>* wpm, Queue<Mission*>* wmm, Queue<Mission*>* cm, Queue<Mission*>* ixm);
	virtual void Execute();

};