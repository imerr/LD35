//
// Created by iMer on 17.04.2016.
//

#ifndef LD35_MAGICLIGHT_HPP
#define LD35_MAGICLIGHT_HPP

#include "misc.hpp"
#include <Engine/SpriteNode.hpp>

class MagicLight: public engine::SpriteNode {
protected:
	bool m_moving;
	float m_moveSpeed;
	float m_moveTime;
	bool m_switching;
	float m_onTime;
	float m_offTime;
	float m_switchTime;
	bool m_toggle;
public:
	MagicLight(engine::Scene*);
	~MagicLight();

	virtual bool initialize(Json::Value& root);
	virtual void OnInitializeDone();

	virtual uint8_t GetType() const {
		return NT_MAGICLIGHT;
	}
	void Toggle();

protected:
	virtual void OnUpdate(sf::Time interval);
};


#endif //LD35_MAGICLIGHT_HPP
