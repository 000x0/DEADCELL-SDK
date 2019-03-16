#pragma once

class ConVar {
public:
	float GetFloat( ) {
		return util::get_method( this, 12 ).as< float(__thiscall *)( decltype( this ) ) >( )( this );
	}

	int GetInt( ) {
		return util::get_method( this, 13 ).as< int(__thiscall *)( decltype( this ) ) >( )( this );
	}

	void SetValue( int value ) {
		util::get_method( this, 16 ).as< void(__thiscall *)( decltype( this ), int ) >( )( this, value );
	}
};

class ICVar {
public:
	ConVar *FindVar( const char *var ) {
		return util::get_method( this, 15 ).as< ConVar *(__thiscall *)( decltype( this ), const char * ) >( )( this, var );
	}

	template< typename ... t >
	void PrintToConsole( float *clr, const char *format, t ... args ) {
		util::get_method( this, 25 ).as< void(__cdecl *)( decltype( this ), const float *, const char *, ... ) >( )(
			this, clr, format, args... );
	}
};
