#include "../../includes.h"
#include "misc.h"

bool util::misc::valid_code_ptr( uintptr_t addr ) {
	static MEMORY_BASIC_INFORMATION32 mbi{};

	if( !addr
		|| addr < 0x10000
		|| addr > 0xFFE00000
		|| !VirtualQuery( ( const void * )addr, ( PMEMORY_BASIC_INFORMATION )&mbi, sizeof( mbi ) ) )
		return false;

	if( !mbi.AllocationBase
		|| mbi.State != MEM_COMMIT
		|| mbi.Protect == PAGE_NOACCESS
		|| mbi.Protect & PAGE_GUARD )
		return false;

	return true;

}

// wide string -> multi-byte string.
std::string util::misc::wide_to_multibyte( const std::wstring &str ) {
	std::string ret;
	int32_t str_len;

	// check if not empty str
	if (str.empty())
		return{};

	// count size
	str_len = WideCharToMultiByte(CP_UTF8, 0, &str[0], (int32_t) str.size(), 0, 0, 0, 0);

	// setup return value
	ret = std::string(str_len, 0);

	// final conversion
	WideCharToMultiByte(CP_UTF8, 0, &str[0], (int32_t) str.size(), &ret[0], str_len, 0, 0);

	return ret;
}

// multi-byte string -> wide string.
std::wstring util::misc::multibyte_to_wide( const std::string &str ) {
	std::wstring ret;
	int32_t      size;
	wchar_t     *wstr;
	const char  *buf = str.c_str();

	// get size
	size = MultiByteToWideChar(CP_UTF8, 0, buf, int32_t(strlen(buf) + 1), 0, 0);

	// alloc new wchars
	wstr = new wchar_t[size];

	// finally convert
	MultiByteToWideChar(CP_UTF8, 0, buf, int32_t(strlen(buf) + 1), wstr, size);

	// construct return string
	ret = std::wstring(wstr);

	// cleanup
	delete[] wstr;
	return ret;
}

std::string util::misc::unicode_to_ascii( const std::wstring &unicode ) {
	std::string ascii_str( unicode.begin( ), unicode.end( ) );
	return ascii_str;
}

std::wstring util::misc::ascii_to_unicode( const std::string &ascii ) {
	std::wstring unicode_str( ascii.begin( ), ascii.end( ) );
	return unicode_str;
}
