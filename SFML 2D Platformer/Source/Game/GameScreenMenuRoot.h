#ifndef __MENU_SCREEN_ROOT_H_
#define __MENU_SCREEN_ROOT_H_

//Include our Framework Library
#include <LJMUPCH.h>

//Include our Game Application Classes
#include <GamePCH.h>

//Include our Menu Control Scheme
#include <MenuControls.h>


namespace LJMU
{
	///////////////////////////////
	// Implementation of a Main Menu Screen.
	//
	// AUTHOR:  DR CHRIS CARTER
	///////////////////////////////
	class GameScreenMenuRoot : public sf::ILJMUScreenBase
	{
		//-----------Simplify the Pointer Declaration via a Using Statement--------------
		using MenuItemPtr = std::shared_ptr<LJMU::GameHUDElemBasic>;

		//------------INNER CLASSES------------------------------------------------------
		enum class MenuActionType
		{
			Increment,
			Decrement,
			Selection,
			Update,
			Save
		};

		struct MenuActions
		{
			using del = std::function<void(MenuItemPtr pid)>;
			std::map<MenuActionType, del> Actions;
			
			void OnIncrement(MenuItemPtr pid)
			{
				auto titer = this->Actions.find(MenuActionType::Increment);
				if (titer != this->Actions.end())
				{
					//Get the function and call it. 
					auto tfunc = this->Actions[MenuActionType::Increment];
					tfunc(pid);
				}
			}
			void OnDecrement(MenuItemPtr pid)
			{
				auto titer = this->Actions.find(MenuActionType::Decrement);
				if (titer != this->Actions.end())
				{
					//Get the function and call it. 
					auto tfunc = this->Actions[MenuActionType::Decrement];
					tfunc(pid);
				}			
			}
			void OnSelect(MenuItemPtr pid)
			{
				auto titer = this->Actions.find(MenuActionType::Selection);
				if (titer != this->Actions.end())
				{
                    this->Actions[MenuActionType::Selection](pid);
				}
			}
			void OnUpdate(MenuItemPtr pid)
			{
				auto titer = this->Actions.find(MenuActionType::Update);
				if (titer != this->Actions.end())
				{
					this->Actions[MenuActionType::Update](pid);
				}
			}
			void OnSave(MenuItemPtr pid)
			{
				if(this->Actions.find(MenuActionType::Save) != this->Actions.end())
				{
					this->Actions[MenuActionType::Save](pid);
				}
			}
		};

	

		//-----------CONSTRUCTOR/DESTRUCTOR----------------------------------
	public:
		GameScreenMenuRoot();	//Default Constructor
		~GameScreenMenuRoot();	//Default Destructor

	public:
		//-----------FUNCTION OVERRIDES/INTERFACE IMPLEMENTATION-------------
		virtual void    loadContent() override;
		virtual void	handleEvent(const sf::Event& pevent) override;
		virtual void    bgUpdate(sf::Time& ptpf, sf::Time& ptotal, bool pcovered = false) override;
		virtual void	update(sf::Time& ptpf, sf::Time& ptotal) override;
		virtual void	render() override;
		virtual void    cleanup() override;

		//-----------PROTECTED FUNCTIONS-------------------------------------
	protected:
		void handleInput(sf::Keyboard::Key pkey, bool ppressed); //Handle Keyboard Events

		//Sub-Routines
		void loadResources();
		void setupMenuBG();
		void setupMenuElements();
		void setupCameras();
		void setupTitle();
		//Menu Wide - Event Handling
		void onMoveUp();
		void onMoveDown();
		void onCancel();
		void onSaveAll();

		MenuItemPtr createMenuItem(std::string pdefaulttext);
		void addItem(MenuItemPtr pitem);


	protected:
		//-----------CLASS MEMBERS-------------------------------------------
		sf::LJMUResourceHelper<sf::Texture,std::string>   _res_level;		//Resource Manager for Level BG
		sf::LJMUResourceHelper<sf::Texture,std::string>   _res_static;	    //Resource Manager for Static Sprites
		sf::LJMUResourceHelper<sf::Font,std::string>	  _res_font;        //Resource Manager for Fonts
		
		
		LJMU::MenuControls								   _controls;		//Use the Control Scheme Class

		std::vector<LJMU::GameObjectBasic>			     _bg_layers;		//Level Collection
		std::vector<MenuItemPtr>						 _menu_items;		//Menu Items
		int												 _selected_index;	//Selected Index
		
		std::map<MenuItemPtr,MenuActions>				 _menu_actions;		//Menu Event Handlers
		std::map<MenuItemPtr,LJMU::GameObjectBasic>      _menu_sprites;		//Menu Sprites

		LJMU::GameHUDElemBasic                           MenuTitle; // Title for menu screen
	
				
		sf::Color								_clr_curr;					//Colour For Current items
		sf::Color								_clr_other;					//Colour For Non-Selected Items
		
		std::deque<LJMU::GameCamera>			_cameras;					//Menu Cameras
		
	};
}
#endif