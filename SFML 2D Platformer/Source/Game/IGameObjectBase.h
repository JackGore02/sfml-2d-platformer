#pragma once
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>

namespace LJMU
{
	class IGameObjectBase
	{
	public:
		//------CONSTRUCTORS/DESTRUCTORS-----------------------------------
		IGameObjectBase():Visible(true),Updatable(true),Collidable(true),
						 _name(""),_layer(0)
		{

		}
		virtual ~IGameObjectBase() {};

	public: 
		//-------GETTERS/SETTERS-------------------------------------------
		inline std::string getName() { return this->_name; }
		inline void setName(std::string pname) { this->_name = pname; }
		inline int getLayer() { return this->_layer; }
		inline void setLayer(int player) { this->_layer = player; }
	public: 
		//-------OVERRIDABLE FUNCTIONS-------------------------------------
		virtual void loadContent() {};								//Optional Override 
		virtual void update(sf::Time& ptpf, sf::Time& ptotal)=0;	//Mandatory Override
		virtual void render(sf::RenderWindow& pwndw) = 0;			//Mandatory Override
		virtual void cleanup() {};									//Optional Overvide

	public:
		//-------PROPERTIES-----------------------------------------------
		bool         Visible;		//Object Visibility		
		bool         Updatable;		//Is Updatable
		bool         Collidable;	//Is Collidable
	public: 
		inline bool isDead() { return (!Visible && !Updatable && !Collidable); }
		
	public: 
		//-------OPERATOR OVERLOAD----------------------------------------
		friend bool operator< (IGameObjectBase const& a, IGameObjectBase const& b)
		{
			//Choose to Compare on the Layer Property of the Object. 
			return a._layer < b._layer;
		}
	protected: 
		//-------CLASS MEMBERS--------------------------------------------
		std::string  _name;			//Object Name
		int			_layer;			//Object Layer
	};
}
