#pragma once

#include <string.h>
#include <string>
#include <SFML/Graphics/Color.hpp>

class Province
{
public:

	Province() {

	}
	Province(sf::Color color, std::string name, sf::Color stateColor) : _color(color), _name(name), _stateColor(stateColor) {

	}

	sf::Color color() const;

	sf::Color stateColor() const;

	std::string name() const;

private:

	std::string _name;
	
	sf::Color _color;

	sf::Color _stateColor;
};

