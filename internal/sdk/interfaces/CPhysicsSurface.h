#pragma once

class CPhysicsSurface {
public:
	SurfaceData_t *GetSurfaceData( int data ) {
		return util::get_method( this, 5 ).as< SurfaceData_t *( __thiscall *)( decltype( this ), int ) >( )( this, data );
	}
};
