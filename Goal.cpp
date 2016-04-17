#include "Goal.hpp"
#include "Level.hpp"
#include <Engine/Game.hpp>
#include <Engine/Factory.hpp>
#include <Engine/ResourceManager.hpp>

Goal::Goal(engine::Scene* scene): SpriteNode(scene), m_won(false) {
	m_mouseClickHandler = scene->GetGame()->OnMouseClick.MakeHandler([this](const sf::Event::MouseButtonEvent& mouseButtonEvent) {
		if (m_won && mouseButtonEvent.button == sf::Mouse::Right) {
			static_cast<Level*>(m_scene)->Next();
		}
	});
	m_sound = engine::ResourceManager::instance()->MakeSound("assets/sound/yaay.ogg");
}

Goal::~Goal() {
	m_scene->GetGame()->OnMouseClick.RemoveHandler(m_mouseClickHandler);
}

void Goal::Win() {
	if (m_sound && m_sound->getStatus() != sf::Sound::Playing) {
		m_sound->play();
	}
	// TODO(imer): sound
	GetChildByID("confetti")->SetActive(true);
	m_scene->GetUi()->GetChildByID("won")->SetActive(true);
	m_won = true;
}




