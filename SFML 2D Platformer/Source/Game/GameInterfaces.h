#ifndef __GAME_INTERFACES_H_
#define __GAME_INTERFACES_H_

namespace LJMU
{
	///////////////////////////////
	// Base class to Represent Shared
	// State Data between Game Objects
	///////////////////////////////
	class ILJMUObjectState
	{
		//------CONSTRUCTORS--------------------------------------
	public: 
		//Default Constructors
		ILJMUObjectState()
			:Visible(true),
			Updatable(true),
			Collidable(true)
		{

		}

	public:
		//-------DATA MEMBERS------------------------------------
		bool         Visible;			//Is the Object Visible?
		bool         Updatable;			//Is the Object Updatable?
		bool         Collidable;		//Is the Object Collidable?
	};
}
#endif