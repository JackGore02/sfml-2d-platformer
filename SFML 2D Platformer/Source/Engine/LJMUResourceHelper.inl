#pragma once 

//-----------------PUBLIC METHODS----------------------------------------------------------------------------------

////////////////////////////////////////////////
// Load the Resource from the File Location Specified
// and store it in the Dictonary at the given key
////////////////////////////////////////////////
template <typename Res, typename Id>
void sf::LJMUResourceHelper<Res, Id>::load(Id pid, const std::string& pfilename)
{
	// Create and load resource - create a default instance of the object.  
	std::unique_ptr<Res> tresource = std::make_unique<Res>();

	//Throw a Run-time error if the Resource cannot be loaded. 
	if (!tresource->loadFromFile(pfilename))
		throw std::runtime_error("ResourceHolder::load - Failed to load " + pfilename);

	// If loading successful, insert resource to map
	this->insertResource(pid, std::move(tresource));
}


////////////////////////////////////////////////
//Load the Resource from the File Location Specified
// and store it in the Dictonary at the given key. 
// Customise the Loading with the Custom Parameter. 
////////////////////////////////////////////////
template <typename Res, typename Id>
template <typename Param>
void sf::LJMUResourceHelper<Res, Id>::load(Id pid, const std::string& pfilename, const Param& psecparam)
{
	// Create and load resource
	std::unique_ptr<Res> tresource = std::make_unique<Res>();

	if (!tresource->loadFromFile(pfilename, psecparam))
	{
		throw std::runtime_error("ResourceHolder::load - Failed to load " + pfilename);
	}
	// If loading successful, insert resource to map
	this->insertResource(pid, std::move(tresource));
}


////////////////////////////////////////////////
// Retrieve the Resource from the Given Key Location.
// The Resource is Mutable. 
////////////////////////////////////////////////
template <typename Res, typename Id>
Res& sf::LJMUResourceHelper<Res, Id>::get(Id pid)
{
	//Get the Resource for the given Key as a Mutable Reference
	auto tfound = this->_res_map.find(pid);
	//TODO:  You should make this functionality more robust - what can go wrong?
	return *tfound->second;
}


////////////////////////////////////////////////
// Retrieve the Resource from the Given Key Location.
// The Resource is Immutable.
////////////////////////////////////////////////
template <typename Res, typename Id>
const Res& sf::LJMUResourceHelper<Res, Id>::get(Id pid) const
{
	//Get the Resource for the given key as a Constant (Immutable) Reference.
	auto tfound = this->_res_map.find(pid);
	//TODO:  You should make this functionality more robust - what can go wrong?
	return *tfound->second;
}


////////////////////////////////////////////////
// Clear all elements from this Resource Dictionary.
// Return True if there was something to clear,
// False otherwise. 
////////////////////////////////////////////////
template <typename Res, typename Id>
bool LJMUResourceHelper< Res, Id>::clear()
{
	if (this->_res_map.size() > 0)
	{
		//Remove all Elements in the Map - since they are Unique Pointers, we can destroy them implicitly
		this->_res_map.clear();
		//Return that the operation cleared memory
		return true;
	}
	//If we are here, we had nothing to clear. 
	return false;
}

//----------------------INTERNAL HELPER FUNCTIONS-------------------------------------------------------------


////////////////////////////////////////////////
// Insert the Resource into the Given Key Location.
// Uses Move Semantics for Unique Pointer Efficiency
// and Ownership. 
////////////////////////////////////////////////
template <typename Res, typename Id>
void LJMUResourceHelper<Res, Id>::insertResource(Id pid, std::unique_ptr<Res> presource) 
{
	// Insert and check success
	auto tinserted = this->_res_map.insert(std::make_pair(pid, std::move(presource)));
}

