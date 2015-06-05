/*
 * StartVerb.cpp
 *
 *  Created on: May 29, 2015
 *      Author: Janos Szalai-Gindl
 */

#include <sys/types.h>
#include <dirent.h>
#include <iostream>
#include <exception>
#include <stdexcept>
#include <regex.h>

#include "StartVerb.hpp"
#include "../mappers/Mapper.hpp"

Strings * StartVerbInitializer::requiredProps =
		StartVerbInitializer::createRequiredProps();

std::map<std::string, std::string> * StartVerbInitializer::optionalProps =
		StartVerbInitializer::createOptionalProps();

std::map<std::string, std::string> * StartVerbInitializer::propDescs =
		StartVerbInitializer::createPropDescs();

void StartVerb::run() {
	std::cout << "Here!" << std::endl;
	std::string source = std::string((*props)["Source"]);
	std::string dirName, pat, ext;
	getPartsOfSource(source, dirName, pat, ext);
	pat = correctPattern(pat);
	std::vector<std::string> * fileNames = new std::vector<std::string>();

	getFiles(dirName, pat, fileNames);

	if ((getMapper()->getPreferredSourceFileExt().compare(ext)) != 0) {
		std::cout << "WARNING: the extension of the given Source does not "
				<< "equal the preferred file extension of the given Mapper "
				<< "type! Are you sure you want to use it?" << std::endl;
	}

	if (fileNames->size() == 0) {
		std::string errmsg("No files matching the source pattern (");
		errmsg.append(source);
		errmsg.append(") were found.\n");
		throw std::runtime_error(errmsg);
	} else {
		std::cout << "Found " << fileNames->size()
				<< " file(s), now creating batch..." << std::endl;
	}

	for (size_t i = 0; i < fileNames->size(); i++) {
		bulkInsertFileCreator->createFiles(dirName, (*fileNames)[i],
				(*props)["BulkPath"]);
		std::cout << (*fileNames)[i] << std::endl;
	}

	/*	std::cout << (*props)["Source"] << std::endl;
	 std::cout << (*props)["BulkPath"] << std::endl;*/
}

void StartVerb::getPartsOfSource(std::string source, std::string& dirName,
		std::string& fileName, std::string& ext) {
	size_t lastSlashPos = source.find_last_of("/");
	if (lastSlashPos == std::string::npos) {
		std::string errmsg("Invalid source syntax: ");
		errmsg.append(source);
		errmsg.append("\n");
		throw std::runtime_error(errmsg);
	} else {
		dirName = source.substr(0, lastSlashPos);
		fileName = source.substr(lastSlashPos + 1);
		size_t lastDotPos = fileName.find_last_of(".");
		if (lastDotPos == std::string::npos) {
			ext = "";
		} else {
			ext = fileName.substr(lastDotPos);
		}
	}
}

std::string StartVerb::correctPattern(std::string pat) {
	std::string result(pat);
	size_t dotPos = result.find(".", 0);
	if (dotPos != std::string::npos) {
		// replace '.' with '\.'
		result.erase(dotPos, 1);
		result.insert(dotPos, "\.");
	}
	size_t starPos = result.find("*", 0);
	if (starPos != std::string::npos) {
		// replace '*' with '.*'
		result.erase(starPos, 1);
		result.insert(starPos, ".*");
	}
	return result;
}

void StartVerb::getFiles(std::string dirName, std::string pat,
		std::vector<std::string> * fileNames) {
	DIR * dir;
	struct dirent * dirp;
	if ((dir = opendir(dirName.c_str())) == NULL) {
		std::string errmsg("Directory ");
		errmsg.append(dirName);
		errmsg.append(" cannot open.\n");
		throw std::runtime_error(errmsg);
	}
	while ((dirp = readdir(dir)) != NULL) {
		std::string candidateFilename = std::string(dirp->d_name);
		regex_t reg;

		// Compile regular expression
		int err = regcomp(&reg, pat.c_str(), 0);
		if (err != 0) {
			std::string errmsg("Could not compile regex\n");
			throw std::runtime_error(errmsg);
		}

		// Execute regular expression
		int nomatch = regexec(&reg, candidateFilename.c_str(), 0, NULL, 0);
		if (nomatch == 0) {
			fileNames->push_back(candidateFilename);
		}
	}
	closedir(dir);
}
