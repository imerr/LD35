#ifndef LD35_GOAL_HPP
#define LD35_GOAL_HPP

#include <Engine/SpriteNode.hpp>
#include "misc.hpp"

class Goal: public engine::SpriteNode {
protected:
	bool m_won;
	engine::util::BaseEventHandler* m_mouseClickHandler;
public:
	Goal(engine::Scene* scene);
	~Goal();

	virtual uint8_t GetType() const {
		return NT_GOAL;
	}
	void Win();


};


#endif //LD35_GOAL_HPP