#include "LJMUAnimSprite.h"
#include <iostream>

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                           ANIMATION SEQUENCE IMPLEMENTATION                                                          //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//-----------CONSTRUCTORS--------------------------------------

///////////////////////////////////////
// Constructor for the Animation Sequence
// Class.
///////////////////////////////////////
sf::LJMUAnimSeq::LJMUAnimSeq() : _sprite_tex(nullptr)
{

}

//------------ACCESSORS/MUTATORS-------------------------------

///////////////////////////////////////
// Add a animation cell to the framelist.
///////////////////////////////////////
void sf::LJMUAnimSeq::addFrame(sf::IntRect prect)
{
	this->_list_frames.push_back(prect);
}

///////////////////////////////////////
// Set the Sprite Sheet Texture used
// for this animation.
///////////////////////////////////////
void sf::LJMUAnimSeq::setSpriteSheet(const sf::Texture& pssheet)
{
	this->_sprite_tex = &pssheet;
}

///////////////////////////////////////
// Get a Pointer to the Sprite Sheet
// Texture used for this animation.
///////////////////////////////////////
const sf::Texture* sf::LJMUAnimSeq::getSpriteSheet() const
{
	return this->_sprite_tex;
}

///////////////////////////////////////
// Get the Number of Frames in this
// Animation Sequence
///////////////////////////////////////
int sf::LJMUAnimSeq::getFrameCount() const
{
	return static_cast<int>(this->_list_frames.size());
}

///////////////////////////////////////
// Get the Rectangle representing the
// given frame's location in the 
// sprite sheet.
///////////////////////////////////////
const sf::IntRect& sf::LJMUAnimSeq::getFrame(int pframeno) const
{
	return this->_list_frames[pframeno];
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//                           ANIMATED SPRITE IMPLEMENTATION                                                             //
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

//-----------CONSTRUCTORS----------------------------------------

///////////////////////////////////////
// Constructor for the animated sprite
// class.
///////////////////////////////////////
sf::LJMUAnimSprite::LJMUAnimSprite(sf::Time pduration, bool ppaused, bool plooping) :
_anim_seq(), 
_time_duration(pduration),
_frame_no(0), 
_paused(ppaused), 
_looping(plooping), 
_sprite_tex(nullptr)
{

}

///////////////////////////////////////
//Set the Duration, Paused State and 
//Looping State of the Sprite. 
///////////////////////////////////////
void sf::LJMUAnimSprite::create(sf::Time pduration, bool ppaused, bool plooping)
{
	this->_time_duration	= pduration;
	this->_paused			= ppaused;
	this->_looping			= plooping;
}

//-----------ACCESSORS/MUTATORS-----------------------------------

///////////////////////////////////////
// Set the state of this sprite to
// Looping the animation.
///////////////////////////////////////
void sf::LJMUAnimSprite::setLooping(bool plooping)
{
	this->_looping = plooping;
}

///////////////////////////////////////
// Set the Colour of this Sprite.
///////////////////////////////////////
void sf::LJMUAnimSprite::setColor(sf::Color pcolour)
{
	//Set the Blend Colour for all four corners.
	this->_verts[0].color = pcolour;
	this->_verts[1].color = pcolour;
	this->_verts[2].color = pcolour;
	this->_verts[3].color = pcolour;
}

///////////////////////////////////////
// Set the Animation to the given
// Frame
///////////////////////////////////////
void sf::LJMUAnimSprite::setFrame(int pframeno, bool presettime)
{
	if (this->_anim_seq.getSpriteSheet() != nullptr)
	{
		//calculate new vertex positions and texture coordiantes
		sf::IntRect trect = this->_anim_seq.getFrame(pframeno);

		//Set the Four Corners of the Sprite
		this->_verts[0].position = sf::Vector2f(0.f, 0.f);
		this->_verts[1].position = sf::Vector2f(0.f, static_cast<float>(trect.height));
		this->_verts[2].position = sf::Vector2f(static_cast<float>(trect.width), static_cast<float>(trect.height));
		this->_verts[3].position = sf::Vector2f(static_cast<float>(trect.width), 0.f);

		//Set the Coordinates of the Sprite to those of the current frame 
		float tleft = static_cast<float>(trect.left) + 0.0001f;
		float tright = tleft + static_cast<float>(trect.width);
		float ttop = static_cast<float>(trect.top);
		float tbottom = ttop + static_cast<float>(trect.height);
		this->_verts[0].texCoords = sf::Vector2f(tleft, ttop);
		this->_verts[1].texCoords = sf::Vector2f(tleft, tbottom);
		this->_verts[2].texCoords = sf::Vector2f(tright,tbottom);
		this->_verts[3].texCoords = sf::Vector2f(tright,ttop);
	}

	if (presettime)
		this->_time_curr = sf::Time::Zero;
}

///////////////////////////////////////
// Set the Animation sequence to 
// use with this sprite.
///////////////////////////////////////
void sf::LJMUAnimSprite::setAnimation(sf::LJMUAnimSeq panim)
{
	//Set the Animation Sequence
	this->_anim_seq = panim;
	this->_sprite_tex = this->_anim_seq.getSpriteSheet();
	this->_frame_no = 0;
	this->setFrame(this->_frame_no);
}

///////////////////////////////////////
// Set The duration that each frame
// should run for.
///////////////////////////////////////
void sf::LJMUAnimSprite::setFrameTime(sf::Time pduration)
{
	this->_time_duration = pduration;
}

///////////////////////////////////////
// Get the Animation Sequence used with
// this sprite.
///////////////////////////////////////
sf::LJMUAnimSeq sf::LJMUAnimSprite::getAnimation()
{
	return this->_anim_seq;
}

///////////////////////////////////////
// Get the Local Bounds of the current
// frame of this sprite.
///////////////////////////////////////
sf::FloatRect sf::LJMUAnimSprite::getLocalBounds()
{
	sf::IntRect trect = this->_anim_seq.getFrame(this->_frame_no);

	float twidth = static_cast<float>(std::abs(trect.width));
	float theight = static_cast<float>(std::abs(trect.height));

	return sf::FloatRect(0.f, 0.f, twidth, theight);
}

///////////////////////////////////////
// Get the Transformed Bounds of the 
// current frame of this sprite.
///////////////////////////////////////
sf::FloatRect sf::LJMUAnimSprite::getGlobalBounds()
{
	return this->getTransform().transformRect(this->getLocalBounds());
}

///////////////////////////////////////
// Get the Duration each frame runs for.
///////////////////////////////////////
sf::Time sf::LJMUAnimSprite::getFrameTime()
{
	return this->_time_duration;
}

///////////////////////////////////////
// Return true if this animation is looping
///////////////////////////////////////
bool sf::LJMUAnimSprite::isLooping()
{
	return this->_looping;
}

///////////////////////////////////////
// Return true if this animation is playing
///////////////////////////////////////
bool sf::LJMUAnimSprite::isPlaying()
{
	return !this->_paused;
}

//---------------PUBLIC METHODS---------------------------------------------------

///////////////////////////////////////
// Start the animation.
///////////////////////////////////////
void sf::LJMUAnimSprite::play()
{
	this->_paused = false;
}

///////////////////////////////////////
// Replace the current animation
// with the given animation and start it.
///////////////////////////////////////
void sf::LJMUAnimSprite::playNew(sf::LJMUAnimSeq panim)
{
	this->setAnimation(panim);
	this->play();
}

///////////////////////////////////////
// Pause this animation.
///////////////////////////////////////
void sf::LJMUAnimSprite::pause()
{
	this->_paused = true;
}

///////////////////////////////////////
// Stop this animation playing and 
// reset it back to the first frame.
///////////////////////////////////////
void sf::LJMUAnimSprite::stop()
{
	this->_paused = true;
	this->_frame_no = 0;
	this->setFrame(this->_frame_no);
}

/////////////////////////////////////////////
// Get the Frame Number
/////////////////////////////////////////////
int sf::LJMUAnimSprite::getFrameNo()
{
	return this->_frame_no;
}

/////////////////////////////////////////////
// Get the Current Frame Time
/////////////////////////////////////////////
sf::Time sf::LJMUAnimSprite::getCurrentFrameTime()
{
	return this->_time_curr;
}

/////////////////////////////////////////////
// Set the Frame Time and the Frame Number
/////////////////////////////////////////////
void sf::LJMUAnimSprite::setFrame(sf::Time ptime, int pframeno)
{
	this->_frame_no = pframeno;
	this->_time_curr = ptime;
	this->setFrame(this->_frame_no, false);
}

/////////////////////////////////////////////
// Increment the Animation Frame
/////////////////////////////////////////////
void sf::LJMUAnimSprite::incrementFrame(sf::Time ptime, bool ploop)
{
	int tfc		         = this->_anim_seq.getFrameCount();
	int tframeno         = this->_frame_no;
	tframeno += 1;
	if (ploop)
		tframeno = tframeno % tfc;
	else
		tframeno = std::min<int>(tframeno, tfc-1);
	this->setFrame(ptime,tframeno);
}

/////////////////////////////////////////////
// Decrement the Animation Frame
/////////////////////////////////////////////
void sf::LJMUAnimSprite::decrementFrame(sf::Time ptime, bool ploop)
{
	int tfc      = this->_anim_seq.getFrameCount();
	int tframeno = this->_frame_no;
	tframeno -= 1;
	if (ploop)
		tframeno = tframeno % tfc;
	else
		tframeno = std::max<int>(tframeno, 0);
	this->setFrame(ptime, tframeno);
}

///////////////////////////////////////
// Update this Animated Sprite
///////////////////////////////////////
void sf::LJMUAnimSprite::update(sf::Time ptpf)
{
	// if not paused and we have a valid animation
	if (!this->_paused && this->_anim_seq.getFrameCount() != 0)
	{
		// add delta time
		this->_time_curr += ptpf;

		// if current time is bigger then the frame time advance one frame
		if (this->_time_curr >= this->_time_duration)
		{
			// reset time, but keep the remainder
			this->_time_curr = sf::microseconds(this->_time_curr.asMicroseconds() % this->_time_duration.asMicroseconds());

			// get next Frame index
			if (this->_frame_no + 1 < this->_anim_seq.getFrameCount())
				this->_frame_no++;
			else
			{
				// animation has ended
				this->_frame_no = 0; // reset to start

				//If we are not looping and at the end then pause the animation
				if (!this->_looping)
				{
					this->_paused = true;
				}
			}

			// set the current frame, not reseting the time
			this->setFrame(this->_frame_no, false);
		}
	}
}

//--------METHOD OVERRIDES---------------------------------------------------------

///////////////////////////////////////
// Draw this Animated Sprite.
///////////////////////////////////////
void sf::LJMUAnimSprite::draw(sf::RenderTarget& ptarget, sf::RenderStates pstates) const
{
	if (this->_anim_seq.getFrameCount() != 0 && this->_sprite_tex != nullptr)
	{
		//Set the States to the Current Transform of the Sprite (Rotation,Translation,Scale - World Matrix)
		pstates.transform *= this->getTransform();
		//Set the Texture to use the Sprite Sheet
		pstates.texture = this->_sprite_tex;
		//Draw the Quadrilateral representing the sprite.
		ptarget.draw(this->_verts, 4, sf::Quads, pstates);
	}
}