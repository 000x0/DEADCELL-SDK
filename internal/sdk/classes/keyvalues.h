#pragma once

class KeyValues
{
public:
	~KeyValues( ) {
		g_csgo.m_mem_alloc->Free( this );
	}
	
	KeyValues* Init( const char* name ) {
		using ctor_t = KeyValues*( __thiscall* )( void*, const char* );
		static auto ctor = pattern::find< ctor_t >( g_csgo.m_client_dll, "55 8B EC 51 33 C0 C7 45" );
		return ctor( this, name );
	};

	// xref '%s\\gameinfo.txt'
	bool LoadFromBuffer( const char* name, const char* buffer ) {
		using load_t = bool( __thiscall* )( KeyValues*, const char*, const char*, void*, void*, void* );
		static auto LoadFromBuffer = pattern::find< load_t >( g_csgo.m_client_dll, "55 8B EC 83 E4 F8 83 EC 34 53 8B 5D 0C 89 4C 24 04" );
		return LoadFromBuffer( this, name, buffer, 0, 0, 0 );
	}

	KeyValues *FindKey( const char *name, bool bCreate ){
		using findkey_t = KeyValues*( __thiscall* )( KeyValues*, const char*, bool );
		static auto FindKey = pattern::find< findkey_t >( g_csgo.m_client_dll, "55 8B EC 83 EC 1C 53 8B D9 85 DB" );
		return FindKey( this, name, bCreate );
	}

	void SetInt( const char *keyName, int val ) {
		auto key_int = FindKey( keyName, true );
		if( key_int ) {
			*reinterpret_cast< int* >( reinterpret_cast< uintptr_t >( key_int ) + 0xC ) = val;
			*reinterpret_cast< char* >( reinterpret_cast< uintptr_t >( key_int ) + 0x10 ) = 2;
		}
	}

	void SetString( const char *name, const char* a2 ){
		auto key = FindKey(name, true);
		using setstring_t =  void( __thiscall* )( void*, const char* );
		if ( key ) {
			static auto SetString = pattern::find< setstring_t >( g_csgo.m_client_dll, "55 8B EC A1 ? ? ? ? 53 56 57 8B F9 8B 08 8B 01" );
			SetString( key, a2) ;
		}
	}
	__forceinline static KeyValues *CreateKV( const char* name ) {
		KeyValues* kv = ( KeyValues* ) g_csgo.m_mem_alloc->Alloc( 36 );
		if ( kv )
			kv->Init( name );

		return kv;
	}
};