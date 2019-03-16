#include "../../includes.h"
#include "game.h"

c_game g_csgo;

void c_game::Init( ) {

	m_client_dll = pe::get_module( HASH( "client_panorama.dll" ) );
	m_engine_dll = pe::get_module( HASH( "engine.dll" ) );

	m_mem_alloc = *pe::get_export< IMemAlloc** >( pe::get_module( HASH( "tier0.dll" ) ), "g_pMemAlloc" );
	m_client = get_interface< CHLClient >( HASH( "VClient" ) );
	m_engine = get_interface< IEngineClient >( HASH( "VEngineClient" ) );
	m_client_mode = util::get_method( m_client, 10 ).add( 5 ).get( 2 ).as< IClientModeShared * >( );
	m_input = util::get_method( m_client, 20 ).at( 4 ).as< CInput * >( );
	m_ent_list = get_interface< IClientEntityList >( HASH( "VClientEntityList" ) );
	m_global_vars = util::get_method( m_client, 0 ).add( 27 ).get( 2 ).as< CGlobalVars * >( );
	m_convar = get_interface< ICVar >( HASH( "VEngineCvar" ) );
	m_model_info = get_interface< IVModelInfo >( HASH( "VModelInfoClient" ) );
	m_material_system = get_interface< IMaterialSystem >( HASH( "VMaterialSystem" ) );
	m_model_render = get_interface< IVModelRender >( HASH( "VEngineModel" ) );
	m_panel = get_interface< IPanel >( HASH( "VGUI_Panel" ) );
	m_surface = get_interface< ISurface >( HASH( "VGUI_Surface" ) );
	m_studio_render = get_interface< IStudioRender >( HASH( "VStudioRender" ) );
	m_engine_trace = get_interface< IEngineTrace >( HASH( "EngineTraceClient" ) );
	m_game_events = get_interface< IGameEventManager2 >( HASH( "GAMEEVENTSMANAGER002" ), 0, false );
	m_localize = get_interface< ILocalize >( HASH( "Localize_001" ), 0, false );
	m_clientstate = util::get_method( m_engine, 12 ).add( 16 ).get( 2 ).as< ClientState* >( );
}
