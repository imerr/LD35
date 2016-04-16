#include "LD35.hpp"
#include "Player.hpp"
#include "Background.hpp"
#include "Rune.hpp"
#include "Goal.hpp"
#include "Tip.hpp"
#include <Engine/Factory.hpp>

int main() {
	engine::Factory::RegisterType("player", engine::Factory::CreateChildNode<Player>);
	engine::Factory::RegisterType("bg", engine::Factory::CreateChildNode<Background>);
	engine::Factory::RegisterType("rune", engine::Factory::CreateChildNode<Rune>);
	engine::Factory::RegisterType("goal", engine::Factory::CreateChildNode<Goal>);
	engine::Factory::RegisterType("tip", engine::Factory::CreateChildNode<Tip>);

	LD35 game;
	game.run();
	return 0;
}