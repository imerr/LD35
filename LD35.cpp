//
// Created by iMer on 16.04.2016.
//

#include <Engine/Factory.hpp>
#include "LD35.hpp"
#include "Level.hpp"

LD35::LD35() {
	m_windowTitle = "LD35 - To be named";
	m_scene = engine::Factory::create<Level>("assets/scripts/level.json", this);
}

LD35::~LD35() {
}




