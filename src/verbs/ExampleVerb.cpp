/*
 * ExampleVerb.cpp
 *
 *  Created on: Jun 1, 2015
 *      Author: Janos Szalai-Gindl
 */

#include <iostream>

#include "ExampleVerb.hpp"

Strings * ExampleVerbInitializer::requiredProps =
		ExampleVerbInitializer::createRequiredProps();

std::map<std::string, std::string> * ExampleVerbInitializer::optionalProps =
		ExampleVerbInitializer::createOptionalProps();

std::map<std::string, std::string> * ExampleVerbInitializer::propDescs =
		ExampleVerbInitializer::createPropDescs();

void ExampleVerb::run() {
	std::cout << "Here!" << std::endl;
	std::cout << (*props)["optional1"] << std::endl;
	std::cout << (*props)["optional2"] << std::endl;
}
