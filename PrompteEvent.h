#pragma once
#include"Event.h"

class PrompteEvent :public Event
{
private:


public:
	using Event::Event;
	virtual void Execute();

};