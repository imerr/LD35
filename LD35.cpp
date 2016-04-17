#include <Engine/Factory.hpp>
#include <Engine/ResourceManager.hpp>
#include "LD35.hpp"
#include "Level.hpp"

LD35::LD35() {
	m_windowTitle = "LD35 - To be named";
	m_scene = engine::Factory::create<Level>("assets/scripts/level.json", this);
	m_music.reset(engine::ResourceManager::instance()->MakeSound("assets/sound/music.wav"));
	if (m_music) {
		m_music->setLoop(true);
		//m_music->play();
	}
	m_keyHandler = OnKeyDown.MakeHandler([this](const sf::Event::KeyEvent& e) {
		if (e.code == sf::Keyboard::M && m_music) {
			if (m_music->getStatus() == sf::Sound::Playing) {
				m_music->pause();
			} else {
				m_music->play();
			}
		}
	});
}

LD35::~LD35() {
	OnKeyDown.RemoveHandler(m_keyHandler);
}




