//
// Created by iMer on 16.04.2016.
//

#include "Level.hpp"
#include <Engine/Factory.hpp>
#include <Engine/Game.hpp>

Level::Level(engine::Game* game) : Scene(game), m_player(nullptr), m_paused(false), m_won(false), m_lost(false) {
	m_mouseClickHandler = GetGame()->OnMouseClick.MakeHandler([this](const sf::Event::MouseButtonEvent& mouseButtonEvent) {
		if (mouseButtonEvent.button == sf::Mouse::Right) {
			if (m_won) {
				Next();
			} else if (m_lost) {
				m_next = m_filename;
				Next();
			}
		}
	});
}

Level::~Level() {
	GetGame()->OnMouseClick.RemoveHandler(m_mouseClickHandler);
}

bool Level::initialize(Json::Value& root) {
	if(!engine::Scene::initialize(root)){
		return false;
	}
	m_next = root.get("next", "").asString();
	return true;
}

void Level::Next() {
	if (m_next.length()) {
		m_scene->GetGame()->SwitchScene(engine::Factory::create<Level>(m_next, m_game));
	}
}

void Level::update(sf::Time interval) {
	if (!m_game->IsFocus() && !m_paused) {
		auto pauseScreen = GetUi()->GetChildByID("paused");
		if (pauseScreen) {
			m_paused = true;
			pauseScreen->SetActive(true);
		}
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		m_next = m_filename;
		Next();
		return;
	}
	if (m_paused) {
		m_ui->update(interval);
		if (m_game->IsFocus() && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
			m_paused = false;
			auto pauseScreen = GetUi()->GetChildByID("paused");
			if (pauseScreen) {
				pauseScreen->SetActive(false);
			}
		}
	} else {
		engine::Node::update(interval);
	}
}

void Level::Lost() {
	m_lost = true;
	m_scene->GetUi()->GetChildByID("lost")->SetActive(true);
}
void Level::Won() {
	m_won = true;
	m_scene->GetUi()->GetChildByID("won")->SetActive(true);
}










