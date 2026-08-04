#include <GameObjectBasic.h>

namespace LJMU
{
	//-----------INTERFACE IMPLEMENTATION---------------------------------------------------------

	/////////////////////////////////
	// Implement our Update Function. 
	/////////////////////////////////
	void GameObjectBasic::update(sf::Time & ptpf, sf::Time & ptotal)
	{
		if (!this->Updatable)
			return;
	}

	/////////////////////////////////
	// Implement our Render Function. 
	/////////////////////////////////
	void GameObjectBasic::render(sf::RenderWindow & pwndw)
	{
		if (this->Visible)
			pwndw.draw(this->_sprite);
	}
}
