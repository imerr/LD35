#include "Goal.hpp"
#include "Level.hpp"
#include <Engine/Game.hpp>
#include <Engine/Factory.hpp>

Goal::Goal(engine::Scene* scene): SpriteNode(scene), m_won(false) {
	m_mouseClickHandler = scene->GetGame()->OnMouseClick.MakeHandler([this](const sf::Event::MouseButtonEvent& mouseButtonEvent) {
		if (m_won && mouseButtonEvent.button == sf::Mouse::Right) {
			static_cast<Level*>(m_scene)->Next();
		}
	});
}

Goal::~Goal() {

}

void Goal::Win() {
	// TODO(imer): sound
	GetChildByID("confetti")->SetActive(true);
	m_scene->GetUi()->GetChildByID("won")->SetActive(true);
	m_won = true;
}




