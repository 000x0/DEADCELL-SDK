#pragma once

class ILocalize {
public:
	wchar_t *find( const char *name ) {
		return util::get_method( this, 11 ).as< wchar_t *( __thiscall *)( void *, const char * ) >( )( this, name );
	}
};
