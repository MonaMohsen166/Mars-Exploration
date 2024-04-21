#pragma once

class Rover {
private:
	char type;
	int checkupDuration;
	int remaningCheckupDuration;
	int speed;
	int numberOfMissionsBeforeCheckup;
	int remaningMissionBeforeCheckup;
	int missionFinishDay;
	int id;
	static int nextId;
public:
	Rover();
	Rover(char, int, int , int);
	int getCheckupDuration();
	int getSpeed();
	int getNumberOfMissionsBeforeCheckup();
	char getType();
	int getRemaningOfMissionsBeforeCheckup();
	int getMissionFinishDay();
	void setSpeed(int);
	void setType(char);
	void setCheckupDuration(int);
	void setNumberOfMissionsBeforeCheckup(int);
	void setRemaningOfMissionsBeforeCheckup(int);
	void setMissionFinishDay(int);
	void serRemaningCheckupDuration(int);
	int gerRemaningCheckupDuration();
	int getID();
};