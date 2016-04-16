//
// Created by iMer on 16.04.2016.
//

#include "Rune.hpp"

Rune::Rune(engine::Scene* scene): SpriteNode(scene), m_runeType("mouse") {
}

Rune::~Rune() {

}

bool Rune::initialize(Json::Value& root) {
	if (!engine::SpriteNode::initialize(root)) {
		return false;
	}
	m_runeType = root.get("rune", m_runeType).asString();
	return true;
}





