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
	bool m_paused;
	bool m_lost;
	bool m_won;
	engine::util::BaseEventHandler* m_mouseClickHandler;
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

	virtual void update(sf::Time interval);

	void Next();
	void Lost();
	void Won();
};


#endif //LD35_LEVEL_HPP
