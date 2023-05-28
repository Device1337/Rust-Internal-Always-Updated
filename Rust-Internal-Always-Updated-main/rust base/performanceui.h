#pragma once
#include "hinclude.h"
#include "esp.h"
#include "game/offsets.hpp"
#include "Glob.hpp"
#include "sky.hpp"
#include "Misc.h"

namespace options {
	bool chams;
	bool box;
	bool name;
	bool helditemname;
	bool Health;
	bool Distance;
	bool norecoil;
	bool admin;
	bool nosway;
	bool instaeoka;
	bool Water;
	bool fullauto;
	bool aimbot;
	bool moonJump;
	bool Shitaim;
	bool shootinair;
	bool extendedmelee;
	bool instabow;
	bool longeyes;
	bool dysnicfromserver;
}
float vr, vg, vb, nr, ng, nb;


void sky_loop()
{
	uintptr_t todsky;

	if (!todsky)
	{
		std::cout << "Not Working";
	}
	auto instantsky = *reinterpret_cast<uintptr_t*>(todsky + offsets::tod_sky_get_instance);

	if (!instantsky)
	{
		std::cout << "Instant not working";
	}
	auto tod_atmosphereparameters = *reinterpret_cast<uintptr_t*>(todsky + offsets::tod_atmosphereparameters);
	if (!tod_atmosphereparameters)
	{
		std::cout << "tod_atmosphereparameters Not Working";
	}
	
	auto tod_dayparameters = *reinterpret_cast<uintptr_t*>(todsky + offsets::tod_dayparameters);
	if (!tod_dayparameters)
	{
		std::cout << "tod_dayparameters Not Working";
	}
	

	auto tod_dayparameters_ambientmultiplier = *reinterpret_cast<uintptr_t*>(tod_dayparameters + offsets::tod_dayparameters_ambientmultiplier);
	if (!tod_dayparameters_ambientmultiplier)
	{
		std::cout << "tod_dayparameters_ambientmultiplier Not Working";
	}
	auto tod_nightparameters = *reinterpret_cast<uintptr_t*>(todsky + offsets::tod_nightparameters);
	if (!tod_nightparameters)
	{
		std::cout << "tod_nightparameters Not Working";
	}
		
	auto tod_nightparameters_ambientmultiplier = *reinterpret_cast<uintptr_t*>(tod_nightparameters + offsets::tod_nightparameters_ambientmultiplier);
	if (!tod_nightparameters_ambientmultiplier)
	{
		std::cout << "tod_nightparameters_ambientmultiplier Not Working";
	}

	
}
void entity_loop()
{
	variables::client_entities = il2cpp::value(xorstr_("BaseNetworkable"), xorstr_("clientEntities"), false);

	if (!variables::client_entities)
	{
		rust::LocalPlayer::ConsoleMessage(xorstr_("!client_entities"));
		return;
	}

	auto entity_realm = *reinterpret_cast<uintptr_t*>(variables::client_entities + 0x10);
	if (!entity_realm)
	{
		return;
	}

	auto buffer_list = *reinterpret_cast<uintptr_t*>(entity_realm + 0x28);
	if (!buffer_list)
	{
		return;
	}

	auto object_list_size = *reinterpret_cast<std::uint32_t*>(buffer_list + 0x10);

	auto object_list = *reinterpret_cast<uintptr_t*>(buffer_list + 0x18);
	if (!object_list)
	{
		return;
	}

	std::vector<rust::BasePlayer*> tempList;



	for (int idx = 0; idx < object_list_size; idx++)
	{
		auto current_object = *reinterpret_cast<uintptr_t*>(object_list + (0x20 + (idx * sizeof(uint64_t))));
		if (!current_object)
		{
			continue;
		}

		auto object_unk = *reinterpret_cast<uintptr_t*>(current_object);
		if (!object_unk)
		{
			continue;
		}

		auto classname_ptr = *reinterpret_cast<uintptr_t*>(object_unk + 0x10);
		if (!classname_ptr)
		{
			continue;
		}

		auto base_object = *reinterpret_cast<uintptr_t*>(current_object + 0x10);
		if (!base_object)
		{
			continue;
		}

		auto object = *reinterpret_cast<uintptr_t*>(base_object + 0x30);
		if (!object)
		{
			continue;
		}

		if (idx == 0)
		{
			auto local_player_object_class = *reinterpret_cast<uintptr_t*>(object + 0x30);

			if (!local_player_object_class)
			{
				continue;
			}

			auto local_entity = *reinterpret_cast<uintptr_t*>(local_player_object_class + 0x18);

			if (!local_entity)
			{
				continue;
			}

			variables::local_player = *reinterpret_cast<rust::BasePlayer**>(local_entity + 0x28);

			if (variables::local_player->get_life_state())
			{
				continue;
			}

			variables::local_position = variables::local_player->get_visual_position(local_player_object_class);
			continue;
		}

		functions::update_view_matrix();

		const auto tag = *reinterpret_cast<std::uint16_t*>(object + 0x54);
		if (tag == 6)
		{
			auto object_class = *reinterpret_cast<uintptr_t*>(object + 0x30);
			if (!object_class)
				return;

			auto entity = *reinterpret_cast<uintptr_t*>(object_class + 0x18);
			if (!entity)
				return;

			auto player = *reinterpret_cast<rust::BasePlayer**>(entity + 0x28);
			if (!reinterpret_cast<uintptr_t>(player))
				return;


			tempList.push_back(player);

			
		}
		else
		{
			std::hash<std::string_view> char_hash;
			const char* class_name = reinterpret_cast<const char*>(classname_ptr);
			auto class_crc = char_hash(class_name);

			auto object_name = xorstr_("OreResourceEntity");
			auto object_crc = char_hash(std::string_view(object_name, functions::my_strlen(object_name)));

		}
	}
	variables::player_list = tempList;

	return;
}

namespace PerformanceUI
{
	bool left;
	bool right;

	bool sleeper;
	bool knocked;
	int comboLeftSelected;
	int comboRightSelected;

	float sliderFloatLeft;
	float sliderFloatRight;

	int sliderIntLeft;
	int sliderIntRight;

	std::vector<std::string> Vis = { "Red", "Green", "Blue", "Purple" };
	std::vector<std::string> nonoVis = { "Red", "Green", "Blue", "Purple" };
	std::vector<std::string> BoneSelection = { "Head", "Neck", "Pelvis", "Dick" };
	int Bones;
	int nonvis;
	int vis;
	BoneList Aimbotbone; 

	inline void ongui_hook(void* instance)
	{
		if (Bones == 0)
		{
			Aimbotbone == head;
		}
		if (Bones == 1)
		{
			Aimbotbone == neck;
		}
		if (Bones == 2)
		{
			Aimbotbone == pelvis;
		}
		if (Bones == 3)
		{
			Aimbotbone == penis;
		}
		if (vis == 0)
		{
			vr = 200.0f;
			vg = 0.0f;
			vb = 55.0f;
		}

		if (vis == 1)
		{
			vr = 0.0f;
			vg = 230.0f;
			vb = 75.0f;
		}

		if (vis == 2)
		{
			vr = 0.0f;
			vg = 100.0f;
			vb = 200.0f;
		}

		if (vis == 3)
		{
			vr = 100.0f;
			vg = 0.0f;
			vb = 255.0f;
		}


		if (nonvis == 0)
		{
			nr = 255.0f;
			ng = 0.0f;
			ng = 0.0f;
		}

		if (nonvis == 1)
		{
			nr = 0.0f;
			ng = 255.0f;
			nb = 0.0f;
		}

		if (nonvis == 2)
		{
			nr = 0.0f;
			ng = 100.0f;
			nb = 200.0f;
		}

		if (nonvis == 3)
		{
			nr = 100.0f;
			ng = 0.0f;
			nb = 255.0f;
		}
		auto skin = functions::get_draw_skin();
		variables::draw_label = *reinterpret_cast<uintptr_t*>(skin + 0x38);
		functions::set_draw_alignment(variables::draw_label, 0x0);
		functions::set_draw_font_size(variables::draw_label, 12);
		functions::set_draw_color(Vector4(1, 1, 1, 1));

		entity_loop();
		//esp::render_esp();
		

		//menu
		mid_framework::begin(xorstr_("WinVer#3625 - Rust"));
		//mid_framework::add_tab(xorstr_("Visuals"), 0, 1);
		//mid_framework::add_tab(xorstr_("Combat"), 1, 2);

		//if (mid_framework::selected == 0)
		//{
			mid_framework::add_child(1);

			//checkmarks
			mid_framework::add_checkbox(xorstr_("Draw Player Box"), &options::box, 1);
			mid_framework::add_checkbox(xorstr_("Draw Player Name"), &options::name, 1);
			mid_framework::add_checkbox(xorstr_("Draw Player Health"), &options::Health, 1);
			mid_framework::add_checkbox(xorstr_("Draw Player Held Item"), &options::helditemname, 1);
			mid_framework::add_checkbox(xorstr_("Draw Player Distance"), &options::Distance, 1);
			mid_framework::add_checkbox(xorstr_("Draw Sleepers"), &sleeper, 1);
			mid_framework::add_checkbox(xorstr_("Draw Knocked"), &knocked, 1);
			mid_framework::add_checkbox(xorstr_("Draw Player Chams"), &options::chams, 1);
			mid_framework::add_checkbox(xorstr_("Draw Long Eyes (Key Arrows)"), &options::longeyes, 1);
			mid_framework::add_checkbox(xorstr_("Draw DeSync (SEMI-SAFE)"), &options::dysnicfromserver, 1);
			mid_framework::add_checkbox(xorstr_("Toggle Safe Admin (SEMI SAFE)"), &options::admin, 1);
			mid_framework::add_label(xorstr_("VISIBLE"), 1);
			mid_framework::add_combo(Vis, &vis, 1);
			mid_framework::add_label(xorstr_("INVISIBLE"), 1);
			mid_framework::add_combo(nonoVis, &nonvis, 1);
			//mid_framework::add_slider_float(xorstr_("Render Distance"), &sliderFloatLeft, 50.0f, 1000.0f, 1);

			


		//}
		//else if (mid_framework::selected == 1)
		//{
		//	mid_framework::add_label(xorstr_("AIMBOT IS IN TESTING!"), 1);
		//	mid_framework::add_child(1);
		//	mid_framework::add_checkbox(xorstr_("Enable Aimbot (Side Mouse)"), &options::aimbot, 1);
		//	mid_framework::add_checkbox(xorstr_("Enable No Recoil"), &options::norecoil, 1);
		//	mid_framework::add_checkbox(xorstr_("Enable No Sway"), &options::nosway, 1);
		//	mid_framework::add_checkbox(xorstr_("Enable Insta Eoka"), &options::instaeoka, 1);
		//	mid_framework::add_checkbox(xorstr_("Enable Full Auto"), &options::fullauto, 1);
		//	mid_framework::add_checkbox(xorstr_("Enable Fast Bow"), &options::instabow, 1);
		//	mid_framework::add_checkbox(xorstr_("Enable Extended Melee"), &options::extendedmelee, 1);

		//	mid_framework::add_combo(BoneSelection, &Bones, 1);

		//	mid_framework::add_checkbox(xorstr_("Enable Moon Jump"), &options::moonJump, 1);
		//	mid_framework::add_checkbox(xorstr_("Enable Shoot In Any State"), &options::shootinair, 1);
		//	mid_framework::add_checkbox(xorstr_("Enable Water Walk"), &options::Water, 1);


		//}
		mid_framework::end();

		functions::outline(Vector4(10, 10, 150, 20), xorstr_("Message WinVer#3625"), Vector4(0, 0, 0, 1));
		functions::label(Vector4(10, 10, 150, 20), xorstr_("Message WinVer#3625"), Vector4(1, 1, 1, 1));
		


		for (int i = 0; i < variables::player_list.size(); i++)
		{
			auto player = variables::player_list[i];
			if (!knocked)
			{
				if (player->is_knocked())
					continue;
			}
			if (!sleeper)
			{
				if (player->is_sleeping())
					continue;

			}
			if (player->is_same_team(player))
				continue;
		

		

			if (options::chams) { esp::do_chams(player, vr, vg, vb, nr, ng, nb); }
			if (options::box) { esp::render_box(player); }
			if (options::name) { esp::render_name(player); }
			if (options::helditemname) { esp::render_weapon(player); }
			if (options::Health) { esp::render_Health(player); }
			if (options::Distance) { esp::render_distance(player); }
			if (options::aimbot) { esp::render_aimbot(player, Aimbotbone); }
			//if (options::Shitaim) { esp::render_shitaim(player, Aimbotbone); }


		}

		if (options::norecoil) { esp::NoRecoil(); }
		if (options::fullauto) { esp::FullAuto(); }
		if (options::nosway) { esp::nosway(); }
		if (options::instaeoka) { esp::instaEoka(); }
		if (options::admin) { esp::SafeAdmin(); }
		if (options::moonJump) { esp::MoonJump(); }
		if (options::Water) { esp::WalkOnWalter(); }
		if (options::shootinair) { esp::ShootWhileInAir(); }
		if (options::extendedmelee) { esp::ExterndMelee(); }
		if (options::instabow) { esp::fastbow(); }
		if (options::longeyes) { esp::longeye(); }
		if (options::dysnicfromserver) { esp::Dysnic(); }
		

		

		return;
	}



	static bool wakeup{ true };
	uintptr_t performaceui_hook;
	void hk_performance_ui_update(void* instance)
	{
		if (wakeup)
		{
			auto game_object = il2cpp::methods::object_new(il2cpp::init_class(xorstr_("GameObject"), xorstr_("UnityEngine")));
			functions::create(game_object, xorstr_(""));
			functions::add_component(game_object, il2cpp::type_object(xorstr_(""), xorstr_("DevControls")));
			functions::dont_destroy_on_load(game_object);
			wakeup = false;
		}

		auto static update_performance_ui = reinterpret_cast<void(*)(void* instance)>(performaceui_hook);
		SpoofReturn(update_performance_ui, instance);
	}
}