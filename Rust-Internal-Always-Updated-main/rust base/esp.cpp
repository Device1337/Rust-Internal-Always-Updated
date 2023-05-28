#include "esp.h"
#include "../rust base/utils/memory.hpp"
#include "../rust base/game/offsets.hpp"
#include <cmath>
#include "Glob.hpp"
#include "aimbot.h"


namespace esp
{
	uintptr_t shader;
	void do_chams(rust::BasePlayer* player, float vischamr, float vischamg, float vischamb, float nonchamr, float nonchamg, float nonchamb)
	{
		if(!variables::asset_bundle)
			variables::asset_bundle = functions::load_bundle_file("C:\\shitcoder\\assets.saph");

		auto multiMesh = player->get_model()->get_multimesh();
		auto ourmesh = variables::local_player->get_model()->get_multimesh();

		if (!multiMesh)
			return;

		auto renderers = functions::get2renderers(multiMesh);
		auto ourrenders = functions::get2renderers(ourmesh);

		if (!renderers)
			return;

		for (int i = 0; i < renderers->get_size(); i++)
		{
			auto renderer = renderers->get_value(i);
			
			if (!renderer)
				return;

			const auto material = functions::get_material(renderer);
			if (!material)
				return;

			if (!shader)
				shader = functions::load_asset(variables::asset_bundle, "flatshader.shader", il2cpp::type_object("UnityEngine", "Shader")); // there are two flatshader.shader and shader.shader

			if (functions::get_shader(material) == shader)
				return;

			functions::set_shader(material, shader);
            
            

            functions::set_color(material, "ColorBehind", {nonchamr, nonchamg, nonchamb, 60});
			functions::set_color(material, "ColorVisible", { vischamr, vischamg, vischamb, 60});   
		}
	}
    void render_box(rust::BasePlayer* player) {
        //for (int i = 0; i < variables::player_list.size(); i++) {
          //  auto player = variables::player_list[i];

            if (player == variables::local_player)
                return;

            auto bounds = get_bounds(player, 2.f);
            float box_width = bounds.right - bounds.left;
            float box_height = bounds.bottom - bounds.top;
            auto half = (bounds.right - bounds.left) / 2;
            Vector2 HeadPos;
            Vector2 NeckPos;
            Vector2 PelvisPos;
            Vector2 LegLPos;
            Vector2 LegRPos;
          
            auto distancea = Math::Calc3D_Dist(variables::local_position, player->get_model()->get_position());

            if (distancea > 200.0f)
                return;

            if (bounds.onscreen) {
                float resp, gesp, besp;
                resp = 0.0f;
                gesp = 1.0f;
                besp = 0.2f;

                if (player->get_model()->is_npc()) {
                    resp = 0.5f;
                    gesp = 0.2f;
                    besp = 0.0f;
                }
                if (player->is_knocked()) {
                    resp = 1.0f;
                    gesp = 0.0f;
                    besp = 0.0f;
                }

                if (player->is_sleeping()) {
                    resp = 0.4f;
                    gesp = 0.0f;
                    besp = 1.0f;
                }
                Vector3 vis = player->get_model()->get_position();
                if (player->is_visible(vis)) {
                    resp = 0.3f;
                    gesp = 0.2f;
                    besp = 0.9f;
                }
                functions::outline_box({
                  bounds.left - 1,
                  bounds.top - 1
                    }, {
                      box_width + 2,
                      box_height + 2
                    }, Vector4(resp, gesp, besp, 1), 1);
                functions::outline_box({
                  bounds.left,
                  bounds.top
                    }, {
                      box_width,
                      box_height
                    }, Vector4(1, 1, 1, 1), 1);

             
            }

            //	functions::set_timescale(12.0f);

        }
    void render_name(rust::BasePlayer* player) {
        //for (int i = 0; i < variables::player_list.size(); i++) {
          //  auto player = variables::player_list[i];

            if (player == variables::local_player)
                return;

            auto bounds = get_bounds(player, 2.f);
            float box_width = bounds.right - bounds.left;
            float box_height = bounds.bottom - bounds.top;
            auto half = (bounds.right - bounds.left) / 2;
            Vector2 HeadPos;
            Vector2 NeckPos;
            Vector2 PelvisPos;
            Vector2 LegLPos;
            Vector2 LegRPos;

            auto distancea = Math::Calc3D_Dist(variables::local_position, player->get_model()->get_position());

            if (distancea > 200.0f)
                return;

            if (bounds.onscreen) {
                float resp, gesp, besp;
                resp = 0.0f;
                gesp = 1.0f;
                besp = 0.2f;

                if (player->get_model()->is_npc()) {
                    resp = 0.5f;
                    gesp = 0.2f;
                    besp = 0.0f;
                }
                if (player->is_knocked()) {
                    resp = 1.0f;
                    gesp = 0.0f;
                    besp = 0.0f;
                }

                if (player->is_sleeping()) {
                    resp = 0.4f;
                    gesp = 0.0f;
                    besp = 1.0f;
                }
                Vector3 vis = player->get_model()->get_position();
                if (player->is_visible(vis)) {
                    resp = 0.3f;
                    gesp = 0.2f;
                    besp = 0.9f;
                }

                auto name = player->get_username();
                std::string wcs = functions::ws2s(name);
                functions::outline(Vector4{
                  bounds.left - 80.f, bounds.bottom + 5, 79.f + half * 2 + 80.f, 13
                    }, wcs, Vector4(resp, gesp, besp, 1), true, 10);
                functions::label(Vector4{
                  bounds.left - 80.f, bounds.bottom + 5, 79.f + half * 2 + 80.f, 13
                    }, wcs, {
                      1,
                      1,
                      1,
                      1
                    }, true, 10);
               

            }

            //	functions::set_timescale(12.0f);

        }
    void render_distance(rust::BasePlayer* player) {
       
       // for (int i = 0; i < variables::player_list.size(); i++) {
        //    auto player = variables::player_list[i];
           
            //auto Vbase = LI_MODULE(("GameAssembly.dll")).get<uintptr_t>(); //GetModuleHandleA(xorstr_("GameAssembly.dll"));

            //	functions::set_draw_color(Vector4(1, 1, 1, 1));

            //bool is_npc = false;
            //	if (model->is_npc())
            //	return;
            //	else
            //	is_npc = true;
            int espas;

            if (player == variables::local_player)
                return;

            auto bounds = get_bounds(player, 2.f);
            float box_width = bounds.right - bounds.left;
            float box_height = bounds.bottom - bounds.top;
            auto half = (bounds.right - bounds.left) / 2;
            Vector2 HeadPos;
            Vector2 NeckPos;
            Vector2 PelvisPos;
            Vector2 LegLPos;
            Vector2 LegRPos;

            auto distancea = Math::Calc3D_Dist(variables::local_position, player->get_model()->get_position());

            if (distancea > 200.0f)
                return;

            if (bounds.onscreen) {

                std::string playerdistance = "[ " + std::to_string(int(distancea)) + "m ]";

                functions::outline(Vector4{
                  bounds.left - 80.f, bounds.bottom + 25, 79.f + half * 2 + 80.f, 13
                    }, playerdistance, Vector4(0.5, 0, 1.2, 1), true, 10);
                functions::label(Vector4{
                  bounds.left - 80.f, bounds.bottom + 25, 79.f + half * 2 + 80.f, 13
                    }, playerdistance, {
                      1,
                      1,
                      1,
                      1
                    }, true, 10);

            }


       // }
    }   
    void render_Health(rust::BasePlayer* player) {
        //for (int i = 0; i < variables::player_list.size(); i++) {
         //   auto player = variables::player_list[i];

            //auto Vbase = LI_MODULE(("GameAssembly.dll")).get<uintptr_t>(); //GetModuleHandleA(xorstr_("GameAssembly.dll"));

            //	functions::set_draw_color(Vector4(1, 1, 1, 1));

            //bool is_npc = false;
            //	if (model->is_npc())
            //	return;
            //	else
            //	is_npc = true;
            int espas;

            if (player == variables::local_player)
                return;

            auto bounds = get_bounds(player, 2.f);
            float box_width = bounds.right - bounds.left;
            float box_height = bounds.bottom - bounds.top;
            auto half = (bounds.right - bounds.left) / 2;
            Vector2 HeadPos;
            Vector2 NeckPos;
            Vector2 PelvisPos;
            Vector2 LegLPos;
            Vector2 LegRPos;

            auto distancea = Math::Calc3D_Dist(variables::local_position, player->get_model()->get_position());

            if (distancea > 200.0f)
                return;

            if (bounds.onscreen) {

                auto health = Vector4(bounds.left - 4, bounds.top + (box_height - box_height * (player->get_health() / 100)), 5, box_height * (player->get_health() / 100));
                const auto health_bg = Vector4(bounds.left - 5, bounds.top, 7, box_height);

                functions::fill_box(health_bg, Vector4(1, 0, 0, 1));

                functions::fill_box(health, Vector4(0.2, 0.8, 0, 1));
            }
       // }
    }
    void render_weapon(rust::BasePlayer* player) {
        //for (int i = 0; i < variables::player_list.size(); i++) {
         //   auto player = variables::player_list[i];

            auto bounds = get_bounds(player, 2.f);
            float box_width = bounds.right - bounds.left;
            float box_height = bounds.bottom - bounds.top;
            auto half = (bounds.right - bounds.left) / 2;
            Vector2 HeadPos;
            Vector2 NeckPos;
            Vector2 PelvisPos;
            Vector2 LegLPos;
            Vector2 LegRPos;

            auto distancea = Math::Calc3D_Dist(variables::local_position, player->get_model()->get_position());

            if (distancea > 200.0f)
                return;

            if (bounds.onscreen) {

                std::string wName = functions::ws2s(player->get_held_item()->get_name());
                functions::outline(Vector4{
                  bounds.left - 80.f, bounds.top - 20, 79.f + half * 2 + 80.f, 13
                    }, wName, Vector4(0, 0.2, 1, 1), true, 10);
                functions::label(Vector4{
                  bounds.left - 80.f, bounds.top - 20, 79.f + half * 2 + 80.f, 13
                    }, wName, {
                      1,
                      1,
                      1,
                      1
                    }, true, 10);

            }

        }
    void render_aimbot(rust::BasePlayer* player, BoneList bone) {
        //for (int i = 0; i < variables::player_list.size(); i++) {
          //  auto player = variables::player_list[i];

            //auto Vbase = LI_MODULE(("GameAssembly.dll")).get<uintptr_t>(); //GetModuleHandleA(xorstr_("GameAssembly.dll"));

            //	functions::set_draw_color(Vector4(1, 1, 1, 1));

            //bool is_npc = false;
            //	if (model->is_npc())
            //	return;
            //	else
            //	is_npc = true;
        int espas;

        if (player == variables::local_player)
            return;

        //variables::local_player->get_movement()->fun();
        //variables::local_player->get_movement()->spiderman();

        auto bounds = get_bounds(player, 2.f);
        float box_width = bounds.right - bounds.left;
        float box_height = bounds.bottom - bounds.top;
        auto half = (bounds.right - bounds.left) / 2;
        Vector2 HeadPos;
        Vector2 NeckPos;
        Vector2 PelvisPos;
        Vector2 LegLPos;
        Vector2 LegRPos;
        //aimbot::getClosestBoneToCrosshair(player);
        //aimbot::getBestPlayerByFov();
        //aimbot::run();
        auto distancea = Math::Calc3D_Dist(variables::local_position, player->get_model()->get_position());

        if (distancea > 200.0f)
            return;

        if (bounds.onscreen) {
            if (functions::get_key(KeyCode::Mouse3)) {
                aimbot::run(bone);
                espas = 1;
            }
            else {
                espas = 0;
            }

            if (espas == 1) {
                functions::outline(Vector4(variables::screen_width / 2, variables::screen_height / 2 - 10, 150, 20), xorstr_("Locking on"), Vector4(0, 0.5, 1, 1));
                functions::label(Vector4(variables::screen_width / 2, variables::screen_height / 2 - 10, 150, 20), xorstr_("Locking on"), Vector4(1, 1, 1, 1));
            }
        }
    }
    void SafeAdmin() { variables::local_player->add_flag(4); }
    void NoRecoil() { variables::local_player->get_held_item()->Norecoil(0.0f); }
    void nosway() {
        variables::local_player->get_held_item()->set_aim_cone(-1.0f);
        variables::local_player->get_held_item()->set_aim_cone_curve_scale(-1.0f);
        variables::local_player->get_held_item()->set_aim_cone_penalty_max(-1.0f);
        variables::local_player->get_held_item()->set_aim_cone_penalty_per_shot(-1.0f);
        variables::local_player->get_held_item()->set_aim_sway(-1.0f);
        variables::local_player->get_held_item()->set_aim_sway_speed(-1.0f);
    }
    void instaEoka() {
        variables::local_player->get_held_item()->set_always_eoka(100.0f);
    }
    void FullAuto() { variables::local_player->get_held_item()->set_automatic(true); }
    void MoonJump() { variables::local_player->get_movement()->fun(); }
    void ShootWhileInAir() { variables::local_player->get_movement()->ShootInAir(); }
    void WalkOnWalter() { variables::local_player->get_movement()->Water(); }
    void ExterndMelee() { variables::local_player->get_held_item()->ExtMelee(); }
    void fastbow() { variables::local_player->get_held_item()->instabow(); }
    void instacharge() { variables::local_player->get_held_item()->instacharge(); }
    void longeye() { variables::local_player->get_eyes()->longeyes(); }
    void Dysnic() {
        std::string ServerTicks = " [ Ticks Per Second -> " + std::to_string(float(variables::local_player->get_lastSentTick()->TicksPerSec())) + " ]";

        functions::outline(Vector4(50 + 5, 75, 150, 20), ServerTicks, Vector4(0, 0, 0, 1));
        functions::label(Vector4(50 + 5, 75, 150, 20), ServerTicks, Vector4(1, 1, 1, 1));
        if (functions::get_key(KeyCode::Mouse2))
        {
            variables::local_player->get_lastSentTick()->SetTicks(0.99);

            std::string ServerTicks = " [ Ticks Per Second -> " + std::to_string(float(variables::local_player->get_lastSentTick()->TicksPerSec())) + " ]";
            functions::outline(Vector4(variables::screen_width / 2 + 5, variables::screen_height / 2, 150, 20), xorstr_("Dysnic"), Vector4(0, 0, 0, 1));
            functions::label(Vector4(variables::screen_width / 2 + 5, variables::screen_height / 2, 150, 20), xorstr_("Dysnic"), Vector4(1, 1, 1, 1));

        }
    }

}
   
    
