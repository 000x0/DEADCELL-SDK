#pragma once

class IPanel {
public:
	const char *GetName( int vguiPanel ) {
		return util::get_method( this, 36 ).as< const char *(__thiscall *)( decltype( this ), int ) >( )( this, vguiPanel );
	}
};
