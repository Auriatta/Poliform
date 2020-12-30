#include "ExpositionMenager.h"

void TurnEveryPoliform::Update(float delta)
{
	TickCounter += delta;
	if (modf(TickCounter / TickInterval, &delta) > 0.06)
		return;

	if (GoalSwitch && TickCounter > ShowedDelay)
	{
		if (!RemoveOne())
		{
			TickCounter = 0;
			GoalSwitch = 0;
			return;
		}
	}
	
	if(!GoalSwitch && TickCounter > HiddenDelay)
	{
		if (!AddOne())
		{
			TickCounter = 0;
			GoalSwitch = 1;
			return;
		}
	}
		

}

bool TurnEveryPoliform::AddOne()
{
	
	if(PoliformListRef->size() >= PoliformNumber)
		return false;
	else
	{
		PoliformListRef->push_front(new Polimorf());
		PoliformListRef->front()->Run();
	}
	return true;
}

bool TurnEveryPoliform::RemoveOne()
{
	
	if (PoliformListRef->empty())
		return false;
	else
	{
		delete PoliformListRef->front();
		PoliformListRef->pop_front();
	}
	return true;
}
