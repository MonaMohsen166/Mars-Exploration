#pragma once
#include"Event.h"

class CancelEvent :public Event
{
private:


public:
	using Event::Event;
	virtual void Execute();

};