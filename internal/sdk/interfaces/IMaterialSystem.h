#pragma once
#include "imatrendercontext.h"

class IMaterialSystem {
public:
	const char *GetName( ) {
		return util::get_method( this, 0 ).as< const char *( __thiscall *)( decltype( this ) ) >( )( this );
	}

	IMaterial *CreateMaterial( const char *material_name, KeyValues *key_values ) {
		return util::get_method( this, 83 ).as< IMaterial *( __thiscall *)( decltype( this ), const char *, KeyValues * ) >( )(
			this, material_name, key_values );
	}

	IMaterial *GetMaterial( const char *material_name, const char *texture_group_name, bool complain = true,
	                        const char *complain_prefix = nullptr ) {
		return util::get_method( this, 84 ).as< IMaterial *( __thiscall *)( decltype( this ), const char *, const char *, bool,
		                                                                    const char * ) >( )(
			this, material_name, texture_group_name, complain, complain_prefix );
	}

	int FirstMaterial( ) {
		return util::get_method( this, 86 ).as< int( __thiscall *)( decltype( this ) ) >( )( this );
	}

	int NextMaterial( int handle ) {
		return util::get_method( this, 87 ).as< int( __thiscall *)( decltype( this ), int ) >( )( this, handle );
	}

	int InvalidMaterial( ) {
		return util::get_method( this, 87 ).as< int( __thiscall *)( decltype( this ) ) >( )( this );
	}

	IMaterial *FindMaterial( int handle ) {
		return util::get_method( this, 89 ).as< IMaterial *( __thiscall *)( decltype( this ), int ) >( )( this, handle );
	}

	ITexture *FindTexture( char const *pTextureName, const char *pTextureGroupName, bool complain = true ) {
		return util::get_method( this, 91 ).as< ITexture *( __thiscall *)( decltype( this ), char const *, const char *, bool )
		>( )( this, pTextureName, pTextureGroupName, complain );
	}

	IMatRenderContext *GetRenderContext( ) {
		return util::get_method( this, 115 ).as< IMatRenderContext *( __thiscall *)( decltype( this ) ) >( )( this );
	}
};
