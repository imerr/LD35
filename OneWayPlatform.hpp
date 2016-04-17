//
// Created by iMer on 17.04.2016.
//

#ifndef LD35_ONEWAYPLATFORM_HPP
#define LD35_ONEWAYPLATFORM_HPP
#include "misc.hpp"
#include <Engine/SpriteNode.hpp>

class OneWayPlatform: public engine::SpriteNode {
public:
	OneWayPlatform(engine::Scene* scene);
	~OneWayPlatform();

private:
	virtual uint8_t GetType() const {
		return NT_ONEWAYPLATFORM;
	}


};


#endif //LD35WRAP_ONEWAYPLATFORM_HPP
