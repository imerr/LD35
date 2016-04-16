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
	std::string m_next;
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

	virtual bool initialize(Json::Value& root);

	void Next();
};


#endif //LD35_LEVEL_HPP
