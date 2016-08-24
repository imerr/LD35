//
// Created by iMer on 16.04.2016.
//

#include "Background.hpp"
#include "Level.hpp"

#include <Engine/Game.hpp>
#include <Engine/util/misc.hpp>
#include <iostream>

Background::Background(engine::Scene* scene) : SpriteNode(scene) {

}

Background::~Background() {

}


void Background::draw(sf::RenderTarget& target, sf::RenderStates states, float delta) {
	auto view = m_scene->GetGame()->GetWindow()->getView();
	auto wSize = view.getSize();
	sf::Vector2f viewPos(view.getCenter().x - wSize.x / 2.0f,
						 view.getCenter().y - wSize.y / 2.0f);
	auto levelSize = m_scene->GetSize();
	sf::Vector2f posRatio(viewPos.x / (levelSize.x - wSize.x),
					   viewPos.y / (levelSize.y - wSize.y));

	setPosition(viewPos.x + (wSize.x - GetSize().x)* posRatio.x,
				viewPos.y + (wSize.y - GetSize().y)* posRatio.y);

	engine::Node::draw(target, states, delta);
}



