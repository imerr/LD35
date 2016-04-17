#include "Goal.hpp"
#include "Level.hpp"
#include <Engine/Game.hpp>
#include <Engine/Factory.hpp>
#include <Engine/ResourceManager.hpp>

Goal::Goal(engine::Scene* scene): SpriteNode(scene) {

	m_sound.reset(engine::ResourceManager::instance()->MakeSound("assets/sound/yaay.ogg"));
}

Goal::~Goal() {

}

void Goal::Win() {
	if (m_sound && m_sound->getStatus() != sf::Sound::Playing) {
		m_sound->play();
	}
	GetChildByID("confetti")->SetActive(true);
	static_cast<Level*>(m_scene)->Won();
}




