#pragma once
#ifndef __GAME_SCREEN_SHOP_H_
#define __GAME_SCREEN_SHOP_H_

//Include our Framework Library
#include <LJMUPCH.h>

//Include our Game Application Classes
#include "GameEnums.h"
#include "GameHUDElemBasic.h"
#include "GamePlayer.h"
#include "GameShopElemsBasic.h"

namespace LJMU
{
	class GameScreenShop : public sf::ILJMUScreenBase
	{

		//-----------Simplify the Pointer Declaration via a Using Statement--------------
		using ShopItemPtr = std::shared_ptr<LJMU::GameShopElemBasic>;

		using ItemsHeldPtr = std::shared_ptr<LJMU::GameShopElemBasic>;

		//------------INNER CLASSES------------------------------------------------------
		enum class ShopActionType
		{
			Increment,
			Decrement,
			Selection,
			Update,
			Purchase
		};

		struct ShopActions
		{
			using del = std::function<void(ShopItemPtr pid)>;
			std::map<ShopActionType, del> Actions;

			void OnIncrement(ShopItemPtr pid)
			{
				auto titer = this->Actions.find(ShopActionType::Increment);
				if (titer != this->Actions.end())
				{
					//Get the function and call it. 
					auto tfunc = this->Actions[ShopActionType::Increment];
					tfunc(pid);
				}
			}
			void OnDecrement(ShopItemPtr pid)
			{
				auto titer = this->Actions.find(ShopActionType::Decrement);
				if (titer != this->Actions.end())
				{
					//Get the function and call it. 
					auto tfunc = this->Actions[ShopActionType::Decrement];
					tfunc(pid);
				}
			}
			void OnSelect(ShopItemPtr pid)
			{
				auto titer = this->Actions.find(ShopActionType::Selection);
				if (titer != this->Actions.end())
				{
					this->Actions[ShopActionType::Selection](pid);
				}
			}
			void OnUpdate(ShopItemPtr pid)
			{
				auto titer = this->Actions.find(ShopActionType::Update);
				if (titer != this->Actions.end())
				{
					this->Actions[ShopActionType::Update](pid);
				}
			}
			void OnPurchase(ShopItemPtr pid)
			{
				if (this->Actions.find(ShopActionType::Purchase) != this->Actions.end())
				{
					this->Actions[ShopActionType::Purchase](pid);
				}
			}
		};


		//---------CONSTANTS-------------------------------------------------------
		static const unsigned int   HUD_SCALE = 48;   //Constant to hold the scale of the HUD

		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		GameScreenShop();	//Default Constructor
		~GameScreenShop();	//Default Destructor

	public:
		//-----------FUNCTION OVERRIDES/INTERFACE IMPLEMENTATION-------------
		virtual void    loadContent() override;
		virtual void	handleEvent(const sf::Event& pevent) override;
		virtual void    bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered = false) override;
		virtual void	update(sf::Time& ptpf, sf::Time& ptotal) override;
		virtual void	render() override;
		virtual void    cleanup() override;

	public:
		//-----------PUBLIC FUNCTIONS----------------------------------------

		//-----------PROTECTED FUNCTIONS-------------------------------------
	protected:
		
		void handleInput(sf::Keyboard::Key pkey, bool ppressed); //Handle Keyboard Events
		void onBack();
		//Sub-Routines
		void loadResources();
		void setupShopBG();
		void setupShopElements();
		void setupCameras();
		void setupTitle();

		//Shpp navigation - Event Handling
		void onMoveUp();
		void onMoveDown();
		void onPurchase();

		ShopItemPtr createShopExit(std::string defaultText);
void addItem(ShopItemPtr pitem);

	public:

		//-----------GETTERS/SETTERS-----------------------------------------

	protected:
		//-----------CLASS MEMBERS-------------------------------------------

	


		sf::LJMUResourceHelper<sf::Texture, std::string>   _res_level;		//Resource Manager for Level BG
		sf::LJMUResourceHelper<sf::Texture, std::string>   _res_static;	    //Resource Manager for Static Sprites
		sf::LJMUResourceHelper<sf::Font, std::string>	  _res_font;        //Resource Manager for Fonts


		LJMU::MenuControls								   _controls;		//Use the Menu Control Scheme Class

		std::vector<LJMU::GameObjectBasic>			     _bg_layers;		//Level Collection
		std::vector<ShopItemPtr>						 _shopItems;		//Shop Items vector

		std::vector<ItemsHeldPtr>                        _heldItems; // Vector for items "purchases"/"held"

		int												 _selected_index;	//Selected Index
		int												 _selectedItem;	//Selected Item

		std::map<ShopItemPtr, ShopActions>				 _shopActions;		// Shop Event Handlers
		std::map<ShopItemPtr, LJMU::GameObjectBasic>      _shopSprites;		// Shop Sprites

		LJMU::GameHUDElemBasic                           ShopTitle; // Title for shop screen


		sf::Color								_clr_curr;					//Colour For Current items
		sf::Color								_clr_other;					//Colour For Non-Selected Items

		std::deque<LJMU::GameCamera>			_cameras;					//Menu Cameras


		

	};
}
#endif