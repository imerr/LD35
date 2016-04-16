#include "LD35.hpp"
#include "Player.hpp"
#include <Engine/Factory.hpp>

int main() {
	engine::Factory::RegisterType("player", engine::Factory::CreateChildNode<Player>);
	// TODO(imer): make background always follow the camera (fancy relative moving background even!?)
	//engine::Factory::RegisterType("bg", engine::Factory::CreateChildNode<Background>);

	LD35 game;
	game.run();
	return 0;
}