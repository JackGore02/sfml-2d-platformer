#include <GameObjectAnimated.h>

namespace LJMU
{
	//-----------INTERFACE IMPLEMENTATION---------------------------------------------------------

	/////////////////////////////////
	// Implement our Update Function. 
	/////////////////////////////////
	void GameObjectAnimated::update(sf::Time & ptpf, sf::Time & ptotal)
	{
		if(this->Updatable)
			this->_anim.update(ptpf);
	}

	/////////////////////////////////
	// Implement our Render Function. 
	/////////////////////////////////
	void GameObjectAnimated::render(sf::RenderWindow & pwndw)
	{
		if(this->Visible)
			pwndw.draw(this->_anim);
	}
}
