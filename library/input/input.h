#pragma once

class c_input {
private:
	HWND m_window_handle;
	WNDPROC m_original_wndproc;
	std::array< bool, 255 > m_key_pressed;

public:
	c_input( );

	bool Init( const std::string &window_name );

	bool handle( HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam );
	bool Release( ) const;

	WNDPROC get_original_wndproc( ) const;
	bool key_pressed( int virtual_key );

};

extern c_input input;
