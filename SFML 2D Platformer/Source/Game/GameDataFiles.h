#pragma once
#include <LJMUPCH.h>
#include <fstream>
#include <sstream>
#include <iterator>
#include <iostream>

namespace LJMU
{
	//-----STRING TOKENISER-------------------------------------------------------

	////////////////////////////////////////
	// Helper Function to Split a String 
	// using Get Line. 
	////////////////////////////////////////
	inline void splitString(std::string pstring, std::vector<std::string>& plist, char pdelim = ' ')
	{
		std::istringstream is(pstring);
		std::string part;
		while (std::getline(is, part, pdelim))
		{
			plist.push_back(part);
		}
	}

	//-----FILE MANIPULATION------------------------------------------------------

	///////////////////////////////////////
	// Read a File's Contents
	///////////////////////////////////////
	inline std::string readFileContents(std::string pfilename)
	{
		try
		{
			std::ostringstream tbuf;
			std::ifstream tinput(pfilename.c_str());
			tbuf << tinput.rdbuf();
			return tbuf.str();
		}
		catch (std::exception e)
		{
			std::cout << "FILE PARSING ERROR: " << pfilename << ": " << e.what() << std::endl;
			return "";
		}
	}

	//-----DEBUGGER HELPERS-------------------------------------------------------

	///////////////////////////////////////
	// Debug Helper to Output Tokens from a 
	// Vector of Strings. 
	///////////////////////////////////////
	inline void outputTokens(std::vector<std::string>& ptokens)
	{
		std::copy(ptokens.begin(), ptokens.end(), std::ostream_iterator<std::string>(std::cout, ", "));
		std::cout << std::endl << std::endl;
	}

	//-----DATA HANDLING CLASSES--------------------------------------------------

	class TileSetInfoBasic
	{
	public:
		//----TileSet Information---------------------------------
		std::map<std::string, sf::IntRect> TileRects;
		std::vector<std::string>		   TileIndex;

	public:
		//----File Parsing Function-------------------------------
		bool loadFromFile(std::string pfilename)
		{
			try
			{
				char tdelim = ' ';
				std::string tscratch;
				std::vector<std::string> tbodylines;
				std::vector<std::vector<std::string>> tbodytokens;

				//Create an Input File Stream and open the file
				std::ifstream tinput(pfilename);
				if (!tinput.is_open())
					return false;

				//NOTE: There is no header data, but we might want to add some. 
				while (!tinput.eof())
				{
					std::getline(tinput, tscratch);
					std::vector<std::string> tst;
					splitString(tscratch, tst, tdelim);
					if (tst.size() < 6)
						continue;
					sf::IntRect trect(std::stoi(tst[2]), std::stoi(tst[3]), std::stoi(tst[4]), std::stoi(tst[5]));
					this->TileRects.insert(std::make_pair(tst[0], trect));
					this->TileIndex.push_back(tst[0]);
				}

				return true;
			}
			catch (std::runtime_error e)
			{
				std::cout << "FILE PARSING ERROR: " << pfilename << ": " << e.what() << std::endl;
				return false;
			}
		}
	};

	class TileMapData
	{
	public:
		//----Tile Map Data----------------------------------------
		int Rows = 0;
		int Columns = 0;
		int TileWidth = 0;
		int TileHeight = 0;
		std::string MapName = "";
		std::vector<int> TileNums;

	public:
		//----File Parsing Function-------------------------------
		bool loadFromFile(std::string pfilename)
		{
			try
			{
				//--------PARSER DATA---------------------------------
				std::string theaderline;
				char tdelim = ' ';
				std::vector<std::string> theadertokens;

				std::string tscratch;
				std::vector<std::string> tbodylines;

				//Create an Input File Stream and open the file
				std::ifstream tinput(pfilename);
				if (!tinput.is_open())
					return false;

				//--------PARSER LOGIC--------------------------------
				//Ignore the comment line
				std::getline(tinput, tscratch);

				//Get the Header Line
				std::getline(tinput, tscratch);

				splitString(tscratch, theadertokens);
				this->MapName = theadertokens[0];
				this->Rows = stoi(theadertokens[1]);
				this->Columns = stoi(theadertokens[2]);
				this->TileWidth = stoi(theadertokens[3]);
				this->TileHeight = stoi(theadertokens[4]);

				//Process the Body (Our Tile Indices) 
				if (!tinput.eof())
				{
					std::copy(std::istream_iterator<int>(tinput),
						std::istream_iterator<int>(),
						std::back_inserter(this->TileNums));
				}
				return true;
			}
			catch (std::runtime_error e)
			{
				std::cout << "FILE PARSING ERROR: " << pfilename << ": " << e.what() << std::endl;
				return false;
			}
		}
	};

	class IconSet
	{
	public:
		//----TileSet Information---------------------------------
		std::map<std::string, sf::IntRect> IconCell;
	public:
		//----File Parsing Function-------------------------------
		bool loadFromFile(std::string pfilename)
		{
			try
			{
				char tdelim = ' ';
				std::string tscratch;
				std::vector<std::string> tbodylines;
				std::vector<std::vector<std::string>> tbodytokens;

				//Create an Input File Stream and open the file
				std::ifstream tinput(pfilename);
				if (!tinput.is_open())
					return false;

				//NOTE: There is no header data, but we might want to add some. 
				while (!tinput.eof())
				{
					std::getline(tinput, tscratch);
					std::vector<std::string> tst;
					splitString(tscratch, tst, tdelim);
					if (tst.size() < 6)
						continue;
					sf::IntRect trect(std::stoi(tst[2]), std::stoi(tst[3]), std::stoi(tst[4]), std::stoi(tst[5]));
					this->IconCell.insert(std::make_pair(tst[0], trect));
				}

				return true;
			}
			catch (std::runtime_error e)
			{
				std::cout << "FILE PARSING ERROR: " << pfilename << ": " << e.what() << std::endl;
				return false;
			}
		}
	};

	class AssetColl
	{
	public:
		//----TileSet Information---------------------------------
		std::map<std::string, std::string> Assets;
	public:
		//----File Parsing Function-------------------------------
		bool loadFromFile(std::string pfilename)
		{
			try
			{
				char tdelim = ' ';
				std::string tscratch;

				//Create an Input File Stream and open the file
				std::ifstream tinput(pfilename);
				if (!tinput.is_open())
					return false;

				//NOTE: There is no header data, but we might want to add some. 
				while (!tinput.eof())
				{
					std::getline(tinput, tscratch);
					std::vector<std::string> tst;
					splitString(tscratch, tst, tdelim);

					if (tst.size() < 2)
						continue;
					this->Assets.insert(std::make_pair(tst[0], tst[1]));
				}

				return true;
			}
			catch (std::runtime_error e)
			{
				std::cout << "FILE PARSING ERROR: " << pfilename << ": " << e.what() << std::endl;
				return false;
			}
		}
	};

	class SideEnvMgr
	{
	public:
		struct EnvInfo
		{
			std::string TexRef;
			bool WithCamera;
			sf::Vector2f Position;
			int Layer;
		};
	public:
		//----Environment Information-----------------------------
		std::vector<EnvInfo> Environments;
	public:
		//----File Parsing Function-------------------------------
		bool loadFromFile(std::string pfilename)
		{
			try
			{
				char tdelim = ' ';
				std::string tscratch;

				//Create an Input File Stream and open the file
				std::ifstream tinput(pfilename);
				if (!tinput.is_open())
					return false;

				//NOTE: There is no header data, but we might want to add some. 
				while (!tinput.eof())
				{
					std::getline(tinput, tscratch);
					std::vector<std::string> tst;
					splitString(tscratch, tst, tdelim);

					if (tst.size() < 5)
						continue;
					EnvInfo tinfo;
					tinfo.TexRef = tst[0];
					tinfo.Position = sf::Vector2f(std::stof(tst[1]), std::stof(tst[2]));
					tinfo.Layer = std::stoi(tst[3]);
					tinfo.WithCamera = std::stoi(tst[4]) > 0 ? true : false;
					this->Environments.push_back(tinfo);
				}

				return true;
			}
			catch (std::runtime_error e)
			{
				std::cout << "FILE PARSING ERROR: " << pfilename << ": " << e.what() << std::endl;
				return false;
			}
		}
	};

	class SidePickupMgr
	{
	public:
		struct PickupInfo
		{
			std::string TexRef;
			sf::Vector2f Pos;
		};
	public:
		//----Environment Information-----------------------------
		std::vector<PickupInfo> Pickups;
	public:
		//----File Parsing Function-------------------------------
		bool loadFromFile(std::string pfilename)
		{
			try
			{
				char tdelim = ' ';
				std::string tscratch;

				//Create an Input File Stream and open the file
				std::ifstream tinput(pfilename);
				if (!tinput.is_open())
					return false;

				//NOTE: There is no header data, but we might want to add some. 
				while (!tinput.eof())
				{
					std::getline(tinput, tscratch);
					std::vector<std::string> tst;
					splitString(tscratch, tst, tdelim);

					if (tst.size() < 3)
						continue;
					PickupInfo tpinfo;
					tpinfo.TexRef = tst[0];
					tpinfo.Pos = sf::Vector2f(std::stof(tst[1]), std::stof(tst[2]));
					this->Pickups.push_back(tpinfo);
				}

				return true;
			}
			catch (std::runtime_error e)
			{
				std::cout << "FILE PARSING ERROR: " << pfilename << ": " << e.what() << std::endl;
				return false;
			}
		}
	};

	class SideLevelMgr
	{
	public:
		struct LevelInfo
		{
			std::string  TexRef;
			sf::Vector2f Pos;
			bool isMovable;
			float Amplitude;
			bool isTrap;
			bool isGoal;
		};
	public:
		//----Environment Information-----------------------------
		std::vector<LevelInfo> Elements;
	public:
		//----File Parsing Function-------------------------------
		bool loadFromFile(std::string pfilename)
		{
			try
			{
				std::string tscratch;
				this->Elements.clear();

				//Create an Input File Stream and open the file
				std::ifstream tinput(pfilename);
				if (!tinput.is_open())
					return false;

				while (std::getline(tinput, tscratch))
				{
					if (tscratch.empty() || tscratch[0] == '-')
						continue;

					std::istringstream tline(tscratch);
					LevelInfo tlinfo;
					int tmovable = 0;
					int ttrap = 0;
					int tgoal = 0;
					if (!(tline >> tlinfo.TexRef >> tlinfo.Pos.x >> tlinfo.Pos.y
						>> tmovable >> tlinfo.Amplitude >> ttrap >> tgoal))
					{
						throw std::runtime_error("invalid level element: " + tscratch);
					}
					tlinfo.isMovable = tmovable > 0;
					tlinfo.isTrap = ttrap > 0;
					tlinfo.isGoal = tgoal > 0;
					this->Elements.push_back(tlinfo);
				}

				return !this->Elements.empty();
			}
			catch (const std::exception& e)
			{
				std::cout << "FILE PARSING ERROR: " << pfilename << ": " << e.what() << std::endl;
				return false;
			}
		}
	};

}
