#pragma once

enum LifeState {
	ALIVE = 0,
	DYING,
	DEAD,
	RESPAWNABLE,
	DISCARDBODY,
};

class C_BaseEntity : public IClientEntity {
public:
	NETVAR( int, model_index, "DT_BaseEntity", "m_nModelIndex" )
	NETVAR( int, team, "DT_BaseEntity", "m_iTeamNum" )
	NETVAR( vec3_t, origin, "DT_BaseEntity", "m_vecOrigin" )
	NETVAR( vec3_t, mins, "DT_BaseEntity", "m_vecMins" )
	NETVAR( vec3_t, maxs, "DT_BaseEntity", "m_vecMaxs" )
	NETVAR( float, simtime, "DT_BaseEntity", "m_flSimulationTime" )

	vec3_t abs_origin( ){
		return util::get_method( this, 10 ).as< vec3_t&( __thiscall* )( void* ) >()(this);
	}

	player_info_t get_info( ) {
		player_info_t info;
		g_csgo.m_engine->GetPlayerInfo( this->GetIndex( ), &info );
		return info;
	}

	matrix3x4_t &coord_frame( ) {
		const static auto m_CollisionGroup = g_netvars.get_offset( "DT_BaseEntity", "m_CollisionGroup" );

		auto m_rgflCoordinateFrame = m_CollisionGroup - 0x30;

		return *reinterpret_cast< matrix3x4_t * >( reinterpret_cast< uintptr_t >( this ) + m_rgflCoordinateFrame );
	}
};

class C_BaseCombatCharacter : public C_BaseEntity {
public:
	NETVAR( float, next_attack, "DT_BaseCombatCharacter", "m_flNextAttack" )
};

class C_BasePlayer : public C_BaseCombatCharacter {
public:
	NETVAR( int, health, "DT_BasePlayer", "m_iHealth" );
	NETVAR( short, lifestate, "DT_BasePlayer", "m_lifeState" );
	NETVAR( int, tickbase, "DT_BasePlayer", "m_nTickBase" );
	NETVAR( CBaseHandle, weapon_handle, "DT_BasePlayer", "m_hActiveWeapon" )
	NETVAR( CBaseHandle, viewmodel_handle, "DT_BasePlayer", "m_hViewModel[0]" )
	NETVAR( vec3_t, velocity, "DT_BasePlayer", "m_vecVelocity[0]" );
	NETVAR( vec3_t, view_offset, "DT_BasePlayer", "m_vecViewOffset[0]" );
	NETVAR( vec3_t, punch_angle, "DT_BasePlayer", "m_aimPunchAngle" );
	NETVAR( int, flags, "DT_BasePlayer", "m_fFlags" );

	OFFSET( CCSGOPlayerAnimState *, animstate, 0x3900 )

	CUtlVector< AnimationLayer_t >& animoverlays( ) {
		return *reinterpret_cast< CUtlVector< AnimationLayer_t >* >( reinterpret_cast< uintptr_t >( this ) + 0x2980 );
	}

	bool alive( ) {
		return lifestate( ) == ALIVE;
	}

	studiohdr_t *studio_hdr( ){
		return **reinterpret_cast< studiohdr_t *** >( uintptr_t( this ) + 0x294C );
	}
};

class C_BaseCSGrenade : public C_BaseEntity {
public:
	NETVAR( bool, pin_pulled, "DT_BaseCSGrenade", "m_bPinPulled" );
	NETVAR( float, throw_time, "DT_BaseCSGrenade", "m_fThrowTime" );
	NETVAR( float, throw_strength, "DT_BaseCSGrenade", "m_flThrowStrength" );
};

class C_BaseCombatWeapon : public C_BaseCSGrenade {
public:
	NETVAR( short, item_index, "DT_WeaponBaseItem", "m_iItemDefinitionIndex" )
	NETVAR( int, clip, "DT_WeaponBaseItem", "m_iClip1" );
	NETVAR( float, ready_time, "DT_WeaponBaseItem", "m_flPostponeFireReadyTime" );
	NETVAR( float, next_attack, "DT_BaseCombatWeapon", "m_flNextPrimaryAttack" );
	NETVAR( float, next_sec_attack, "DT_BaseCombatWeapon", "m_flNextSecondaryAttack" );

	float spread( ) {
		return util::get_method( this, 440 ).as< float( __thiscall *)( void * ) >()(this);
	}

	float inaccuracy( ) {
		return util::get_method( this, 471 ).as< float( __thiscall *)( void * ) >()(this);
	}

	void update_accuracy( ) {
		util::get_method( this, 472 ).as< void( __thiscall *)( void * ) >()(this);
	}
};

class C_BaseAttributableItem : public C_BaseCombatWeapon {
public:

};

class C_BaseAnimating : public C_BasePlayer {
public:
	NETVAR( int, hitbox_set, "DT_BaseAnimating", "m_nHitboxSet" )
};

class C_CSPlayer : public C_BaseAnimating {
public:
	NETVAR( CUtlVector< CBaseHandle >, my_weapons, "DT_CSPlayer", "m_hMyWeapons" )
	NETVAR( int, armor, "DT_CSPlayer", "m_ArmorValue" );
	NETVAR( bool, has_heavy_armor, "DT_CSPlayer", "m_bHasHeavyArmor" );
	NETVAR( bool, helmet, "DT_CSPlayer", "m_bHasHelmet" );
	NETVAR( bool, is_scoped, "DT_CSPlayer", "m_bIsScoped" );
	NETVAR( bool, has_defuser, "DT_CSPlayer", "m_bHasDefuser" );
	NETVAR( bool, immune, "DT_CSPlayer", "m_bGunGameImmunity" );

	C_BaseCombatWeapon *active_wep( ) {
		return g_csgo.m_ent_list->Get< C_BaseCombatWeapon >( weapon_handle( ) );
	}

	static C_CSPlayer *get_local( ){
		return g_csgo.m_ent_list->Get< C_CSPlayer >( g_csgo.m_engine->GetLocalPlayer( ) );
	}
};
