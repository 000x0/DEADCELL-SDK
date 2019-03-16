#pragma once

class IMaterialVar {
private:
public:
	void SetFloatValue( float value ) {
		util::get_method( this, 4 ).as< float(__thiscall *)( decltype( this ), float ) >( )( this, value );
	}
};
