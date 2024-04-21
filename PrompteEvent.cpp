#include "PrompteEvent.h"

void PrompteEvent::Execute()
{
	//loop on mountain queue
	Queue<Mission*> mountainTemp;
	Mission* m;
	while (!waitingMountainMissions->isEmpty()) {
		waitingMountainMissions->dequeue(m);
		if (m->getId() != ID) {
			mountainTemp.enqueue(m);
		}
		else {
			int priority = ((double)m->getSignificance() / ((double)m->getFormulationDay() + m->getMissionDuration() + m->getTargetLocation()))*100;//max sign,ealier fd, least duration,least distance
			waitingEmergencyMissions->add(m, priority);
		}
	}
	while (!mountainTemp.isEmpty()) {
		mountainTemp.dequeue(m);
		waitingMountainMissions->enqueue(m);
	}
}
