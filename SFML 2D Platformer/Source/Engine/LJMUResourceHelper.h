#ifndef __LJMU_RES_HELPER_H_
#define __LJMU_RES_HELPER_H_

//Required STL Includes
#include <map>
#include <string>
#include <memory>
#include <stdexcept>
#include <sstream>

namespace sf
{
	/////////////////////////////////////////////
	// Templated class to represent
	// Loading and Retrieval of data
	// for our game.  Works with 
	// a mixture of key and value pairs.
	// 
	// NOTE:  ONE RESTRICTION ON THE RESOURCE
	// TYPE - MUST IMPLEMENT TWO FUNCTIONS
	// WITH THE SIGNATURES: 
	// 
	// bool loadFromFile(string)
	// bool loadFromFile(string,Parameter)
	// WHERE Parameter is a Templated Value.
	// 
	// AUTHOR:  DR CHRIS CARTER
	// DATE:    23/05/2017
	//////////////////////////////////////////////
	template<typename Res, typename Id>
	class LJMUResourceHelper
	{
	//-------PUBLIC MEMBER FUNCTIONS------------------------------------------
	public:
		template <typename Param>
		void load(Id pid, const std::string& pfilename, const Param& psecparam); //Load the Given Resource From File into the Following Key, with a Custom Parameter for Loading.
		void load(Id pid, const std::string& pfilename); //Load the Given Resource From File into the Following Key
		Res& get(Id pid); //Get the Resource Associated with the Given Key
		const Res& get(Id pid) const; //Get a Constant Reference to the Resource with the Given Key.
		bool clear(); //Remove All Existing Keys from the Resource Dictionary. 

	private:
	//-------PRIVATE HELPER FUNCTIONS------------------------------------------
		void insertResource(Id pid, std::unique_ptr<Res> presource); //Handle the Data Structure Insert. 

    //-------CLASS MEMBER FUNCTIONS--------------------------------------------
	private:
		std::map<Id, std::unique_ptr<Res>>	_res_map; //STL Map to hold the Pointers to the Resources.
	};

//With Templated Functions, The Compiler Needs awareness of the Function Source as well (Definition)
#include "LJMUResourceHelper.inl"
}

#endif