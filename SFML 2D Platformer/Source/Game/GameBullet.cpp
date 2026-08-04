#include "GameBullet.h"

//-----------CONSTRUCTORS/DESTRUCTORS-----------------------------------------------

/////////////////////////////////////////////
// Constructor for the Bullet Class. 
/////////////////////////////////////////////
LJMU::LJMUBullet::LJMUBullet(sf::Sprite psprite,sf::Vector2f pdir, sf::Vector2f pspawnpos, sf::Time pspawntime):
ILJMUObjectState(),
Bullet(psprite),
Direction(pdir),
SpawnPos(pspawnpos),
SpawnTime(pspawntime),
Speed(static_cast<float>(DEF_SPEED)),
LifeTime(0.0f),
Alpha(DEF_ALPHA)
{
	this->Bullet.setPosition(pspawnpos);	
	sf::Color tcolour = this->Bullet.getColor();
	tcolour.a = Alpha;
	this->Bullet.setColor(tcolour);
}

/////////////////////////////////////////////
// Destructor for the Bullet Classs
/////////////////////////////////////////////
LJMU::LJMUBullet::~LJMUBullet()
{

}

//------------PUBLIC METHODS---------------------------------------------------------

/////////////////////////////////////////////
// Update the Position of the Bullets. 
/////////////////////////////////////////////
void LJMU::LJMUBullet::update(sf::Time& ptpf, sf::Time& ptotal)
{	
    float ttpf = ptpf.asSeconds();
	this->LifeTime += ttpf;
	if (this->Updatable)
		this->Bullet.move(this->Direction * this->Speed * ttpf);
}