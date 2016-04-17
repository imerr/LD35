//
// Created by iMer on 17.04.2016.
//

#ifndef LD35_SWITCH_HPP
#define LD35_SWITCH_HPP

#include <Engine/SpriteNode.hpp>
#include "misc.hpp"

class Switch : public engine::SpriteNode{
protected:
	std::string m_target;
	bool m_on;
public:
	Switch(engine::Scene* scene);
	~Switch();

	virtual uint8_t GetType() const {
		return NT_SWITCH;
	}

	virtual bool initialize(Json::Value& root);

	void Flip();

};


#endif //LD35_SWITCH_HPP
