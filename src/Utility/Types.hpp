#ifndef UTIL_TYPES_HPP
#define UTIL_TYPES_HPP

#include <cstdint>

typedef std::uint8_t uchar;
typedef std::uint16_t ushort;
typedef std::uint32_t uint;
typedef std::uint64_t ullong;

typedef std::int64_t llong;

// struct to store particles
struct Particle
{
	sf::Vector2f position;
	sf::Vector2f velocity;
	sf::Color color;
	float radius;
};

#endif // UTIL_TYPES_HPP
