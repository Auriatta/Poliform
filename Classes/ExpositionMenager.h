#pragma once
#include "Include.h"
#include "Polimorf.h"

class TurnEveryPoliform
{
public:
	TurnEveryPoliform(std::list<Polimorf*>* PoliformListRef,
		float ShowedDelay, float HiddenDelay,
		float PoliformNumber = 1, float TickInterval = 0.2)
		: ShowedDelay(ShowedDelay), TickInterval(TickInterval),
		 TickCounter(0), PoliformNumber(PoliformNumber), GoalSwitch(0),
		PoliformListRef(PoliformListRef), HiddenDelay(HiddenDelay)
	{}


	void Update(float delta);

private:
	int PoliformNumber;
	std::list<Polimorf*>* PoliformListRef;
	float TickCounter;
	bool GoalSwitch;
	float ShowedDelay;
	float HiddenDelay;
	float TickInterval;
	
	bool AddOne();
	bool RemoveOne();
};

