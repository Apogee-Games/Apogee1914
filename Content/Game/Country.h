#pragma once

#include <string>
#include <string.h>

#include "SFML/Graphics/Color.hpp"

class Country
{
public:

	std::string name() const;

	sf::Color color() const;


private:
	std::string _name;

	sf::Color _color;


};

