#include "il2cpp.hpp"
#include <map>

std::map<const char*, uintptr_t> klasses;
std::map<const char*, uintptr_t> method_list;
std::map<const char*, uintptr_t> field_list;

uintptr_t il2cpp::get_module_base(const char* Name)
{
	return NULL;//LI_MODULE(Name).get<uintptr_t>();
}

void il2cpp::init()
{
	MUTATE_START
	using il2cpp_domain_get = uintptr_t(*)();
	methods::domain_get = LI_FIND_DEF(il2cpp_domain_get);

	using il2cpp_class_get_methods = uintptr_t(*)(uintptr_t, uintptr_t*);
	methods::class_get_methods = LI_FIND_DEF(il2cpp_class_get_methods);

	using il2cpp_method_get_param = uintptr_t(*)(uintptr_t, int);
	methods::method_get_param = LI_FIND_DEF(il2cpp_method_get_param);

	using il2cpp_method_get_param_count = int (*)(uintptr_t);
	methods::method_get_param_count = LI_FIND_DEF(il2cpp_method_get_param_count);

	using il2cpp_assembly_get_image = uintptr_t(*)(uintptr_t);
	methods::assembly_get_image = LI_FIND_DEF(il2cpp_assembly_get_image);

	using il2cpp_domain_get_assemblies = uintptr_t * (*)(void* domain, uintptr_t* size);
	methods::domain_get_assemblies = LI_FIND_DEF(il2cpp_domain_get_assemblies);

	using il2cpp_class_from_name = uintptr_t(*)(uintptr_t, const char*, const char*);
	methods::class_from_name = LI_FIND_DEF(il2cpp_class_from_name);

	using il2cpp_resolve_icall = uintptr_t(*)(const char*);
	methods::resolve_icall = LI_FIND_DEF(il2cpp_resolve_icall);

	using il2cpp_class_get_field_from_name = uintptr_t(*)(uintptr_t, const char*);
	methods::class_get_field_from_name = LI_FIND_DEF(il2cpp_class_get_field_from_name);

	using il2cpp_field_static_get_value = uintptr_t(*)(uintptr_t, uintptr_t*);
	methods::field_static_get_value = LI_FIND_DEF(il2cpp_field_static_get_value);

	using il2cpp_class_get_fields = uintptr_t(*)(uintptr_t, uintptr_t*);
	methods::class_get_fields = LI_FIND_DEF(il2cpp_class_get_fields);

	using il2cpp_field_get_offset = uintptr_t(*)(uintptr_t);
	methods::field_get_offset = LI_FIND_DEF(il2cpp_field_get_offset);

	using il2cpp_object_new = uintptr_t(*)(uintptr_t);
	methods::object_new = LI_FIND_DEF(il2cpp_object_new);

	using il2cpp_type_get_object = uintptr_t(*)(uintptr_t);
	methods::type_get_object = LI_FIND_DEF(il2cpp_type_get_object);

	using il2cpp_class_get_type = uintptr_t(*)(uintptr_t);
	methods::class_get_type = LI_FIND_DEF(il2cpp_class_get_type);

	using il2cpp_runtime_class_init = uintptr_t(*)(uintptr_t);
	methods::runtime_class_init = LI_FIND_DEF(il2cpp_runtime_class_init);

	using il2cpp_string_new_wrapper = il2cppstring * (*)(const char*);
	methods::new_string = LI_FIND_DEF(il2cpp_string_new_wrapper);
	MUTATE_END
}

uintptr_t il2cpp::init_class(const char* name, const char* name_space)
{
	uintptr_t domain = methods::domain_get();

	if (!domain)
	{
		return NULL;
	}

	uintptr_t nrofassemblies;
	uintptr_t* assemblies;
	assemblies = methods::domain_get_assemblies((void*)domain, &nrofassemblies);

	for (int i = 0; i < nrofassemblies; i++)
	{
		uintptr_t img = methods::assembly_get_image(assemblies[i]);

		uintptr_t kl = methods::class_from_name(img, name_space, name);
		if (!kl)
			continue;

		return kl;
	}

	return NULL;
}

uintptr_t il2cpp::type_object(const char* name_space, const char* name)
{
	auto klass = il2cpp::init_class(name, name_space);
	return il2cpp::methods::type_get_object(il2cpp::methods::class_get_type(klass));
}

int il2cpp::m_strcmp(const char* s1, const char* s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return *(const unsigned char*)s1 - *(const unsigned char*)s2;
}

uintptr_t il2cpp::method_alt(const char* kl, const char* name, int argument_number, const char* arg_name, const char* name_space, int selected_argument) {
	uintptr_t iter = 0;
	uintptr_t f;
	auto klass = init_class(kl, name_space);

	while (f = methods::class_get_methods(klass, &iter)) {

		char* st = *reinterpret_cast<char**>(f + 0x10);

		if (m_strcmp(st, (char*)name)) {
			if (selected_argument >= 0 && arg_name) {
				uintptr_t args = *reinterpret_cast<uintptr_t*>(f + 0x28);
				int method_count = methods::method_get_param_count(f);
				if (selected_argument > method_count || (argument_number >= 0 && method_count != argument_number)) continue;

				char* argname;
				if (method_count > 0) {
					argname = *reinterpret_cast<char**>(args + (selected_argument - 1) * 0x18);
				}
				else
					argname = (char*)("-");

				if (!argname || !m_strcmp(argname, arg_name)) continue;
			}

			return f;
		}
	}
	return 0;
}

uintptr_t il2cpp::method(std::string kl, std::string name, int param_count, const char* name_space, bool param_check, int param_idx, std::string param_name)
{
	uintptr_t klass = init_class(kl.c_str(), name_space);
	if (!klass)
	{
		std::cout << "[Debug] Failed to init class in il2cpp::method: " << name_space << "::" << kl << std::endl;
		return NULL;
	}
	if (!param_check)
	{
		uintptr_t method = methods::class_get_method_from_name(klass, name.c_str(), param_count);
		return method;
	}
	else
	{
		uintptr_t nrofmethods;
		uintptr_t methods;
		methods = methods::class_get_methods(klass, &nrofmethods);
		while (methods = methods::class_get_methods(klass, &nrofmethods))
		{
			char* method_name = *reinterpret_cast<char**>(methods + 0x10);
			//std::cout << "Method Name: " << method_name << std::endl;
			if (std::string(method_name) == name)
			{
				uintptr_t args = *reinterpret_cast<uintptr_t*>(methods + 0x28);
				char* arg_name = *reinterpret_cast<char**>(args + 1 * 0x18);
				//printf("[%s] %s", name, std::string(arg_name));
			}
		}
	}
}

uintptr_t il2cpp::hook(void* our_func, std::string kl, std::string name, int arg, const char* name_space)
{
	auto il2cpp_method = method(kl.c_str(), name.c_str(), arg, name_space);
	*reinterpret_cast<void**>(il2cpp_method) = our_func;

	void* written = *reinterpret_cast<void**>(il2cpp_method);
	if (written == our_func)
	{
		std::cout << "[Debug] Hooked " << kl << " successfully" << std::endl;
	}

	return il2cpp_method;
}

uintptr_t il2cpp::hook_virtual_function(const char* classname, const char* function_to_hook, void* our_func, int param_count, const char* name_space)
{
	auto method = il2cpp::method(classname, function_to_hook, param_count, name_space);
	if (!method)
	{
		std::cout << "[Debug] Error getting method! Failed to hook " << name_space << "::" << classname << "::" << function_to_hook << std::endl;
		return NULL;
	}
	uintptr_t search = *reinterpret_cast<uintptr_t*>(method);
	uintptr_t table = il2cpp::init_class(classname, name_space);

	if (search == (uintptr_t)our_func)
	{
		std::cout << "[Debug] Already hooked " << name_space << "::" << classname << "::" << function_to_hook << std::endl;
		return (uintptr_t)our_func;
	}

	for (uintptr_t i = table; i <= table + 0x10000; i += 0x1) {
		uintptr_t addr = *reinterpret_cast<uintptr_t*>(i);
		if (addr == search)
		{
			std::cout << "[Debug] Hooking " << name_space << "::" << classname << "::" << function_to_hook << " at address: 0x" << std::hex << addr << std::dec << std::endl;
			*reinterpret_cast<uintptr_t*>(i) = (uintptr_t)our_func;
			return addr;
		}
	}

	std::cout << "[Debug] Failed to hook " << name_space << "::" << classname << "::" << function_to_hook << std::endl;
}

uintptr_t il2cpp::field(uintptr_t klass, const char* name)
{
	return methods::class_get_field_from_name(klass, name);
}

uintptr_t il2cpp::value(const char* kl, const char* name, bool get_offset, const char* name_space)
{
	uintptr_t klass = il2cpp::init_class(kl, name_space);

	if (!klass)
		return NULL;

	auto field = il2cpp::field(klass, name);
	if (get_offset)
	{
		uintptr_t out = 0;
		uintptr_t il2cpp_field;
		uintptr_t field_offset = NULL;

		while (il2cpp_field = methods::class_get_fields(klass, &out))
		{
			char* char_name = (char*)*reinterpret_cast<uintptr_t*>(il2cpp_field);
			if (!char_name)
				continue;

			uintptr_t offset = methods::field_get_offset(il2cpp_field);
			std::string field_name = std::string(char_name);
			if (name == field_name)
			{
				field_offset = offset;
				break;
			}
		}
		return field_offset;
	}

	uintptr_t static_value;
	methods::field_static_get_value(field, &static_value);
	if (static_value)
		return static_value;

	return NULL;
}

void il2cpp::appendLineToFile(std::string filepath, std::string line)
{
	std::ofstream file;
	//can't enable exception now because of gcc bug that raises ios_base::failure with useless message
	//file.exceptions(file.exceptions() | std::ios::failbit);
	file.open(filepath, std::ios::out | std::ios::app);

	//make sure write fails with exception if something is wrong
	file.exceptions(file.exceptions() | std::ios::failbit | std::ifstream::badbit);

	file << line << std::endl;
}

//template <typename I>
//std::string n2hexstr(I w, size_t hex_len = sizeof(I) << 1) {
//	static const char* digits = xorstr_("0123456789ABCDEF");
//	std::string rc(hex_len, xorstr_("0"));
//	for (size_t i = 0, j = (hex_len - 1) * 4; i < hex_len; ++i, j -= 4)
//		rc[i] = digits[(w >> j) & 0x0f];
//	return rc;
//}

void il2cpp::dump_class_offsets(std::string class_to_dump, const char* name_space)
{
	auto klass = init_class(class_to_dump.c_str());

	uintptr_t out = 0;
	uintptr_t iter = 0;
	uintptr_t il2cpp_field;
	uintptr_t il2cpp_method;
	//appendLineToFile("Dump.hpp", "	namespace " + class_to_dump + "\n	{");
	std::string appendme;
	while (il2cpp_field = methods::class_get_fields(klass, &out))
	{
		char* char_name = (char*)*reinterpret_cast<uintptr_t*>(il2cpp_field);
		if (!char_name)
			continue;

		uintptr_t offset = methods::field_get_offset(il2cpp_field);
		std::string name = std::string(char_name);
		std::string name_backup = name;
		//std::string offset_string = n2hexstr<uint32_t>(offset);
		//name = std::regex_replace(name, std::regex("<"), "");
		//name = std::regex_replace(name, std::regex(">"), "");
		//if (name.find(xorstr_("__BackingField")) != std::string::npos)
		if (true)
		{
			//appendme += "		const uint32_t " + name + " = 0x" + offset_string + "; //" + name_backup + "\n";
		}
		else
		{
			//appendme += "		const uint32_t " + name + " = 0x" + offset_string + ";\n";
		}
		//printf("[%s] Field %s: 0x%x\n", class_to_dump.c_str(), name, offset);
	}
	//appendLineToFile("Dump.hpp", appendme);
	//appendLineToFile("Dump.hpp", "	};\n");
	return;
}

void il2cpp::list_virtual_functions(const char* kl, const char* name_space)
{
	uintptr_t table = il2cpp::init_class(kl, name_space);

	for (uintptr_t i = table; i <= table + 0x10000; i += 0x1) {
		uintptr_t addr = *reinterpret_cast<uintptr_t*>(i);

	}
}