#pragma once

class IVRenderView {
public:
	void set_blend( float blend ) {
		util::get_method( this, 4 ).as< void( __thiscall *)( decltype( this ), float ) >( )( this, blend );
	}

	void set_color_modulation( float *col ) {
		util::get_method( this, 6 ).as< void( __thiscall*)( void *, const float * ) >( )( this, col );
	}
};
