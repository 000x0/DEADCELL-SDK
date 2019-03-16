#include "includes.h"

c_netvars g_netvars;
c_client g_cl;

static ulong_t __stdcall init( void *arg ) {
	while( !pe::get_module( HASH( "serverbrowser.dll" ) ) )
		std::this_thread::sleep_for( std::chrono::milliseconds( 100 ) );

	console::allocate( "sdk" );

	input.Init( "Valve001" );

	g_csgo.Init( );

	g_netvars.Init( );

	g_hooks.Init( );

	LVLOG( WARNING ) << "Injected successfully";

	return 1;
}

int __stdcall DllMain( HMODULE self, ulong_t reason_for_call, void *reserved ) {
	HANDLE cheat_thread;

	switch( reason_for_call ) {
		case 1: {
			util::mem::disable_thread_lib_calls( self );
		
			cheat_thread = util::mem::create_thread( &init );
			if( !cheat_thread )
				return 0;

			util::mem::close_handle( cheat_thread );

			break;
		}
		default:
			break;
	}

	return 1;
}
