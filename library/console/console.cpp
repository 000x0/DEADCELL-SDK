#include "../includes.h"
#include "console.h"

void console::allocate( const char *window_name ) {
	AllocConsole( );

	_iobuf *data;
	freopen_s( &data, "CONIN$", "r", stdin );
	freopen_s( &data, "CONOUT$", "w", stdout );

	SetConsoleTitleA( window_name );
}

void console::detach( ) {
	HMENU menu = GetSystemMenu( GetConsoleWindow( ), true ); // use true to restore buttons.
	if( !menu )
		return;

	DeleteMenu( menu, SC_CLOSE, MF_BYCOMMAND );

	FreeConsole( );
}
