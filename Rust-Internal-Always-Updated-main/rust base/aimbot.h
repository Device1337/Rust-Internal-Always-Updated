#pragma once
#include "includes.hpp"
#include "game/classes.hpp"

namespace aimbot {
	rust::BasePlayer* getBestPlayerByFov();
	int getClosestBoneToCrosshair(rust::BasePlayer* player);
	void run(BoneList abone);
	void silentaim();
}