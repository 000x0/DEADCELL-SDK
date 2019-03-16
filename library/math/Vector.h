#pragma once

class vec3_t {
private:

public:
	float x, y, z;

	__forceinline vec3_t() : x{ 0.f }, y{ 0.f }, z{ 0.f } {

	}

	__forceinline vec3_t( float x, float y, float z ) : x{ x }, y{ y }, z{ z } {

	}

	__forceinline void init( float _x, float _y, float _z ) {
		x = _x;
		y = _y;
		z = _z;
	}

	__forceinline bool empty() const {
		return x == 0.f && y == 0.f && z == 0.f;
	}

	__forceinline bool is_valid() const {
		return std::isfinite( x ) && std::isfinite( y ) && std::isfinite( z );
	}

	__forceinline float &operator[]( int i ) {
		return reinterpret_cast<float *>( this )[ i ];
	}

	__forceinline float operator[]( int i ) const {
		return reinterpret_cast< float * >( (vec3_t*)this )[ i ];
	}

	__forceinline bool operator==( const vec3_t &src ) const {
		return src.x == x && src.y == y && src.z == z;
	}

	__forceinline bool operator!=( const vec3_t& src ) const {
		return src.x != x || src.y != y;
	}

	__forceinline vec3_t &operator+=( const vec3_t &v ) {
		x += v.x; y += v.y; z += v.z;
		return *this;
	}

	__forceinline vec3_t &operator+=( float fl ) {
		x += fl; y += fl; z += fl;
		return *this;
	}

	__forceinline vec3_t operator+( const vec3_t &v ) const {
		return vec3_t( x + v.x, y + v.y, z + v.z );
	}

	__forceinline vec3_t operator+( float fl ) const {
		return vec3_t( x + fl, y + fl, z + fl );
	}

	__forceinline vec3_t operator-( const vec3_t &vec ) const {
		return vec3_t( x - vec.x, y - vec.y, z - vec.z );
	}

	__forceinline vec3_t &operator=( const vec3_t &vec ) = default;

	__forceinline bool operator==( const vec3_t &source ) {
		return source.x == x && source.y == y && source.z == z;
	}

	__forceinline vec3_t operator*( const float &fl ) const {
		return vec3_t( x * fl, y * fl, z * fl );
	}

	__forceinline vec3_t operator*( const vec3_t &vec ) const {
		return vec3_t( x * vec.x, y * vec.y, z * vec.z );
	}

	__forceinline vec3_t &operator+=( const float &fl ) {
		x += fl; y += fl; z += fl;
		return *this;
	}

	__forceinline vec3_t &operator-=( const float &fl ) {
		x -= fl; y -= fl; z -= fl;
		return *this;
	}

	__forceinline vec3_t operator-( const float &fl ) const {
		return vec3_t( x - fl, y - fl, z - fl );
	}

	__forceinline vec3_t &operator-=( const vec3_t &v )	 { 
		x -= v.x; y -= v.y; z -= v.z;	
		return *this;
	}

	__forceinline vec3_t &operator/=( const float &fl ) {
		float oofl = 1.f / fl;
		x *= oofl; y *= oofl; z *= oofl;
		return *this;
	}

	__forceinline vec3_t &operator*=( const float &fl ) {
		x *= fl; y *= fl; z *= fl;
		return *this;
	}

	__forceinline vec3_t operator/( const float &fl ) const	{
		return vec3_t( x / fl, y / fl, z / fl );
	}

	__forceinline vec3_t operator/( const vec3_t &vec ) const {
		return vec3_t( x / vec.x, y / vec.y, z / vec.z );
	}

	__forceinline float dot( const float *fl ) const {
		const vec3_t &a = *this;
		return a.x * fl[ 0 ] + a.y * fl[ 1 ] + a.z * fl[ 2 ];
	}

	__forceinline float dot( const vec3_t &vec ) const {
		const vec3_t &a = *this;
		return a.x * vec.x + a.y * vec.y + a.z * vec.z;
	}

	__forceinline float length() const {
		float sqsr = x * x + y * y + z * z;

		const auto sqrtss = []( float in ) {
			__m128 reg = _mm_load_ss( &in );
			return _mm_mul_ss( reg, _mm_rsqrt_ss( reg ) ).m128_f32 [ 0 ];
		};

		return sqrtss( sqsr );
	}

	__forceinline float length_2d() const {
		float sqsr = x * x + y * y;

		const auto sqrtss = []( float in ) {
			__m128 reg = _mm_load_ss( &in );
			return _mm_mul_ss( reg, _mm_rsqrt_ss( reg ) ).m128_f32 [ 0 ];
		};

		return sqrtss( sqsr );
	}

	__forceinline float length_sqr() const {
		return x * x + y * y + z * z;
	}

	__forceinline float *base() {
		return (float *)this;
	}

	__forceinline float const *base() const {
		return (const float *)this;
	}

	__forceinline float dist( const vec3_t &vec ) const {
		vec3_t delta;

		delta.x = x - vec.x;
		delta.y = y - vec.y;
		delta.z = z - vec.z;

		return delta.length();
	}

	__forceinline float normalize_in_place() {
		vec3_t &v = *this;

		float iradius = 1.f / ( this->length() + 1.192092896e-07F );

		v.x *= iradius;
		v.y *= iradius;
		v.z *= iradius;

		return 1;
	}

	__forceinline void normalize() {
		*this /= length();
	}

	__forceinline vec3_t normalized() const {
		vec3_t vec = *this;
		vec.normalize();
		return vec;
	}
};

class __declspec( align( 16 ) ) vectorAligned : public vec3_t
{
public:
	inline vectorAligned( void )
	{ };

	inline vectorAligned( float X, float Y, float Z )
	{
		init( X, Y, Z );
	}

public:
	explicit vectorAligned( const vec3_t &vOther )
	{
		init( vOther.x, vOther.y, vOther.z );
	}

	vectorAligned& operator=( const vec3_t &vOther )
	{
		init( vOther.x, vOther.y, vOther.z );
		return *this;
	}

	vectorAligned& operator=( const vectorAligned &vOther )
	{
		init( vOther.x, vOther.y, vOther.z );
		return *this;
	}

	float w;
};