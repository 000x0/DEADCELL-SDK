#pragma once

class c_client {
public:
	int          m_ping;
	int          m_rtt;
	int			 m_fps;
	bool		 m_sendpacket;
	C_CSPlayer *m_local;
};

extern c_client g_cl;