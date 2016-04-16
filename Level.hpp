//
// Created by iMer on 16.04.2016.
//

#ifndef LD35_LEVEL_HPP
#define LD35_LEVEL_HPP
#include <Engine/Scene.hpp>
#include "Player.hpp"

class Level: public engine::Scene {
protected:
	Player* m_player;
public:
	Level(engine::Game* game);
	~Level();
	Player* GetPlayer() const {
		return m_player;
	}
	void SetPlayer(Player* player, Player* from = nullptr) {
		if (!from || from == m_player) {
			m_player = player;
		}
	}
};


#endif //LD35_LEVEL_HPP
