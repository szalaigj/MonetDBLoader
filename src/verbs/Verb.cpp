/*
 * Verb.cpp
 *
 *  Created on: May 29, 2015
 *      Author: Janos Szalai-Gindl
 */

#include <iostream>
#include <exception>
#include <stdexcept>

#include "Verb.hpp"

void BaseVerb::check() {
	for (size_t idx = 0; idx < requiredProps->size(); ++idx) {
		if (props->find((*requiredProps)[idx]) == props->end()) {
			std::string errmsg("Parameter required: ");
			errmsg.append((*requiredProps)[idx]);
			errmsg.append(". Its description: ");
			errmsg.append((*propDescs)[(*requiredProps)[idx]]);
			throw std::runtime_error(errmsg);
		}
	}
}

void BaseVerb::setOptionalProps() {
	for (std::map<std::string, std::string>::iterator iter =
			optionalProps->begin(); iter != optionalProps->end(); ++iter) {
		std::string optProp = iter->first;
		if (props->find(optProp) == props->end()) {
			std::string optPropValue = iter->second;
			(*props)[optProp] = optPropValue;
		}
	}
}

void BaseVerb::printUsage() {
	std::cout << "Verb " << BaseVerb::name << ": " << BaseVerb::description
			<< std::endl;
	std::cout << std::endl;
	std::cout << "        " << "Parameters and options:" << std::endl;
	std::cout << "        " << "(Key in config file - Description)"
			<< std::endl;
	std::cout << std::endl;
	for (std::map<std::string, std::string>::iterator iter = propDescs->begin();
			iter != propDescs->end(); ++iter) {
		std::cout << "        " << iter->first << " - " << iter->second
				<< std::endl;
	}
}

Mapper * BaseVerb::getMapper() {
	return currentMapper;
}
