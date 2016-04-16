//
// Created by iMer on 16.04.2016.
//

#ifndef LD35_BACKGROUND_HPP
#define LD35_BACKGROUND_HPP


#include <Engine/SpriteNode.hpp>

class Background: public engine::SpriteNode {
	public:
		Background(engine::Scene* scene);
		~Background();

	virtual void draw(sf::RenderTarget& target, sf::RenderStates states, float delta);


protected:


};


#endif //LD35_BACKGROUND_HPP
