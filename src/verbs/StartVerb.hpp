/*
 * StartVerb.hpp
 *
 *  Created on: May 29, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef STARTVERB_HPP_
#define STARTVERB_HPP_

#include <iostream>

#include "Verb.hpp"
#include "../services/BaseBulkInsertFileCreator.hpp"

typedef std::vector<std::string> Strings;

struct StartVerbInitializer {
	static Strings * createRequiredProps() {
		Strings * result = new Strings();
		result->push_back("Mode");
		result->push_back("Source");
		result->push_back("BulkPath");
		return result;
	}

	static std::map<std::string, std::string> * createOptionalProps() {
		std::map<std::string, std::string> * result = new std::map<std::string,
				std::string>();
		(*result)["Binary"] = "false";
		return result;
	}

	static std::map<std::string, std::string> * createPropDescs() {
		std::map<std::string, std::string> * result = new std::map<std::string,
				std::string>();
		(*result)["Mode"] =
				"Mapper/Merger class names which are used for load/target tables.";
		(*result)["Source"] = "Source file pattern.";
		(*result)["BulkPath"] = "Bulk load files path";
		(*result)["Binary"] = "User binary files for bulk insert.";
		return result;
	}

	static Strings * requiredProps;
	static std::map<std::string, std::string> * optionalProps;
	static std::map<std::string, std::string> * propDescs;
};

class StartVerb: public BaseVerb {
public:
	StartVerb(BasePropertiesAdapter propAdapter, std::string settingsfilename,
			Mapper * currentMapper,
			BaseBulkInsertFileCreator * bulkInsertFileCreator,
			const std::string name = "Start", const std::string description =
					"Starts processing of a batch", Strings * requiredProps =
					StartVerbInitializer::requiredProps,
			std::map<std::string, std::string> * optionalProps =
					StartVerbInitializer::optionalProps,
			std::map<std::string, std::string> * propDescs =
					StartVerbInitializer::propDescs) :
			BaseVerb(propAdapter, settingsfilename, currentMapper, name,
					description, requiredProps, optionalProps, propDescs), bulkInsertFileCreator(
					bulkInsertFileCreator) {
	}

	~StartVerb() {
	}

	void run();
private:
	void getPartsOfSource(std::string source, std::string& dirName,
			std::string& fileName, std::string& ext);
	std::string correctPattern(std::string pat);
	void getFiles(std::string dirName, std::string pat,
			std::vector<std::string> * fileNames);

	BaseBulkInsertFileCreator * bulkInsertFileCreator;
};

#endif /* STARTVERB_HPP_ */
