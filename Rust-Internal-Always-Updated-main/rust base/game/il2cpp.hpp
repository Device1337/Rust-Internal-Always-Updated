#pragma once
#include "../includes.hpp"
#include "../utils/lazy_importer.hpp"

#define STR_MERGE_IMPL(a, b) a##b
#define STR_MERGE(a, b) STR_MERGE_IMPL(a, b)
#define MAKE_PAD(size) STR_MERGE(_pad, __COUNTER__)[size]
#define DEFINE_MEMBER_N(type, name, offset) struct {unsigned char MAKE_PAD(offset); type name;}
#define min(a,b)            (((a) < (b)) ? (a) : (b))
#define max(a,b)            (((a) > (b)) ? (a) : (b))

namespace il2cpp
{


	void init();
	uintptr_t init_class(const char* name, const char* name_space = (""));
	int m_strcmp(const char* s1, const char* s2);
	uintptr_t method(std::string kl, std::string name, int param_count, const char* name_space = (""), bool param_check = false, int param_idx = 0, std::string param_name = "");
	uintptr_t method_alt(const char* kl, const char* name, int argument_number = -1, const char* arg_name = "", const char* name_space = (""), int selected_argument = -1);
	uintptr_t hook(void* our_func, std::string kl, std::string name, int arg, const char* name_space = (""));
	uintptr_t hook_virtual_function(const char* classname, const char* function_to_hook, void* our_func, int param_count, const char* name_space = (""));
	uintptr_t field(uintptr_t klass, const char* field_name);
	uintptr_t value(const char* kl, const char* name, bool get_offset = true, const char* name_space = (""));
	void appendLineToFile(std::string filepath, std::string line);
	void dump_class_offsets(std::string k1, const char* name_space = (""));
	ULONG64 get_module_base(const char* Name = xorstr_("GameAssembly.dll"));
	void list_virtual_functions(const char* kl, const char* name_space = (""));
	uintptr_t type_object(const char* name_space, const char* name);

	class il2cppstring
	{
	public:
		char pad_0000[0x10];
		int len;
		wchar_t buffer[0];

		static il2cppstring* New(const char* str);
	};

	namespace methods
	{
		using il2cpp_domain_get = uintptr_t(*)();
		static il2cpp_domain_get domain_get = LI_FIND_DEF(il2cpp_domain_get);//LI_FIND_DEF(il2cpp_domain_get);

		using il2cpp_class_get_methods = uintptr_t(*)(uintptr_t, uintptr_t*);
		static auto class_get_methods = LI_FIND_DEF(il2cpp_class_get_methods);

		using il2cpp_method_get_param = uintptr_t(*)(uintptr_t, int);
		static auto method_get_param = LI_FIND_DEF(il2cpp_method_get_param);

		using il2cpp_method_get_param_count = int (*)(uintptr_t);
		static auto method_get_param_count = LI_FIND_DEF(il2cpp_method_get_param_count);

		using il2cpp_assembly_get_image = uintptr_t(*)(uintptr_t);
		static auto assembly_get_image = LI_FIND_DEF(il2cpp_assembly_get_image);

		using il2cpp_domain_get_assemblies = uintptr_t * (*)(void* domain, uintptr_t* size);
		static auto domain_get_assemblies = LI_FIND_DEF(il2cpp_domain_get_assemblies);

		using il2cpp_object_new = uintptr_t(*)(uintptr_t);
		static auto object_new = LI_FIND_DEF(il2cpp_object_new);

		using il2cpp_type_get_object = uintptr_t(*)(uintptr_t);
		static auto type_get_object = LI_FIND_DEF(il2cpp_type_get_object);

		using il2cpp_class_get_type = uintptr_t(*)(uintptr_t);
		static auto class_get_type = LI_FIND_DEF(il2cpp_class_get_type);

		using il2cpp_class_from_name = uintptr_t(*)(uintptr_t, const char*, const char*);
		static auto class_from_name = LI_FIND_DEF(il2cpp_class_from_name);

		using il2cpp_resolve_icall = uintptr_t(*)(const char*);
		static auto resolve_icall = LI_FIND_DEF(il2cpp_resolve_icall);

		using il2cpp_class_get_field_from_name = uintptr_t(*)(uintptr_t, const char*);
		static auto class_get_field_from_name = LI_FIND_DEF(il2cpp_class_get_field_from_name);

		using il2cpp_field_static_get_value = uintptr_t(*)(uintptr_t, uintptr_t*);
		static auto field_static_get_value = LI_FIND_DEF(il2cpp_field_static_get_value);

		using il2cpp_class_get_fields = uintptr_t(*)(uintptr_t, uintptr_t*);
		static auto class_get_fields = LI_FIND_DEF(il2cpp_class_get_fields);

		using il2cpp_field_get_offset = uintptr_t(*)(uintptr_t);
		static auto field_get_offset = LI_FIND_DEF(il2cpp_field_get_offset);

		using il2cpp_runtime_class_init = uintptr_t(*)(uintptr_t);
		static auto runtime_class_init = LI_FIND_DEF(il2cpp_runtime_class_init);

		using il2cpp_string_new_wrapper = il2cppstring * (*)(const char*);
		static auto new_string = LI_FIND_DEF(il2cpp_string_new_wrapper);

		using  il2cpp_class_get_method_from_name = uintptr_t(*)(uintptr_t, const char*, int);
		static il2cpp_class_get_method_from_name class_get_method_from_name = LI_FIND_DEF(il2cpp_class_get_method_from_name);
	}
}