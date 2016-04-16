#ifndef LD35_RUNE_HPP
#define LD35_RUNE_HPP

#include "misc.hpp"

#include <Engine/SpriteNode.hpp>

class Rune : public engine::SpriteNode {
protected:
	std::string m_runeType;
public:
	Rune(engine::Scene* scene);

	virtual uint8_t GetType() const {
		return NT_RUNE;
	}

	virtual bool initialize(Json::Value& root);

	~Rune();

	const std::string& GetRuneType() const {
		return m_runeType;
	}
};


#endif //LD35_RUNE_HPP
