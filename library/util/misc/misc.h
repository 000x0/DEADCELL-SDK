#pragma once

namespace util {

	using NtCreateThreadEx_t = long(__stdcall*)(PHANDLE, ACCESS_MASK, PVOID, HANDLE, LPTHREAD_START_ROUTINE, PVOID, ULONG, ULONG_PTR, SIZE_T, SIZE_T, PVOID);
	using DisableThreadLibraryCalls_t = long(__stdcall*)(HMODULE);
	using CloseHandle_t = long(__stdcall*)(HANDLE);
	using GetCurrentProcess_t = HANDLE(__stdcall*)(void);

	namespace mem {
		__forceinline static pe::Module& get_kernel32() {
			static pe::Module kernel32_dll{};

			if (!kernel32_dll)
				kernel32_dll = pe::get_module(nt_static_module::kernel32);

			return kernel32_dll;
		}
		__forceinline static pe::Module& get_nt() {
			static pe::Module nt_dll{};

			if (!nt_dll)
				nt_dll = pe::get_module(nt_static_module::nt);

			return nt_dll;
		}
		__forceinline static pe::Module& get_kernelbase() {
			static pe::Module kernelbase_dll{};

			if (!kernelbase_dll)
				kernelbase_dll = pe::get_module(nt_static_module::kernelbase);

			return kernelbase_dll;
		}
		__forceinline static HANDLE get_current_process() {
			static GetCurrentProcess_t get_cur_process{};

			if (get_cur_process == nullptr)
				get_cur_process = pe::get_export<GetCurrentProcess_t>( get_kernel32(), "GetCurrentProcess" );

			if (get_cur_process != nullptr)
				return get_cur_process();

			return INVALID_HANDLE_VALUE;
		}

		__forceinline static HWND find_window( const std::string &window_name ) {
			static decltype(&FindWindowA) find_window{};

			if (find_window == nullptr)
				find_window = pe::get_export< decltype( &FindWindowA ) >( pe::get_module( "user32.dll" ), "FindWindowA" );
			
			if (find_window != nullptr)
				return find_window(window_name.c_str(), nullptr);

			return 0;
		}

		// sneaky way of invoking ntcreatethreadex in DllMain
		__forceinline static HANDLE create_thread(LPTHREAD_START_ROUTINE routine) {
			static NtCreateThreadEx_t create_thread_ex = nullptr;

			HANDLE                    out = INVALID_HANDLE_VALUE;

			if (create_thread_ex == nullptr)
				create_thread_ex = pe::get_export< NtCreateThreadEx_t >( get_nt(), "NtCreateThreadEx" );

			if (create_thread_ex != nullptr) {
				create_thread_ex(
					&out,
					THREAD_ALL_ACCESS,
					0,
					get_current_process(),
					routine,
					0,
					0x4,
					0,
					0,
					0,
					0
				);
			}

			return out;
		}

		__forceinline static bool close_handle(HANDLE handle) {
			static CloseHandle_t close_handle{};

			if (close_handle == nullptr)
				close_handle = pe::get_export< CloseHandle_t >( get_kernel32(), "CloseHandle" );

			if (close_handle != nullptr)
				return !!close_handle(handle);

			return false;
		}

		__forceinline static bool disable_thread_lib_calls(HMODULE inst) {
			static DisableThreadLibraryCalls_t disable_calls{};

			if (disable_calls == nullptr)
				disable_calls = pe::get_export< DisableThreadLibraryCalls_t >( get_kernel32(), "DisableThreadLibraryCalls" );

			if (disable_calls != nullptr)
				return !!disable_calls(inst);

			return false;
		}
	}

	namespace misc {
		bool valid_code_ptr( uintptr_t addr );

		std::string wide_to_multibyte( const std::wstring &str );
		std::wstring multibyte_to_wide( const std::string &str );
		std::string unicode_to_ascii( const std::wstring &unicode );
		std::wstring ascii_to_unicode( const std::string &ascii );

		// returns a random floating point value in range.
		template< typename t >
		t get_random_float_range( const t &min, const t &max ) {
			std::random_device rd;
			std::mt19937 e2( rd( ) );
			std::uniform_real_distribution< t > distribution( min, max );

			return distribution( e2 );
		}

		// returns a random integral value in range.
		template< typename t >
		t get_random_int_range( const t &min, const t &max ) {
			std::random_device rd;
			std::mt19937 e2( rd( ) );
			std::uniform_int_distribution< t > distribution( min, max );

			return distribution( e2 );
		}

		template< typename t >
		t clamp( t in, t low, t high ) {
			return std::min( std::max( in, low ), high );
		}
	}
}
