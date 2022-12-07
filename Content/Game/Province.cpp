#include "Province.h"

sf::Color Province::color() const
{
	return _color;
}

sf::Color Province::stateColor() const
{
	return _stateColor;
}

std::string Province::name() const
{
	return _name;
}
