#pragma once

class IVModelInfo {
public:
	const model_t *GetModel( int modelindex ) {
		return util::get_method( this, 1 ).as< model_t *( __thiscall *)( decltype( this ), int ) >( )( this, modelindex );
	}

	const int GetModelIndex( const char *name ) {
		return util::get_method( this, 2 ).as< int( __thiscall *)( decltype( this ), const char * ) >( )( this, name );
	}

	const char *GetModelName( const model_t *model ) {
		return util::get_method( this, 3 ).as< const char *( __thiscall *)( decltype( this ), const model_t * )
		>( )( this, model );
	}

	studiohdr_t *GetStudioModel( const model_t *model ) {
		return util::get_method( this, 32 ).as< studiohdr_t *( __thiscall *)( decltype( this ), const model_t * )
		>( )( this, model );
	}
};

class CStudioHdr {
public:
	studiohdr_t *m_pStudioHdr; //0x0000 
	virtualmodel_t *m_pVModel; //0x0004 
	CUtlVector< const studiohdr_t * > m_pStudioHdrCache; //0x0008 
	int m_nFrameUnlockCounter; //0x001C 
	int *m_pFrameUnlockCounter; //0x0020 
	char pad_0x0024[ 0x8 ]; //0x0024
	CUtlVector< int > m_boneFlags; //0x002C 
	CUtlVector< int > m_boneParent; //0x0040 
	int numbones( void ) const {
		return m_pStudioHdr->numbones;
	};

	mstudiobone_t *pBone( int i ) const {
		return m_pStudioHdr->pBone( i );
	};
}; //Size=0x0054
