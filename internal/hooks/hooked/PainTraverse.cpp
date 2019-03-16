#include "../../includes.h"

void c_hooks::PaintTraverse( IPanel *ecx, uintptr_t edx, int vguiPanel, bool forceRepaint, bool allowForce ) {
	g_hooks.m_Panel->get_method< fn::PaintTraverse_t >( 41 )( ecx, vguiPanel, forceRepaint, allowForce );

	static int mat_system_panel = 0;
	if( !mat_system_panel ) {
		if( hash::fnv1a_32( g_csgo.m_panel->GetName( vguiPanel ) ) == HASH( "MatSystemTopPanel" ) )
			mat_system_panel = vguiPanel;
	}

	if( vguiPanel != mat_system_panel )
		return;

}
