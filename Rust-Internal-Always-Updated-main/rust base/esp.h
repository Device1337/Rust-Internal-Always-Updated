#pragma once
#include "includes.hpp"
#include "game/classes.hpp"

namespace esp
{
	void render_aimbot(rust::BasePlayer* player, BoneList bone);
	void render_shitaim(rust::BasePlayer* player, BoneList bone);
	void ShootWhileInAir();
	void render_weapon(rust::BasePlayer* player);
	void render_Health(rust::BasePlayer* player);
	void render_distance(rust::BasePlayer* player);
	void render_name(rust::BasePlayer* player);
	void render_box(rust::BasePlayer* player);
	void do_chams(rust::BasePlayer* player, float vischamr, float vischamg, float vischamb, float nonchamr, float nonchamg, float nonchamb);
	void SafeAdmin();
	void NoRecoil();
	void nosway();
	void instaEoka();
	void MoonJump();
	void FullAuto();
	void WalkOnWalter();
	void ExterndMelee();
	void fastbow();
	void longeye();
	void Dysnic();
}