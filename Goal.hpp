#ifndef LD35_GOAL_HPP
#define LD35_GOAL_HPP

#include <Engine/SpriteNode.hpp>
#include "misc.hpp"
#include <SFML/Audio.hpp>
#include <memory>

class Goal: public engine::SpriteNode {
protected:
	std::unique_ptr<sf::Sound> m_sound;
public:
	Goal(engine::Scene* scene);
	~Goal();

	virtual uint8_t GetType() const {
		return NT_GOAL;
	}
	void Win();


};


#endif //LD35_GOAL_HPP
