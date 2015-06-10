/*
 * PropertiesAdapter.cpp
 *
 *  This is an implementation for loading settings from a properties file.
 *
 *  Created on: May 28, 2015
 *      Author: Janos Szalai-Gindl
 */

#include "PropertiesAdapter.hpp"

#include <string>
#include <stdexcept>
#include <fstream>

std::map<std::string, std::string> * BasePropertiesAdapter::readSettings(
		std::string settingsfile) {
	std::map<std::string, std::string> * props = new std::map<std::string,
			std::string>();
	std::string baseDelimiter = "=";
	std::ifstream settingsFileStream(settingsfile.c_str());
	std::string line;
	if (settingsFileStream.good()) {
		while (std::getline(settingsFileStream, line)) {
			int basePos = line.find(baseDelimiter);
			std::string propKey = line.substr(0, basePos);
			std::string propValue = line.substr(basePos + 1);
			(*props)[propKey] = propValue;
		}
		settingsFileStream.close();
	} else {
		std::string errmsg("File ");
		errmsg.append(settingsfile);
		errmsg.append(" does not exist.\n");
		throw std::runtime_error(errmsg);
	}
	return props;
}
