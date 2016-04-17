//
// Created by iMer on 17.04.2016.
//

#include <iostream>
#include "Switch.hpp"
#include "MagicLight.hpp"

Switch::Switch(engine::Scene* scene): SpriteNode(scene), m_on(false) {

}

Switch::~Switch() {

}

bool Switch::initialize(Json::Value& root) {
	if (!engine::SpriteNode::initialize(root)) {
		return false;
	}
	m_target = root.get("target", "").asString();
	return true;
}

void Switch::Flip() {
	engine::Node* target = m_parent->GetChildByID(m_target);
	switch (target->GetType()) {
		case NT_MAGICLIGHT:
			static_cast<MagicLight*>(target)->Toggle();
			break;
		default:
			std::cerr << "Unknown target type for '"<< m_target << "'" << std::endl;
	}
	m_on = !m_on;
	if (m_on) {
		PlayAnimation("active");
	} else {
		PlayAnimation("default");
	}
}