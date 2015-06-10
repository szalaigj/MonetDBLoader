/*
 * Verb.hpp
 *
 *  Created on: May 28, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef VERB_HPP_
#define VERB_HPP_

#include <vector>
#include <map>
#include <string>

#include "PropertiesAdapter.hpp"
#include "../mappers/Mapper.hpp"

typedef std::vector<std::string> Strings;

class IVerb {
public:
	// virtual destructor is needed if subclass of this base class will be destroyed
	// otherwise if the subclass has a base class reference or pointer and it is destroyed
	// only the base class destructor will be invoked.
	virtual ~IVerb() {
	}

	// run verb
	virtual void run() = 0;

	// print usage of this verb
	virtual void printUsage() = 0;

	// get current mapper
	virtual Mapper * getMapper() = 0;
};

class BaseVerb: public IVerb {
public:
	BaseVerb(BasePropertiesAdapter propAdapter, std::string settingsfile,
			Mapper * currentMapper, const std::string name,
			const std::string description, Strings * requiredProps,
			std::map<std::string, std::string> * optionalProps,
			std::map<std::string, std::string> * propDescs) :
			props(), settingsfile(settingsfile), currentMapper(currentMapper), name(
					name), description(description), requiredProps(
					requiredProps), optionalProps(optionalProps), propDescs(
					propDescs) {
		props = propAdapter.readSettings(settingsfile);
		check();
		setOptionalProps();
	}

	~BaseVerb() {
		delete requiredProps;
		delete optionalProps;
		delete propDescs;
		delete props;
	}

	virtual void run() = 0;

	void printUsage();

	Mapper * getMapper();
protected:

	std::map<std::string, std::string> * props;

private:
	// check existence of all required properties
	void check();

	// set optional properties with default values
	void setOptionalProps();

	std::string settingsfile;
	Mapper * currentMapper;
	const std::string name;
	const std::string description;
	Strings * requiredProps;
	std::map<std::string, std::string> * optionalProps;
	std::map<std::string, std::string> * propDescs;
};

#endif /* VERB_HPP_ */
