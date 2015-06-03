/*
 * PropertiesAdapter.hpp
 *
 *  This is an interface for loading settings from a properties file.
 *
 *  Created on: May 28, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef PROPERTIESADAPTER_HPP_
#define PROPERTIESADAPTER_HPP_

// standard includes
#include <string>
#include <map>

class IPropertiesAdapter {
public:
	// virtual destructor is needed if subclass of this base class will be destroyed
	// otherwise if the subclass has a base class reference or pointer and it is destroyed
	// only the base class destructor will be invoked.
	virtual ~IPropertiesAdapter() {
	}

	// read settings from a file
	virtual std::map<std::string, std::string> * readSettings(
			std::string settingsfilename) = 0;

};

class BasePropertiesAdapter: public IPropertiesAdapter {
public:
	~BasePropertiesAdapter() {
	}

	std::map<std::string, std::string> * readSettings(
			std::string settingsfilename);
};

#endif /* PROPERTIESADAPTER_HPP_ */
