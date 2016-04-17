//
// Created by iMer on 17.04.2016.
//

#include "MagicLight.hpp"
#include <Engine/Light.hpp>
#include <iostream>

MagicLight::MagicLight(engine::Scene* scene) : SpriteNode(scene), m_moving(false), m_moveSpeed(0), m_moveTime(0),
											   m_switching(false), m_onTime(0), m_offTime(0), m_switchTime(0), m_toggle(true) {
}

MagicLight::~MagicLight() {

}

bool MagicLight::initialize(Json::Value& root) {
	if (!engine::SpriteNode::initialize(root)) {
		return false;
	}
	m_moving = root.get("moving", true).asBool();
	m_moveSpeed = root.get("moveSpeed", 1.0f).asFloat();
	m_switching = root.get("switching", false).asBool();
	m_onTime = root.get("onTime", 3.0f).asFloat();
	m_offTime = root.get("offTime", 3.0f).asFloat();
	m_toggle = root.get("toggle", true).asBool();
	return true;
}

void MagicLight::OnUpdate(sf::Time interval) {
	if (!m_toggle) return;
	auto head = m_children.front();
	auto light = static_cast<engine::Light*>(head->GetChildren().front());
	if (m_moving) {
		float startAngle = (GetRotation() + 75 - 90 - 45) * engine::util::fPI / 180;
		float changeAngle = engine::util::fPI * 1.5f;
		auto easing = [](float t, float b, float c, float d) -> float {
			if ((t/=d/2) < 1) return c/2*t*t*t + b;
			return c/2*((t-=2)*t*t + 2) + b;
		};
		float rot = 0;
		if (m_moveTime < m_moveSpeed || m_moveTime >= m_moveSpeed*2) {
			if (m_moveTime >= m_moveSpeed*2) {
				m_moveTime -= m_moveSpeed * 2;
			}
			rot = easing(m_moveTime, startAngle, changeAngle, m_moveSpeed);
		} else if (m_moveTime < m_moveSpeed*2) {
			rot = easing(m_moveTime - m_moveSpeed, startAngle + changeAngle, -changeAngle, m_moveSpeed);
		}
		light->SetAngle(rot);
		head->setRotation(rot * 180 / engine::util::fPI - 75 - GetRotation());
		m_moveTime += interval.asSeconds();
	}
	if (m_switching) {
		m_switchTime += interval.asSeconds();
		if (m_switchTime < m_onTime) {
			light->SetActive(true);
		} else if (m_switchTime < m_onTime + m_offTime) {
			light->SetActive(false);
		} else {
			m_switchTime -= m_onTime + m_offTime;
		}
	}
}

void MagicLight::OnInitializeDone() {
	auto head = m_children.front();
	auto light = static_cast<engine::Light*>(head->GetChildren().front());
	light->SetAngle((GetRotation() + 75) * engine::util::fPI / 180);
	m_moveTime = m_moveSpeed/2;
}

void MagicLight::Toggle() {
	auto head = m_children.front();
	auto light = static_cast<engine::Light*>(head->GetChildren().front());
	m_toggle = !m_toggle;
	light->SetActive(m_toggle);
	m_switchTime = 0;
	m_moveTime = 0;
}











