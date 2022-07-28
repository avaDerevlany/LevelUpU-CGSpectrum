#pragma once
#include "PlacableActor.h"
class Sword : public PlacableActor
{
public:
	Sword(int x, int y, ActorColor color)
		: PlacableActor(x, y, color)
	{

	}

	virtual ActorType GetType() override { return ActorType::Sword; }
	virtual void Draw() override;
};

