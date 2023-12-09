#pragma once

//#include "Containers/Map.h"
//#include "Templates/Tuple.h"

#include <utility>

enum class WorldState
{
	IsHungry,
	IsThirsty,

	IsInDanger,
	IsDamaged,

	IsNearTree,
	IsNearBuyer,
	
	HaveWood,
	HaveAxe,
	HaveWater,
	HaveFood,

	HaveMoney,
};

//using Precondition = TPair<WorldStates, bool>;
//using Consequence = TPair<WorldStates, bool>;
using Precondition = std::pair<WorldState, bool>;
using Consequence = std::pair<WorldState, bool>;
using DesiredState = std::pair<WorldState, bool>;

using Goal = std::pair<Precondition, DesiredState>;