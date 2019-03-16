#pragma once

class ITexture {
private:
public:
	int GetActualWidth( ) {
		return util::get_method( this, 3 ).as< int( __thiscall *)( decltype( this ) ) >( )( this );
	}

	int GetActualHeight( ) {
		return util::get_method( this, 4 ).as< int( __thiscall *)( decltype( this ) ) >( )( this );
	}
};
