#pragma once

#include <SFML/System/Vector2.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <string>
#include <IGameObjectBase.h>
#include <SFML/Graphics/Sprite.hpp>

#include "LJMUResourceHelper.h"
#include "LJMUSettings.h"

namespace LJMU
{
	////////////////////////////
	// Class to represent some 
	// In Game Text.
	////////////////////////////
	class GameShopElemBasic : public IGameObjectBase
	{
	public:
	

		//--------CONSTRUCTORS/DESTRUCTORS---------------------------------
		explicit GameShopElemBasic() :IGameObjectBase(),txtItemName(){ }
		~GameShopElemBasic() override = default;

		//----------GETTERS/SETTERS----------------------------------------
		inline sf::Text& getItemName() { return this->txtItemName; };
		inline sf::Text& getItemCost() { return this->txtItemCost; };
		inline sf::Text& getItDes() { return this->txtItemDescription; };
		inline sf::Sprite& getItemIcon() { return this->sprItemIcon; };
		inline sf::Sprite& getItemBG() { return this->sprItemBackground; };
		inline std::string getTitleString() { return this->strItemTitle; }
		void setString(std::string pdata) { this->_exitShop = pdata; }
		inline sf::Text& getText() { return this->exitShopOption; };
		

		//----------INTERFACE IMPLEMENTATION-------------------------------

		void loadContent() override;
		virtual void update(sf::Time& ptpf, sf::Time& ptotal)override;
		virtual void render(sf::RenderWindow& pwndw) override;

		void setImageId(int ID );
		void SetItDescription(std::string itemDes);
		void SetItemName(std::string itemName);
		void SetItemCost(int itemCost);
	

		void setItemPos(sf::Vector2f pos);
		
		void setItemIconSize(sf::Vector2f Icsize);

		void setupIcons();
		void setupTextElems();

	protected:
		//----------MEMBER DATA--------------------------------------------
		sf::LJMUResourceHelper<sf::Texture, int>   _resImage;	    //Resource Manager for Static Sprites
		sf::LJMUResourceHelper<sf::Font, std::string>	  _resFont;

		int ImageId = 0;
		int intItemCost = 0;

		sf::Text    txtItemName;
		sf::Text   txtItemDescription;
		sf::Text   txtItemCost;
		sf::Text   exitShopOption;

		sf::String   sprItemTitle;

		sf::Sprite sprItemIcon;
		sf::Sprite sprItemBackground;

		std::string strItemDes = "Health will heal you!";
		std::string strItemTitle = "Health Pickup!";
		std::string strItemCost = "0";

		std::string _exitShop;

		sf::Vector2f OffsetPos{ 0.f,0.f };

		sf::Color  Clr_Selected = sf::Color::Cyan;
		sf::Color  Clr_Normal = sf::Color::White;
	public:
	

		bool IsSelected = false;

	protected:

	

		std::string itemName = "Health";
		int         itemCost = 0;
	};

	inline void GameShopElemBasic::loadContent()
	{
		IGameObjectBase::loadContent();

		//Load the Default Font
		std::string ts_dir = sf::LJMUSettings::DIR_STATICS;
		std::string tf_dir = sf::LJMUSettings::DIR_FONTS;

		using namespace LJMU;

		//Load the Fonts		
		this->_resFont.load("Elems", tf_dir + "Ninja.otf");

		//Load the backgrounds
		this->_resImage.load(-1, ts_dir + "shop_frame_norm.png");
		this->_resImage.load(-2, ts_dir + "shop_frame_sel.png");

		//Load the Static Sprites
		this->_resImage.load(0, ts_dir + "health.png");
		this->_resImage.load(1, ts_dir + "damage.png");
		this->_resImage.load(2, ts_dir + "speed.png");

		//Setup our Icons and Text Elements
		setupIcons();
		setupTextElems();
	}

	inline void GameShopElemBasic::update(sf::Time& ptpf, sf::Time& ptotal)
	{
		if (this->IsSelected)
		{
			this->txtItemName.setFillColor(this->Clr_Selected);
			this->sprItemBackground.setTexture(this->_resImage.get(-2));
		}
		else
		{
			this->txtItemName.setFillColor(this->Clr_Normal);
			this->sprItemBackground.setTexture(this->_resImage.get(-1));
		}
	}

	inline void GameShopElemBasic::render(sf::RenderWindow& pwndw)
	{
		pwndw.draw(this->sprItemBackground);
		pwndw.draw(this->txtItemName);
		pwndw.draw(this->txtItemDescription);
		pwndw.draw(this->txtItemCost);
		pwndw.draw(this->sprItemIcon);
		
	}

	inline void GameShopElemBasic::setImageId(int ID)
		{
		this->ImageId = ID;
	    }

	inline void GameShopElemBasic::SetItDescription(std::string itemDes)
	{
		strItemDes = std::move(itemDes);
	}

	inline void GameShopElemBasic::SetItemName(std::string itemName)
	{
		this->strItemTitle = std::move(itemName);
	}

	inline void GameShopElemBasic::SetItemCost(int itemCost)
	{
		this->intItemCost = itemCost;
		this->strItemCost = std::to_string(itemCost);
	}

	inline void GameShopElemBasic::setItemPos(sf::Vector2f pos)
	{
		this->OffsetPos = pos;
	}

	
	inline void GameShopElemBasic::setItemIconSize(sf::Vector2f Icsize)
	{
		this->sprItemIcon.setScale(Icsize.x / this->sprItemIcon.getLocalBounds().width,
			Icsize.y / this->sprItemIcon.getLocalBounds().height);
	}

	inline void GameShopElemBasic::setupIcons()
	{
		//Setup the Data for the 2 Sprite Elements
		this->sprItemIcon.setTexture(this->_resImage.get(this->ImageId));
		this->sprItemBackground.setTexture(this->_resImage.get(-1));

		//Position the Sprites
		//const sf::Vector2f ticonpos(20.f, 20.f);
		const sf::Vector2f tbgpos(0.f, 0.f);
		this->sprItemBackground.setPosition(this->OffsetPos + tbgpos);
		this->sprItemIcon.setPosition(sprItemBackground.getPosition().x + 35, sprItemBackground.getPosition().y + 70);
		this->sprItemIcon.setScale(0.15,0.15);

		

	}

	inline void GameShopElemBasic::setupTextElems()
	{
		//Setup the data for the Three Text Elements. 					
		this->txtItemDescription.setString(strItemDes);
		this->txtItemDescription.setCharacterSize(15);
		this->txtItemDescription.setFont(this->_resFont.get("Elems"));

		this->txtItemName.setString(strItemTitle);
		this->txtItemName.setCharacterSize(30);
		this->txtItemName.setFont(this->_resFont.get("Elems"));

		this->txtItemCost.setString(this->strItemCost);
		this->txtItemCost.setCharacterSize(40);
		this->txtItemCost.setFont(this->_resFont.get("Elems"));

		//Position the Text Elements
		const sf::Vector2f ttitlepos(150.f, -35.f);
		const sf::Vector2f tdescpos(25.f, 65.f);
		const sf::Vector2f tcostpos(40.f, 350.f);

		this->txtItemName.setPosition(ttitlepos + this->OffsetPos);
		this->txtItemDescription.setPosition(tdescpos + this->OffsetPos);
		this->txtItemCost.setPosition(tcostpos + this->OffsetPos);
	}
}
