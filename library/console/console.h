#pragma once

#undef ERROR

namespace console {
	void allocate( const char *window_name );
	void detach( );
}

#define LOG( ) logger()
#define LVLOG( level ) logger( level )

enum color { GRAY = 8, RED = 12, YELLOW = 14, WHITE = 15 };
enum level { NONE, INFO = 1, WARNING = 2, ERROR = 3 };

template< class Elem, class Traits >
constexpr std::basic_ostream< Elem, Traits > &operator<<( std::basic_ostream< Elem, Traits > &os, const color col ) {
	SetConsoleTextAttribute( GetStdHandle( STD_OUTPUT_HANDLE ), col );
	return os;
}

class logger {
private:
	std::ostringstream m_stream;

	static std::pair< color, std::string > get_level_format( const level lvl ) {
		switch( lvl ) {
		case INFO: return{ WHITE, "INFO" };
		case WARNING: return{ YELLOW, "WARNING" };
		case ERROR: return{ RED, "ERROR" };
		}

		return{ WHITE, "" };
	}

	void construct( const level lvl ) {
		// construct time.
		char current_time[ 128 ];

		time_t raw_time = std::time( nullptr );
		struct tm *time = std::localtime( &raw_time );
		std::strftime( current_time, 128, "%F %T", time );

		const auto level_format = get_level_format( lvl );

		// construct log format.
		if( lvl > 0 ) {
			m_stream << "[" << current_time << "]" << "[" << level_format.first << level_format.second << "] ";
		}
		else {
			m_stream << "[" << current_time << "] ";
		}
	}

public:
	explicit logger( const level lvl = NONE ) {
		construct( lvl );
	}

	template< typename T >
	logger &operator<<( T const &in ) {
		m_stream << in;
		return *this;
	}

	~logger( ) {
		m_stream << '\n';
		std::cout << m_stream.str( );
		m_stream << WHITE;
	}
};