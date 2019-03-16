#pragma once

class c_interface_mgr {
private:
	// used internally by the game to register classes.
	class InterfaceReg {
	private:
		using create_t = void *(__cdecl *)( );

	public:
		create_t m_create_fn;
		const char *m_name;
		InterfaceReg *m_next;
	};

	struct interface_t {
		std::string m_name;
		uintptr_t m_ptr;
		std::string dll_name;
	};

	// holds every interface used by the game.
	std::vector< interface_t > m_interfaces;

protected:
	c_interface_mgr( ) : m_interfaces{} {
		pe::modules_t modules;

		if( !get_all_modules( modules ) )
			return;

		for( const auto &m : modules ) {
			auto createinterface = pe::get_export< Address >( m, "CreateInterface" );
			if( !Address::safe( createinterface ) )
				continue;

			// ensure 4th byte is actually a jmp instruction.
			if( createinterface.add( 4 ).get< uint8_t >( ) != 0xE9 )
				continue;

			// follow the 5th byte's relative jump, add 6 to get s_pInterfaceRegs
			auto reg = createinterface.rel( 5 ).add( 6 ).get< InterfaceReg * >( 2 );
			if( !reg )
				continue;

			// iterate s_pInterfaceRegs linked list and store off needed data.
			for( reg; reg != nullptr; reg = reg->m_next ) {
				m_interfaces.push_back( { reg->m_name, reinterpret_cast< uintptr_t >( reg->m_create_fn( ) ), m.get_module_nameA( ) } );
			}
		}
	}

	// get interface by hash.
	template< typename t >
	t *get_interface( hash32_t name, size_t skip = 0, bool truncate = true ) {
		std::string interface_name;

		if( m_interfaces.empty( ) )
			return nullptr;

		for( const auto &i : m_interfaces ) {
			interface_name = i.m_name;

			if( truncate )
				interface_name.resize( interface_name.size( ) - 3 );

			if( hash::fnv1a_32( interface_name ) == name ) {
				if( skip > 0 ) {
					--skip;
					continue;
				}
				return reinterpret_cast< t * >( i.m_ptr );
			}
		}

		return nullptr;
	}

};
