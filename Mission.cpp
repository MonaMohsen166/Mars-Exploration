#include "Mission.h"


Mission::Mission(int i, int f, char mt, int t, int md, int s, int a)
{
	id = i;
	formulationDay = f;
	missionType = mt;
	targetLocation = t;
	missionDuration = md;
	significance = s;
	AutoP = a;
	roverId = -1;
}

void Mission::setFormulationDay(int f)
{
	formulationDay = f;
}
void Mission::setMissionType(char m)
{
	missionType = m;
}
void Mission::setTargetLocation(int t)
{
	targetLocation = t;
}
void Mission::setMissionDuration(int m)
{
	missionDuration = m;
}
void Mission::setSignificance(int s)
{
	significance = s;
}
void Mission::setStartDay(int d)
{
	startDay = d;
}
void Mission::setEndDay(int d)
{
	endDay = d;
}
void Mission::setAutoP(int a)
{
	AutoP = a;
}
void Mission::setPriority(int p)
{
	priority = p;
}
void Mission::setRoverId(int r)
{
	roverId = r;
}
void Mission::setExcutionDays(int d)
{
	excutionDays = d;
}
int Mission::getFormulationDay()
{
	return formulationDay;
}
char Mission::getMissionType()
{
	return missionType;
}
int Mission::getTargetLocation()
{
	return targetLocation;
}
int Mission::getMissionDuration()
{
	return missionDuration;
}
int Mission::getSignificance()
{
	return significance;
}

int Mission::getStartDay()
{
	return startDay;
}

int Mission::getEndDay()
{
	return endDay;
}

int Mission::getAutoP()
{
	return AutoP;
}

int Mission::getExcutionDays()
{
	return excutionDays;
}

int Mission::getId()
{
	return id;
}

int Mission::getRoverId()
{
	return roverId;
}

int Mission::getPriority()
{
	return priority;
}
