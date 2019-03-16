#pragma once

using hook = std::unique_ptr< VMT >;

namespace fn {
	using PaintTraverse_t = void (__thiscall *)( IPanel *, int, bool, bool );
};

class c_hooks {
private:
	hook m_Panel;
private:
	static void __fastcall PaintTraverse( IPanel *ecx, uintptr_t edx, int vguiPanel, bool forceRepaint, bool allowForce );
public:
	void Init( );
	void Release( ) const;
};

extern c_hooks g_hooks;
