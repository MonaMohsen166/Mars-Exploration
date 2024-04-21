#include "Rover.h"

int Rover::nextId = 0;

Rover::Rover() {

}

Rover::Rover(char t, int c, int s, int n)
{
	type = t;
	checkupDuration = c;
	remaningCheckupDuration = c;
	speed = s;
	numberOfMissionsBeforeCheckup = n;
	remaningMissionBeforeCheckup = n;
	id = nextId;
	nextId++;
}


int Rover::getCheckupDuration()
{
	return checkupDuration;
}
int Rover::getSpeed()
{
	return speed;
}
int Rover::getNumberOfMissionsBeforeCheckup()
{
	return numberOfMissionsBeforeCheckup;
}

char Rover::getType()
{
	return type;
}
int Rover::getRemaningOfMissionsBeforeCheckup()
{
	return remaningMissionBeforeCheckup;
}
int Rover::getMissionFinishDay()
{
	return missionFinishDay;
}
void Rover::setSpeed(int s)
{
	speed = s;
}
void Rover::setType(char t)
{
	type = t;
}
void Rover::setCheckupDuration(int s)
{
	checkupDuration = s;
}

void Rover::setNumberOfMissionsBeforeCheckup(int n)
{
	numberOfMissionsBeforeCheckup = n;
}

void Rover::setRemaningOfMissionsBeforeCheckup(int r)
{
	remaningMissionBeforeCheckup = r;
}

void Rover::setMissionFinishDay(int f)
{
	missionFinishDay = f;
}

void Rover::serRemaningCheckupDuration(int r)
{
	remaningCheckupDuration = r;
}

int Rover::gerRemaningCheckupDuration()
{
	return remaningCheckupDuration;
}

int Rover::getID()
{
	return id;
}
