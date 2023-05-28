#pragma once
#include "../includes.hpp"
#include "il2cpp.hpp"

#define print(a, args) printf("%s(%s:%d) " a,  __func__,__FILE__, __LINE__, ##args)
#define println(a, args) print(a "\n", ##args)
#define min(a,b)            (((a) < (b)) ? (a) : (b))

bool is_valid(uintptr_t variable);

template<typename T, typename... Args>
inline T call(const char* func, Args... args);

struct weapon_data {
	float initial_velocity;
	float gravity_modifier;
	float drag;
	float initial_distance;
};

enum ammo_types : int32_t {
	shotgun = -1685290200,
	shotgun_slug = -727717969,
	shotgun_fire = -1036635990,
	shotgun_handmade = 588596902,

	rifle_556 = -1211166256,
	rifle_556_hv = 1712070256,
	rifle_556_fire = 605467368,
	rifle_556_explosive = -1321651331,

	pistol = 785728077,
	pistol_hv = -1691396643,
	pistol_fire = 51984655,

	arrow_wooden = -1234735557,
	arrow_hv = -1023065463,
	arrow_fire = 14241751,
	arrow_bone = 215754713,

	nailgun_nails = -2097376851
};

enum weapon_types : int32_t {
	spear_stone = 1602646136,
	spear_wooden = 1540934679
};

enum BoneList : int
{
	l_hip = 1,
	l_knee,
	l_foot,
	l_toe,
	l_ankle_scale,
	pelvis,
	penis,
	GenitalCensor,
	GenitalCensor_LOD0,
	Inner_LOD0,
	GenitalCensor_LOD1,
	GenitalCensor_LOD2,
	r_hip,
	r_knee,
	r_foot,
	r_toe,
	r_ankle_scale,
	spine1,
	spine1_scale,
	spine2,
	spine3,
	spine4,
	l_clavicle,
	l_upperarm,
	l_forearm,
	l_hand,
	l_index1,
	l_index2,
	l_index3,
	l_little1,
	l_little2,
	l_little3,
	l_middle1,
	l_middle2,
	l_middle3,
	l_prop,
	l_ring1,
	l_ring2,
	l_ring3,
	l_thumb1,
	l_thumb2,
	l_thumb3,
	IKtarget_righthand_min,
	IKtarget_righthand_max,
	l_ulna,
	neck,
	head,
	jaw,
	eyeTranform,
	l_eye,
	l_Eyelid,
	r_eye,
	r_Eyelid,
	r_clavicle,
	r_upperarm,
	r_forearm,
	r_hand,
	r_index1,
	r_index2,
	r_index3,
	r_little1,
	r_little2,
	r_little3,
	r_middle1,
	r_middle2,
	r_middle3,
	r_prop,
	r_ring1,
	r_ring2,
	r_ring3,
	r_thumb1,
	r_thumb2,
	r_thumb3,
	IKtarget_lefthand_min,
	IKtarget_lefthand_max,
	r_ulna,
	l_breast,
	r_breast,
	BoobCensor,
	BreastCensor_LOD0,
	BreastCensor_LOD1,
	BreastCensor_LOD2,
	collision,
	displacement
};

enum class KeyCode
{
	Backspace = 8,
	Delete = 127,
	Tab = 9,
	Clear = 12,
	Return = 13,
	Pause = 19,
	Escape = 27,
	Space = 32,
	Keypad0 = 256,
	Keypad1 = 257,
	Keypad2 = 258,
	Keypad3 = 259,
	Keypad4 = 260,
	Keypad5 = 261,
	Keypad6 = 262,
	Keypad7 = 263,
	Keypad8 = 264,
	Keypad9 = 265,
	KeypadPeriod = 266,
	KeypadDivide = 267,
	KeypadMultiply = 268,
	KeypadMinus = 269,
	KeypadPlus = 270,
	KeypadEnter = 271,
	KeypadEquals = 272,
	UpArrow = 273,
	DownArrow = 274,
	RightArrow = 275,
	LeftArrow = 276,
	Insert = 277,
	Home = 278,
	End = 279,
	PageUp = 280,
	PageDown = 281,
	F1 = 282,
	F2 = 283,
	F3 = 284,
	F4 = 285,
	F5 = 286,
	F6 = 287,
	F7 = 288,
	F8 = 289,
	F9 = 290,
	F10 = 291,
	F11 = 292,
	F12 = 293,
	F13 = 294,
	F14 = 295,
	F15 = 296,
	Alpha0 = 48,
	Alpha1 = 49,
	Alpha2 = 50,
	Alpha3 = 51,
	Alpha4 = 52,
	Alpha5 = 53,
	Alpha6 = 54,
	Alpha7 = 55,
	Alpha8 = 56,
	Alpha9 = 57,
	Exclaim = 33,
	DoubleQuote = 34,
	Hash = 35,
	Dollar = 36,
	Percent = 37,
	Ampersand = 38,
	Quote = 39,
	LeftParen = 40,
	RightParen = 41,
	Asterisk = 42,
	Plus = 43,
	Comma = 44,
	Minus = 45,
	Period = 46,
	Slash = 47,
	Colon = 58,
	Semicolon = 59,
	Less = 60,
	Equals = 61,
	Greater = 62,
	Question = 63,
	At = 64,
	LeftBracket = 91,
	Backslash = 92,
	RightBracket = 93,
	Caret = 94,
	Underscore = 95,
	BackQuote = 96,
	A = 97,
	B = 98,
	C = 99,
	D = 100,
	E = 101,
	F = 102,
	G = 103,
	H = 104,
	I = 105,
	J = 106,
	K = 107,
	L = 108,
	M = 109,
	N = 110,
	O = 111,
	P = 112,
	Q = 113,
	R = 114,
	S = 115,
	T = 116,
	U = 117,
	V = 118,
	W = 119,
	X = 120,
	Y = 121,
	Z = 122,
	LeftCurlyBracket = 123,
	Pipe = 124,
	RightCurlyBracket = 125,
	Tilde = 126,
	Numlock = 300,
	CapsLock = 301,
	ScrollLock = 302,
	RightShift = 303,
	LeftShift = 304,
	RightControl = 305,
	LeftControl = 306,
	RightAlt = 307,
	LeftAlt = 308,
	LeftCommand = 310,
	LeftApple = 310,
	LeftWindows = 311,
	RightCommand = 309,
	RightApple = 309,
	RightWindows = 312,
	AltGr = 313,
	Help = 315,
	Pr = 316,
	SysReq = 317,
	Break = 318,
	Menu = 319,
	Mouse0 = 323,
	Mouse1 = 324,
	Mouse2 = 325,
	Mouse3 = 326,
	Mouse4 = 327,
	Mouse5 = 328,
	Mouse6 = 329
};

enum class QueryTriggerInteraction
{
	// Token: 0x0400005B RID: 91
	UseGlobal,
	// Token: 0x0400005C RID: 92
	Ignore,
	// Token: 0x0400005D RID: 93
	Collide
};

enum class Layers
{
	Terrain = 8388608,
	World = 65536,
	Ragdolls = 512,
	Construction = 2097152,
	ConstructionSocket = 4194304,
	Craters = 1,
	GameTrace = 16384,
	Trigger = 262144,
	VehiclesDetailed = 8192,
	RainFall = 1101070337,
	Deploy = 1235288065,
	DefaultDeployVolumeCheck = 537001984,
	BuildLineOfSightCheck = 2097152,
	ProjectileLineOfSightCheck = 2162688,
	ProjectileLineOfSightCheckTerrain = 10551296,
	MeleeLineOfSightCheck = 2162688,
	EyeLineOfSightCheck = 2162688,
	EntityLineOfSightCheck = 1218519041,
	PlayerBuildings = 18874624,
	PlannerPlacement = 161546496,
	Solid = 1218652417,
	VisCulling = 10551297,
	AltitudeCheck = 1218511105,
	HABGroundEffect = 1218511105,
	AILineOfSight = 1218519297,
	DismountCheck = 1486946561,
	AIPlacement = 278986753,
	WheelRay = 1235321089,
};

enum class layer : uint32_t {
	Default = 0,
	TransparentFX = 1,
	Ignore_Raycast = 2,
	Reserved1 = 3,
	Water = 4,
	UI = 5,
	Reserved2 = 6,
	Reserved3 = 7,
	Deployed = 8,
	Ragdoll = 9,
	Invisible = 10,
	AI = 11,
	PlayerMovement = 12,
	Vehicle_Detailed = 13,
	Game_Trace = 14,
	Vehicle_World = 15,
	World = 16,
	Player_Server = 17,
	Trigger = 18,
	Player_Model_Rendering = 19,
	Physics_Projectile = 20,
	Construction = 21,
	Construction_Socket = 22,
	Terrain = 23,
	Transparent = 24,
	Clutter = 25,
	Debris = 26,
	Vehicle_Large = 27,
	Prevent_Movement = 28,
	Prevent_Building = 29,
	Tree = 30,
	Unused2 = 31
};

enum class EventType
{
	MouseDown = 0,
	MouseUp = 1,
	MouseMove = 2,
	MouseDrag = 3,
	KeyDown = 4,
	KeyUp = 5,
	ScrollWheel = 6,
	Repaint = 7,
	Layout = 8,
	DragUpdated = 9,
	DragPerform = 10,
	DragExited = 15,
	Ignore = 11,
	Used = 12,
	ValidateCommand = 13,
	ExecuteCommand = 14,
	ContextClick = 16,
	MouseEnterWindow = 20,
	MouseLeaveWindow = 21
};

enum class MessageType : int // TypeDefIndex: 6667
{
	Welcome = 1,
	Auth = 2,
	Approved = 3,
	Ready = 4,
	Entities = 5,
	EntityDestroy = 6,
	GroupChange = 7,
	GroupDestroy = 8,
	RPCMessage = 9,
	EntityPosition = 10,
	ConsoleMessage = 11,
	ConsoleCommand = 12,
	Effect = 13,
	DisconnectReason = 14,
	Tick = 15,
	Message = 16,
	RequestUserInformation = 17,
	GiveUserInformation = 18,
	GroupEnter = 19,
	GroupLeave = 20,
	VoiceData = 21,
	EAC = 22,
	EntityFlags = 23,
	World = 24,
	ConsoleReplicatedVars = 25,
	Last = 25
};

class BufferList
{
public:
	char pad_0000[0x10];
	int32_t size;
	char pad_0014[0x4];
	void* buffer;
};

class ListDictionary
{
public:
	char pad_0000[0x20];
	class BufferList* keys;
	class BufferList* vals;
};

std::wstring			   get_name(uintptr_t object);

template<typename T>
class laddy_list {
public:
	T get(uint32_t idx)
	{
		const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}

	T get_value(uint32_t idx)
	{
		const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
		const auto internal_list = list + 0x20;
		return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
	}

	const uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }
};


namespace functions
{
	bool					WorldToScreen(const Vector3& EntityPos, Vector2& ScreenPos);
	Vector3					WorldToScreenAlt(Vector3 position);
	char* memstr(char* haystack, const char* needle, int size);
	uintptr_t				scan_for_camera_list();
	int						strCmp(const char* s1, const char* s2);
	size_t					my_strlen(const char* str);
	bool					update_view_matrix();
	Vector3					get_camera_pos();
	Vector3					get_mouse_pos();
	int						get_screen_width();
	int						get_screen_height();
	std::string				ws2s(const std::wstring& wstr);
	std::wstring			s2ws(const std::string& str);
	std::wstring			read_unicode(uint64_t address, std::size_t size);
	std::string				read_ascii(uint64_t address, std::size_t size = 0x50);
	const char* read_ascii_alt(uint64_t address);
	bool					get_key_down(KeyCode key);
	bool					get_key_up(KeyCode key);
	bool					get_key(KeyCode key);
	void					ignore_layer_collision(layer the_layer, layer ignore_layer, bool should_collide);
	bool					line_of_sight(Vector3 start, Vector3 end, Layers layer_mask, float padding = 0);
	bool					is_visible(Vector3 start, Vector3 end);
	void					set_timescale(float value);
	float					clamp(float value, float min, float max);
	float					mathf_atan2(float y, float x);
	float					mathf_abs(float f);
	float					mathf_max(float a, float b);
	void					setup_bullet_data();
	laddy_list<uintptr_t>* get2renderers(uintptr_t multimesh);
	uintptr_t				get_material(uintptr_t renderer);
	uintptr_t				get_shader(uintptr_t material);
	uintptr_t				load_asset(uintptr_t assetbundle, std::string shader, uintptr_t typeobject);
	uintptr_t				load_bundle_file(std::string data);
	uintptr_t				find(const char* shader);
	void					set_shader(uintptr_t material, uintptr_t shader);
	void					set_color(uintptr_t material, const char* name, Vector4 color);
	void					set_material_int(uintptr_t material, const char* name, int value);
	uintptr_t				get_current();
	EventType				get_event_type(uintptr_t current);
	uintptr_t				get_draw_skin();
	uintptr_t				get_white_texture();
	uintptr_t				get_guicontent_temp(il2cpp::il2cppstring* content);
	void					set_draw_font_size(uintptr_t label, int size);
	void					set_draw_color(Vector4 color);
	void					set_draw_alignment(uintptr_t label, uintptr_t value);
	void					set_cursor_lockstate(int value);
	void					create(uintptr_t self, const char* shader);
	void					dont_destroy_on_load(uintptr_t target);
	void					add_component(uintptr_t self, uintptr_t componentType);
	void					draw_texture(Vector4 position, uintptr_t texture);
	void					outline_box(Vector2 position, Vector2 size, Vector4 color, float girth = 2.f);
	void					fill_box(Vector4 position, Vector4 color);
	void					line(Vector2 point1, Vector2 point2, Vector4 color);
	void					label(Vector4 position, std::string text, Vector4 color, bool centered = false, float font_size = 12);
	void					outline(Vector4 position, std::string text, Vector4 color, bool centered = false, float font_size = 12);
	void					ddraw_get();
	float					getprojectilevelocityscale(uintptr_t base_projectile, bool max);
	uintptr_t				CreatePrefab(const char* prefab, bool active = true);
	void					Destroy(uintptr_t object);
	float					get_time();
	float					get_deltaTime();
	void					ddraw_line(Vector3 start, Vector3 end, Vector4 color, float duration = 1.0f, bool distanceFade = true, bool ztest = true);
	void					ddraw_arrow(Vector3 start, Vector3 end, float size, Vector4 color, float duration = 0.5f);
	void					ddraw_text(il2cpp::il2cppstring* text, Vector3 pos, Vector4 color, float duration = 0.5f);
	void					ddraw_screentext(il2cpp::il2cppstring* text, float x, Vector4 color, float duration = 0.5f);
	float					random_range(float min, float max);
	bool					physics_checkcapsule(Vector3 start, Vector3 end, float radius, int layer_mask, QueryTriggerInteraction querytriggerinteraction);
}

class bone_data;

struct bounds_t {
	float left, right, top, bottom;
};

namespace rust
{
	class HitTest;

	class Transform
	{
	public:
		Vector3				get_position();
		void				set_position(Vector3 value);
		Vector3				inverse_tranform_point(Vector3 point);
		Vector3				transform_direction(Vector3 direction);
	};

	class BaseEntity
	{
	public:
		std::wstring		get_name();
		std::string			get_prefab_name();
		std::string			get_class_name();
		Vector3				get_visual_position(uintptr_t object_class);
		void				longeyes();
		Vector3				get_closest_point(Vector3 position);
		Transform* get_transform();
		void				set_hit_direction(Vector3 value);
		void				server_rpc(const char*);
		static void			server_rpc(uintptr_t, const char*);
		void				send_signal_broadcast(int signal, const char* arg = "");
	};

	class BaseMelee
	{
	public:
		static inline void (*ProcessAttack_)(BaseMelee*, HitTest*) = nullptr;
		void ProcessAttack(HitTest* test)
		{
			return ProcessAttack_(this, test);
		}
	};

	class BaseCombatEntity : public BaseEntity
	{
	public:
		float				get_health();
		float				get_max_health();
		int					get_life_state();
	};

	class RigidBody
	{
	public:
		void				set_velocity(Vector3 val);
	};

	class PlayerWalkMovement
	{
	public:
		RigidBody* get_body();
		void				set_ground_angle(float angle);
		void				set_ground_angle_new(float angle);
		void				set_max_angle_walking(float angle);
		void				set_max_angle_climbing(float angle);
		void				set_ground_time(float time);
		void				set_gravity_multiplier(float multiplier);
		void				set_jump_time(float time);
		void				set_land_time(float time);
		void				set_targetmovement(Vector3);
		bool				ducking();
		bool				swimming();
		bool				flying();
		bool				spiderman();
		bool				fun();
		void				ShootInAir();
		void				Water();

	};

	class PlayerInput
	{
	public:
		Vector2				get_view_angles();
		Vector2				get_recoil_angles();
		void				set_view_angles(Vector2 angle);
		void				set_recoil_angles(Vector2 angle);
	};

	class ItemDefinition : public BaseEntity
	{
	public:
		int					get_itemid();
		std::wstring		get_shortname();

	};

	class BaseProjectile : public BaseEntity
	{
	public:
		class Magazine : public BaseEntity
		{
		public:
			ItemDefinition* get_ammotype();
		};

		Magazine* get_primaryMagazine();
	};

	class Item : public BaseEntity
	{
	public:
		int					get_amount();
		int					get_uid();
		void				Fastbow();
		int32_t				get_definition_id();
		std::wstring		get_name();
		Vector3				get_visual_position(uintptr_t);
		bool				get_recoil_min_max();
		float				get_bullet_velocity();
		float				get_bullet_gravity();
		BaseEntity* get_held_entity();
		weapon_data			get_weapon_data();
		uintptr_t			get_damage_properties();
		float				get_repeat_delay();
		void				NoahBullets(float);
		void				set_automatic(bool);
		void				set_rapid_fire(float);
		void				set_always_eoka(float);
		void				set_aim_sway(float);
		int					ammocount();
		int					maxammo();
		void				Norecoil(float);
		float				ReloadTime();
		void				set_aim_sway_speed(float);
		void				set_aim_cone(float);
		void				set_aim_cone_curve_scale(float);
		void				set_hip_aim_cone(float);
		void				set_aim_cone_penalty_max(float);
		void				set_aim_cone_penalty_per_shot(float);

		void				start_attack_cooldown(float);
		void				process_attack(HitTest*);
		void				ExtMelee();
		void				instabow();
		bool				is_melee();
		void				instacharge();
		bool				is_gun();
	};

	class ItemContainer
	{
	public:
		Item* get_item(int);
	};

	class PlayerInventory
	{
	public:
		ItemContainer* get_belt();
	};

	class TeamMember : public BaseEntity
	{
	public:
		long				get_uid();
	};

	class PlayerTeam
	{
	public:
		std::vector<long>	get_members();
	};

	class PlayerModel
	{
	public:
		Vector3				get_position(); //0x218
		Vector3				get_velocity();
		uintptr_t			get_multimesh();
		bool				is_npc();
		void				set_velocity(Vector3);
		void				set_position(Vector3);
	};

	class ModelState
	{
	public:
		void				set_onLadder(bool value);
		void				remove_flag(int flag);
		void				add_flag(int flag);
		bool				has_flag(int flag);
	};



	class PlayerEyes : public BaseEntity
	{
	public:
		Vector3             get_viewoffset();
		Vector3				get_position();
		Vector3				get_center();
		Vector3				get_bodyforward();
		Vector3				get_bodyright();
		void				set_position(Vector3 value);
		void				set_center(Vector3 value);
		void				set_body_rotation(Vector4 value);
		void				set_view_offset(Vector3 value);
	};

	template<typename T>
	class list {
	public:
		T get(uint32_t idx)
		{
			const auto internal_list = reinterpret_cast<uintptr_t>(this + 0x20);
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T get_value(uint32_t idx)
		{
			const auto list = *reinterpret_cast<uintptr_t*>((uintptr_t)this + 0x10);
			const auto internal_list = list + 0x20;
			return *reinterpret_cast<T*>(internal_list + idx * sizeof(T));
		}

		T operator[](uint32_t idx) { return get(idx); }

		const uint32_t get_size() { return *reinterpret_cast<uint32_t*>((uintptr_t)this + 0x18); }

		template<typename F>
		void for_each(const F callback)
		{
			for (auto i = 0; i < get_size(); i++) {
				auto object = this->get(i);
				if (!object)
					continue;
				callback(object, i);
			}
		}
	};


	class Attack
	{
	public:
		Vector3				get_point_start();
		Vector3				get_point_end();
		int					get_hit_id();
		int					get_hit_bone();
		Vector3				get_hit_normal_local();
		Vector3				get_hit_position_local();
		Vector3				get_hit_normal_world();
		Vector3				get_hit_position_world();
		int					get_hit_part_id();
		int					get_hit_material_id();
		int					get_hit_item();
	};

	class PlayerAttack
	{
	public:
		Attack* get_attack();
		int					get_projectile_id();
	};

	class PlayerProjectileAttack
	{
	public:
		PlayerAttack* get_player_attack();
		Vector3				get_hit_velocity();
		float				get_hit_distance();
		float				get_travel_time();
	};

	class PlayerTick
	{
	public:
		Vector3				get_position();
		void				SetTicks(float ticks);
		float				TicksPerSec();
	};

	class BasePlayer : public BaseCombatEntity
	{
	public:
		std::wstring		get_username();
		long				get_uid();
		int					get_active_weapon_id();
		PlayerWalkMovement* get_movement();
		PlayerInput* get_input();
		PlayerInventory* get_inventory();
		PlayerTeam* get_team();
		PlayerModel* get_model();
		ModelState* get_modelstate();
		PlayerEyes* get_eyes();
		PlayerTick* get_lastSentTick();
		Item* get_held_item();
		bool				is_same_team(BasePlayer* local_player);
		bool				is_knocked();
		bool				is_sleeping();
		void				longeye();
		bool				is_local_player();
		bool				is_visible(Vector3 end);
		Vector3				get_bone_position(int bone);
		Transform* get_bone_transform(int bone);
		bone_data	get_bone_data(int bone);
		static uintptr_t	visiblePlayerList();
		void				add_flag(int flag);
		void				invite_to_team(BasePlayer* player);
		float				get_radius();
		float				get_height(bool ducked);
		float				get_jumpheight();
		uintptr_t			object;
	};

	inline std::array<int, 20> valid_bones = {
		1, 2, 3, 5, 6, 14, 15, 17, 18, 21, 23, 24, 25, 26, 27, 48, 55, 56, 57, 76
	};
	struct box_bounds {
		float left, right, top, bottom;
		bool onscreen = false;

		bool empty() {
			if (this->left == 0 && this->right == 0 && this->top == 0 && this->bottom == 0)
				return true;

			if (this->left == FLT_MAX || this->right == FLT_MIN || this->top == FLT_MAX || this->bottom == FLT_MIN)
				return true;

			return false;
		}
		static box_bounds null() {
			return { 0, 0, 0, 0 };
		}
	};

	inline box_bounds get_bounds(rust::BasePlayer* player, float expand = 0) {
		box_bounds ret = { FLT_MAX, FLT_MIN, FLT_MAX, FLT_MIN };

		for (auto j : valid_bones) {
			auto transform = player->get_bone_transform(j);
			if (transform) {
				Vector2 sc;
				auto world_pos = transform->get_position();

				if (j == 48)
					world_pos.y += 0.2f;

				if (functions::WorldToScreen(world_pos, sc)) {
					Vector2 bone_screen = sc;

					if (bone_screen.x < ret.left)
						ret.left = bone_screen.x;
					if (bone_screen.x > ret.right)
						ret.right = bone_screen.x;
					if (bone_screen.y < ret.top)
						ret.top = bone_screen.y;
					if (bone_screen.y > ret.bottom)
						ret.bottom = bone_screen.y;
					ret.onscreen = true;
				}
			}
		}

		if (ret.left == FLT_MAX)
			return box_bounds::null();
		if (ret.right == FLT_MIN)
			return box_bounds::null();
		if (ret.top == FLT_MAX)
			return box_bounds::null();
		if (ret.bottom == FLT_MIN)
			return box_bounds::null();

		ret.left -= expand;
		ret.right += expand;
		ret.top -= expand;
		ret.bottom += expand;

		return ret;
	};

	class LocalPlayer : BasePlayer {
	public:
		static BasePlayer* Entity();
		static void			ConsoleMessage(const char* message);
	};

	class ItemModProjectile
	{
	public:
		void				set_projectile_spread(float value);
		void				set_projectile_velocity_spread(float value);
	};

	class Projectile : public BaseEntity
	{
	public:
		float				get_thickness();
		float				get_integrity();
		float				get_traveled_distance();
		float				get_max_distance();
		//float				get_partial_time();
		float				get_traveled_time();
		float				get_move_delta_time();
		float				get_gravity_modifier();
		float				get_drag();
		BasePlayer* get_owner();
		ItemModProjectile* get_item_mod_projectile();
		Vector3				get_initial_velocity();
		Vector3				get_current_position();
		Vector3				get_current_velocity();
		bool				is_alive();
		void				set_thickness(float value);
		void				set_current_velocity(Vector3);
	};

	struct Ray {
		Vector3 origin;
		Vector3 dir;
		Ray(Vector3 o, Vector3 d) {
			origin = o;
			dir = d;
		}
	};

	class HitTest
	{
	public:
		BaseEntity* get_hit_entity();
		Vector3				get_hit_normal();
		void				set_hit_entity(BaseEntity* entity);
		void				set_hit_transform(Transform* transform);
		void				set_hit_hitpoint(Vector3 hit_point);
		void				set_hit_distance(float distance);
		void				set_max_distance(float distance);
		void				set_did_hit(bool didhit);
		void				set_damage_properties(uintptr_t properties);
		void				set_attack_ray(Ray);
		void				set_hit_normal(Vector3);
	};

	class HitInfo
	{
	public:
		BaseEntity* get_initiator();
		BaseEntity* get_hit_entity();
		int					get_hit_bone();
		Vector3				get_hit_start();
		Vector3				get_hit_end();
		Vector3				get_hit_position_world();
		Vector3				get_hit_position_local();
		Vector3				get_hit_velocity();
		float				get_hit_distance();

	};

	class BuildingBlock
	{
	public:
		bool				can_afford(int grade, BasePlayer* player);
		bool				can_upgrade(int grade, BasePlayer* player);
		void				upgrade(int grade, BasePlayer* player);
	};

	class TOD_NightParameters
	{
	public:
		void				set_light_intensity(float intensity);
		void				set_reflection_multiplier(float multiplier);
		void				set_ambient_multiplier(float multiplier);
	};

	class TOD_DayParameters
	{
	public:
		void				set_ambient_multiplier(float multiplier);
	};

	class TOD_Sky
	{
	public:
		static TOD_Sky* get_instance();
		TOD_NightParameters* get_night();
		TOD_DayParameters* get_day();
	};

	class DownloadHandler
	{
	public:
		il2cpp::il2cppstring* GetText();
	};

	class UnityWebRequest
	{
	public:
		static UnityWebRequest* Get(il2cpp::il2cppstring* string);
		uintptr_t				SendWebRequest();
		DownloadHandler* GetDownloadHandler();
		long					GetResponseCode();
	};
}

class bone_data
{
public:
	int							index;
	Vector3						position;
	rust::Transform* transform;
	bool						is_visible;

	bone_data()
	{
		this->index = 0;
		this->position = Vector3();
		this->is_visible = false;
		this->transform = nullptr;
	}

	bone_data(int index, Vector3 position, bool visible, rust::Transform* trans)
	{
		this->index = index;
		this->position = position;
		this->is_visible = visible;
		this->transform = trans;
	}

	bool check_is_visible(Vector3 from)
	{
		return functions::is_visible(this->position, from);
	}
};

class player_data
{
public:
	int							player_uid;
	uintptr_t					object;
	rust::BasePlayer* player;
	std::vector<bone_data>		bones;
	bool						is_visible;

	player_data(int uid, uintptr_t object, rust::BasePlayer* player, std::vector<bone_data> bones, bool is_visible)
	{
		this->player_uid = uid;
		this->object = object;
		this->player = player;
		this->bones = bones;
		this->is_visible = is_visible;
	}

	bool operator==(player_data pd)
	{
		if (pd.player_uid == this->player_uid)
			return true;
		else
			return false;
	}

	bool operator==(int uid)
	{
		if (uid == this->player_uid)
			return true;
		else
			return false;
	}
};

class explosion_data
{
public:
	std::chrono::steady_clock::time_point start;
	rust::BaseEntity* entity;
	Vector3 position;
	std::string class_name;
	std::string prefab_name;
};

namespace variables
{
	extern uintptr_t asset_bundle;
	extern rust::BasePlayer* local_player;
	extern Vector3				local_position;
	extern Matrix4x4			view_matrix;
	extern int					screen_width;
	extern int					screen_height;
	extern int					image_width;
	extern int					image_height;
	//extern ID3D11ShaderResourceView* resource_view;
	//extern ImDrawList* draw_list;
	//extern ImFont* smallest_pixel_7_font;
	//extern std::vector<player_data> player_data;
	//extern std::vector<explosion_data> explosion_data;
	extern Vector2				mouse_position;
	extern Vector2				mouse_position_backup;
	extern bool					loaded;
	extern uintptr_t			draw_label;
	extern uintptr_t			white_texture;
	extern uintptr_t			camera_list;
	extern uintptr_t			client_entities;
	extern uintptr_t			debug_camera_address;
	extern uintptr_t			todSky;
	extern std::vector<rust::BasePlayer*> player_list;
	extern float				fly_hack_vert;
	extern float				fly_hack_vert_max;
	extern float				fly_hack_hori;
	extern float				fly_hack_hori_max;
	//extern chaiscript::ChaiScript chai;
	//extern ImFont* smallestpixel7;
}