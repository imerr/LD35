//
// Created by iMer on 16.04.2016.
//

#include "Tip.hpp"
#include <Engine/Scene.hpp>
#include <Engine/Text.hpp>
#include <limits>

Tip::Tip(engine::Scene* scene): SpriteNode(scene), m_clearTimer(std::numeric_limits<float>::infinity()) {

}

Tip::~Tip() {

}

bool Tip::initialize(Json::Value& root) {
	if (!engine::SpriteNode::initialize(root)) {
		return false;
	}
	m_text = root.get("tip", "someone [IMER] forgot to put text for the tip.. mmmh").asString();
	return true;
}

void Tip::Show() {
	engine::Node* t = m_scene->GetUi()->GetChildByID("tip");
	if (t) {
		static_cast<engine::Text*>(t)->SetText(m_text);
	}
	m_clearTimer = 15;
}

void Tip::OnUpdate(sf::Time interval) {
	m_clearTimer -= interval.asSeconds();
	if (m_clearTimer < 0) {
		m_clearTimer = std::numeric_limits<float>::infinity();
		engine::Node* t = m_scene->GetUi()->GetChildByID("tip");
		if (t) {
			engine::Text* text = static_cast<engine::Text*>(t);
			if (text->GetText() == m_text) {
				text->SetText("");
			}
		}
	}
}









