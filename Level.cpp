//
// Created by iMer on 16.04.2016.
//

#include "Level.hpp"
#include <Engine/Factory.hpp>
#include <Engine/Game.hpp>

Level::~Level() {

}

Level::Level(engine::Game* game) : Scene(game), m_player(nullptr) {

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







