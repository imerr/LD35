//
// Created by iMer on 16.04.2016.
//

#ifndef LD35_PLAYER_HPP
#define LD35_PLAYER_HPP

#include <Engine/SpriteNode.hpp>
#include <Engine/util/Event.hpp>

class Rune;

class Player : public engine::SpriteNode {
protected:
	// Settings
	bool m_canFly;
	bool m_canJump;
	bool m_canMove;
	sf::Vector2f m_speed;
	float m_jumpStrength;
	// State
	uint32_t m_grounded;
	Rune* m_activeRune;
	// Event handlers
	engine::util::BaseEventHandler* m_contactHandler;
	engine::util::BaseEventHandler* m_presolveContactHandler;
	engine::util::BaseEventHandler* m_mouseclickHandler;
public:
	Player(engine::Scene* scene);
	~Player();
	virtual bool initialize(Json::Value& root);
	void ShapeShift(std::string what);
protected:
	virtual void OnUpdate(sf::Time interval);


};


#endif //LD35_PLAYER_HPP
