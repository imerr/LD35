//
// Created by iMer on 16.04.2016.
//

#include "Player.hpp"
#include "Level.hpp"
#include "misc.hpp"
#include "Rune.hpp"
#include "Goal.hpp"
#include "Tip.hpp"

#include <Engine/util/json.hpp>
#include <Engine/Game.hpp>
#include <Engine/ResourceManager.hpp>

#include <SFML/Window.hpp>

#include <iostream>
#include <Engine/Text.hpp>
#include <Engine/Factory.hpp>

Player::Player(engine::Scene* scene) : SpriteNode(scene), m_canMove(true), m_canJump(true), m_canFly(false),
									   m_speed(0, 0), m_jumpStrength(0),
									   m_grounded(0), m_activeRune(nullptr) {

	m_mouseclickHandler = m_scene->GetGame()->OnMouseClick.MakeHandler([this](const sf::Event::MouseButtonEvent& m) {
		if (m_activeRune && m.button == sf::Mouse::Right) {
			ShapeShift(m_activeRune->GetRuneType());
			m_activeRune = nullptr;
			engine::Node* runeDesc = m_scene->GetUi()->GetChildByID("rune_desc");
			if (runeDesc) {
				static_cast<engine::Text*>(runeDesc)->SetText("");
			}
		}
	});
	m_contactHandler = m_scene->OnContact.MakeHandler([this](b2Contact* contact, bool begin) {
		void* A = contact->GetFixtureA()->GetBody()->GetUserData();
		void* B = contact->GetFixtureB()->GetBody()->GetUserData();
		engine::Node* other = nullptr;
		b2Fixture* fixture = nullptr;
		if (A == this) {
			other = static_cast<engine::Node*>(B);
			fixture = contact->GetFixtureA();
		} else if (B == this) {
			other = static_cast<engine::Node*>(A);
			fixture = contact->GetFixtureB();
		}
		if (!other ||other->GetType() >= engine::NT_END && other->GetType() != NT_ONEWAYPLATFORM) return;
		if (A == this || B == this) {
			if (fixture->GetFriction() >= 0.3) {
				if (begin) {
					m_grounded += 1;
				} else {
					m_grounded -= 1;
				}
			}
		}
	});
	m_presolveContactHandler = m_scene->OnContactPreSolve.MakeHandler(
			[this](b2Contact* contact, const b2Manifold* manifold) {
				if (this->m_destroy) return;
				void* A = contact->GetFixtureA()->GetBody()->GetUserData();
				void* B = contact->GetFixtureB()->GetBody()->GetUserData();
				engine::Node* other = nullptr;
				b2Fixture* otherFixture = nullptr;

				if (A == this) {
					other = static_cast<engine::Node*>(B);
					otherFixture = contact->GetFixtureB();
				} else if (B == this) {
					other = static_cast<engine::Node*>(A);
					otherFixture = contact->GetFixtureA();
				}
				if (!other) return;
				if (other->GetType() == NT_RUNE) {
					contact->SetEnabled(false);
					Rune* rune = static_cast<Rune*>(other);
					if ("assets/scripts/player_" + rune->GetRuneType() + ".json" != m_filename) {
						m_activeRune = rune;
						m_activeRune->PlayAnimation("active", "default");
						engine::Node* runeDesc = m_scene->GetUi()->GetChildByID("rune_desc");
						if (runeDesc) {
							static_cast<engine::Text*>(runeDesc)->SetText(
									"Press rightclick to shape-shift into a " + m_activeRune->GetRuneType());
						}
					}
				}
				if (other->GetType() == NT_GOAL) {
					contact->SetEnabled(false);
					static_cast<Goal*>(other)->Win();
				}

				if (other->GetType() == NT_TIP) {
					contact->SetEnabled(false);
					static_cast<Tip*>(other)->Show();
				}
				if (other->GetType() == NT_ONEWAYPLATFORM) {
					if (this->m_canFly) {
						contact->SetEnabled(false);
						return;
					}

					b2AABB aabb;
					b2AABB myAABB;
					b2AABB myAABB_;
					otherFixture->GetShape()->ComputeAABB(&aabb, otherFixture->GetBody()->GetTransform(), 0 /* we only have boxes */);
					auto f = this->m_body->GetFixtureList();
					while (f != nullptr) {
						f->GetShape()->ComputeAABB(&myAABB_, m_body->GetTransform(), 0);
						f = f->GetNext();
						myAABB.Combine(myAABB_);
					}
					if (myAABB.upperBound.y > aabb.upperBound.y) {
						contact->SetEnabled(false);
					}
				}
			});
	static_cast<Level*>(scene)->SetPlayer(this);
	m_explodeSound.reset(engine::ResourceManager::instance()->MakeSound("assets/sound/explode.ogg"));
	m_lightRayHandler = OnLightRay.MakeHandler([this](const engine::Light* light) {
		auto c = light->GetLightColor();
		if (c.r > c.b + c.g){ // red light!
			this->Die();
		}
	});
}

Player::~Player() {
	OnLightRay.RemoveHandler(m_lightRayHandler);
	m_scene->OnContact.RemoveHandler(m_contactHandler);
	m_scene->OnContactPreSolve.RemoveHandler(m_presolveContactHandler);
	m_scene->GetGame()->OnMouseClick.RemoveHandler(m_mouseclickHandler);
	static_cast<Level*>(m_scene)->SetPlayer(nullptr, this);
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
	if (!m_activeRune && m_grounded && m_canJump && sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
		vel.y = -m_jumpStrength;
	}
	if (m_canMove && sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		// move towards mouse
		if (m_canFly) {
			vel.x = std::min(m_speed.x, 3 * fabsf((pos.x - toPos.x) / m_scene->GetPixelMeterRatio()));
			if (toPos.x < pos.x) {
				vel.x *= -1;
			}
			vel.y =std::min(m_speed.y, 3 * fabsf((pos.y - toPos.y) / m_scene->GetPixelMeterRatio()));
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

	if (m_activeRune) {
		auto dist = (GetPosition() - m_activeRune->GetPosition());
		float d = sqrtf(dist.x * dist.x + dist.y * dist.y);
		if (d > 300) {
			m_activeRune = nullptr;
			engine::Node* runeDesc = m_scene->GetUi()->GetChildByID("rune_desc");
			if (runeDesc) {
				static_cast<engine::Text*>(runeDesc)->SetText("");
			}
		} else {
			m_activeRune->PlayAnimation("active", "default");
		}
	}
}

void Player::ShapeShift(std::string what) {
	engine::Node* n = engine::Factory::CreateChildFromFile("assets/scripts/player_" + what + ".json", m_scene);
	engine::Node* explosion = engine::Factory::CreateChildFromFile("assets/scripts/explosion.json", m_scene);
	n->SetPosition(GetPosition().x, GetPosition().y - GetSize().y / 2 - n->GetSize().y);
	explosion->SetPosition(GetPosition().x, GetPosition().y + 180);
	static_cast<Player*>(n)->PlayExplodeSound();
	Delete();
}

void Player::PlayExplodeSound() {
	if (m_explodeSound) {
		m_explodeSound->play();
	}
}

void Player::Die() {
	if (!m_active) return;
	engine::Node* explosion = engine::Factory::CreateChildFromFile("assets/scripts/explosion.json", m_scene);
	explosion->SetPosition(GetPosition().x, GetPosition().y + 180);
	PlayExplodeSound();
	SetActive(false);
	static_cast<Level*>(m_scene)->Lost();
}








