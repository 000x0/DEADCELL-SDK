#include "../includes.h"
#include "input.h"

c_input input;

ulong_t __stdcall hook( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
	if( input.handle( hwnd, msg, wparam, lparam ) )
		return true;

	return CallWindowProcA( input.get_original_wndproc( ), hwnd, msg, wparam, lparam );
}

c_input::c_input( )
	: m_window_handle{}, m_original_wndproc{}, m_key_pressed{} { }

bool c_input::Init( const std::string &window_name ) {
	if( m_window_handle )
		return false;

	m_window_handle = util::mem::find_window( window_name );
	m_original_wndproc = reinterpret_cast< WNDPROC >( SetWindowLongA( m_window_handle, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( hook ) ) );

	return m_original_wndproc != nullptr;
}

bool c_input::handle( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam ) {
	switch( msg ) {
			// left mouse
		case WM_LBUTTONDOWN:
			m_key_pressed[ VK_LBUTTON ] = true;
			break;
		case WM_LBUTTONUP:
			m_key_pressed[ VK_LBUTTON ] = false;
			break;

			// right mouse
		case WM_RBUTTONDOWN:
			m_key_pressed[ VK_RBUTTON ] = true;
			break;
		case WM_RBUTTONUP:
			m_key_pressed[ VK_RBUTTON ] = false;
			break;

			//middle mouse
		case WM_MBUTTONDOWN:
			m_key_pressed[ VK_MBUTTON ] = true;
			break;
		case WM_MBUTTONUP:
			m_key_pressed[ VK_MBUTTON ] = false;
			break;

			// regular key
		case WM_KEYDOWN:
			m_key_pressed[ wparam ] = true;
			break;
		case WM_KEYUP:
			m_key_pressed[ wparam ] = false;
			break;

			// side mouse
		case WM_XBUTTONDOWN: {
			switch( GET_XBUTTON_WPARAM( wparam ) ) {
				case XBUTTON1:
					m_key_pressed[ VK_XBUTTON1 ] = true;
					break;
				case XBUTTON2:
					m_key_pressed[ VK_XBUTTON2 ] = true;
					break;
				default:
					break;
			}

			break;
		}
		case WM_XBUTTONUP: {
			switch( GET_XBUTTON_WPARAM( wparam ) ) {
				case XBUTTON1:
					m_key_pressed[ VK_XBUTTON1 ] = false;
					break;
				case XBUTTON2:
					m_key_pressed[ VK_XBUTTON2 ] = false;
					break;
				default:
					break;
			}

			break;
		}

		default:
			break;
	}

	return false;
}

bool c_input::Release( ) const {
	if( !m_window_handle || !m_original_wndproc )
		return false;

	SetWindowLongA( m_window_handle, GWLP_WNDPROC, reinterpret_cast< LONG_PTR >( m_original_wndproc ) );

	return true;
}

WNDPROC c_input::get_original_wndproc( ) const {
	return m_original_wndproc;
}

bool c_input::key_pressed( int virtual_key ) {
	if( !m_window_handle )
		return false;

	return m_key_pressed[ virtual_key ];
}
