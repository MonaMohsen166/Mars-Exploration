#include "MarsStation.h"

MarsStation::MarsStation()
{

}

void MarsStation::loadFile()
{
	string filename;
	ifstream file;
	int m, p, e,
		sm, sp, se,
		n, cm, cp, ce,
		autoP,
		E;

	ui->PrintMessage("Enter File Name: ");

	while (!file.is_open())
	{
		filename = ui->readInput();
		file.open(filename);
		if (!file.is_open())
			ui->PrintMessage("File does not exis, Try again.\n");
	}
	if (file.is_open())
	{
		file >> m >> p >> e >>
			sm >> sp >> se >>
			n >> cm >> cp >> ce >>
			autoP >>
			E;
		for (int i = 0; i < e; i++) {
			availableEmergencyRovers.enqueue(new Rover('E', se, ce, n));
		}

		for (int i = 0; i < p; i++) {
			availablePolarRovers.enqueue(new Rover('P', sp, cp, n));
		}

		for (int i = 0; i < m; i++) {
			availableMountainRovers.enqueue(new Rover('M', sm, cm, n));
		}

		char eventType;
		char typ;
		int ed, id, tloc, mdur, sig;
		for (int i = 0; i < E; i++)
		{
			file >> eventType;
			if (eventType == 'F') {
				file >> typ >> ed >> id >> tloc >> mdur >> sig;
				allEvents.enqueue(new FormulationEvent(id, autoP, ed, typ, tloc, mdur, sig, &waitingEmergencyMissions, &waitingPolarMissions, &waitingMountainMissions, &completeMissions, &inExecutionMissions));
			}
			else if (eventType == 'X') {
				file >> ed >> id;
				allEvents.enqueue(new CancelEvent(id, ed, &waitingEmergencyMissions, &waitingPolarMissions, &waitingMountainMissions, &completeMissions, &inExecutionMissions));
			}
			else if (eventType == 'P') {
				file >> ed >> id;
				allEvents.enqueue(new PrompteEvent(id, ed, &waitingEmergencyMissions, &waitingPolarMissions, &waitingMountainMissions, &completeMissions, &inExecutionMissions));
			}
		}
	}
	file.close();
}

void MarsStation::run()
{
	ui = new UI;
	int mode = ui->getOutPutMode();
	if (mode == 1) {
		interactiveMode();
	}
	else if (mode == 2) {
		stepByStepMode();
	}
	else if (mode == 3) {
		silentMode();
	}
	delete ui;
}

void MarsStation::interactiveMode()
{
	loadFile();
	currentDay = 0;
	while (!(waitingEmergencyMissions.isEmpty() &&
		waitingMountainMissions.isEmpty() &&
		waitingPolarMissions.isEmpty() &&
		inExecutionMissions.isEmpty() &&
		allEvents.isEmpty())
		) {
		excuteEvents();
		assignMissionsToRovers();
		completingMissions();
		RoversCheckup();
		mountainAutomaticallyPromoted();
		ui->printDaySummary(currentDay, &waitingEmergencyMissions,
			&waitingMountainMissions, &waitingPolarMissions, &inExecutionMissions,
			&inExecutionRover, &availableMountainRovers, &availableEmergencyRovers,
			&availablePolarRovers, &checkupEmergencyRovers, &checkupMountainRovers, &checkupPolarRovers, &completeMissions);
		currentDay++;
		cin.get();
	}
}

void MarsStation::stepByStepMode()
{
	loadFile();
	currentDay = 1;
	while (!(waitingEmergencyMissions.isEmpty() &&
		waitingMountainMissions.isEmpty() &&
		waitingPolarMissions.isEmpty() &&
		inExecutionMissions.isEmpty() &&
		allEvents.isEmpty())
		) {
		excuteEvents();
		mountainAutomaticallyPromoted();
		assignMissionsToRovers();
		completingMissions();
		ui->printDaySummary(currentDay, &waitingEmergencyMissions,
			&waitingMountainMissions, &waitingPolarMissions, &inExecutionMissions,
			&inExecutionRover, &availableMountainRovers, &availableEmergencyRovers,
			&availablePolarRovers, &checkupEmergencyRovers, &checkupMountainRovers, &checkupPolarRovers, &completeMissions);
		RoversCheckup();
		currentDay++;
		this_thread::sleep_for(std::chrono::seconds(1));
	}
}

void MarsStation::silentMode()
{
	loadFile();
	currentDay = 1;
	while (!(waitingEmergencyMissions.isEmpty() &&
		waitingMountainMissions.isEmpty() &&
		waitingPolarMissions.isEmpty() &&
		inExecutionMissions.isEmpty() &&
		allEvents.isEmpty())
		) {
		excuteEvents();
		mountainAutomaticallyPromoted();
		assignMissionsToRovers();
		completingMissions();
		RoversCheckup();
		currentDay++;
		cout << "k";
	}
	//return 0;
	//writeInOutPutFile();
}

void MarsStation::excuteEvents()
{
	Event* e;
	while (!allEvents.isEmpty()) {
		allEvents.peekFront(e);
		if (e->GetDay() <= currentDay) {
			allEvents.dequeue(e);
			e->Execute();
		}
		else {
			break;
		}
	}
}

void MarsStation::assignMissionsToRovers()
{
	//Emergency
	while (!waitingEmergencyMissions.isEmpty()) {
		Mission* mission = NULL;
		waitingEmergencyMissions.peek(mission);
		Rover* rover;
		if (availableEmergencyRovers.peekFront(rover)) {
			availableEmergencyRovers.dequeue(rover);
		}
		else if (availableMountainRovers.peekFront(rover)) {
			availableMountainRovers.dequeue(rover);
		}
		else if (availablePolarRovers.peekFront(rover)) {
			availablePolarRovers.dequeue(rover);
		}

		if (rover != NULL) {
			waitingEmergencyMissions.remove(mission);
			mission->setStartDay(currentDay);
			int excutionsDays = ((mission->getTargetLocation() / rover->getSpeed()) / 24) * 2 + mission->getMissionDuration();
			mission->setExcutionDays(excutionsDays);
			int waitingDays = mission->getStartDay() - currentDay;
			int endDay = mission->getStartDay() + excutionsDays + waitingDays;
			mission->setEndDay(endDay);
			mission->setRoverId(rover->getID());
			inExecutionMissions.enqueue(mission);  //to make the nearst mission on time first
			rover->setMissionFinishDay(endDay);
			rover->setRemaningOfMissionsBeforeCheckup(rover->getRemaningOfMissionsBeforeCheckup() - 1);
			inExecutionRover.enqueue(rover);
		}
		else break;
	}

	//Polar
	while (!waitingPolarMissions.isEmpty()) {
		Mission* mission = NULL;
		waitingPolarMissions.peekFront(mission);
		Rover* rover;
		if (availablePolarRovers.peekFront(rover)) {
			availablePolarRovers.dequeue(rover);
		}

		if (rover != NULL) {
			waitingPolarMissions.dequeue(mission);
			mission->setStartDay(currentDay);
			int excutionsDays = ((mission->getTargetLocation() / rover->getSpeed())/24) * 2 + mission->getMissionDuration();
			mission->setExcutionDays(excutionsDays);
			int waitingDays = mission->getStartDay() - currentDay;
			int endDay = mission->getStartDay() + excutionsDays + waitingDays;
			mission->setEndDay(endDay);
			mission->setRoverId(rover->getID());
			inExecutionMissions.enqueue(mission);
			rover->setMissionFinishDay(endDay);
			rover->setRemaningOfMissionsBeforeCheckup(rover->getRemaningOfMissionsBeforeCheckup() - 1);
			inExecutionRover.enqueue(rover);
		}
		else break;
	}

	//Mountain
	while (!waitingMountainMissions.isEmpty()) {
		Mission* mission = NULL;
		waitingMountainMissions.peekFront(mission);
		Rover* rover;
		if (availableMountainRovers.peekFront(rover)) {
			availableMountainRovers.dequeue(rover);
		}
		else if (availableEmergencyRovers.peekFront(rover)) {
			availableEmergencyRovers.dequeue(rover);
		}

		if (rover != NULL) {
			waitingMountainMissions.dequeue(mission);
			mission->setStartDay(currentDay);
			int excutionsDays = ((mission->getTargetLocation() / rover->getSpeed()) / 24) * 2 + mission->getMissionDuration();
			mission->setExcutionDays(excutionsDays);
			int waitingDays = mission->getStartDay() - currentDay;
			int endDay = mission->getStartDay() + excutionsDays + waitingDays;
			mission->setEndDay(endDay);
			mission->setRoverId(rover->getID());
			inExecutionMissions.enqueue(mission);
			rover->setMissionFinishDay(endDay);
			rover->setRemaningOfMissionsBeforeCheckup(rover->getRemaningOfMissionsBeforeCheckup() - 1);
			inExecutionRover.enqueue(rover);
		}
		else break;
	}
}

void MarsStation::completingMissions()
{
	Mission* m;
	Rover* r;
	Queue<Mission*>temp;
	Queue<Rover*> tempr;

	while (!inExecutionMissions.isEmpty()) {
		inExecutionMissions.dequeue(m);
		if (currentDay >= m->getEndDay()) {
			completeMissions.enqueue(m);
		}
		else {
			temp.enqueue(m);
		}
	}
	while (!temp.isEmpty()) {
		temp.dequeue(m);
		inExecutionMissions.enqueue(m);
	}

	while (!inExecutionRover.isEmpty()) {
		inExecutionRover.dequeue(r);
		if (currentDay >= r->getMissionFinishDay()) {
			switch (r->getType())
			{
			case 'E':
				availableEmergencyRovers.enqueue(r);
				break;
			case 'M':
				availableMountainRovers.enqueue(r);
				break;
			case 'P':
				availablePolarRovers.enqueue(r);
				break;
			default:
				break;
			}
		}
		else {
			tempr.enqueue(r);
		}
	}
	while(!temp.isEmpty()) {
		tempr.dequeue(r);
		inExecutionRover.enqueue(r);
	}
}

void MarsStation::mountainAutomaticallyPromoted()
{
	//loop on mountain queue
	Queue<Mission*> mountainTemp;
	Mission* m;
	while (!waitingMountainMissions.isEmpty()) {
		waitingMountainMissions.dequeue(m);
		if (m->getAutoP() > (currentDay - m->getFormulationDay())) {
			mountainTemp.enqueue(m);
		}
		else {
			int priority = ((double)m->getSignificance() / ((double)m->getFormulationDay() + m->getMissionDuration() + m->getTargetLocation())) * 100;//max sign,ealier fd, least duration,least distance
			waitingEmergencyMissions.add(m, priority);
		}
	}
	while (!mountainTemp.isEmpty()) {
		mountainTemp.dequeue(m);
		waitingMountainMissions.enqueue(m);
	}
}

void MarsStation::RoversCheckup() {
	//waiting -> checkup
	Queue<Rover*> temp;
	while (!availableEmergencyRovers.isEmpty()) {
		Rover* rover;
		availableEmergencyRovers.dequeue(rover);
		if (rover->getRemaningOfMissionsBeforeCheckup() == 0) {
			rover->setRemaningOfMissionsBeforeCheckup(rover->getNumberOfMissionsBeforeCheckup());
			checkupEmergencyRovers.enqueue(rover);
		}
		else {
			temp.enqueue(rover);
		}
	}
	while (!temp.isEmpty()) {
		Rover* rover;
		temp.dequeue(rover);
		availableEmergencyRovers.enqueue(rover);
	}

	while (!availableMountainRovers.isEmpty()) {
		Rover* rover;
		availableMountainRovers.dequeue(rover);
		if (rover->getRemaningOfMissionsBeforeCheckup() == 0) {
			rover->setRemaningOfMissionsBeforeCheckup(rover->getNumberOfMissionsBeforeCheckup());
			checkupMountainRovers.enqueue(rover);
		}
		else {
			temp.enqueue(rover);
		}
	}
	while (!temp.isEmpty()) {
		Rover* rover;
		temp.dequeue(rover);
		availableMountainRovers.enqueue(rover);
	}

	while (!availablePolarRovers.isEmpty()) {
		Rover* rover;
		availablePolarRovers.dequeue(rover);
		if (rover->getRemaningOfMissionsBeforeCheckup() == 0) {
			rover->setRemaningOfMissionsBeforeCheckup(rover->getNumberOfMissionsBeforeCheckup());
			checkupPolarRovers.enqueue(rover);
		}
		else {
			temp.enqueue(rover);
		}
	}
	while (!temp.isEmpty()) {
		Rover* rover;
		temp.dequeue(rover);
		availablePolarRovers.enqueue(rover);
	}	///////////////

	//checkup -> waiting
	while (!checkupEmergencyRovers.isEmpty()) {
		Rover* rover;
		checkupEmergencyRovers.dequeue(rover);
		if (rover->gerRemaningCheckupDuration() <= 0) {
			rover->serRemaningCheckupDuration(rover->getCheckupDuration());
			availableEmergencyRovers.enqueue(rover);
		}
		else {
			rover->setRemaningOfMissionsBeforeCheckup(rover->gerRemaningCheckupDuration() - 1);
			temp.enqueue(rover);
		}
	}
	while (!temp.isEmpty()) {
		Rover* rover;
		temp.dequeue(rover);
		checkupEmergencyRovers.enqueue(rover);
	}

	while (!checkupMountainRovers.isEmpty()) {
		Rover* rover;
		checkupMountainRovers.dequeue(rover);
		if (rover->gerRemaningCheckupDuration() <= 0) {
			rover->serRemaningCheckupDuration(rover->getCheckupDuration());
			availableMountainRovers.enqueue(rover);
		}
		else {
			rover->setRemaningOfMissionsBeforeCheckup(rover->gerRemaningCheckupDuration() - 1);
			temp.enqueue(rover);
		}
	}
	while (!temp.isEmpty()) {
		Rover* rover;
		temp.dequeue(rover);
		checkupMountainRovers.enqueue(rover);
	}

	while (!checkupPolarRovers.isEmpty()) {
		Rover* rover;
		checkupPolarRovers.dequeue(rover);
		if (rover->gerRemaningCheckupDuration() <= 0) {
			rover->serRemaningCheckupDuration(rover->getCheckupDuration());
			availablePolarRovers.enqueue(rover);
		}
		else {
			rover->setRemaningOfMissionsBeforeCheckup(rover->gerRemaningCheckupDuration() - 1);
			temp.enqueue(rover);
		}
	}
	while (!temp.isEmpty()) {
		Rover* rover;
		temp.dequeue(rover);
		checkupPolarRovers.enqueue(rover);
	}
}