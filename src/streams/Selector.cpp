/*
 * Selector.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Janos Szalai-Gindl
 */

#include "Selector.hpp"

std::string DefaultSelector::selectObjects(std::string status) {
	std::string retVal = status;
	if (prefix.compare("")!=0) {
		retVal = prefix + delimiter + status;
	}
	return retVal;
}

std::string DefaultSelector::getPrefix() {
	return prefix;
}

void DefaultSelector::setPrefix(std::string inputPrefix) {
	prefix = inputPrefix;
}
