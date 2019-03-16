#include "../includes.h"
#include "manager.h"

c_hooks g_hooks;

void c_hooks::Init( ) {
	m_Panel = std::make_unique< VMT >( g_csgo.m_panel );

	m_Panel->hook_method( PaintTraverse, 41 );
}

void c_hooks::Release( ) const {
	m_Panel->unhook_all( );
}
