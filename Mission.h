#pragma once
#include "PriQueue.h"
#include "Queue.h"

class Mission {
private:
	int id;
	int formulationDay;
	char missionType;
	int targetLocation;
	int missionDuration;
	int significance;
	int startDay;
	int endDay;
	int excutionDays;
	int priority;
	int AutoP;
	int roverId;
public:
	Mission(int, int, char, int, int, int,int);
	void setFormulationDay(int);
	void setMissionType(char);
	void setTargetLocation(int);
	void setMissionDuration(int);
	void setSignificance(int);
	void setStartDay(int);
	void setEndDay(int);
	void setAutoP(int);
	void setPriority(int);
	void setRoverId(int);
	void setExcutionDays(int);

	int getFormulationDay();
	char getMissionType();
	int getTargetLocation();
	int getMissionDuration();
	int getSignificance();
	int getStartDay();
	int getEndDay();
	int getAutoP();
	int getExcutionDays();
	int getId();
	int getRoverId();
	int getPriority();
};