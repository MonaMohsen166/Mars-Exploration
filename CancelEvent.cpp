#include "CancelEvent.h"

void CancelEvent::Execute()
{

	//loop on mountain queue
	Queue<Mission*> mountainTemp;
	Mission* m;
	while (!waitingMountainMissions->isEmpty()) {
		waitingMountainMissions->dequeue(m);
		if (m->getId() != ID) {
			mountainTemp.enqueue(m);
		}
	}
	while (!mountainTemp.isEmpty()) {
		mountainTemp.dequeue(m);
		waitingMountainMissions->enqueue(m);
	}

	//loop on emergency queue
	PriQueue<Mission*> emergencyTemp;
	while (!waitingEmergencyMissions->isEmpty()) {
		waitingEmergencyMissions->remove(m);
		if (m->getId() != ID) {
			emergencyTemp.add(m, m->getPriority());
		}
	}
	while (!emergencyTemp.isEmpty()) {
		emergencyTemp.remove(m);
		waitingEmergencyMissions->add(m ,m->getPriority());
	}
}
