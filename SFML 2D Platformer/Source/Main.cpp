#include "LJMUGameBase.h"
#include "GameScreenMain.h"
#include "GameScreenMenuRoot.h"
#include "GameScreenShop.h"
#include "GameScreenSplash.h"
#include "GameScreenLevel.h"
#include "GameScreenHUB.h"

/////////////////////////////////////////
// Entry Point to our Application
// In this case it just needs to start
// our SFML Application.
//
// AUTHOR:  DR CHRIS CARTER
/////////////////////////////////////////
#ifdef _DEBUG
int main()
{
#else
#include <Windows.h>
int WINAPI WinMain(HINSTANCE hThisInstance, HINSTANCE hPrevInstance, LPSTR lpszArgument, int nCmdShow)
{
#endif 
	try
	{
		//Construct our Game Instance as a Shared Pointer
		std::shared_ptr<sf::LJMUGameBase> tgame = std::make_shared<sf::LJMUGameBase>();	
		tgame->setupEngine();

		//Create our Initial Screen for the game.
		//std::shared_ptr<sf::ILJMUScreenBase> tscreen(new LJMU::LJMUGameScreenMain());
		//tgame->addScreen(tscreen, 0);

		


		std::shared_ptr<sf::ILJMUScreenBase> tscreen1(new LJMU::GameScreenSplash); // START APP WITH a Splash SCREEN as ScreenBase ID "0" - must be at end of stack 
		tgame->addScreen(tscreen1, static_cast<int>(sf::GameScreens::ScreenMenu));

		

		//Call Run on Our Game - when the game exits it will be cleaned up
		tgame->runGameLoop();
	}
	catch (std::runtime_error e)
	{
		std::cout << "ERROR: " << e.what() << std::endl;
		system("PAUSE");
	}
}

