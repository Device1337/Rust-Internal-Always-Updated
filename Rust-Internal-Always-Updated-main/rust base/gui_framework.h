#pragma once
#include "includes.hpp"
#include "game/classes.hpp"

namespace mid_framework
{
	Vector2 cursor1;
	Vector2 cursor2;
	Vector2 resolution;
	Vector2 position;
	float x = 500, y = 500;
	int selected = 0;
	bool lmb = false;
	bool open = true;

	auto get_lmb() -> bool
	{
		static int delay = 0;

		if (functions::get_key_down(KeyCode::Mouse0) && delay <= 0)
		{
			delay = 25;
			return true;
		}

		delay--;

		return false;
	}

	auto get_ins() -> bool
	{
		static int delay = 0;

		if (functions::get_key_down(KeyCode::UpArrow) && delay <= 0)
		{
			delay = 25;
			return true;
		}

		delay--;

		return false;
	}

	auto is_hovering(Vector2 position, Vector2 size) -> bool
	{
		auto cursor = functions::get_mouse_pos();
		cursor.y = variables::screen_height - cursor.y;

		return cursor.x > position.x && cursor.x < position.x + size.x && cursor.y > position.y && cursor.y < position.y + size.y;
	}
	auto add_child(int num) -> void
	{
		if (!open)
			return;

		if (num > 2)
			num = 2;
		else if (num <= 0)
			num = 1;

		if (num == 1)
		{
			functions::outline_box({ position.x + 8, position.y + 74 }, { resolution.x - 17, resolution.y - 83 }, { 1, 1, 1, 1 }, 1.f);
		}
		else if (num == 2)
		{
			functions::outline_box({ position.x + 8, position.y + 74 }, { resolution.x - 334, resolution.y - 83 }, { 1, 1, 1, 1 }, 1.f);

			functions::outline_box({ position.x + 325, position.y + 74 }, { resolution.x - 334, resolution.y - 83 }, { 1, 1, 1, 1 }, 1.f);
		}
	}

	auto add_tab(std::string name, int index, int offset) -> void
	{
		if (!open)
			return;
		auto hovering = is_hovering({ position.x + 8 + (126 * index), position.y + 33 }, { 120, 35 });

		functions::fill_box({ position.x + 8 + (126 * index), position.y + 33, 120, 35 }, { 0, 0, 0, 1 });
		if (selected == index)
		{
			functions::fill_box({ position.x + 9 + (126 * index), position.y + 34, 118, 33 }, { 0.3, 0.3, 0.3, 1 });
		}
		else if (hovering)
		{
			functions::fill_box({ position.x + 9 + (126 * index), position.y + 34, 118, 33 }, { 0.1, 1, 0.1, 1 });
		}
		else
		{
			functions::fill_box({ position.x + 9 + (126 * index), position.y + 34, 118, 33 }, { 0.1, 0.1, 1, 1 });
		}

		if (hovering && lmb)
		{
			selected = index;
		}

		functions::label({ position.x + 8 + (126 * index), position.y + 33, 120, 35 }, name, { 1,1,1,1 }, true);
	}

	auto add_label(std::string text, int child) -> void
	{
		if (!open)
			return;

		Vector2 cursor;
		if (child == 1)
			cursor = cursor1;
		else if (child == 2)
			cursor = cursor2;

		functions::label({ cursor.x, cursor.y - 2, 150, 20 }, text, { 1,1,1,1 });

		if (child == 1)
			cursor1.y += 20;
		else if (child == 2)
			cursor2.y += 20;
	}

	auto add_checkbox(std::string name, bool* value, int child) -> void
	{
		if (!open)
			return;

		Vector2 cursor;
		if (child == 1)
			cursor = cursor1;
		else if (child == 2)
			cursor = cursor2;

		const auto hovered = is_hovering({ cursor.x - 3, cursor.y - 2 }, { 70, 14 + 3 });

		if (hovered)
		{
			functions::fill_box({ cursor.x, cursor.y + 1, 14, 14 }, { 0.329f, 0.329f, 0.329f, 1 });
		}


		functions::fill_box({ cursor.x, cursor.y, 14, 14 }, { 0.153f, 0.153f, 0.153f, 1 });

		if (*value)
		{
			functions::fill_box({ cursor.x, cursor.y, 14, 14 }, { 0.149f, 0.149f, 0.149f, 1 });
		}
		else
		{
			functions::fill_box({ cursor.x + 3, cursor.y + 3, 8, 8 }, { 0.667f, 0.667f, 0.667f, 1 });
		}

		functions::label({ cursor.x + 19, cursor.y - 2, 150, 20 }, name, { 1,1,1,1 });

		if (hovered && lmb)
		{
			*value = !*value;
		}

		if(child == 1)
			cursor1.y += 20;
		else if(child == 2)
			cursor2.y += 20;
	}

	auto add_combo(std::vector<std::string> list, int* selected, int child) -> void
	{
		if (!open)
			return;

		Vector2 cursor;
		if (child == 1)
			cursor = cursor1;
		else if (child == 2)
			cursor = cursor2;

		const auto left_hovered = is_hovering({ cursor.x, cursor.y }, { 18, 18 });
		const auto middle_hovered = is_hovering({ cursor.x + 20, cursor.y }, { 120, 19 });
		const auto right_hovered = is_hovering({ cursor.x + 141, cursor.y }, { 19, 19 });

		functions::fill_box({ cursor.x, cursor.y, 19, 19 }, left_hovered
			? Vector4(0.325f, 0.325f, 0.325f, 1) :
			Vector4(0.215f, 0.215f, 0.215f, 1));
		

		functions::fill_box({ cursor.x + 20, cursor.y, 120, 19 }, middle_hovered
			? Vector4(0.325f, 0.325f, 0.325f, 1) :
			Vector4(0.215f, 0.215f, 0.215f, 1));
		

		functions::fill_box({ cursor.x + 141, cursor.y, 19, 19 }, right_hovered 
			? Vector4( 0.325f, 0.325f, 0.325f, 1 )
			: Vector4(0.215f, 0.215f, 0.215f, 1 ));

		functions::label({ cursor.x + 6, cursor.y - 3, 150, 20 }, xorstr_("-"), { 1, 1, 1, 1 }, false, 16);
		functions::label({ cursor.x + 20, cursor.y - 1, 120, 19 }, list[*selected], { 1, 1, 1, 1 }, true, 14);
		functions::label({ cursor.x + 146, cursor.y - 2, 150, 20 }, xorstr_("+"), { 1, 1, 1, 1 }, false, 16);

		if (*selected > 0 && left_hovered && lmb)
		{
			--* selected;
		}
		else if (*selected < list.size() - 1 && right_hovered && lmb)
		{
			++* selected;
		}
		else if (middle_hovered && lmb)
		{
			*selected = 0;
		}

		if (child == 1)
			cursor1.y += 25;
		else if (child == 2)
			cursor2.y += 25;
	}

	auto add_slider_float(std::string name, float* value, float min, float max, int child) -> void
	{
		if (!open)
			return;

		Vector2 cursor;
		if (child == 1)
			cursor = cursor1;
		else if (child == 2)
			cursor = cursor2;

		const auto hovered = is_hovering({ cursor.x - 3, cursor.y + 7 }, { 310, 24 });
		const static auto max_width = 293;

		if (hovered)
		{
			functions::fill_box({ cursor.x, cursor.y + 19 - 4, max_width, 3 }, { 0.254f, 0.254f, 0.254f, 1 });
		}
		else
		{
			functions::fill_box({ cursor.x, cursor.y + 19 - 4, max_width, 3 }, { 0.196f, 0.196f, 0.196f, 1 });
		}

		if (hovered && functions::get_key(KeyCode::Mouse0))
		{
			const auto mouse_x = static_cast<float>(functions::get_mouse_pos().x);

			*value = ((mouse_x - cursor.x) / max_width * max);
		}

		if (*value > max)
		{
			*value = max;
		}
		else if (*value < min)
		{
			*value = min;
		}

		functions::fill_box({ cursor.x, cursor.y + 19 - 4, (*value * max_width) / max, 2 }, { 0.705f, 0.705f, 0.705f, 1 });

		functions::label({ cursor.x, cursor.y - 4, 150, 20 }, name, { 1, 1, 1, 1 });
		functions::label({ cursor.x + max_width - 15, cursor.y - 4, 150, 20 }, std::to_string(static_cast<std::int32_t>(*value)).c_str(), { 1, 1, 1, 1 }, false);

		if (child == 1)
			cursor1.y += 21;
		else if (child == 2)
			cursor2.y += 21;
	}

	auto add_slider_int(std::string name, int* value, int min, int max, int child) -> void
	{
		if (!open)
			return;

		Vector2 cursor;
		if (child == 1)
			cursor = cursor1;
		else if (child == 2)
			cursor = cursor2;

		const auto hovered = is_hovering({ cursor.x - 3, cursor.y + 7 }, { 310, 24 });
		const static auto max_width = 293;

		if (hovered)
		{
			functions::fill_box({ cursor.x, cursor.y + 19 - 4, max_width, 3 }, { 0.254f, 0.254f, 0.254f, 1 });
		}
		else
		{
			functions::fill_box({ cursor.x, cursor.y + 19 - 4, max_width, 3 }, { 0.196f, 0.196f, 0.196f, 1 });
		}

		if (hovered && functions::get_key(KeyCode::Mouse0))
		{
			const auto mouse_x = static_cast<float>(functions::get_mouse_pos().x);

			*value = ((mouse_x - cursor.x) / max_width * max);
		}

		if (*value > max)
		{
			*value = max;
		}
		else if (*value < min)
		{
			*value = min;
		}

		functions::fill_box({ cursor.x, cursor.y + 19 - 4, (float)(*value * max_width / max), 2}, {0.705f, 0.705f, 0.705f, 1});

		functions::label({ cursor.x, cursor.y - 4, 150, 20 }, name, { 1, 1, 1, 1 });
		functions::label({ cursor.x + max_width - 15, cursor.y - 4, 150, 20 }, std::to_string(static_cast<std::int32_t>(*value)).c_str(), { 1, 1, 1, 1 }, false);

		if (child == 1)
			cursor1.y += 21;
		else if (child == 2)
			cursor2.y += 21;
	}



	auto begin(std::string cheat_name) -> void
	{
		if (!open)
			return;
		if (functions::get_key(KeyCode::Mouse0) && is_hovering(position, { resolution.x, 25 }))
		{
			auto cursor = functions::get_mouse_pos();
			cursor.y = variables::screen_height - cursor.y;

			x = cursor.x - (resolution.x / 2);
			y = cursor.y - (12.5);
		}



		functions::fill_box({ position.x, position.y, resolution.x, resolution.y }, { 0.1, 0.1, 0.1, 1 });
		functions::fill_box({ position.x + 2, position.y + 2, resolution.x - 4, resolution.y - 4 }, { 0.060f, 0.060f, 0.060f, 1 });

		functions::fill_box({ position.x, position.y, resolution.x, 26 }, { 0.030f, 0.030f, 0.030f, 1 });
		functions::fill_box({ position.x, position.y, resolution.x, 25 }, { 0.0f, 0.0f, 0.0f, 1 });

		functions::label({ position.x + 10, position.y + 3, 150, 20 }, cheat_name, { 1,1,1,1 });

	}

	auto end() -> void
	{
		if (get_ins())
			open = !open;
		lmb = get_lmb();
		resolution = { 640, 440 };
		position = { x, y };
		cursor1 = { position.x + 15, position.y + 81 };
		cursor2 = { position.x + 332, position.y + 81 };
	}
}