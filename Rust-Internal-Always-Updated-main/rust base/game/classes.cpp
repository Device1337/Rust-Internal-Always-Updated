#include "classes.hpp"
#include <cmath>
#include "il2cpp.hpp"
#include "offsets.hpp"
#include "../utils/memory.hpp"
#include "../utils/returnspoofer.hpp"

auto gameAssembly = LI_MODULE(("GameAssembly.dll")).get<uintptr_t>(); //GetModuleHandleA(xorstr_("GameAssembly.dll"));

#define ProcAddr(func) GetProcAddress((HMODULE)gameAssembly, func)

template<typename T, typename... Args>
inline T call(const char* func, Args... args) {
	return reinterpret_cast<T(__fastcall*)(Args...)>(ProcAddr(func))(args...);
}

static auto getMainCamera = reinterpret_cast<uintptr_t(*)()>(il2cpp::methods::resolve_icall(xorstr_("UnityEngine.Camera::get_main()")));

void functions::setup_bullet_data()
{

}

bool is_valid(uintptr_t entity)
{
	if (!entity)
	{
		return false;
	}

	return true;
}

il2cpp::il2cppstring* il2cpp::il2cppstring::New(const char* str)
{
	//return call<il2cpp::il2cppstring*, const char*>(xorstr_("il2cpp_string_new"), str);
	return SpoofReturn(il2cpp::methods::new_string, str);
}

namespace variables
{
	uintptr_t asset_bundle = NULL;
	rust::BasePlayer* local_player = nullptr;
	Vector3				local_position = Vector3();
	Matrix4x4			view_matrix = Matrix4x4();
	int					screen_width = 1920;
	int					screen_height = 1080;
	int					image_width = 0;
	int					image_height = 0;
	Vector2				mouse_position = Vector2();
	Vector2				mouse_position_backup = Vector2();
	bool				loaded = true;
	uintptr_t			draw_label = NULL;
	uintptr_t			white_texture = NULL;
	uintptr_t			camera_list = NULL;
	uintptr_t			client_entities = NULL; 
	uintptr_t			debug_camera_address = NULL;
	std::vector<rust::BasePlayer*> player_list;
	float				fly_hack_vert = 0.f;
	float				fly_hack_vert_max = 0.f;
	float				fly_hack_hori = 0.f;
	float				fly_hack_hori_max = 0.f;
}

namespace funcs1
{
	void function1();
}

namespace functions
{
	int my_memcmp(const void* str1, const void* str2, size_t count)
	{
		const unsigned char* s1 = (const unsigned char*)str1;
		const unsigned char* s2 = (const unsigned char*)str2;

		while (count-- > 0)
		{
			if (*s1++ != *s2++)
				return s1[-1] < s2[-1] ? -1 : 1;
		}
		return 0;
	}

	int strCmp(const char* s1, const char* s2)
	{
		std::hash<std::string_view> char_hash;
		auto class_crc = char_hash(s1);
		auto object_crc = char_hash(s2);
		if (class_crc == object_crc)
			return 0;
		else
			return 1;
	}

	size_t my_strlen(const char* str)
	{
		const char* s;

		for (s = str; *s; ++s)
			;
		return (s - str);
	}

	char* memstr(char* haystack, const char* needle, int size)
	{
		char* p;
		char needlesize = my_strlen(needle);
		for (p = haystack; p <= (haystack - needlesize + size); p++) {
			if (memcmp(p, needle, needlesize) == 0)
			{
				//std::cout << "[" << __FUNCTION__ << "] Returning: " << p << std::endl;
				return p;
			}
		}
		return NULL;
	}

	std::string ws2s(const std::wstring& wstr)
	{
		std::string str(wstr.begin(), wstr.end());
		return str;
	}

	std::wstring s2ws(const std::string& str)
	{
		int size_needed = MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), NULL, 0);
		std::wstring wstrTo(size_needed, 0);
		MultiByteToWideChar(CP_UTF8, 0, &str[0], (int)str.size(), &wstrTo[0], size_needed);
		return wstrTo;
	}

	std::wstring read_unicode(uint64_t address, std::size_t size)
	{
		const auto buffer = std::make_unique<wchar_t[]>(size);
		memcpy(buffer.get(), reinterpret_cast<const void*>(address), size * 2); //Try Rusts memcpy. public static class UnsafeUtility::MemCpy(void* destination, void* source, long size)
		return std::wstring(buffer.get());
	}

	std::string read_ascii(uint64_t address, std::size_t size)
	{
		return std::string(reinterpret_cast<const char*>(address));
	}

	const char* read_ascii_alt(uint64_t address)
	{
		return reinterpret_cast<const char*>(address);
	}

	bool WorldToScreen(const Vector3& EntityPos, Vector2& ScreenPos)
	{
		if (true)
		{
			Vector3 TransVec = Vector3(variables::view_matrix._14, variables::view_matrix._24, variables::view_matrix._34);
			Vector3 RightVec = Vector3(variables::view_matrix._11, variables::view_matrix._21, variables::view_matrix._31);
			Vector3 UpVec = Vector3(variables::view_matrix._12, variables::view_matrix._22, variables::view_matrix._32);
			float w = Math::Dot(TransVec, EntityPos) + variables::view_matrix._44;
			if (w < 0.098f) return false;
			float y = Math::Dot(UpVec, EntityPos) + variables::view_matrix._42;
			float x = Math::Dot(RightVec, EntityPos) + variables::view_matrix._41;
			ScreenPos = Vector2((variables::screen_width / 2) * (1.f + x / w), (variables::screen_height / 2) * (1.f - y / w));
			return true;
		}
		else
		{
			return false;
		}
	}

	laddy_list<uintptr_t>* get2renderers(uintptr_t multimesh)
	{
		uintptr_t method = il2cpp::method(xorstr_("SkinnedMultiMesh"), xorstr_("get_Renderers"), 0);
		if (!(method))
		{
			return NULL;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return NULL;
		}

		auto get_renderers = reinterpret_cast<laddy_list<uintptr_t>*(*)(uintptr_t)>(method_ptr);
		return SpoofReturn(get_renderers, multimesh);

	}

	uintptr_t get_material(uintptr_t renderer)
	{
		uintptr_t method = offsets::get_material; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return NULL;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return NULL;
		}

		auto get_material = reinterpret_cast<uintptr_t(*)(uintptr_t)>(method_ptr);
		return SpoofReturn(get_material, renderer);
	}

	uintptr_t get_shader(uintptr_t material)
	{
		uintptr_t method = offsets::get_shader; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return NULL;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return NULL;
		}

		auto get_shader = reinterpret_cast<uintptr_t(*)(uintptr_t)>(method_ptr);
		return SpoofReturn(get_shader, material);
	}

	uintptr_t load_asset(uintptr_t assetbundle, std::string shader, uintptr_t typeobject)
	{
		uintptr_t method = il2cpp::method(xorstr_("AssetBundle"), xorstr_("LoadAsset_Internal"), 2, xorstr_("UnityEngine"));; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return NULL;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return NULL;
		}

		auto load_asset = reinterpret_cast<uintptr_t(*)(uintptr_t, il2cpp::il2cppstring*, uintptr_t)>(method_ptr);
		return SpoofReturn(load_asset, assetbundle, il2cpp::il2cppstring::New(shader.c_str()), typeobject);
	}

	uintptr_t load_bundle_file(std::string data)
	{
		uintptr_t method = il2cpp::method(xorstr_("AssetBundle"), xorstr_("LoadFromFile_Internal"), 3, xorstr_("UnityEngine")); //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return NULL;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return NULL;
		}

		auto bundle = reinterpret_cast<uintptr_t(*)(il2cpp::il2cppstring*, std::uint32_t, std::uint64_t)>(method_ptr);
		return SpoofReturn(bundle, il2cpp::il2cppstring::New(data.c_str()), std::uint32_t(0), std::uint64_t(0));
	}

	uintptr_t find(const char* shader)
	{
		uintptr_t method = offsets::find; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return NULL;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return NULL;
		}

		auto get_shader = reinterpret_cast<uintptr_t(*)(il2cpp::il2cppstring * shader)>(method_ptr);
		return SpoofReturn(get_shader, il2cpp::il2cppstring::New(shader));
	}

	void set_shader(uintptr_t material, uintptr_t shader)
	{
		uintptr_t method = offsets::set_shader; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("Engine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto set_color = reinterpret_cast<void(*)(uintptr_t material, uintptr_t shader)>(method_ptr);
		SpoofReturn(set_color, material, shader);
	}

	void set_color(uintptr_t material, const char* name, Vector4 color)
	{
		uintptr_t method = offsets::set_color; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto set_color = reinterpret_cast<void(*)(uintptr_t material, il2cpp::il2cppstring * name, Vector4 color)>(method_ptr);

		SpoofReturn(set_color, material, il2cpp::il2cppstring::New(name), color);
	}

	void set_material_int(uintptr_t material, const char* name, int value)
	{
		uintptr_t method = offsets::set_int; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto set_color = reinterpret_cast<void(*)(uintptr_t material, il2cpp::il2cppstring * name, int value)>(method_ptr);

		SpoofReturn(set_color, material, il2cpp::il2cppstring::New(name), value);
	}

	Vector3 WorldToScreenAlt(Vector3 position)
	{
		Vector3 out;

		return out;
	}

	uintptr_t scan_for_camera_list()
	{
		const auto base = LI_MODULE(("UnityPlayer.dll")).get<uintptr_t>(); //reinterpret_cast<uint64_t>(GetModuleHandle(xorstr_("UnityPlayer.dll")));

		if (!base)
			return NULL;

		const auto dos_header = reinterpret_cast<IMAGE_DOS_HEADER*>(base);
		const auto nt_header = reinterpret_cast<IMAGE_NT_HEADERS64*>(base + dos_header->e_lfanew);

		uint64_t data_base;
		uint64_t data_size;

		for (int i = 0;;)
		{
			const auto section = reinterpret_cast<IMAGE_SECTION_HEADER*>(
				base + dos_header->e_lfanew + // nt_header base
				sizeof(IMAGE_NT_HEADERS64) +  // start of section headers
				(i * sizeof(IMAGE_SECTION_HEADER))); // section header at our index

			//std::cout << "[" << __FUNCTION__ << "] Section Name: " << (char*)section->Name << std::endl;

			if (strCmp((char*)section->Name, xorstr_(".data")) == 0)
			{
				data_base = section->VirtualAddress + base;
				data_size = section->SizeOfRawData;
				break;
			}

			i++;

			if (i >= nt_header->FileHeader.NumberOfSections)
			{
				//std::cout << "[" << __FUNCTION__ << "] Section not found" << std::endl;
				//DEBUG("[!] Section not found\n"));
				return NULL;
			}
		}

		uint64_t camera_table = 0;

		const auto camera_string = memstr((char*)data_base, xorstr_("AllCameras"), data_size);

		for (auto walker = (uint64_t*)camera_string; walker > (uint64_t*)0; walker -= 1)
		{
			if (*walker > 0x100000 && *walker < 0xF00000000000000)
			{
				// [[[[unityplayer.dll + ctable offset]]] + 0x30] = Camera
				//std::cout << "[" << __FUNCTION__ << "] camera_table found" << std::endl;
				camera_table = *walker;
				break;
			}
		}

		if (camera_table)
		{
			//std::cout << "[" << __FUNCTION__ << "] Returning Camera Table: " << camera_table << std::endl;
			return camera_table;
		}

		//DEBUG("[!] Unable to locate camera\n"));
		return NULL;
	}

	bool update_view_matrix()
	{
		static uintptr_t maincam; //variables::camera_list; //scan_for_camera_list();
		if (!maincam)
		{
			maincam = getMainCamera();
			//std::cout << "[" << __FUNCTION__ << "] !camera_list" << std::endl;
			return false;
		}

		//uintptr_t camera_table = *reinterpret_cast<uintptr_t*>(camera_list);
		//if (!camera_table)
		//{
		//	//std::cout << "[" << __FUNCTION__ << "] !object_list" << std::endl;
		//	return false;
		//}

		uintptr_t camera = *reinterpret_cast<uintptr_t*>(maincam + 0x10);
		if (!camera)
		{
			//std::cout << "[" << __FUNCTION__ << "] !object_list" << std::endl;
			return false;
		}

		variables::view_matrix = *reinterpret_cast<Matrix4x4*>(camera + 0x2E4);
		return true;
	}

	Vector3 get_camera_pos()
	{
		auto camera_list = variables::camera_list; //scan_for_camera_list();
		if (!(camera_list))
		{
			return Vector3();
		}

		uintptr_t camera_table = *reinterpret_cast<uintptr_t*>(camera_list);
		if (!(camera_table))
		{
			return Vector3();
		}

		uintptr_t camera = *reinterpret_cast<uintptr_t*>(camera_table);
		if (!(camera))
		{
			return Vector3();
		}

		return *reinterpret_cast<Vector3*>(camera + 0x42C);
	}

	Vector3 get_mouse_pos()
	{
		uintptr_t method = offsets::get_mousePosition;
		if (!(method))
		{
			return Vector3();
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return Vector3();
		}

		auto get_mousePosition = reinterpret_cast<Vector3(*)()>(method_ptr);
		return get_mousePosition();
	}

	int get_screen_width()
	{
		uintptr_t method = offsets::screen_get_width;
		if (!(method))
		{
			return int();
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return int();
		}

		auto get_screen_position = reinterpret_cast<int(*)()>(method_ptr);
		return SpoofReturn(get_screen_position);
	}

	int get_screen_height()
	{
		uintptr_t method = offsets::screen_get_height;
		if (!(method))
		{
			return int();
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return int();
		}

		auto get_screen_position = reinterpret_cast<int(*)()>(method_ptr);
		return SpoofReturn(get_screen_position);
	}

	void ignore_layer_collision(layer the_layer, layer ignore_layer, bool should_collide)
	{
		uintptr_t method = offsets::ignore_layer_collision;
		if (!(method))
		{
			return;
		}

		auto ignore_layer_func = reinterpret_cast<void(*)(layer, layer, bool)>(method);
		SpoofReturn(ignore_layer_func, the_layer, ignore_layer, should_collide);
	}

	bool get_key_down(KeyCode key)
	{
		uintptr_t method = offsets::input_get_key_down;
		if (!(method))
		{
			return false;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return false;
		}

		auto get_keydown = reinterpret_cast<bool(*)(KeyCode)>(method_ptr);
		return SpoofReturn(get_keydown, key);
	}

	bool get_key_up(KeyCode key)
	{
		uintptr_t method = offsets::input_get_key_up; //il2cpp::method(xorstr_("Input"), xorstr_("GetKeyUp"), 1, xorstr_("UnityEngine"));
		if (!(method))
		{
			return false;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return false;
		}

		auto get_keydown = reinterpret_cast<bool(*)(KeyCode)>(method_ptr);
		return SpoofReturn(get_keydown, key);
	}

	bool get_key(KeyCode key)
	{
		uintptr_t method = offsets::input_get_key; //il2cpp::method(xorstr_("Input"), xorstr_("GetKey"), 1, xorstr_("UnityEngine"));
		if (!(method))
		{
			return false;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return false;
		}

		auto get_keydown = reinterpret_cast<bool(*)(KeyCode)>(method_ptr);
		return SpoofReturn(get_keydown, key);
	}

	bool line_of_sight(Vector3 start, Vector3 end, Layers layer_mask, float padding)
	{
		uintptr_t method = offsets::gamephysics_line_of_site; //il2cpp::method(xorstr_("GamePhysics"), xorstr_("LineOfSight"), 4);
		if (!(method))
		{
			return false;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return false;
		}

		auto get_line_of_sight = reinterpret_cast<bool(*)(Vector3, Vector3, Layers, float)>(method_ptr);
		return SpoofReturn(get_line_of_sight, start, end, layer_mask, padding);
	}

	bool is_visible(Vector3 start, Vector3 end)
	{
		auto layer = (int)Layers::ProjectileLineOfSightCheck | (int)Layers::Terrain;

		return line_of_sight(start, end, Layers(layer), 0);
	}

	float clamp(float value, float min, float max)
	{
		uintptr_t method = offsets::mathf_clamp; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return false;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return false;
		}

		auto clamp = reinterpret_cast<float(*)(float, float, float)>(method_ptr);
		return SpoofReturn(clamp, value, min, max);
	}

	float mathf_atan2(float y, float x)
	{
		uintptr_t method = offsets::mathf_atan2; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			std::cout << "ma2 method false!" << std::endl;
			return 0.f;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			std::cout << "ma2 method_ptr false!" << std::endl;
			return 0.f;
		}

		auto atan2 = reinterpret_cast<float(*)(float, float)>(method_ptr);
		return SpoofReturn(atan2, y, x);
	}

	float mathf_max(float a, float b)
	{
		uintptr_t method = offsets::mathf_max; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			std::cout << "mmax method false!" << std::endl;
			return 0.f;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			std::cout << "mmax method_ptr false!" << std::endl;
			return 0.f;
		}

		auto atan2 = reinterpret_cast<float(*)(float, float)>(method_ptr);
		return SpoofReturn(atan2, a, b);
	}

	float mathf_abs(float f)
	{
		uintptr_t method = offsets::mathf_abs; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			std::cout << "mabs method false!" << std::endl;
			return 0.f;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			std::cout << "mabs method_ptr false!" << std::endl;
			return 0.f;
		}

		auto atan2 = reinterpret_cast<float(*)(float)>(method_ptr);
		return SpoofReturn(atan2, f);
	}

	uintptr_t get_current()
	{
		uintptr_t method = offsets::event_get_current; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return NULL;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return NULL;
		}

		auto get_current = reinterpret_cast<uintptr_t(*)()>(method_ptr);
		return SpoofReturn(get_current);
	}

	EventType get_event_type(uintptr_t current)
	{
		uintptr_t method = offsets::event_get_type; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return EventType::Ignore;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return EventType::Ignore;
		}

		auto get_type = reinterpret_cast<EventType(*)(uintptr_t)>(method_ptr);
		return SpoofReturn(get_type, current);
	}

	uintptr_t get_draw_skin()
	{
		uintptr_t method = offsets::gui_get_skin; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return false;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return false;
		}

		auto get_skin = reinterpret_cast<uintptr_t(*)()>(method_ptr);
		return SpoofReturn(get_skin);
	}

	uintptr_t get_white_texture()
	{
		uintptr_t method = offsets::texture2d_get_whitetexture; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return false;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return false;
		}

		auto get_whiteTexture = reinterpret_cast<uintptr_t(*)()>(method_ptr);
		return SpoofReturn(get_whiteTexture);
	}

	uintptr_t get_guicontent_temp(il2cpp::il2cppstring* content)
	{
		uintptr_t method = offsets::guicontent_temp;
		if (!(method))
		{
			return NULL;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return NULL;
		}

		auto temp = reinterpret_cast<uintptr_t(*)(il2cpp::il2cppstring * content)>(method_ptr);
		return SpoofReturn(temp, content);
	}

	void set_draw_font_size(uintptr_t label, int size)
	{
		uintptr_t method = offsets::guistyle_set_fontsize; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto set_fontSize = reinterpret_cast<void(*)(uintptr_t label, int size)>(method_ptr);
		SpoofReturn(set_fontSize, label, size);
	}

	void set_draw_color(Vector4 color)
	{
		uintptr_t method = offsets::gui_set_color; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto set_color = reinterpret_cast<void(*)(Vector4 color)>(method_ptr);
		SpoofReturn(set_color, color);
	}

	void set_draw_alignment(uintptr_t label, uintptr_t value)
	{
		uintptr_t method = offsets::guistyle_set_alignment; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto set_alignment = reinterpret_cast<void(*)(uintptr_t label, uintptr_t value)>(method_ptr);
		SpoofReturn(set_alignment, label, value);
	}

	void set_cursor_lockstate(int value)
	{
		uintptr_t method = offsets::cursor_set_lockState; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto set_lockState = reinterpret_cast<void(*)(int)>(method_ptr);
		SpoofReturn(set_lockState, value);
	}

	void draw_texture(Vector4 position, uintptr_t texture)
	{
		uintptr_t method = offsets::gui_drawtexture; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto DrawTexture = reinterpret_cast<void(*)(Vector4 position, uintptr_t texture)>(method_ptr);
		SpoofReturn(DrawTexture, position, texture);
	}
	void draw_texture2(Vector2 position, uintptr_t texture)
	{
		uintptr_t method = offsets::gui_drawtexture; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto DrawTexture = reinterpret_cast<void(*)(Vector2 position, uintptr_t texture)>(method_ptr);
		SpoofReturn(DrawTexture, position, texture);
	}

	void outline_box(Vector2 position, Vector2 size, Vector4 color, float girth)
	{
		if (!variables::white_texture)
			variables::white_texture = get_white_texture();

		set_draw_color(color);

		draw_texture(Vector4(position.x, position.y, girth, size.y), variables::white_texture);
		draw_texture(Vector4(position.x + size.x, position.y, girth, size.y + 1), variables::white_texture);
		draw_texture(Vector4(position.x, position.y, size.x, girth), variables::white_texture);
		draw_texture(Vector4(position.x, position.y + size.y, size.x, girth), variables::white_texture);
	}

	void fill_box(Vector4 position, Vector4 color)
	{
		if (!variables::white_texture)
			variables::white_texture = get_white_texture();
		set_draw_color(color);
		draw_texture(position, variables::white_texture);
	}
	void fill_box2(Vector2 position, Vector4 color)
	{
		if (!variables::white_texture)
			variables::white_texture = get_white_texture();
		set_draw_color(color);
		draw_texture2(position, variables::white_texture);
	}

	void line(Vector2 point1, Vector2 point2, Vector4 color)
	{
		set_draw_color(color);
		if (point1.x - point2.x < 1)
			draw_texture(Vector4(point1.x, point1.y, point1.x - point2.x, 1), variables::white_texture);
		else
			draw_texture(Vector4(point1.x, point1.y, 1, point1.y - point2.y), variables::white_texture);
	}

	void label(Vector4 position, std::string text, Vector4 color, bool centered, float font_size)
	{
		set_draw_color(color);

		set_draw_font_size(variables::draw_label, font_size);

		if (centered)
			set_draw_alignment(variables::draw_label, 0x4);
		else
			set_draw_alignment(variables::draw_label, 0x0);

		uintptr_t method = offsets::gui_label;//LI_MODULE_SAFE_("GameAssembly.dll") + 0x1A61F60; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto Label = reinterpret_cast<void(*)(Vector4 position, il2cpp::il2cppstring*)>(method_ptr);
		SpoofReturn(Label, position, il2cpp::il2cppstring::New(text.c_str()));
	}

	void outline(Vector4 position, std::string text, Vector4 color, bool centered, float font_size)
	{
		label({ position.x - 1, position.y - 1, position.z, position.w }, text, color, centered, font_size);
		label({ position.x + 1, position.y + 1, position.z, position.w }, text, color, centered, font_size);
		label({ position.x - 1, position.y + 1, position.z, position.w }, text, color, centered, font_size);
		label({ position.x + 1, position.y - 1, position.z, position.w }, text, color, centered, font_size);
	}

	void xddraw_line(Vector2 start, Vector2 to, Vector4 color)
	{
		set_draw_color(color);

		uintptr_t method = offsets::vector2_signed_angle; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto SignedAngle = reinterpret_cast<float(*)(Vector2, Vector2)>(method_ptr);
		float signed_angle = SpoofReturn(SignedAngle, start, to);

		method = offsets::guiutility_rotatearoundpivot; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto RotateAroundPivot = reinterpret_cast<void(*)(float, Vector2)>(method_ptr);
		SpoofReturn(RotateAroundPivot, signed_angle, start);
		outline_box(start, Vector2(1, 0) * (start - to).magnitude(), color);
		SpoofReturn(RotateAroundPivot, -signed_angle, start);

	}

	void ddraw_line(Vector3 start, Vector3 end, Vector4 color, float duration, bool distanceFade, bool ztest)
	{
		uintptr_t method = offsets::ddraw_line; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto line = reinterpret_cast<void(*)(Vector3, Vector3, Vector4, float, bool, bool)>(method_ptr);
		SpoofReturn(line, start, end, color, duration, distanceFade, ztest);
	}

	void ddraw_arrow(Vector3 start, Vector3 end, float size, Vector4 color, float duration)
	{
		uintptr_t method = offsets::ddraw_arrow; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto arrow = reinterpret_cast<void(*)(Vector3, Vector3, float, Vector4, float)>(method_ptr);
		SpoofReturn(arrow, start, end, size, color, duration);
	}

	void ddraw_text(il2cpp::il2cppstring* text, Vector3 pos, Vector4 color, float duration)
	{
		uintptr_t method = offsets::ddraw_text; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto drawtext = reinterpret_cast<void(*)(il2cpp::il2cppstring*, Vector3, Vector4, float)>(method_ptr);
		SpoofReturn(drawtext, text, pos, color, duration);
	}

	void ddraw_screentext(il2cpp::il2cppstring* text, float x, Vector4 color, float duration)
	{
		uintptr_t method = offsets::ddraw_screentext; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto drawscreentext = reinterpret_cast<void(*)(il2cpp::il2cppstring*, float, Vector4, float)>(method_ptr);
		SpoofReturn(drawscreentext, text, x, color, duration);
	}

	void ddraw_get()
	{
		uintptr_t method = offsets::ddraw_get; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto Get = reinterpret_cast<void(*)()>(method_ptr);
		SpoofReturn(Get);
	}

	float getprojectilevelocityscale(uintptr_t base_projectile, bool max)
	{
		uintptr_t method = offsets::baseprojectile_getprojectilevelocityscale; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return 0.f;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return 0.f;
		}

		auto GetProjectileVelocityScale = reinterpret_cast<float(*)(uintptr_t, bool)>(method_ptr);
		GetProjectileVelocityScale(base_projectile, max);
	}

	void create(uintptr_t self, const char* shader)
	{
		uintptr_t method = offsets::create;
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto create = reinterpret_cast<void(*)(uintptr_t self, il2cpp::il2cppstring * shader)>(method_ptr);
		SpoofReturn(create, self, il2cpp::il2cppstring::New(shader));
	}

	void add_component(uintptr_t self, uintptr_t componentType)
	{
		uintptr_t method = offsets::add_component;
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto add_component = reinterpret_cast<void(*)(uintptr_t self, uintptr_t componentType)>(method_ptr);
		SpoofReturn(add_component, self, componentType);
	}



	void dont_destroy_on_load(uintptr_t target)
	{
		uintptr_t method = offsets::dont_destroy_on_load;
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto dont_destroy_on_load = reinterpret_cast<void(*)(uintptr_t target)>(method_ptr);
		SpoofReturn(dont_destroy_on_load, target);
	}

	uintptr_t CreatePrefab(const char* prefab, bool active)
	{
		uintptr_t method = offsets::gamemanager_createprefab; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return NULL;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return NULL;
		}

		auto create_prefab = reinterpret_cast<uintptr_t(*)(il2cpp::il2cppstring*, bool)>(method_ptr);
		return SpoofReturn(create_prefab, il2cpp::il2cppstring::New(prefab), active);
	}

	void Destroy(uintptr_t object)
	{
		uintptr_t method = offsets::gamemanager_destroy; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto create_prefab = reinterpret_cast<void(*)(uintptr_t)>(method_ptr);
		return SpoofReturn(create_prefab, object);
	}

	float get_time()
	{
		uintptr_t method = offsets::time_get_time; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return 0.f;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return 0.f;
		}

		auto get_time = reinterpret_cast<float(*)()>(method_ptr);
		return SpoofReturn(get_time);
	}

	float get_deltaTime()
	{
		uintptr_t method = offsets::time_get_deltaTime; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			std::cout << "dT method false!" << std::endl;
			return 0.f;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			std::cout << "dT method_ptr false!" << std::endl;
			return 0.f;
		}

		auto get_deltaTime = reinterpret_cast<float(*)()>(method_ptr);
		return SpoofReturn(get_deltaTime);
	}

	float random_range(float min, float max)
	{
		uintptr_t method = offsets::randomrange; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return min + (max - min);
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return min + (max - min);
		}

		auto range = reinterpret_cast<float(*)(float min, float max)>(method_ptr);
		return SpoofReturn(range, min, max);
	}

	bool physics_checkcapsule(Vector3 start, Vector3 end, float radius, int layer_mask, QueryTriggerInteraction querytriggerinteraction)
	{
		uintptr_t method = offsets::physics_checkcapsule; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			std::cout << "PCC method false!" << std::endl;
			return false;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			std::cout << "PCC method_ptr false!" << std::endl;
			return false;
		}

		auto checkcapsule = reinterpret_cast<bool(*)(Vector3 start, Vector3 end, float radius, int layer_mask, QueryTriggerInteraction querytriggerinteraction)>(method_ptr);
		return SpoofReturn(checkcapsule, start, end, radius, layer_mask, querytriggerinteraction);
	}
}

std::wstring get_name(uintptr_t object)
{
	if (!(object))
	{
		return std::wstring();
	}

	uintptr_t address = offsets::object_name;
	if (!address)
		return std::wstring();

	il2cpp::il2cppstring* entity_name = *reinterpret_cast<il2cpp::il2cppstring**>(object + address);
	if (!(reinterpret_cast<uintptr_t>(entity_name)))
		return std::wstring();

	return entity_name->buffer;
}

namespace rust
{
	Vector3 Transform::get_position()
	{
		uintptr_t transform = reinterpret_cast<uintptr_t>(this);
		if (!(transform))
			return Vector3();

		uintptr_t method = offsets::transform_get_position;
		if (!(method))
			return Vector3();

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
			return Vector3();

		auto get_transform_position = reinterpret_cast<Vector3(*)(uintptr_t transform)>(method_ptr);
		return get_transform_position(transform);
	}

	void Transform::set_position(Vector3 value)
	{
		uintptr_t transform = reinterpret_cast<uintptr_t>(this);
		if (!(transform))
			return;

		uintptr_t method = offsets::transform_set_position; //il2cpp::method(xorstr_("Transform"), xorstr_("get_position"), 0, xorstr_("UnityEngine"));
		if (!(method))
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return;
		}

		auto set_transform_position = reinterpret_cast<void(*)(uintptr_t transform, Vector3 value)>(method_ptr);
		SpoofReturn(set_transform_position, transform, value);
	}

	Vector3 Transform::inverse_tranform_point(Vector3 point)
	{
		uintptr_t transform = reinterpret_cast<uintptr_t>(this);
		if (!transform)
			return Vector3();

		uintptr_t method = offsets::transform_inverse_transform_point; //il2cpp::method(xorstr_("Transform"), xorstr_("InverseTransformPoint"), 1, xorstr_("UnityEngine"));
		if (!(method))
		{
			return Vector3();
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return Vector3();
		}

		auto inverse_tranform_point = reinterpret_cast<Vector3(*)(uintptr_t transform, Vector3 position)>(method_ptr);
		return inverse_tranform_point(transform, point);
	}

	Vector3 Transform::transform_direction(Vector3 direction)
	{
		uintptr_t transform = reinterpret_cast<uintptr_t>(this);
		if (!transform)
			return Vector3();

		uintptr_t method = offsets::transform_transform_direction; //il2cpp::method(xorstr_("Transform"), xorstr_("InverseTransformPoint"), 1, xorstr_("UnityEngine"));
		if (!(method))
		{
			return Vector3();
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return Vector3();
		}

		auto inverse_tranform_point = reinterpret_cast<Vector3(*)(uintptr_t transform, Vector3 position)>(method_ptr);
		return inverse_tranform_point(transform, direction);
	}

	std::wstring BaseEntity::get_name()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return std::wstring();
		}

		uintptr_t address = offsets::baseentity__name; //il2cpp::value(xorstr_("BaseEntity"), xorstr_("_name"));
		if (!address)
			return std::wstring();

		il2cpp::il2cppstring* entity_name = *reinterpret_cast<il2cpp::il2cppstring**>(entity + address);
		if (!(reinterpret_cast<uintptr_t>(entity_name)))
			return std::wstring();

		return entity_name->buffer;
	}

	std::string BaseEntity::get_prefab_name()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return std::string();
		}

		auto object_name_ptr = *reinterpret_cast<uintptr_t*>(entity + 0x60);
		//std::cout << "[" << __FUNCTION__ << "] object_name_ptr: 0x" << std::hex << object_name_ptr << std::endl;
		if (!(object_name_ptr))
		{
			return std::string();
		}

		return functions::read_ascii(object_name_ptr);
	}

	std::string BaseEntity::get_class_name()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return std::string();

		uintptr_t object_unk = *reinterpret_cast<uintptr_t*>(entity);
		if (!(object_unk))
			return std::string();

		uintptr_t class_name_ptr = *reinterpret_cast<uintptr_t*>(object_unk + 0x10);
		if (!(class_name_ptr))
			return std::string();

		return functions::read_ascii(class_name_ptr);
	}
	void BaseEntity::longeyes()
	{
		
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;
		
		if (functions::get_key(KeyCode::DownArrow))
		{
			memory::write<Vector3>(entity + 0x38, Vector3(0.0f, 1, 0.0f));

		}
		if (functions::get_key(KeyCode::LeftArrow))
		{
			memory::write<Vector3>(entity + 0x38, Vector3(1, 0.0f, 0.0f));

		}
		if (functions::get_key(KeyCode::RightArrow))
		{
			memory::write<Vector3>(entity + 0x38, Vector3(0.0f, 0.0f, 1));

		}
	}
	Vector3 BaseEntity::get_visual_position(uintptr_t object_class)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return Vector3();

		uintptr_t player_visual = *reinterpret_cast<uintptr_t*>(object_class + 0x8);
		if (!(player_visual))
			return Vector3();

		uintptr_t visual_state = *reinterpret_cast<uintptr_t*>(player_visual + 0x38);
		if (!(visual_state))
			return Vector3();

		return *reinterpret_cast<Vector3*>(visual_state + 0x90);
	}

	Vector3 BaseEntity::get_closest_point(Vector3 position)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!entity)
			return Vector3();

		uintptr_t method = offsets::baseentity_closest_point; //il2cpp::method(xorstr_("BaseEntity"), xorstr_("ClosestPoint"), 1);
		if (!(method))
		{
			return Vector3();
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return Vector3();
		}

		auto get_ClosestPoint = reinterpret_cast<Vector3(*)(uintptr_t entity, Vector3 position)>(method_ptr);
		return get_ClosestPoint(entity, position);
	}

	Transform* BaseEntity::get_transform()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!entity)
			return nullptr;

		uintptr_t method = offsets::component_get_transform; //il2cpp::method(xorstr_("Component"), xorstr_("get_transform"), 0, xorstr_("UnityEngine"));
		if (!(method))
		{
			return nullptr;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return nullptr;
		}

		auto get_transform = reinterpret_cast<Transform * (*)(uintptr_t entity)>(method_ptr);
		return SpoofReturn(get_transform, entity);
	}

	void BaseEntity::set_hit_direction(Vector3 value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::treeentity_hit_direction; //il2cpp::value(xorstr_("TreeEntity"), xorstr_("hitDirection"));
		if (!address)
			return;

		memory::write<Vector3>(entity + address, value);
	}

	float BaseCombatEntity::get_health()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return 0.f;

		uintptr_t address = offsets::basecombatentity__health; //il2cpp::value(xorstr_("BaseCombatEntity"), xorstr_("_health"));
		if (!address)
			return 0.f;

		return *reinterpret_cast<float*>(entity + address);
	}

	void BaseEntity::server_rpc(const char* rpc)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t method = offsets::baseentity_serverrpc_1arg; //il2cpp::method(xorstr_("Input"), xorstr_("GetKey"), 1, xorstr_("UnityEngine"));
		if (!(method))
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return;
		}

		auto ServerRPC = reinterpret_cast<void (*)(uintptr_t, il2cpp::il2cppstring*)>(method_ptr);
		return SpoofReturn(ServerRPC, entity, il2cpp::il2cppstring::New(rpc));
	}

	void BaseEntity::server_rpc(uintptr_t entity, const char* rpc)
	{
		uintptr_t method = offsets::baseentity_serverrpc_1arg; //il2cpp::method(xorstr_("Input"), xorstr_("GetKey"), 1, xorstr_("UnityEngine"));
		if (!(method))
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return;
		}

		auto ServerRPC = reinterpret_cast<void (*)(uintptr_t, il2cpp::il2cppstring*)>(method_ptr);
		return SpoofReturn(ServerRPC, entity, il2cpp::il2cppstring::New(rpc));
	}

	void BaseEntity::send_signal_broadcast(int signal, const char* arg)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!entity)
			return;

		uintptr_t method = offsets::baseentity_sendsignalbroadcast;
		if (!method)
			return;

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
			return;

		auto ServerRPC = reinterpret_cast<void (*)(uintptr_t, int, il2cpp::il2cppstring*)>(method_ptr);
		return SpoofReturn(ServerRPC, entity, signal, il2cpp::il2cppstring::New(arg));
	}

	float BaseCombatEntity::get_max_health()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return 0.f;

		uintptr_t address = offsets::basecombatentity__maxHealth;
		if (!address)
			return 0.f;

		return *reinterpret_cast<float*>(entity + address);
	}

	int BaseCombatEntity::get_life_state()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return 1;

		uintptr_t address = offsets::basecombatentity_lifestate; //il2cpp::value(xorstr_("BaseCombatEntity"), xorstr_("lifestate"));
		if (!address)
			return 1;

		return *reinterpret_cast<int*>(entity + address);
	}

	bool PlayerWalkMovement::swimming()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return 1;

		uintptr_t address = offsets::playerwalkmovement_swimming; //il2cpp::value(xorstr_("BaseCombatEntity"), xorstr_("lifestate"));
		if (!address)
			return 1;

		return *reinterpret_cast<bool*>(entity + address);
	}

	bool PlayerWalkMovement::flying()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return 1;

		uintptr_t address = offsets::playerwalkmovement_flying; //il2cpp::value(xorstr_("BaseCombatEntity"), xorstr_("lifestate"));
		if (!address)
			return 1;

		return *reinterpret_cast<bool*>(entity + address);
	}

	void PlayerWalkMovement::ShootInAir()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;
		//uintptr_t address = offsets::;
		//if (!address)
			//return;

	//	auto mov_flag = memory::read<uintptr_t>(entity + address);
		auto address = 0x134; //  sprintForced
		auto ground = 0xc4; //groundAngle
		auto groundnew = 0xc8; //groundAngleNew
		auto angle = 0x94; //maxAngleSliding

		memory::write<float>(entity + address, 2.5f); // our first sprit power
		memory::write<float>(entity + ground, 0.1f); // lowering our ground angle to slide
		memory::write<float>(entity + groundnew, 0.05f); // lowering our new angle
		memory::write<float>(entity + 0x94, 5.0f); // increase our slide angle
		
	}

	void PlayerWalkMovement::Water()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!entity)
			return;

		uintptr_t GroundAngle = offsets::playerwalkmovement_groundAngle;
		uintptr_t GroundAnleNew = offsets::playerwalkmovement_groundAngleNew;
		uintptr_t Gravity = offsets::playerwalkmovement_gravityMultiplier;
		if (!GroundAngle)
			return;
		if (!GroundAnleNew)
			return;
		if (!Gravity)
			return;
		if (functions::get_key(KeyCode::W))
		{
			if (memory::read<float>(entity + GroundAngle) != 0.f) {
				memory::write<float>(entity + GroundAngle, 0.f);//groundAngle
				memory::write<float>(entity + GroundAnleNew, 0.f);//groundAngleNew
				memory::write<float>(entity + Gravity, 0.f);//gravityMultiplier
			}
		}
		else
		{
			if (memory::read<float>(entity + Gravity) != 2.5f) {
				memory::write<float>(entity + Gravity, 2.5f);//gravityMultiplier
			}
		}
	}

	bool PlayerWalkMovement::ducking()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return 1;

		uintptr_t address = offsets::playerwalkmovement_ducking; //il2cpp::value(xorstr_("BaseCombatEntity"), xorstr_("lifestate"));
		if (!address)
			return 1;

		return *reinterpret_cast<bool*>(entity + address);
	}

	bool PlayerWalkMovement::spiderman()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return 1;
		if (functions::get_key(KeyCode::Mouse2))
		{
			memory::write<Vector3>(entity + offsets::playerwalkmovement_groundAngle, Vector3(200000.0f, 10000.0f, 100000.0f));
		}
		else {
			memory::write<Vector3>(entity + offsets::playerwalkmovement_groundAngle, Vector3(0.0f, 0.0f, 0.0f));
		}
		

		

	}

	bool PlayerWalkMovement::fun()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity)) {
			return 1;
		}

		uintptr_t address = offsets::playerwalkmovement_gravityMultiplier;
		if (!address)
		{
			return 1;
		}
		uintptr_t address1 = offsets::playerwalkmovement_gravityMultiplier;
		
		if (functions::get_key(KeyCode::Space))
		{
			memory::write<float>(entity + offsets::playerwalkmovement_gravityMultiplier, 1.0f);

		}
		else
		{
			memory::write<float>(entity + offsets::playerwalkmovement_gravityMultiplier, 2.5f);

		}
		

		
		
		
		


		memory::write<float>(entity + address1, 1.5f);
	}

	void PlayerWalkMovement::set_ground_angle(float angle)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::playerwalkmovement_groundAngle; //il2cpp::value(xorstr_("PlayerWalkMovement"), xorstr_("groundAngle"));
		if (!address)
			return;

		memory::write<float>(entity + address, angle);
	}

	void PlayerWalkMovement::set_ground_angle_new(float angle)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::playerwalkmovement_groundAngleNew; //il2cpp::value(xorstr_("PlayerWalkMovement"), xorstr_("groundAngleNew"));
		if (!address)
			return;

		memory::write<float>(entity + address, angle);
	}

	void PlayerWalkMovement::set_max_angle_walking(float angle)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::playerwalkmovement_maxAngleWalking; //il2cpp::value(xorstr_("PlayerWalkMovement"), xorstr_("maxAngleWalking"));
		if (!address)
			return;

		memory::write<float>(entity + address, angle);
	}

	void PlayerWalkMovement::set_max_angle_climbing(float angle)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::playerwalkmovement_maxAngleClimbing; //il2cpp::value(xorstr_("PlayerWalkMovement"), xorstr_("maxAngleClimbing"));
		if (!address)
			return;

		memory::write<float>(entity + address, angle);
	}

	void PlayerWalkMovement::set_ground_time(float time)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::playerwalkmovement_groundTime; //il2cpp::value(xorstr_("PlayerWalkMovement"), xorstr_("groundTime"));
		if (!address)
			return;

		memory::write<float>(entity + address, time);
	}

	void PlayerWalkMovement::set_gravity_multiplier(float multiplier)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::playerwalkmovement_gravityMultiplier; //il2cpp::value(xorstr_("PlayerWalkMovement"), xorstr_("gravityMultiplier"));
		if (!address)
			return;

		memory::write<float>(entity + address, multiplier);
	}

	void PlayerWalkMovement::set_jump_time(float time)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::playerwalkmovement_jumpTime; //il2cpp::value(xorstr_("PlayerWalkMovement"), xorstr_("jumpTime"));
		if (!address)
			return;

		memory::write<float>(entity + address, time);
	}

	void PlayerWalkMovement::set_land_time(float time)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::playerwalkmovement_landTime; //il2cpp::value(xorstr_("PlayerWalkMovement"), xorstr_("landTime"));
		if (!address)
			return;

		memory::write<float>(entity + address, time);
	}

	void PlayerWalkMovement::set_targetmovement(Vector3 new_val)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		memory::write<Vector3>(entity + 0x34, new_val);
	}

	void RigidBody::set_velocity(Vector3 val)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t method = offsets::rigidbody_setVelocity; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!(method))
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!(method_ptr))
		{
			return;
		}

		auto set_velocity = reinterpret_cast<void(*)(uintptr_t, Vector3)>(method_ptr);
		return SpoofReturn(set_velocity, entity, val);
	}

	RigidBody* PlayerWalkMovement::get_body()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return nullptr;

		return memory::read<RigidBody*>(entity + 0xA0);
	}

	Vector2 PlayerInput::get_view_angles()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return Vector2();

		uintptr_t address = offsets::playerinput_bodyAngles; //il2cpp::value(xorstr_("PlayerInput"), xorstr_("bodyAngles"));
		if (!address)
			return Vector2();

		return *reinterpret_cast<Vector2*>(entity + address);
	}

	Vector2 PlayerInput::get_recoil_angles()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return Vector2();

		uintptr_t address = il2cpp::value(xorstr_("PlayerInput"), xorstr_("recoilAngles"));
		if (!address)
			return Vector2();

		return *reinterpret_cast<Vector2*>(entity + address);
	}

	void PlayerInput::set_view_angles(Vector2 angle)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::playerinput_bodyAngles; //il2cpp::value(xorstr_("PlayerInput"), xorstr_("bodyAngles"));
		if (!address)
			return;

		memory::write<Vector2>(entity + address, angle);
	}

	void PlayerInput::set_recoil_angles(Vector2 angle)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = il2cpp::value(xorstr_("PlayerInput"), xorstr_("recoilAngles"));
		if (!address)
			return;

		memory::write<Vector2>(entity + address, angle);
	}

	int ItemDefinition::get_itemid()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return 0;

		return *reinterpret_cast<int*>(entity + offsets::itemdefinition_itemid);
	}

	std::wstring ItemDefinition::get_shortname()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return std::wstring();

		il2cpp::il2cppstring* entity_name = *reinterpret_cast<il2cpp::il2cppstring**>(entity + offsets::itemdefinition_shortname);
		if (!entity_name)
			return std::wstring();

		return entity_name->buffer;
	}


	BaseEntity* Item::get_held_entity()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!entity)
			return nullptr;

		auto held = *reinterpret_cast<BaseEntity**>(entity + offsets::item_heldEntity);
		if (!held)
			return nullptr;

		return held;
	}

	ItemDefinition* BaseProjectile::Magazine::get_ammotype()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return nullptr;

		return *reinterpret_cast<ItemDefinition**>(entity + 0x20);
	}

	BaseProjectile::Magazine* BaseProjectile::get_primaryMagazine()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return NULL;

		return *reinterpret_cast<BaseProjectile::Magazine**>(entity + offsets::baseprojectile_primaryMagazine);
	}

	Vector3 PlayerModel::get_position()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!entity)
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + offsets::playermodel_position);
	}

	void PlayerModel::set_position(Vector3 new_pos)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!entity)
			return;

		*reinterpret_cast<Vector3*>(entity + offsets::playermodel_position) = new_pos;
	}

	Vector3 PlayerModel::get_velocity()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!entity)
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + offsets::playermodel_newVelocity);
	}

	uintptr_t PlayerModel::get_multimesh()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!entity)
			return NULL;

		return *reinterpret_cast<uintptr_t*>(entity + offsets::playermodel_multimesh);
	}

	void PlayerModel::set_velocity(Vector3 new_velo)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!entity)
			return;

		*reinterpret_cast<Vector3*>(entity + offsets::playermodel_newVelocity) = new_velo;
	}

	bool PlayerModel::is_npc()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!entity)
			return bool();

		return *reinterpret_cast<bool*>(entity + 0x320);
	}

	void ModelState::set_onLadder(bool value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!entity)
			return;

		uintptr_t method = offsets::modelstate_set_onLadder; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto onLadder = reinterpret_cast<void(*)(uintptr_t, bool)>(method_ptr);
		SpoofReturn(onLadder, entity, value);
	}

	void ModelState::remove_flag(int flag)
	{
		int flags = *reinterpret_cast<int*>((uintptr_t)this + 0x24);

		flags &= ~flag;

		*reinterpret_cast<int*>((uintptr_t)this + 0x24) = flags;
	}

	void ModelState::add_flag(int flag)
	{
		int flags = *reinterpret_cast<int*>((uintptr_t)this + 0x24);

		*reinterpret_cast<int*>((uintptr_t)this + 0x24) = flags |= (int)flag;
	}

	bool ModelState::has_flag(int flag)
	{
		int flags = *reinterpret_cast<int*>((uintptr_t)this + 0x24);
		return (flags & flag);
	}

	Vector3 PlayerEyes::get_position()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + 0x44);
	}
	Vector3 PlayerEyes::get_viewoffset()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return Vector3();
		return *reinterpret_cast<Vector3*>(entity + 0x38);
	}
	Vector3 PlayerEyes::get_bodyforward()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return Vector3();

		uintptr_t method = offsets::playereyes_bodyforward; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return Vector3();
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return Vector3();
		}

		auto bodyforward = reinterpret_cast<Vector3(*)(uintptr_t)>(method_ptr);
		return bodyforward(entity);
	}
	Vector3 PlayerEyes::get_bodyright()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return Vector3();

		uintptr_t method = offsets::playereyes_bodyright; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return Vector3();
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return Vector3();
		}

		auto bodyforward = reinterpret_cast<Vector3(*)(uintptr_t)>(method_ptr);
		return bodyforward(entity);
	}

	void PlayerEyes::set_body_rotation(Vector4 value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		memory::write<Vector4>(entity + 0x44, value);
	}

	void PlayerEyes::set_view_offset(Vector3 value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		memory::write<Vector3>(entity + 0x38, value);
	}

	float Item::get_bullet_velocity()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return NULL;

		auto WeaponName = functions::ws2s(get_name());
		
		//std::cout << "Getting Weapon Info: " << WeaponName << std::endl;
		float Speed = 1.f;

		if (WeaponName == "spear.wooden")
		{
			return 25.f;
		}
		else if (WeaponName == "spear.stone")
		{
			return 30.f;
		}
		else if (WeaponName == "pistol.nailgun")
		{
			return 50.f;
		}
		else if (WeaponName == "snowballgun")
		{
			return 25.f;
		}
		else if (WeaponName == "rock")
		{
			return 18.f;
		}
		else
		{
			BaseProjectile* base_projectile = *reinterpret_cast<BaseProjectile**>(entity + offsets::item_heldEntity);
			if (!base_projectile)
				return Speed;

			BaseProjectile::Magazine* magazine = base_projectile->get_primaryMagazine();
			if (!magazine)
				return Speed;

			ItemDefinition* ammo_type_definition = magazine->get_ammotype();
			if (!ammo_type_definition)
				return Speed;

			std::wstring ammo_name = ammo_type_definition->get_shortname();

			/* Rifles */
			if (WeaponName == "AK")
			{
				if (ammo_name == L"ammo.rifle")
				{
					return 375.f;
				}
				else if (ammo_name == L"ammo.rifle.hv")
				{
					return 450.f;
				}
				else if (ammo_name == L"ammo.rifle.explosive")
				{
					return 225.f;
				}
				else if (ammo_name == L"ammo.rifle.incendiary")
				{
					return 225.f;
				}
				else
				{
					return 375.f;
				}
			}
			if (WeaponName == "LR300")
			{
				if (ammo_name == L"ammo.rifle")
				{
					return 375.f;
				}
				else if (ammo_name == L"ammo.rifle.hv")
				{
					return 450.f;
				}
				else if (ammo_name == L"ammo.rifle.explosive")
				{
					return 225.f;
				}
				else if (ammo_name == L"ammo.rifle.incendiary")
				{
					return 225.f;
				}
				else
				{
					return 375.f;
				}
			}
			if (WeaponName == "Bolty")
			{
				if (ammo_name == L"ammo.rifle")
				{
					return 656.25f;
				}
				else if (ammo_name == L"ammo.rifle.hv")
				{
					return 787.5f;
				}
				else if (ammo_name == L"ammo.rifle.explosive")
				{
					return 393.75f;
				}
				else if (ammo_name == L"ammo.rifle.incendiary")
				{
					return 393.75f;
				}
				else
				{
					return 656.25f;
				}
			}
			if (WeaponName == "L96")
			{
				if (ammo_name == L"ammo.rifle")
				{
					return 1125.f;
				}
				else if (ammo_name == L"ammo.rifle.hv")
				{
					return 1350.f;
				}
				else if (ammo_name == L"ammo.rifle.explosive")
				{
					return 675.f;
				}
				else if (ammo_name == L"ammo.rifle.incendiary")
				{
					return 675.f;
				}
				else
				{
					return 1125.f;
				}
			}
			if (WeaponName == "M39")
			{
				if (ammo_name == L"ammo.rifle")
				{
					return 468.75f;
				}
				else if (ammo_name == L"ammo.rifle.hv")
				{
					return 562.5f;
				}
				else if (ammo_name == L"ammo.rifle.explosive")
				{
					return 281.25f;
				}
				else if (ammo_name == L"ammo.rifle.incendiary")
				{
					return 281.25f;
				}
				else
				{
					return 468.75f;
				}
			}
			if (WeaponName == "Semiauto")
			{
				if (ammo_name == L"ammo.rifle")
				{
					return 375.f;
				}
				else if (ammo_name == L"ammo.rifle.hv")
				{
					return 450.f;
				}
				else if (ammo_name == L"ammo.rifle.explosive")
				{
					return 225.f;
				}
				else if (ammo_name == L"ammo.rifle.incendiary")
				{
					return 225.f;
				}
				else
				{
					return 375.f;
				}
			}
			/* LMG */
			if (WeaponName == "M249")
			{
				if (ammo_name == L"ammo.rifle")
				{
					return 487.5f;
				}
				else if (ammo_name == L"ammo.rifle.hv")
				{
					return 585.f;
				}
				else if (ammo_name == L"ammo.rifle.explosive")
				{
					return 292.5f;
				}
				else if (ammo_name == L"ammo.rifle.incendiary")
				{
					return 292.5f;
				}
				else
				{
					return 487.5f;
				}
			}
			/* SMGs */
			if (WeaponName == "Thompson")
			{
				if (ammo_name == L"ammo.pistol")
				{
					return 300.f;
				}
				else if (ammo_name == L"ammo.pistol.hv")
				{
					return 400.f;
				}
				else if (ammo_name == L"ammo.pistol.fire")
				{
					return 225.f;
				}
				else
				{
					return 300.f;
				}
			}
			if (WeaponName == "Custom")
			{
				if (ammo_name == L"ammo.pistol")
				{
					return 240.f;
				}
				else if (ammo_name == L"ammo.pistol.hv")
				{
					return 320.f;
				}
				else if (ammo_name == L"ammo.pistol.fire")
				{
					return 180.f;
				}
				else
				{
					return 240.f;
				}
			}
			if (WeaponName == "Mp5")
			{
				if (ammo_name == L"ammo.pistol")
				{
					return 240.f;
				}
				else if (ammo_name == L"ammo.pistol.hv")
				{
					return 320.f;
				}
				else if (ammo_name == L"ammo.pistol.fire")
				{
					return 180.f;
				}
				else
				{
					return 240.f;
				}
			}
			/* Pistols */
			if (WeaponName == "Python")
			{
				if (ammo_name == L"ammo.pistol")
				{
					return 300.f;
				}
				else if (ammo_name == L"ammo.pistol.hv")
				{
					return 400.f;
				}
				else if (ammo_name == L"ammo.pistol.fire")
				{
					return 225.f;
				}
				else
				{
					return 300.f;
				}
			}
			if (WeaponName == "Semiauto")
			{
				if (ammo_name == L"ammo.pistol")
				{
					return 300.f;
				}
				else if (ammo_name == L"ammo.pistol.hv")
				{
					return 400.f;
				}
				else if (ammo_name == L"ammo.pistol.fire")
				{
					return 225.f;
				}
				else
				{
					return 300.f;
				}
			}
			if (WeaponName == "Revolver")
			{
				if (ammo_name == L"ammo.pistol")
				{
					return 300.f;
				}
				else if (ammo_name == L"ammo.pistol.hv")
				{
					return 400.f;
				}
				else if (ammo_name == L"ammo.pistol.fire")
				{
					return 225.f;
				}
				else
				{
					return 300.f;
				}
			}
			if (WeaponName == "M92")
			{
				if (ammo_name == L"ammo.pistol")
				{
					return 300.f;
				}
				else if (ammo_name == L"ammo.pistol.hv")
				{
					return 400.f;
				}
				else if (ammo_name == L"ammo.pistol.fire")
				{
					return 225.f;
				}
				else
				{
					return 300.f;
				}
			}
			if (WeaponName == "Eoka")
			{
				if (ammo_name == L"handmade.shell")
				{
					return 90.f;
				}
				else if (ammo_name == L"ammo.shotgun")
				{
					return 222.f;
				}
				else if (ammo_name == L"ammo.shotgun.slug")
				{
					return 225.f;
				}
				else if (ammo_name == L"ammo.shotgun.fire")
				{
					return 77.f;
				}
				else
				{
					return 90.f;
				}
			}
			/* Bows/Arrows */
			if (WeaponName == "Crossbow")
			{
				if (ammo_name == L"arrow.wooden")
				{
					return 75.f;
				}
				else if (ammo_name == L"arrow.hv") //+35
				{
					return 120.f;
				}
				else if (ammo_name == L"arrow.fire")
				{
					return 60.f;
				}
				else if (ammo_name == L"arrow.bone")
				{
					return 67.5f;
				}
				else
				{
					return 75.f;
				}
			}
			if (WeaponName == "Compound Bow")
			{
				if (ammo_name == L"arrow.wooden")
				{
					return 100.f;
				}
				else if (ammo_name == L"arrow.hv")
				{
					return 160.f;
				}
				else if (ammo_name == L"arrow.fire")
				{
					return 80.f;
				}
				else if (ammo_name == L"arrow.bone")
				{
					return 90.f;
				}
				else
				{
					return 100.f;
				}
			}
			if (WeaponName == "Hunting Bow")
			{
				if (ammo_name == L"arrow.wooden") //+18.5
				{
					return 50.f;
				}
				else if (ammo_name == L"arrow.hv") //+24 for head.
				{
					return 80.f;
				}
				else if (ammo_name == L"arrow.fire") //+12
				{
					return 40.f;
				}
				else if (ammo_name == L"arrow.bone") // 13
				{
					return 45.f;
				}
				else
				{
					return 50.f;
				}
			}
			/* Shotguns */
			if (WeaponName == "Pump")
			{
				if (ammo_name == L"handmade.shell")
				{
					return 99.f;
				}
				else if (ammo_name == L"ammo.shotgun")
				{
					return 219.f;
				}
				else if (ammo_name == L"ammo.shotgun.slug")
				{
					return 225.f;
				}
				else if (ammo_name == L"ammo.shotgun.fire")
				{
					return 71.f;
				}
				else
				{
					return 99.f;
				}
			}
			if (WeaponName == "Spas12")
			{
				if (ammo_name == L"handmade.shell")
				{
					return 90.f;
				}
				else if (ammo_name == L"ammo.shotgun")
				{
					return 222.f;
				}
				else if (ammo_name == L"ammo.shotgun.slug")
				{
					return 225.f;
				}
				else if (ammo_name == L"ammo.shotgun.fire")
				{
					return 100.f;
				}
				else
				{
					return 90.f;
				}
			}
			if (WeaponName == "Waterpipe")
			{
				if (ammo_name == L"handmade.shell")
				{
					return 110.f;
				}
				else if (ammo_name == L"ammo.shotgun")
				{
					return 234.f;
				}
				else if (ammo_name == L"ammo.shotgun.slug")
				{
					return 225.f;
				}
				else if (ammo_name == L"ammo.shotgun.fire")
				{
					return 110.f;
				}
				else
				{
					return 110.f;
				}
			}
			if (WeaponName == "shotgun double")
			{
				if (ammo_name == L"handmade.shell")
				{
					return 91.f;
				}
				else if (ammo_name == L"ammo.shotgun")
				{
					return 207.f;
				}
				else if (ammo_name == L"ammo.shotgun.slug")
				{
					return 225.f;
				}
				else if (ammo_name == L"ammo.shotgun.fire")
				{
					return 107.f;
				}
				else
				{
					return 91.f;
				}
			}
		}

		if (Speed == 0.f)
		{
			return 300.0f;
		}

		return Speed;
	}

	float Item::get_bullet_gravity()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return NULL;

		auto WeaponName = functions::ws2s(get_name());
		float Speed = 1.f;


		if (WeaponName == "spear.wooden")
		{
			return 2.0f;
		}
		else if (WeaponName == "spear.stone")
		{
			return 2.0f;
		}
		else if (WeaponName == "pistol.nailgun")
		{
			return 0.75f;
		}
		else if (WeaponName == "snowballgun")
		{
			return 0.75f;
		}
		else if (WeaponName == "rock")
		{
			return 1.0f;
		}
		else
		{
			auto held = this->get_held_entity();
			if (!held)
				return Speed;

			BaseProjectile* base_projectile = reinterpret_cast<BaseProjectile*>(held);
			if (!base_projectile)
				return Speed;

			BaseProjectile::Magazine* magazine = base_projectile->get_primaryMagazine();
			if (!magazine)
				return Speed;

			ItemDefinition* ammo_type_definition = magazine->get_ammotype();
			if (!ammo_type_definition)
				return Speed;

			std::wstring ammo_name = ammo_type_definition->get_shortname();


			if (WeaponName == "rifle.ak")
			{
				if (ammo_name == L"ammo.rifle.explosive")
				{
					return 1.25f;
				}
			}
			if (WeaponName == "rifle.lr300")
			{
				if (ammo_name == L"ammo.rifle.explosive")
				{
					return 1.25f;
				}
			}
			if (WeaponName == "rifle.bolt")
			{
				if (ammo_name == L"ammo.rifle.explosive")
				{
					return 1.25f;
				}
			}
			if (WeaponName == "rifle.l96")
			{
				if (ammo_name == L"ammo.rifle.explosive")
				{
					return 1.25f;
				}
			}
			if (WeaponName == "rifle.m39")
			{
				if (ammo_name == L"ammo.rifle.explosive")
				{
					return 1.25f;
				}
			}
			if (WeaponName == "rifle.semiauto")
			{
				if (ammo_name == L"ammo.rifle.explosive")
				{
					return 1.25f; //12.2625
				}
			}

			if (WeaponName == "lmg.m249")
			{
				if (ammo_name == L"ammo.rifle.explosive")
				{
					return 1.25f;
				}
			}

			if (WeaponName == "smg.thompson")
			{
				return 1.f;
			}
			if (WeaponName == "smg.custom")
			{
				return 1.f;
			}
			if (WeaponName == "smg.mp5")
			{
				return 1.f;
			}

			if (WeaponName == "pistol.python")
			{
				return 1.f;
			}
			if (WeaponName == "pistol.semi")
			{
				return 1.f;
			}
			if (WeaponName == "pistol.revolver")
			{
				return 1.f;
			}
			if (WeaponName == "pistol.m92")
			{
				return 1.f;
			}
			if (WeaponName == "pistol.eoka")
			{
				return 1.f;
			}

			if (WeaponName == "crossbow")
			{
				if (ammo_name == L"arrow.wooden")
				{
					return 0.75f;
				}
				else if (ammo_name == L"arrow.hv")
				{
					return 0.5f;
				}
				else if (ammo_name == L"arrow.fire")
				{
					return 1.f;
				}
				else if (ammo_name == L"arrow.bone")
				{
					return 0.75f;
				}
				else
				{
					return 0.75f;
				}
			}
			if (WeaponName == "bow.compound")
			{
				if (ammo_name == L"arrow.wooden")
				{
					return 1.f;
				}
				else if (ammo_name == L"arrow.hv")
				{
					return 1.f;
				}
				else if (ammo_name == L"arrow.fire")
				{
					return 1.f;
				}
				else if (ammo_name == L"arrow.bone")
				{
					return 0.75f;
				}
				else
				{
					return 1.f;
				}
			}
			if (WeaponName == "bow.hunting")
			{
				if (ammo_name == L"arrow.wooden")
				{
					return 0.75f;
				}
				else if (ammo_name == L"arrow.hv")
				{
					return 0.5f;
				}
				else if (ammo_name == L"arrow.fire")
				{
					return 1.f;
				}
				else if (ammo_name == L"arrow.bone")
				{
					return 0.75f;
				}
				else
				{
					return 0.75f;
				}
			}

			if (WeaponName == "shotgun.pump")
			{
				return 1.f;
			}
			if (WeaponName == "shotgun.spas12")
			{
				return 1.f;
			}
			if (WeaponName == "shotgun.waterpipe")
			{
				return 1.f;
			}
			if (WeaponName == "shotgun.doublebarrel")
			{
				return 1.f;
			}
		}

		if (Speed == 0.f)
		{
			return 1.f;
		}

		return Speed;
	}

	weapon_data Item::get_weapon_data()
	{
		//std::cout << "Getting Held Entity" << std::endl;
		auto held = this->get_held_entity();
		if (!held)
			return weapon_data{ (1000) };

		//std::cout << "Converting Held Entity" << std::endl;
		BaseProjectile* base_projectile = reinterpret_cast<BaseProjectile*>(held);
		if (!base_projectile)
			return weapon_data{ (1000) };

		//std::cout << "Getting Held Mag" << std::endl;
		BaseProjectile::Magazine* magazine = base_projectile->get_primaryMagazine();
		if (!magazine)
			return weapon_data{ (1000) };

		float velocity = (1000);
		float gravity_modifier = (1);
		float drag = (.001f);
		float distance = (0);

		auto velocity_scale = (1);
		bool scale_velocity = false;

		//std::cout << "Getting Held Ammo Def" << std::endl;
		const auto ammo_definition = *reinterpret_cast<uintptr_t*>((uintptr_t)magazine + 0x20);
		if (ammo_definition) {
			// itemid
			//std::cout << "Getting Held Ammo ID" << std::endl;
			const auto ammo_id = *reinterpret_cast<int32_t*>(ammo_definition + 0x18);
			//std::cout << "Switching: " << ammo_id << std::endl;
			switch (ammo_id) {
			case shotgun:
				velocity = (225);
				drag = (1);
				distance = (3);
				break;
			case shotgun_slug:
				velocity = (225);
				drag = (1);
				distance = (10);
				break;
			case shotgun_fire:
				velocity = 100;
				drag = 1;
				distance = 3;
				break;
			case shotgun_handmade:
				velocity = 100;
				drag = 1;
				distance = 0;
				break;
			case rifle_556:
				velocity = 375;
				drag = .6;
				distance = 15;
				break;
			case rifle_556_hv:
				velocity = 450;
				drag = .6;
				distance = 15;
				break;
			case rifle_556_fire:
				velocity = 225;
				drag = .6;
				distance = 15;
				break;
			case rifle_556_explosive:
				velocity = 225;
				gravity_modifier = 1.25;
				drag = .6;
				distance = 15;
				break;
			case pistol:
				velocity = 300;
				drag = .7;
				distance = 15;
				break;
			case pistol_hv:
				velocity = 400;
				drag = .7;
				distance = 15;
				break;
			case pistol_fire:
				velocity = 225;
				drag = .7;
				distance = 15;
				break;
			case arrow_wooden:
				velocity = 50;
				gravity_modifier = .75;
				drag = .005;
				break;
			case arrow_hv:
				velocity = 80;
				gravity_modifier = .5;
				drag = .005;
				break;
			case arrow_fire:
				velocity = 40;
				gravity_modifier = 1;
				drag = .01;
				break;
			case arrow_bone:
				velocity = 45;
				gravity_modifier = .75;
				drag = .01;
				break;
			case nailgun_nails:
				velocity = 50;
				gravity_modifier = .75;
				drag = .005;
				break;
			}
			//std::cout << "Getting getprojectilevelocityscale" << std::endl;
			//scale_velocity = true;
			//velocity_scale = functions::getprojectilevelocityscale(reinterpret_cast<uintptr_t>(held), false);
		}

		//std::cout << "Getting Held Entity Def ID" << std::endl;
		switch (this->get_definition_id()) {
		case spear_wooden:
			velocity = 25;
			scale_velocity = false;
			gravity_modifier = 2;
			drag = .1f;
			distance = .25f;
			break;
		case spear_stone:
			velocity = 30;
			scale_velocity = false;
			gravity_modifier = 2;
			drag = .1f;
			distance = .25f;
			break;
		}

		if (scale_velocity && (velocity_scale != 0))
			velocity *= velocity_scale;

		//std::cout << "Getting Held Entity" << std::endl;
		return { velocity, gravity_modifier, drag, distance };

	}

	int Item::get_amount()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return int();

		uintptr_t address = offsets::item_amount; //il2cpp::value(xorstr_("Item"), xorstr_("amount"));
		if (!address)
			return int();

		return *reinterpret_cast<int*>(entity + address);
	}

	void Item::Fastbow()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t address = offsets::item_amount; //il2cpp::value(xorstr_("Item"), xorstr_("amount"));
		if (!address)
			return;

		uintptr_t MaxDistance = offsets::hittest_maxDistance;
		if (!MaxDistance)
			return;
		
			memory::write<float>(entity + 0x31C, 0.f);
			memory::write<float>(entity + 0x320, 0.f);
			memory::write<float>(entity + 0x2EC, 0.f);
			memory::write<float>(entity + 0x2E8, 0.f);
			memory::write<float>(entity + 0x2F0, 0.f);
		
	}

	int32_t Item::get_definition_id()
	{
		const auto     item_definition = *reinterpret_cast<uintptr_t*>((uintptr_t)this + offsets::item_info);
		if (!item_definition)
			return 0;

		return *reinterpret_cast<int32_t*>(item_definition + 0x18);
	}

	int Item::get_uid()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return int();

		uintptr_t address = offsets::item_uid; //il2cpp::value(xorstr_("Item"), xorstr_("uid"));
		if (!address)
			return int();

		return *reinterpret_cast<int*>(entity + address);
	}

	std::wstring Item::get_name()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return std::wstring();
		}

		uintptr_t address = offsets::item_info; //il2cpp::value(xorstr_("Item"), xorstr_("info"))
		if (!address)
			return std::wstring();

		uintptr_t info = *reinterpret_cast<uintptr_t*>(entity + address);
		if (!(info))
			return std::wstring();

		uintptr_t address2 = offsets::itemdefinition_shortname; //il2cpp::value(xorstr_("ItemDefinition"), xorstr_("shortname"));
		if (!address2)
			return std::wstring();

		il2cpp::il2cppstring* entity_name = *reinterpret_cast<il2cpp::il2cppstring**>(info + address2);
		if (!(reinterpret_cast<uintptr_t>(entity_name)))
			return std::wstring();

		return entity_name->buffer;
	}

	Vector3 Item::get_visual_position(uintptr_t object_class)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return Vector3();

		uintptr_t player_visual = *reinterpret_cast<uintptr_t*>(object_class + 0x8);
		if (!(player_visual))
			return Vector3();

		uintptr_t visual_state = *reinterpret_cast<uintptr_t*>(player_visual + 0x38);
		if (!(visual_state))
			return Vector3();

		return *reinterpret_cast<Vector3*>(visual_state + 0x90);
	}

	bool Item::get_recoil_min_max()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return false;
		}
		Vector2 pitch_bounds;
		pitch_bounds.x = 0.0f;
		pitch_bounds.y = 0.0f;
		Vector2 yaw_bounds;
		yaw_bounds.x = 0.0f;
		yaw_bounds.y = 0.0f;
		auto item_definition = *reinterpret_cast<uintptr_t*>(entity + offsets::item_info); //public ItemDefinition info; // 0x20
		if (!(item_definition))
		{
			return false;
		}

		if (!is_gun())
		{
			return false;
		}

		unsigned int weapon_id = *reinterpret_cast<unsigned int*>(item_definition + 0x18);
		switch (weapon_id)
		{
		case 0x5c22b98e/*Assault Rifle*/: { //Updated.
			pitch_bounds.x = -2.5;
			pitch_bounds.y = -3.5;
			yaw_bounds.x = 1.5;
			yaw_bounds.y = 2.5;
			return true;
		}
		case 0xb065ec45/*Assault Rifle (ICE)*/: { //Updated.
			pitch_bounds.x = -2.5;
			pitch_bounds.y = -3.5;
			yaw_bounds.x = 1.5;
			yaw_bounds.y = 2.5;
			return true;
		}
		case 0x5eab82c3/*Bolt Action Rifle*/: { //Updated.
			pitch_bounds.x = -2;
			pitch_bounds.y = -3;
			yaw_bounds.x = -4;
			yaw_bounds.y = 4;
			return true;
		}
		case 0x34b73d71/*Compound Bow*/: { //Updated.
			pitch_bounds.x = -3;
			pitch_bounds.y = -6;
			yaw_bounds.x = -3;
			yaw_bounds.y = 3;
			return true;
		}
		case 0x7523110a/*Crossbow*/: { //Updated.
			pitch_bounds.x = -3;
			pitch_bounds.y = -6;
			yaw_bounds.x = -3;
			yaw_bounds.y = 3;
			return true;
		}
		case 0x6b1731e1/*Custom SMG*/: { //Updated.
			pitch_bounds.x = -1.5;
			pitch_bounds.y = -2;
			yaw_bounds.x = -1;
			yaw_bounds.y = 1;
			return true;
		}
		case 0xd264397f/*Double Barrel Shotgun*/: { //Updated.
			pitch_bounds.x = -10;
			pitch_bounds.y = -15;
			yaw_bounds.x = 8;
			yaw_bounds.y = 15;
			return true;
		}
		case 0x560b474f/*Hunting Bow*/: { //Updated.
			pitch_bounds.x = -3;
			pitch_bounds.y = -6;
			yaw_bounds.x = -3;
			yaw_bounds.y = 3;
			return true;
		}
		case 0xd19b0ec1/*L96 Rifle*/: { //Updated.
			pitch_bounds.x = -1;
			pitch_bounds.y = -1.5;
			yaw_bounds.x = -2;
			yaw_bounds.y = 2;
			return true;
		}
		case 0x93f69a57/*LR-300 Assault Rifle*/: { //Updated.
			pitch_bounds.x = -2;
			pitch_bounds.y = -3;
			yaw_bounds.x = -1;
			yaw_bounds.y = 1;
			return true;
		}
		case 0x84a4bb78/*M249*/: { //Updated.
			pitch_bounds.x = -3;
			pitch_bounds.y = -3;
			yaw_bounds.x = -1;
			yaw_bounds.y = 1;
			return true;
		}
		case 0x1ae5371/*M39 Rifle*/: { //Updated.
			pitch_bounds.x = -5;
			pitch_bounds.y = -7;
			yaw_bounds.x = -1.5;
			yaw_bounds.y = 1.5;
			return true;
		}
		case 0xcd2eebb5/*M92 Pistol*/: {
			pitch_bounds.x = -7;
			pitch_bounds.y = -8;
			yaw_bounds.x = -1;
			yaw_bounds.y = 1;
			return true;
		}
		case 0x4e979c37/*MP5A4*/: { //Updated
			pitch_bounds.x = -1;
			pitch_bounds.y = -3;
			yaw_bounds.x = -1;
			yaw_bounds.y = 1;
			return true;
		}
		case 0xbd092660/*Multiple Grenade Launcher*/: {
			pitch_bounds.x = -15.f;
			pitch_bounds.y = -20.f;
			yaw_bounds.x = 5.f;
			yaw_bounds.y = 10.f;
			return true;
		}
		case 0x74763261/*Nailgun*/: {
			pitch_bounds.x = -3;
			pitch_bounds.y = -6;
			yaw_bounds.x = -1;
			yaw_bounds.y = 1;
			return true;
		}
		case 0x2f686650/*Pump Shotgun*/: {
			pitch_bounds.x = -10.f;
			pitch_bounds.y = -14.f;
			yaw_bounds.x = 4.f;
			yaw_bounds.y = 8.f;
			return true;
		}
		case 0x51e52593/*Python Revolver*/: {
			pitch_bounds.x = -15.f;
			pitch_bounds.y = -16.f;
			yaw_bounds.x = -2.f;
			yaw_bounds.y = 2.f;
			return true;
		}
		case 0x26bce126/*Revolver*/: {
			pitch_bounds.x = -3.f;
			pitch_bounds.y = -6.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 1.f;
			return true;
		}
		case 0x1a65e87c/*Rocket Launcher*/: {
			pitch_bounds.x = -15.f;
			pitch_bounds.y = -20.f;
			yaw_bounds.x = 5.f;
			yaw_bounds.y = 10.f;
			return true;
		}
		case 0x30cf142c/*Semi-Automatic Pistol*/: {
			pitch_bounds.x = -6.f;
			pitch_bounds.y = -8.f;
			yaw_bounds.x = -2.f;
			yaw_bounds.y = 2.f;
			return true;
		}
		case 0xca10e257/*Semi-Automatic Rifle*/: {
			pitch_bounds.x = -5.f;
			pitch_bounds.y = -6.f;
			yaw_bounds.x = -1.f;
			yaw_bounds.y = 1.f;
			return true;
		}
		case 0xfd87ab32/*Spas-12 Shotgun*/: {
			pitch_bounds.x = -10.f;
			pitch_bounds.y = -14.f;
			yaw_bounds.x = 4.f;
			yaw_bounds.y = 8.f;
			return true;
		}
		case 0x97315c8b/*Thompson*/: { //Updated
			pitch_bounds.x = -1.5;
			pitch_bounds.y = -2;
			yaw_bounds.x = -1;
			yaw_bounds.y = 1;
			return true;
		}
		case 0xae80eeeb/*Waterpipe Shotgun*/: {
			pitch_bounds.x = -10.f;
			pitch_bounds.y = -14.f;
			yaw_bounds.x = 4.f;
			yaw_bounds.y = 8.f;
			return true;
		}
		case 0xb79b8d5f/*HMLMG*/: { //Updated.
			pitch_bounds.x = -3;
			pitch_bounds.y = -4;
			yaw_bounds.x = -1;
			yaw_bounds.y = -1.5;
			return true;
		}
		default: {
			return false;
		}
		}
	}

	void Item::instacharge()
	{
		
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}
	}

	void Item::instabow()
	{

		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}
		memory::write<bool>(held + 0x38c, 1); // trigger read
		memory::write<float>(held + 0x388, 99999990.f);
	}
	void Item::ExtMelee()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_melee())
		{
			return;
		}

		memory::write<float>(held + offsets::projectile_maxDistance, 5.0f); // max distance
		memory::write<float>(held + 0x294, 2.0f); // attack raidus
		memory::write<bool>(held + 0x2d0, 1); // throw ready
		memory::write<bool>(held + 0x299, 0); //Block Sprint
		memory::write<bool>(held + 0x2d3, 0); // onlyThrowAsProjectile
		memory::write<bool>(held + 0x2b0, 1);




	}
	void Item::set_automatic(bool automatic)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}

		memory::write<bool>(held + offsets::baseprojectile_automatic, automatic);
	}

	void Item::set_rapid_fire(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}

		memory::write<float>((uintptr_t)this + 0x650, 0.99f);
		memory::write<float>(held + 0x1f4, 0.01f);
		memory::write<float>(held + 0x31C, 0.f);
		memory::write<float>(held + 0x320, 0.f);
		memory::write<float>(held + 0x2EC, 0.f);
		memory::write<float>(held + 0x2E8, 0.f);
		memory::write<float>(held + 0x2F0, 0.f);

	}


	int Item::ammocount()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!entity)
		{
			return 1;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity); 
		if (!held)
			return 1;

		auto primemag = *reinterpret_cast<uintptr_t*>(held + 0x2C0);// BaseProjectile.Magazine
		if (!primemag)
			return 1;

		return *reinterpret_cast<uintptr_t*>(primemag + 0x1C); // Magazine.contants
	}

	int Item::maxammo()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!entity)
		{
			return 1;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!held)
			return 1;

		auto primemag = *reinterpret_cast<uintptr_t*>(held + 0x2C0);// BaseProjectile.Magazine
		if (!primemag)
			return 1;

		return *reinterpret_cast<uintptr_t*>(primemag + 0x18); // Magazine.contants
	}
	void Item::set_always_eoka(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto item_name = get_name();
		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);

	//	memory::write<float>(held + offsets::projectile_thickness, 1.0f);
		if (item_name.find(xorstr_(L"eoka")) != std::string::npos)
		{
			if (!(held))
			{
				return;
			}

			memory::write<float>(held + offsets::flintstrikeweapon_successFraction, value);
		}
	}

	void Item::set_aim_sway(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}

		memory::write<float>(held + offsets::baseprojectile_aimSway, value);
	}

	float Item::ReloadTime()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		
		return memory::read<float>(held + 0x2CC);

		}
	void Item::Norecoil(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}

		
		std::wstring item_name = get_name();
		uintptr_t newrecoil = *reinterpret_cast<uintptr_t*>(held + 0x2E0);
		uintptr_t recoiloverride = *reinterpret_cast<uintptr_t*>(newrecoil + 0x78);
		if (item_name.find(xorstr_(L"eoka")) != std::string::npos)
		{
			//return;
		}
		if (item_name.find(xorstr_(L"rifle.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			memory::write<float>(recoiloverride + 0x18, 0.0f);
			memory::write<float>(recoiloverride + 0x1C, 0.0f);
			memory::write<float>(recoiloverride + 0x20, 0.0f);
			memory::write<float>(recoiloverride + 0x24, 0.0f);
		}
		else if (item_name.find(xorstr_(L"pistol.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			
		}
		else if (item_name.find(xorstr_(L"bow.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
		}
		else if (item_name.find(xorstr_(L"cross")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
		}
		else if (item_name.find(xorstr_(L"lmg.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			memory::write<float>(recoiloverride + 0x18, 0.0f);
			memory::write<float>(recoiloverride + 0x1C, 0.0f);
			memory::write<float>(recoiloverride + 0x20, 0.0f);
			memory::write<float>(recoiloverride + 0x24, 0.0f);
		}
		else if (item_name.find(xorstr_(L"hmlmg")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			memory::write<float>(recoiloverride + 0x18, 0.0f);
			memory::write<float>(recoiloverride + 0x1C, 0.0f);
			memory::write<float>(recoiloverride + 0x20, 0.0f);
			memory::write<float>(recoiloverride + 0x24, 0.0f);
		}
		else if (item_name.find(xorstr_(L"shotgun.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
		}
		else if (item_name.find(xorstr_(L"smg.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			memory::write<float>(recoiloverride + 0x18, 0.0f);
			memory::write<float>(recoiloverride + 0x1C, 0.0f);
			memory::write<float>(recoiloverride + 0x20, 0.0f);
			memory::write<float>(recoiloverride + 0x24, 0.0f); 
		}//hmlmg
	
	

	}

	void Item::set_aim_sway_speed(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}

		memory::write<float>(held + offsets::baseprojectile_aimSway, value);
	}
	void Item::NoahBullets(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}
		auto list = *reinterpret_cast<uintptr_t*>(held + offsets::baseprojectile_createdProjectiles); // <-- correct
		list =  *reinterpret_cast<uintptr_t*>(list + 0x10); // <-- correct
		for (int i = 0; i < 8; ++i)
		{
			UINT64 Item = *reinterpret_cast<uintptr_t*>(list + 0x20 + (i * 0x8)); // <-- correc
			memory::write<float>(Item + 0x2C, 0.8f); //maybe offset
		}



	}


	void Item::set_aim_cone(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}

		memory::write<float>(held + offsets::baseprojectile_aimCone, value);
	}

	void Item::set_aim_cone_curve_scale(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}

		memory::write<float>(held + offsets::baseprojectile_aimCone, value);
	}

	void Item::set_aim_cone_penalty_max(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}

		memory::write<float>(held + offsets::baseprojectile_aimConePenaltyMax, value);
	}

	void Item::set_aim_cone_penalty_per_shot(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}

		memory::write<float>(held + offsets::baseprojectile_aimconePenaltyPerShot, value);
	}

	void Item::set_hip_aim_cone(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		if (!is_gun())
		{
			return;
		}

		memory::write<float>(held + offsets::baseprojectile_hipAimCone, value);
	}

	uintptr_t Item::get_damage_properties()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return NULL;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return NULL;
		}

		return *reinterpret_cast<uintptr_t*>(held + offsets::basemelee_damageproperties);
	}

	float Item::get_repeat_delay()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return float();
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return float();
		}

		return *reinterpret_cast<float*>(held + offsets::attackentity_repeatdelay);
	}

	void Item::start_attack_cooldown(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		uintptr_t method = offsets::attackentity_startattackcooldown; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		auto startcooldown = reinterpret_cast<void(*)(uintptr_t, float)>(method_ptr);
		SpoofReturn(startcooldown, held, value);
	}

	void Item::process_attack(HitTest* value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
		{
			return;
		}

		uintptr_t method = offsets::basemelee_processattack; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto held = *reinterpret_cast<uintptr_t*>(entity + offsets::item_heldEntity);
		if (!(held))
		{
			return;
		}

		auto startcooldown = reinterpret_cast<void(*)(uintptr_t, HitTest*)>(method_ptr);
		SpoofReturn(startcooldown, held, value);
	}

	bool Item::is_melee()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return false;

		int32_t item_id = get_definition_id();
		if (item_id == -1104520648)
		{
			return true;
		}
		else if (item_id == -1137865085) // machete
		{
			return true;
		}
		else if (item_id == -1252059217) { // hatchet
			return true;
		}
		else if (item_id == -1302129395) { // pickaxe
			return true;
		}
		else if (item_id == -262590403) {  // axe.salvaged
			return true;
		}
		else if (item_id == -1506397857) { // hammer.salvaged
			return true;
		}
		else if (item_id == -1780802565) { // icepick.salvaged
			return true;
		}
		else if (item_id == -1583967946) { // stonehatchet
			return true;
		}
		else if (item_id == 171931394) {   // stone.pickaxe
			return true;
		}
		else if (item_id == 795236088) { // torch
			return true;
		}
		else if (item_id == 1711033574) { // bone.club
			return true;
		}
		else if (item_id == 1814288539) { // knife.bone
			return true;
		}
		else if (item_id == -194509282) { // knife.butcher
			return true;
		}
		else if (item_id == 1789825282) { // candycaneclub
			return true;
		}
		else if (item_id == -1252059217) { // hatchet
			return true;
		}
		else if (item_id == 2040726127) { // knife.combat
			return true;
		}
		else if (item_id == -1469578201) { // longsword
			return true;
		}
		else if (item_id == -1966748496) { // mace
			return true;
		}
		else if (item_id == -1137865085) { // paddle
			return true;
		}
		else if (item_id == 1491189398) { // paddle
			return true;
		}
		else if (item_id == 1090916276) { // pitchfork
			return true;
		}
		else if (item_id == 1602646136) { // spear.stone
			return true;
		}
		else if (item_id == -1978999529) { // salvaged.cleaver
			return true;
		}
		else if (item_id == 1326180354) { // salvaged.sword
			return true;
		}
		else if (item_id == 1491189398) { // paddle
			return true;
		}
		else if (item_id == 1540934679) { // spear.wooden
			return true;
		}
		else if (item_id == 963906841) { // rock
			return true;
		}
		else
		{
			return false;
		}
	}

	bool Item::is_gun()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return false;

		std::wstring item_name = get_name();

		if (item_name.find(xorstr_(L"rifle.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			return true;
		}
		else if (item_name.find(xorstr_(L"pistol.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			return true;
		}
		else if (item_name.find(xorstr_(L"bow.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			return true;
		}
		else if (item_name.find(xorstr_(L"cross")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			return true;
		}
		else if (item_name.find(xorstr_(L"lmg.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			return true;
		}
		else if (item_name.find(xorstr_(L"hmlmg")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			return true;
		}
		else if (item_name.find(xorstr_(L"shotgun.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			return true;
		}
		else if (item_name.find(xorstr_(L"smg.")) != std::string::npos && item_name.find(xorstr_(L"ammo.")) == std::string::npos)
		{
			return true;
		}//hmlmg
		else
			return false;
	}

	Item* ItemContainer::get_item(int id)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return nullptr;

		uintptr_t address = offsets::itemcontainer_itemList; //il2cpp::value(xorstr_("ItemContainer"), xorstr_("itemList"));
		if (!address)
			return nullptr;

		uintptr_t item_list = *reinterpret_cast<uintptr_t*>(entity + address);
		if (!(item_list))
			return nullptr;

		uintptr_t items = *reinterpret_cast<uintptr_t*>(item_list + 0x10);
		if (!(items))
			return nullptr;

		return *reinterpret_cast<Item**>(items + 0x20 + (id * 0x8));
	}

	ItemContainer* PlayerInventory::get_belt()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return nullptr;

		uintptr_t address = offsets::playerinventory_containerBelt; //il2cpp::value(xorstr_("PlayerInventory"), xorstr_("containerBelt"));
		if (!address)
			return nullptr;

		return *reinterpret_cast<ItemContainer**>(entity + address);
	}

	long TeamMember::get_uid()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return long();

		return *reinterpret_cast<long*>(entity + 0x20);
	}

	std::vector<long> PlayerTeam::get_members()
	{
		std::vector<long> member_vector;
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return member_vector;

		uintptr_t member_list = *reinterpret_cast<uintptr_t*>(entity + 0x30);
		if (!(member_list))
			return member_vector;

		uintptr_t members = *reinterpret_cast<uintptr_t*>(member_list + 0x10);
		if (!(members))
			return member_vector;

		int members_size = *reinterpret_cast<int*>(member_list + 0x18);

		if (members_size > 0)
		{
			for (auto i = 0; i < members_size; i++)
			{
				TeamMember* member = *reinterpret_cast<TeamMember**>(members + (0x20 + (i * 0x8)));
				if (!(reinterpret_cast<uintptr_t>(member)))
					continue;

				long member_uid = member->get_uid();
				if (member_uid > 0)
				{
					member_vector.push_back(member_uid);
				}
			}
		}

		return member_vector;
	}

	Vector3 PlayerTick::get_position()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + offsets::playertick_position);
	}
	void PlayerTick::SetTicks(float ticks)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		

		if (functions::get_key(KeyCode::Mouse2))
		{
			memory::write<float>(entity + offsets::player_lastSentTick, ticks);
		}
	}

	float PlayerTick::TicksPerSec()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		

		
		return memory::read<float>(entity + offsets::player_lastSentTick);
		
	}
	PlayerTick* BasePlayer::get_lastSentTick()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return nullptr;

		return *reinterpret_cast<PlayerTick**>(entity + offsets::player_lastSentTick);
	}

	float BasePlayer::get_height(bool ducked)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return 0.f;

		uintptr_t method = offsets::baseplayer_get_height; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return 0.f;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return 0.f;
		}

		auto func = reinterpret_cast<float(*)(uintptr_t, bool)>(method_ptr);
		return SpoofReturn(func, entity, ducked);
	}

	float BasePlayer::get_radius()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return 0.f;

		uintptr_t method = offsets::baseplayer_get_radius; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return 0.f;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return 0.f;
		}

		auto func = reinterpret_cast<float(*)(uintptr_t)>(method_ptr);
		return SpoofReturn(func, entity);
	}

	float BasePlayer::get_jumpheight()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return 0.f;

		uintptr_t method = offsets::baseplayer_get_jumpheight; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return 0.f;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return 0.f;
		}

		auto func = reinterpret_cast<float(*)(uintptr_t)>(method_ptr);
		return SpoofReturn(func, entity);
	}

	std::wstring BasePlayer::get_username()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return std::wstring();

		uintptr_t address = offsets::_displayName;

		il2cpp::il2cppstring* player_name = *reinterpret_cast<il2cpp::il2cppstring**>(entity + address);
		if (!(reinterpret_cast<uintptr_t>(player_name)))
			return std::wstring();

		return player_name->buffer;
	}

	long BasePlayer::get_uid()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return long();

		uintptr_t address = offsets::userID;
		if (!address)
			return long();

		return *reinterpret_cast<long*>(entity + address);
	}

	int BasePlayer::get_active_weapon_id()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!entity)
			return int();

		return *reinterpret_cast<int*>(entity + offsets::clActiveItem);
	}

	PlayerWalkMovement* BasePlayer::get_movement()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return nullptr;

		return *reinterpret_cast<PlayerWalkMovement**>(entity + offsets::movement);
	}

	PlayerInput* BasePlayer::get_input()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return nullptr;

		uintptr_t address = offsets::input;
		if (!address)
			return nullptr;

		return *reinterpret_cast<PlayerInput**>(entity + address);
	}

	PlayerInventory* BasePlayer::get_inventory()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return nullptr;

		uintptr_t address = offsets::inventory;
		if (!address)
			return nullptr;

		return *reinterpret_cast<PlayerInventory**>(entity + address);
	}

	PlayerTeam* BasePlayer::get_team()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return nullptr;

		uintptr_t address = offsets::clientTeam;
		if (!address)
			return nullptr;

		return *reinterpret_cast<PlayerTeam**>(entity + address);
	}

	ModelState* BasePlayer::get_modelstate()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return nullptr;

		uintptr_t address = offsets::modelstate;
		if (!address)
			return nullptr;

		return *reinterpret_cast<ModelState**>(entity + address);
	}

	PlayerModel* BasePlayer::get_model()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!entity)
			return nullptr;

		uintptr_t address = offsets::player_model;
		if (!address)
			return nullptr;

		return *reinterpret_cast<PlayerModel**>(entity + address);
	}

	PlayerEyes* BasePlayer::get_eyes()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return nullptr;

		uintptr_t address = offsets::player_eyes;
		if (!address)
			return nullptr;

		return *reinterpret_cast<PlayerEyes**>(entity + address);
	}

	Item* BasePlayer::get_held_item()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!entity)
			return nullptr;

		int active_item_id = get_active_weapon_id();
		if (!active_item_id || active_item_id == NULL)
		{
			return nullptr;
		}

		for (int i = 0; i < 6; i++)
		{
			PlayerInventory* inventory = get_inventory();
			if (!(reinterpret_cast<uintptr_t>(inventory)))
				continue;

			ItemContainer* belt = inventory->get_belt();
			if (!(reinterpret_cast<uintptr_t>(belt)))
				continue;

			Item* weapon = belt->get_item(i);
			if (!(reinterpret_cast<uintptr_t>(weapon)))
				continue;

			if (active_item_id == weapon->get_uid())
			{
				return weapon;
			}
		}

		return nullptr;
	}

	bool BasePlayer::is_same_team(BasePlayer* local_player)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return false;

		if (!(reinterpret_cast<uintptr_t>(local_player)))
			return false;

		PlayerTeam* player_team = local_player->get_team();
		if (!(reinterpret_cast<uintptr_t>(player_team)))
			return false;

		std::vector<long> teammates = player_team->get_members();

		long check_uid = get_uid();

		for (long uid : teammates)
		{
			if (check_uid == uid)
			{
				return true;
			}
		}

		return false;
	}

	bool BasePlayer::is_knocked()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return bool();

		uintptr_t address1 = offsets::playerFlags;

		int flags = *reinterpret_cast<int*>(entity + address1);

		return flags & 64;
	}

	bool BasePlayer::is_sleeping()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return bool();

		uintptr_t address1 = offsets::playerFlags;

		int flags = *reinterpret_cast<int*>(entity + address1);

		return flags & 16;
	}

	void BasePlayer::longeye()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t eye = *reinterpret_cast<uintptr_t*>(this + 0x1672);
		memory::write<Vector3>(eye + 0x38, Vector3(0.0f, 4.0f, 0.0f));
	}
	bool BasePlayer::is_local_player()
	{
		if (variables::local_player == NULL)
			return false;

		auto temp = reinterpret_cast<BasePlayer*>(this);
		if (temp == variables::local_player)
			return true;
		else
			return false;
	}

	bool BasePlayer::is_visible(Vector3 end)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return bool();

		return functions::is_visible(get_bone_position(eyeTranform), end);
	}

	Vector3 BasePlayer::get_bone_position(int bone)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return Vector3();

		uintptr_t address1 = offsets::model;
		if (!address1)
			return Vector3();

		uintptr_t player_model = *reinterpret_cast<uintptr_t*>(entity + address1); //BaseEntity -> model.
		if (!(player_model))
			return Vector3();

		uintptr_t address2 = offsets::boneTransforms;

		uintptr_t bone_transforms = *reinterpret_cast<uintptr_t*>(player_model + address2);
		if (!(bone_transforms))
			return Vector3();

		Transform* entity_bone = *reinterpret_cast<Transform**>(bone_transforms + (0x20 + (bone * 0x8)));
		if (!entity_bone)
			return Vector3();

		return entity_bone->get_position();
	}

	Transform* BasePlayer::get_bone_transform(int bone)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return nullptr;

		uintptr_t address1 = offsets::model;
		if (!address1)
			return nullptr;

		uintptr_t player_model = *reinterpret_cast<uintptr_t*>(entity + address1); //BaseEntity -> model.
		if (!player_model)
			return nullptr;

		uintptr_t address2 = offsets::boneTransforms;

		uintptr_t bone_transforms = *reinterpret_cast<uintptr_t*>(player_model + address2);
		if (!(bone_transforms))
			return nullptr;

		Transform* entity_bone = *reinterpret_cast<Transform**>(bone_transforms + (0x20 + (bone * 0x8)));
		if (!entity_bone)
			return nullptr;

		return entity_bone;
	}

	bone_data BasePlayer::get_bone_data(int bone)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return bone_data();

		uintptr_t address1 = offsets::model; //il2cpp::value(xorstr_("BaseEntity"), xorstr_("model")); //PLayer -> model -> boneTransforms[];
		if (!address1)
			return bone_data();

		uintptr_t player_model = *reinterpret_cast<uintptr_t*>(entity + address1); //BaseEntity -> model.
		if (!(entity))
			return bone_data();

		uintptr_t address2 = offsets::boneTransforms; //il2cpp::value(xorstr_("Model"), xorstr_("boneTransforms"));

		uintptr_t bone_transforms = *reinterpret_cast<uintptr_t*>(player_model + address2);
		if (!(entity))
			return bone_data();

		Transform* entity_bone = *reinterpret_cast<Transform**>(bone_transforms + (0x20 + (bone * 0x8)));
		if (!(reinterpret_cast<uintptr_t>(entity_bone)))
			return bone_data();

		Vector3 bone_position = entity_bone->get_position();

		bool is_visible = functions::is_visible(variables::local_position, bone_position);

		return bone_data(bone, bone_position, is_visible, entity_bone);
	}

	uintptr_t BasePlayer::visiblePlayerList()
	{
		static auto clazz = il2cpp::init_class(xorstr_("BasePlayer"));
		if (!(clazz))
			return NULL;

		uintptr_t static_fields = *reinterpret_cast<uintptr_t*>(clazz + 0xB8);
		if (!(static_fields))
			return NULL;

		return *reinterpret_cast<uintptr_t*>(static_fields + 0x8); //private static ListDictionary<ulong, BasePlayer> visiblePlayerList; // 0x8
	}

	void BasePlayer::add_flag(int flag)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		auto address = offsets::playerFlags;

		int flags = *reinterpret_cast<int*>(entity + address);

		flags |= flag;

		memory::write<int>(entity + address, flags);
		return;
	}

	void BasePlayer::invite_to_team(BasePlayer* player)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);
		if (!(entity))
			return;

		uintptr_t method = offsets::invitetoteam; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto InviteToTeam = reinterpret_cast<void(*)(uintptr_t, BasePlayer*)>(method_ptr);
		SpoofReturn(InviteToTeam, entity, player);
	}

	BasePlayer* LocalPlayer::Entity()
	{
		static auto clazz = il2cpp::init_class(xorstr_("LocalPlayer"));
		if (!(clazz))
			return nullptr;

		uintptr_t static_fields = *reinterpret_cast<uintptr_t*>(clazz + 0xB8);
		if (!(static_fields))
			return nullptr;

		return *reinterpret_cast<BasePlayer**>(static_fields);
	}

	void LocalPlayer::ConsoleMessage(const char* message)
	{
		uintptr_t method = offsets::baseplayer_consolemessage; //il2cpp::method(xorstr_("Mathf"), xorstr_("Clamp"), 3, xorstr_("UnityEngine"));
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto consoleMessage = reinterpret_cast<void(*)(uintptr_t, il2cpp::il2cppstring*)>(method_ptr);
		uintptr_t blank = NULL;
		SpoofReturn(consoleMessage, blank, il2cpp::il2cppstring::New(message));
	}

	void ItemModProjectile::set_projectile_spread(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<float>(entity + offsets::itemmodprojectile_projectileSpread, value); // Rust_Offsets::Projectile::thickness);
	}

	void ItemModProjectile::set_projectile_velocity_spread(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<float>(entity + offsets::itemmodprojectile_projectileVelocitySpread, value);
	}

	float Projectile::get_thickness()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return false;

		return *reinterpret_cast<float*>(entity + offsets::projectile_thickness); // Rust_Offsets::Projectile::thickness);
	}

	float Projectile::get_integrity()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return false;

		return *reinterpret_cast<float*>(entity + offsets::projectile_integrity); //Rust_Offsets::Projectile::integrity);
	}

	float Projectile::get_traveled_distance()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return false;

		return *reinterpret_cast<float*>(entity + offsets::projectile_traveledDistance);//Rust_Offsets::Projectile::traveledDistance);
	}

	float Projectile::get_max_distance()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return false;

		return *reinterpret_cast<float*>(entity + offsets::projectile_maxDistance); //Rust_Offsets::Projectile::maxDistance);
	}

	float Projectile::get_move_delta_time()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return false;

		return *reinterpret_cast<float*>(entity + il2cpp::value(xorstr_("Projectile"), xorstr_("moveDeltaTime"))); //Rust_Offsets::Projectile::traveledTime);
	}

	float Projectile::get_drag()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return false;

		return *reinterpret_cast<float*>(entity + il2cpp::value(xorstr_("Projectile"), xorstr_("drag"))); //Rust_Offsets::Projectile::traveledTime);
	}

	Vector3 Projectile::get_current_position()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + il2cpp::value("Projectile", "currentPosition")); //Rust_Offsets::Projectile::traveledTime);
	}

	Vector3 Projectile::get_current_velocity()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + il2cpp::value(xorstr_("Projectile"), xorstr_("currentVelocity"))); //Rust_Offsets::Projectile::traveledTime);
	}

	float Projectile::get_traveled_time()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return false;

		return *reinterpret_cast<float*>(entity + offsets::projectile_traveledTime); //Rust_Offsets::Projectile::traveledTime);
	}

	bool Projectile::is_alive()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return false;

		return (this->get_integrity() > 0.001f && this->get_traveled_distance() < this->get_max_distance() && this->get_traveled_time() < 8);
	}

	void Projectile::set_thickness(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<float>(entity + offsets::projectile_thickness, value); //Rust_Offsets::Projectile::thickness) = value;
	}

	BasePlayer* Projectile::get_owner()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return nullptr;

		return *reinterpret_cast<BasePlayer**>(entity + offsets::projectile_owner); //*Rust_Offsets::HitTest::HitEntity);
	}

	ItemModProjectile* Projectile::get_item_mod_projectile()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return nullptr;

		return *reinterpret_cast<ItemModProjectile**>(entity + offsets::projectile_mod); //*Rust_Offsets::HitTest::HitEntity);
	}

	Vector3 Projectile::get_initial_velocity()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + offsets::projectile_initialVelocity);
	}

	float Projectile::get_gravity_modifier()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return float();

		return *reinterpret_cast<float*>(entity + offsets::projectile_gravityModifier);
	}

	void Projectile::set_current_velocity(Vector3 value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!entity)
			return;

		*reinterpret_cast<Vector3*>(entity + offsets::projectile_currentVelocity) = value; //Rust_Offsets::Projectile::traveledTime);
	}

	BaseEntity* HitTest::get_hit_entity()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return nullptr;

		return *reinterpret_cast<BaseEntity**>(entity + offsets::hittest_hitEntity);
	}

	Vector3 HitTest::get_hit_normal()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + offsets::hittest_hitNormal);
	}

	void HitTest::set_hit_entity(BaseEntity* new_entity)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<BaseEntity*>(entity + offsets::hittest_hitEntity, new_entity);
	}

	void HitTest::set_hit_transform(Transform* new_transform)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<Transform*>(entity + offsets::hittest_hitTransform, new_transform);
	}

	void HitTest::set_hit_hitpoint(Vector3 new_hitpoint)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<Vector3>(entity + offsets::hittest_hitPoint, new_hitpoint);
	}

	void HitTest::set_hit_distance(float distance)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<float>(entity + offsets::hittest_hitDistance, distance);
	}

	void HitTest::set_did_hit(bool value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<bool>(entity + offsets::hittest_didHit, value);
	}

	void HitTest::set_attack_ray(Ray value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<Ray>(entity + offsets::hittest_attackray, value);
	}

	void HitTest::set_max_distance(float value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<bool>(entity + offsets::hittest_maxDistance, value);
	}

	void HitTest::set_damage_properties(uintptr_t value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<uintptr_t>(entity + offsets::hittest_damageProperties, value);
	}

	void HitTest::set_hit_normal(Vector3 value)
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return;

		memory::write<Vector3>(entity + offsets::hittest_hitNormal, value);
	}

	BaseEntity* HitInfo::get_initiator()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return nullptr;

		return *reinterpret_cast<BaseEntity**>(entity + il2cpp::value(xorstr_("HitInfo"), xorstr_("Initiator")));
	}

	BaseEntity* HitInfo::get_hit_entity()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return nullptr;

		return *reinterpret_cast<BaseEntity**>(entity + il2cpp::value(xorstr_("HitInfo"), xorstr_("HitEntity")));
	}

	int HitInfo::get_hit_bone()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return NULL;

		return *reinterpret_cast<int*>(entity + il2cpp::value(xorstr_("HitInfo"), xorstr_("HitBone")));
	}

	Vector3 HitInfo::get_hit_start()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + il2cpp::value(xorstr_("HitInfo"), xorstr_("PointStart")));
	}

	Vector3 HitInfo::get_hit_end()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + il2cpp::value(xorstr_("HitInfo"), xorstr_("PointEnd")));
	}

	Vector3 HitInfo::get_hit_position_world()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + il2cpp::value(xorstr_("HitInfo"), xorstr_("HitPositionWorld")));
	}

	Vector3 HitInfo::get_hit_position_local()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + il2cpp::value(xorstr_("HitInfo"), xorstr_("HitPositionLocal")));
	}

	Vector3 HitInfo::get_hit_velocity()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return Vector3();

		return *reinterpret_cast<Vector3*>(entity + il2cpp::value(xorstr_("HitInfo"), xorstr_("ProjectileVelocity")));
	}

	float HitInfo::get_hit_distance()
	{
		uintptr_t entity = reinterpret_cast<uintptr_t>(this);

		if (!(entity))
			return float();

		return *reinterpret_cast<float*>(entity + il2cpp::value(xorstr_("HitInfo"), xorstr_("ProjectileDistance")));
	}

	bool BuildingBlock::can_afford(int grade, BasePlayer* player)
	{
		uintptr_t method = offsets::buildingblock_canaffordupgrade; //il2cpp::method(xorstr_("Input"), xorstr_("GetKey"), 1, xorstr_("UnityEngine"));
		if (!method)
		{
			return false;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return false;
		}

		auto CanAffordUpgrade = reinterpret_cast<bool(*)(uintptr_t, int, uintptr_t)>(method_ptr);
		return SpoofReturn(CanAffordUpgrade, reinterpret_cast<uintptr_t>(this), grade, (uintptr_t)player);
	}

	bool BuildingBlock::can_upgrade(int grade, BasePlayer* player)
	{
		uintptr_t method = offsets::buildingblock_canchangetograde; //il2cpp::method(xorstr_("Input"), xorstr_("GetKey"), 1, xorstr_("UnityEngine"));
		if (!method)
		{
			return false;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return false;
		}

		auto CanChangeToGrade = reinterpret_cast<bool(*)(uintptr_t, int, uintptr_t)>(method_ptr);
		return SpoofReturn(CanChangeToGrade, reinterpret_cast<uintptr_t>(this), grade, (uintptr_t)player);
	}

	void BuildingBlock::upgrade(int grade, BasePlayer* player)
	{
		uintptr_t method = offsets::buildingblock_upgradetograde;
		if (!method)
		{
			return;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return;
		}

		auto UpgradeToGrade = reinterpret_cast<void(*)(uintptr_t, int, uintptr_t)>(method_ptr);
		SpoofReturn(UpgradeToGrade, reinterpret_cast<uintptr_t>(this), grade, (uintptr_t)player);
	}

	void TOD_NightParameters::set_light_intensity(float intensity)
	{
		if (!this)
			return;

		*reinterpret_cast<float*>(this + offsets::tod_nightparameters_lightintensity) = intensity;
	}

	void TOD_NightParameters::set_reflection_multiplier(float multiplier)
	{
		if (!this)
			return;

		*reinterpret_cast<float*>(this + offsets::tod_nightparameters_reflectionmultiplier) = multiplier;
	}

	void TOD_NightParameters::set_ambient_multiplier(float multiplier)
	{
		if (!this)
			return;

		*reinterpret_cast<float*>(this + offsets::tod_nightparameters_ambientmultiplier) = multiplier;
	}

	void TOD_DayParameters::set_ambient_multiplier(float multiplier)
	{
		if (!this)
			return;

		*reinterpret_cast<float*>(this + offsets::tod_nightparameters_ambientmultiplier) = multiplier;
	}

	TOD_Sky* TOD_Sky::get_instance()
	{
		uintptr_t method = offsets::tod_sky_get_instance;
		if (!method)
		{
			return nullptr;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return nullptr;
		}

		auto get_instance = reinterpret_cast<TOD_Sky * (*)()>(method_ptr);
		SpoofReturn(get_instance);
	}

	TOD_NightParameters* TOD_Sky::get_night()
	{
		if (!this)
			return nullptr;

		return *reinterpret_cast<TOD_NightParameters**>(this + offsets::tod_nightparameters);
	}

	TOD_DayParameters* TOD_Sky::get_day()
	{
		if (!this)
			return nullptr;

		return *reinterpret_cast<TOD_DayParameters**>(this + offsets::tod_nightparameters);
	}

	il2cpp::il2cppstring* DownloadHandler::GetText()
	{
		if (!this)
			return il2cpp::il2cppstring::New("Failed to get Text!");

		uintptr_t method = offsets::download_handler_get_text;
		if (!method)
		{
			return il2cpp::il2cppstring::New("Failed to get Text!");
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return il2cpp::il2cppstring::New("Failed to get Text!");
		}

		auto get_Text = reinterpret_cast<il2cpp::il2cppstring * (*)(uintptr_t)>(method_ptr);
		return SpoofReturn(get_Text, (uintptr_t)this);
	}

	UnityWebRequest* UnityWebRequest::Get(il2cpp::il2cppstring* url)
	{
		uintptr_t method = offsets::unity_web_request_get;
		if (!method)
		{
			std::cout << "Failed to get UWR::GET method: " << method << std::endl;
			auto new_method = il2cpp::method(xorstr_("UnityWebRequest"), xorstr_("Get"), 1, "Networking");
			if (!new_method)
			{
				std::cout << "Failed to get NEW UWR::GET method: " << new_method << std::endl;
				return nullptr;
			}
			else
			{
				method = new_method;
			}
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return nullptr;
		}

		auto get = reinterpret_cast<UnityWebRequest * (*)(il2cpp::il2cppstring*)>(method_ptr);
		return SpoofReturn(get, url);
	}

	uintptr_t UnityWebRequest::SendWebRequest()
	{
		if (!this)
			return uintptr_t();

		uintptr_t method = offsets::unity_web_request_send_web_request;
		if (!method)
		{
			return uintptr_t();
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return uintptr_t();
		}

		auto sendwebrequest = reinterpret_cast<uintptr_t(*)(uintptr_t)>(method_ptr);
		SpoofReturn(sendwebrequest, (uintptr_t)this);
	}

	long UnityWebRequest::GetResponseCode()
	{
		if (!this)
			return long();

		uintptr_t method = offsets::unity_web_request_get_response_code;
		if (!method)
		{
			return long();
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return long();
		}

		auto sendwebrequest = reinterpret_cast<long(*)(uintptr_t)>(method_ptr);
		return SpoofReturn(sendwebrequest, (uintptr_t)this);
	}

	DownloadHandler* UnityWebRequest::GetDownloadHandler()
	{
		if (!this)
			return nullptr;

		uintptr_t method = offsets::unity_web_request_get_download_handler;
		if (!method)
		{
			return nullptr;
		}

		uintptr_t method_ptr = *reinterpret_cast<uintptr_t*>(method);
		if (!method_ptr)
		{
			return nullptr;
		}

		auto getdownloadhandler = reinterpret_cast<DownloadHandler * (*)(uintptr_t)>(method_ptr);
		return SpoofReturn(getdownloadhandler, (uintptr_t)this);
	}
}
