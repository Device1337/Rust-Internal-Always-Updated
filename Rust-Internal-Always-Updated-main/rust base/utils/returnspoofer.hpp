#pragma once
#include <type_traits>

// https://github.com/juniorjacob/ret_addr_spoofer

#pragma section(".text")
__declspec(allocate(".text")) const unsigned char jmpRdx[] = { 0xFF, 0x27 };//ReturnSpoof

namespace ReturnAddressSpoofer {
	extern "C" void* SpooferStub();
	template <typename Ret, typename... Args>
	__forceinline static Ret Helper(const void* shell, Args... args)
	{
		auto fn = (Ret(*)(Args...))(shell);
		return fn(args...);
	}

	template <std::size_t Argc, typename>
	struct Remapper
	{
		// At least 5 params
		template< typename Ret, typename First, typename Second, typename Third, typename Fourth, typename... Pack>
		__forceinline static Ret Call(const void* shell, void* shellParam, First first, Second second, Third third, Fourth fourth, Pack... pack)
		{
			return Helper<Ret, First, Second, Third, Fourth, void*, void*, Pack...>(shell, first, second, third, fourth, shellParam, nullptr, pack...);
		}
	};

	template <std::size_t Argc>
	struct Remapper<Argc, std::enable_if_t<Argc <= 4>>
	{
		// 4 or less params
		template<typename Ret, typename First = void*, typename Second = void*, typename Third = void*, typename Fourth = void*>
		__forceinline static Ret Call(const void* shell, void* shellParam, First first = First{}, Second second = Second{}, Third third = Third{}, Fourth fourth = Fourth{})
		{
			return Helper<Ret, First, Second, Third, Fourth, void*, void*>(shell, first, second, third, fourth, shellParam, nullptr);
		}
	};
};

template <typename result, typename... arguments>
__forceinline static result SpoofReturn(result(*fn)(arguments...), arguments... args)
{
	return fn(args...);

	/*
	struct shell_params
	{
		const void* trampoline;
		void* function;
		void* register_; // originally rbx, currently rdx
	};
	//printf("Calling SpoofReturn from %s\n", __FUNCTION__);
	shell_params params{ jmpRdx, reinterpret_cast<void*>(fn) };
	using mapper = ReturnAddressSpoofer::Remapper<sizeof...(arguments), void>;
	return mapper::template Call<result, arguments...>((const void*)&ReturnAddressSpoofer::SpooferStub, &params, args...);
	*/
}
