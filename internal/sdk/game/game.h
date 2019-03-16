#pragma once



class c_game : protected c_interface_mgr {
public:
	// modules.
	pe::Module m_client_dll;
	pe::Module m_engine_dll;

	CHLClient *m_client;
	IEngineClient *m_engine;
	IClientModeShared *m_client_mode;
	IClientEntityList *m_ent_list;
	CInput *m_input;
	CGlobalVars *m_global_vars;
	ICVar *m_convar;
	IVModelInfo *m_model_info;
	IMaterialSystem *m_material_system;
	IVModelRender *m_model_render;
	ISurface *m_surface;
	IPanel *m_panel;
	IStudioRender *m_studio_render;
	IEngineTrace *m_engine_trace;
	IGameEventManager2 *m_game_events;
	ILocalize *m_localize;
	IMemAlloc *m_mem_alloc;
	ClientState *m_clientstate;

	// functions.
	void Init( );
};

extern c_game g_csgo;
