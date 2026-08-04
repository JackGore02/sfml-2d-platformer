#include <GameHUDElemBasic.h>

namespace LJMU
{
	//-----------INTERFACE IMPLEMENTATION---------------------------------------------------------

	/////////////////////////////////
	// Implement our Update Function 
	/////////////////////////////////
	void GameHUDElemBasic::update(sf::Time & ptpf, sf::Time & ptotal)
	{
		if (!this->Updatable)
			return;
	}

	/////////////////////////////////
	// Implement our Render Function. 
	/////////////////////////////////
	void GameHUDElemBasic::render(sf::RenderWindow & pwndw)
	{
		if (this->Visible)
			pwndw.draw(this->_hud);
	}
}
