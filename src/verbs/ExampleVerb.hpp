/*
 * ExampleVerb.hpp
 *
 *  Created on: Jun 1, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef EXAMPLEVERB_HPP_
#define EXAMPLEVERB_HPP_

#include <iostream>

#include "Verb.hpp"

typedef std::vector<std::string> Strings;

struct ExampleVerbInitializer {
	static Strings * createRequiredProps() {
		Strings * result = new Strings();
		result->push_back("prop1");
		result->push_back("prop2");
		return result;
	}

	static std::map<std::string, std::string> * createOptionalProps() {
		std::map<std::string, std::string> * result = new std::map<std::string,
				std::string>();
		(*result)["optional1"] = "default value";
		(*result)["optional2"] = "default value2";
		return result;
	}

	static std::map<std::string, std::string> * createPropDescs() {
		std::map<std::string, std::string> * result = new std::map<std::string,
				std::string>();
		(*result)["prop1"] = "Description1";
		(*result)["prop2"] = "Description2";
		(*result)["optional1"] = "Optional parameter";
		(*result)["optional2"] = "Another optional parameter";
		return result;
	}

	static Strings * requiredProps;
	static std::map<std::string, std::string> * optionalProps;
	static std::map<std::string, std::string> * propDescs;
};

class ExampleVerb: public BaseVerb {
public:
	ExampleVerb(BasePropertiesAdapter propAdapter, std::string settingsfilename,
			Mapper * currentMapper, const std::string name = "Example",
			const std::string description = "Example verb",
			Strings * requiredProps = ExampleVerbInitializer::requiredProps,
			std::map<std::string, std::string> * optionalProps =
					ExampleVerbInitializer::optionalProps,
			std::map<std::string, std::string> * propDescs =
					ExampleVerbInitializer::propDescs) :
			BaseVerb(propAdapter, settingsfilename, currentMapper, name,
					description, requiredProps, optionalProps, propDescs) {
	}

	~ExampleVerb() {
	}

	void run();
};

#endif /* EXAMPLEVERB_HPP_ */
