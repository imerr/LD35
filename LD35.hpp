#ifndef LD35_LD35_HPP
#define LD35_LD35_HPP
#include <Engine/Game.hpp>
#include <SFML/Audio.hpp>
#include <memory>
class LD35: public engine::Game {
protected:
	std::unique_ptr<sf::Sound> m_music;
	engine::util::BaseEventHandler* m_keyHandler;
public:
	LD35();
	~LD35();
};

#endif //LD35_LD35_HPP
