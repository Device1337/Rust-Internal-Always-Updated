#pragma once
#include "hinclude.h"
#include "esp.h"
#include "game/offsets.hpp"
#include "Glob.hpp"
#include "sky.hpp"

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
		

			//variables::local_player->get_held_item()->set_rapid_fire(true);
			esp::render_esp(player);
		
			//variables::local_player->get_held_item()->set_rapid_fire(25.0f);

		//	esp::WeaponFeatures(Ouritem);
			//esp::Weapon_Feature(player);
		}
		else
		{
			std::hash<std::string_view> char_hash;
			const char* class_name = reinterpret_cast<const char*>(classname_ptr);
			auto class_crc = char_hash(class_name);

			auto object_name = xorstr_("OreResourceEntity");
			auto object_crc = char_hash(std::string_view(object_name, functions::my_strlen(object_name)));


			if (*(int*)(object_name + 46) == '_hsa') {
				
			}
			 if(*(int*)(object_name + 52) == 'nots' || *(int*)(object_name + 47) == 'nots')
			 {
				
			}
			continue;
		}
	}
	variables::player_list = tempList;

	return;
}

namespace ongui
{
	bool left;
	bool right;

	std::vector<std::string> combo = { "Normal Chams", "Holo Chams", "Transparent Chams", "Rainbow", "High Quality"};
	int comboLeftSelected;
	int comboRightSelected;

	float sliderFloatLeft;
	float sliderFloatRight;

	int sliderIntLeft;
	int sliderIntRight;


	inline void ongui_hook(void* instance)
	{
		auto skin = functions::get_draw_skin();
		variables::draw_label = *reinterpret_cast<uintptr_t*>(skin + 0x38);
		functions::set_draw_alignment(variables::draw_label, 0x0);
		functions::set_draw_font_size(variables::draw_label, 12);
		functions::set_draw_color(Vector4(1, 1, 1, 1));

		entity_loop();
		//esp::render_esp();
		

		//menu
		mid_framework::begin(xorstr_("EAC PRIVATE"));
		mid_framework::add_tab("Visuals", 0, 1);
		mid_framework::add_tab("Combat", 1, 2);
		mid_framework::add_tab("Misc", 2, 3);
		mid_framework::add_tab("Exploits", 3, 4);
		mid_framework::add_tab("Rage", 4, 5);

		if (mid_framework::selected == 0)
		{
			mid_framework::add_child(2);

			//checkmarks
			mid_framework::add_label("Player Visuals", 1);
			mid_framework::add_checkbox("Player Name", &left, 1);
			mid_framework::add_checkbox("Player Health", &left, 1);
			mid_framework::add_checkbox("Player Held Item", &left, 1);
			mid_framework::add_checkbox("Player Hotbar", &left, 1);
			mid_framework::add_checkbox("Snaplines", &left, 1);
			mid_framework::add_checkbox("Player Distance", &left, 1);
			mid_framework::add_checkbox("Chams", &left, 1);
			mid_framework::add_combo(combo, &comboLeftSelected, 1);
			mid_framework::add_checkbox("Visibility Check", &left, 1);
			mid_framework::add_checkbox("Knocked", &left, 1);
			mid_framework::add_checkbox("Sleeper", &left, 1);
			mid_framework::add_checkbox("NPC", &left, 1);
		//	mid_framework::add_slider_float("Render Distance", &sliderFloatLeft, 50.0f, 1000.0f, 1);


			mid_framework::add_label("Item Visuals", 2);
			mid_framework::add_checkbox("Wood", &left, 2);
			mid_framework::add_checkbox("Stone", &left, 2);
			mid_framework::add_checkbox("Sulfer", &left, 2);
			mid_framework::add_checkbox("Metal", &left, 2);
			mid_framework::add_checkbox("Hemp", &left, 2);
			mid_framework::add_checkbox("Food", &left, 2);
			mid_framework::add_checkbox("Pickables", &left, 2);
			mid_framework::add_checkbox("Berrys", &left, 2);
			mid_framework::add_checkbox("Horses", &left, 2);
			mid_framework::add_checkbox("Wolfs", &left, 2);
			mid_framework::add_checkbox("Bears", &left, 2);
			mid_framework::add_checkbox("Deer", &left, 2);
			mid_framework::add_checkbox("Creates", &left, 2);
			mid_framework::add_slider_float("Render Distance", &sliderFloatLeft, 50.0f, 1000.0f, 2);






		}
		else if (mid_framework::selected == 1)
		{
			mid_framework::add_child(1);
		}
		else if (mid_framework::selected == 2)
		{
			mid_framework::add_child(1);
		}
		else if (mid_framework::selected == 3)
		{
			mid_framework::add_child(2);
		}
		else if (mid_framework::selected == 4)
		{
			mid_framework::add_child(1);
		}
		mid_framework::end();

		functions::outline(Vector4(10, 10, 150, 20), xorstr_("cheat | private build"), Vector4(0, 0, 0, 1));
		functions::label(Vector4(10, 10, 150, 20), xorstr_("cheat | private build"), Vector4(1, 1, 1, 1));

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