#include "FormulationEvent.h"

FormulationEvent::FormulationEvent(int id,int a, int d, char mt, int tl, int dur,int sign, PriQueue<Mission*>*wem, Queue<Mission*>* wpm, Queue<Mission*>* wmm, Queue<Mission*>* cm, Queue<Mission*>*ixm)
{
	ID = id;
	day = d;
	missionType = mt;
	targetLocation = tl;
	missionDuration = dur;
	significance = sign;
	waitingEmergencyMissions = wem;
	waitingPolarMissions = wpm;
	waitingMountainMissions = wmm;
	completeMissions = cm;
	inExecutionMissions = ixm;
	autoP = a;
}

void FormulationEvent::Execute() {
	Mission* mission = new Mission(ID, day, missionType, targetLocation, missionDuration, significance ,autoP);
	if (missionType == 'M') {
		waitingMountainMissions->enqueue(mission);
	}else if (missionType == 'P') {
		waitingPolarMissions->enqueue(mission);
	}else if (missionType == 'E') {
		double priority = ((double)mission->getSignificance() / ((double)day + missionDuration + targetLocation))*100;//max sign,ealier fd, least duration,least distance
		mission->setPriority(priority);
		waitingEmergencyMissions->add(mission, priority);
	}
}
