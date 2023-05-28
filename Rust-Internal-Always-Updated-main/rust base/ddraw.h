#pragma once


namespace ddraw
{

	inline void ongui_hook(void* instance)
	{
		auto current_event = functions::get_current();
		auto EventType = functions::get_event_type(current_event);
		if (EventType != EventType::Repaint)
			return;

	}
}