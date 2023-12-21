#pragma once

//#include "Containers/Map.h"
//#include "Templates/Tuple.h"

#include <utility>

UENUM()
enum class WorldState
{
	IsHungry,
	IsThirsty,

	IsInDanger,
	IsDamaged,

	IsNearTree,
	IsNearBuyer,
	IsNearSeller,
	
	HaveWood,
	HaveAxe,
	HaveWater,
	HaveFood,

	HaveMoney,

	Chilling
};

using Precondition = std::pair<WorldState, bool>;
using Consequence = std::pair<WorldState, bool>;
using DesiredState = std::pair<WorldState, bool>;

using ConditionalGoal = std::pair<Precondition, DesiredState>;