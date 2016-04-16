//
// Created by iMer on 16.04.2016.
//

#include "Player.hpp"

#include <Engine/util/json.hpp>
#include <Engine/Game.hpp>

#include <SFML/Window.hpp>

#include <iostream>

Player::Player(engine::Scene* scene) : SpriteNode(scene), m_canMove(true), m_canJump(true), m_canFly(false),
									   m_speed(0, 0), m_jumpStrength(0),
									   m_grounded(0) {

	m_contactHandler = m_scene->OnContact.MakeHandler([this](b2Contact* contact, bool begin) {
		void* A = contact->GetFixtureA()->GetBody()->GetUserData();
		void* B = contact->GetFixtureB()->GetBody()->GetUserData();
		// TODO: only use bottom fixtures for ground counting
		if (A == this || B == this) {
			if (begin) {
				m_grounded += 1;
			} else {
				m_grounded -= 1;
			}
		}
	});

}

Player::~Player() {
	m_scene->OnContact.RemoveHandler(m_contactHandler);
}

bool Player::initialize(Json::Value& root) {
	if (!engine::SpriteNode::initialize(root)) {
		return false;
	}
	auto player = root["player"];
	if (player.isObject()) {
		m_canMove = player.get("canMove", true).asBool();
		m_canJump = player.get("canJump", true).asBool();
		m_canFly = player.get("canFly", false).asBool();
		m_speed.x = engine::jsonNodeAs<float>(player["speed_x"]);
		m_speed.y = engine::jsonNodeAs<float>(player["speed_y"]);
		m_jumpStrength = engine::jsonNodeAs<float>(player["jumpStrength"]);
	}
	return true;
}

void Player::OnUpdate(sf::Time interval) {
	auto vel = m_body->GetLinearVelocity();
	auto pos = GetPosition();
	auto toPos = m_scene->GetGame()->GetMousePosition();
	if (m_grounded && m_canJump && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		vel.y = -m_jumpStrength;
	}
	if (m_canMove && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		// move towards mouse
		if (m_canFly) {
			vel.x = std::min(m_speed.x, fabsf((pos.x - toPos.x) / m_scene->GetPixelMeterRatio()));
			if (toPos.x < pos.x) {
				vel.x *= -1;
			}
			vel.y = std::min(m_speed.y, fabsf((pos.y - toPos.y) / m_scene->GetPixelMeterRatio()));
			if (toPos.y < pos.y) {
				vel.y *= -1;
			}
			if (!m_body->IsFixedRotation()) {
				float angle = engine::b2Angle(pos, toPos);
				m_body->SetTransform(m_body->GetPosition(), angle);
			}
		} else {
			vel.x = std::min(m_speed.x, fabsf((pos.x - toPos.x) / m_scene->GetPixelMeterRatio()));
			if (toPos.x < pos.x) {
				vel.x *= -1;
			}
		}
	}
	//std::cout << "Vel (" << vel.x << "," << vel.y << ")" << std::endl;
	m_body->SetLinearVelocity(vel);
	if (m_body->IsFixedRotation() && fabsf(vel.x) > 0.01) {
		SetFlipped(vel.x < 0);
		//SetVFlipped(vel.y < 0);
	}
	// Set animations
	if (fabsf(vel.x) > 0.05 || m_canFly && fabsf(vel.y) > 0.05) {
		if (m_currentAnimation != "moving") {
			PlayAnimation("moving");
		}
	} else {
		if (m_currentAnimation != "default") {
			PlayAnimation("default");
		}
	}
	// Center world on player
	auto view = m_scene->GetGame()->GetWindow()->getView();
	auto windowSize = m_scene->GetGame()->GetWindow()->getSize();
	auto levelSize = m_scene->GetSize();
	sf::Vector2f center(pos);
	if (center.x < windowSize.x / 2) {
		center.x = windowSize.x / 2;
	} else if (center.x > levelSize.x - windowSize.x / 2) {
		center.x = levelSize.x - windowSize.x / 2;
	}
	if (center.y < windowSize.y / 2) {
		center.y = windowSize.y / 2;
	} else if (center.y > levelSize.y - windowSize.y / 2) {
		center.y = levelSize.y - windowSize.y / 2;
	}
	view.setCenter(center);
	m_scene->GetGame()->GetWindow()->setView(view);
}







