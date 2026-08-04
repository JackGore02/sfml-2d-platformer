#ifndef __LJMU_ANIMSPRITE_H_
#define __LJMU_ANIMSPRITE_H_

#include <vector>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <SFML/Graphics/RenderTarget.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Transformable.hpp>
#include <SFML/System/Vector2.hpp>
#include <SFML/System/Time.hpp>

namespace sf
{

///////////////////////////////////////
// Class to represent an animation 
// sequence for a Given SpriteSheet. 
// Framework Default only handles 
// Programmatic Frame building. 
//
// AUTHOR:  DR CHRIS CARTER
///////////////////////////////////////
class LJMUAnimSeq
{
	public:
		//--------CONSTRUCTORS---------------------------------------------
		LJMUAnimSeq(void);		//Default Constructor for the class
		~LJMUAnimSeq(void){};   //Default Destructor for the class

		//--------PUBLIC METHODS-------------------------------------------
		const sf::Texture*		getSpriteSheet() const;				//Get a Pointer to the Active Sprite Sheet
		int						getFrameCount() const;				//Get the number of frames in this Sprite SHeet
		const sf::IntRect&		getFrame(int pno) const;	//Get the Rectangle around a given frame.

		void					addFrame(sf::IntRect prect);		//Add a frame (represented as a Rectangle) to the class
		void					setSpriteSheet(const sf::Texture& pssheet);	//Set the Frame for the Sprite Sheet. 
		
	private:
		//--------CLASS MEMBERS--------------------------------------------
		std::vector<sf::IntRect>	_list_frames;	//Class member to store the list of frames
		const sf::Texture*			_sprite_tex;	//Class member to store the spritesheet texture.
};


///////////////////////////////////////
// Class representing the actual 
// Sprite which can be animated.  
//
// AUTHOR:  DR CHRIS CARTER
///////////////////////////////////////
class LJMUAnimSprite : public sf::Drawable, public sf::Transformable	//Inherit from Drawable and Transformable to allow this Sprite to be Transformed and Drawn like a normal sprite
{
public:
	//-----------CONSTRUCTORS-------------------------------------------
	LJMUAnimSprite(sf::Time pduration = sf::seconds(0.2f), bool ppaused = false, bool plooping = true);	//Default Constructor for this class
	~LJMUAnimSprite(void){};		//Default Destructor for this class

	//-----------PUBLIC METHODS-----------------------------------------
	void				update(sf::Time ptpf);					//Updates the Animation Sequence
	void				play();									//Starts the Animation Sequence
	void				playNew(LJMUAnimSeq panim);		        //Replaces the current Sequence and Plays it
	void				pause();								//Pauses the Animation Sequence
	void				stop();									//Stops the Animation Sequence, returning to Frame 0
	void                create(sf::Time pduration = sf::seconds(0.2f), bool ppaused = false, bool plooping = true); //Creates an Animation Sequence

	//-----------GETTERS/SETTERS----------------------------------------
	LJMUAnimSeq  	    getAnimation();							        		//Get the Animation Sequence
	sf::FloatRect		getLocalBounds();										//Get the Local Bounds of the Current Frame (Cell)
	sf::FloatRect		getGlobalBounds();										//Get the Transformed Bounds of the Current Frame (Cell)
	bool				isLooping();											//Return True if Looping
	bool				isPlaying();											//Return True if Animation is playing
	sf::Time			getFrameTime();											//Get the Duration of each frame of the animation
	void				setFrame(int pframeno, bool presettime = true);	//Set the Frame Manually
	void                setAnimation(LJMUAnimSeq panim);						//Copy the Animation Sequence to Use
	void				setFrameTime(sf::Time ptime);							//Set the Duration of Each Frame
	void				setLooping(bool plooping);								//Set Whether this Animation will Loop
	void				setColor(sf::Color pcolour);						    //Set the Colour of the Sprite

	int				    getFrameNo();											//Get the Frame Number
	sf::Time            getCurrentFrameTime();									//Get Length of Time we have been playing for. 
	void				setFrame(sf::Time ptime,int pframeno);			        //Set the Frame Manually for Timed Animations
	void                incrementFrame(sf::Time ptime,bool ploop = false);		//Increment the Frame
	void                decrementFrame(sf::Time ptime,bool ploop = false);		//Decrement the Frame

private:
	//----------CLASS MEMBERS--------------------------------------------
	LJMUAnimSeq	        _anim_seq;			//The Animation Sequence (SINGLE INSTANCE IN TEMPLATE!!)
	sf::Time			_time_duration;		//The Time Per Frame for the Animation
	sf::Time			_time_curr;			//The Current Animation Time
	int			        _frame_no;			//The Current Frame Number
	bool				_paused;			//Bool to represent whether the animation is paused
	bool				_looping;			//Bool to represent whether the animation is playing
	const sf::Texture*	_sprite_tex;		//The Sprite Sheet Texture 
	sf::Vertex			_verts[4];			//The Four Vertices of the Two Right Angled Triangles Representing the Sprite

	//------------METHOD OVERRIDES---------------------------------------------------
	virtual void draw(sf::RenderTarget& ptarget, sf::RenderStates pstates) const;	//Override the Default Draw Method to draw the animated sprite
};

}

#endif 