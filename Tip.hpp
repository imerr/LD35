#ifndef LD35_TIP_HPP
#define LD35_TIP_HPP

#include "misc.hpp"

#include <Engine/SpriteNode.hpp>

class Tip: public engine::SpriteNode {
protected:
	std::string m_text;
	float m_clearTimer;
public:
	Tip(engine::Scene* scene);
	~Tip();

	virtual bool initialize(Json::Value& root);

	virtual uint8_t GetType() const {
		return NT_TIP;
	}
	const std::string& GetText() {
		return m_text;
	}

	void Show();

protected:
	virtual void OnUpdate(sf::Time interval);


};


#endif //LD35_TIP_HPP
