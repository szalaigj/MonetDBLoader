/*
 * StreamReaderForLoader.cpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Janos Szalai-Gindl
 */

#include "StreamReaderForLoader.hpp"

CommonStreamReaderForLoader::CommonStreamReaderForLoader(ISelector * selector) :
		BaseStreamReaderForLoader(selector), inputStream(NULL) {
// The default new line character is UNIX-style:
	lineDelimiterChar = "\n";
}

CommonStreamReaderForLoader::~CommonStreamReaderForLoader() {
	close();
}

void CommonStreamReaderForLoader::close() {
	inputStream->close();
	delete inputStream;
}

void CommonStreamReaderForLoader::initializeInputStream(std::string path) {
	inputStream = new std::ifstream(path.c_str());
	if (inputStream->bad()) {
		std::string errmsg("File ");
		errmsg.append(path);
		errmsg.append(" does not exist.\n");
		throw std::runtime_error(errmsg);
	}
}

std::string CommonStreamReaderForLoader::getLineDelimiter() {
	return lineDelimiterChar;
}

Strings * CommonStreamReaderForLoader::selectObjects() {
	Strings * objs = new Strings();
	std::string line;
	while (std::getline(*inputStream, line)) {
		line = selector->selectObjects(line);
		objs->push_back(line);
	}
	return objs;
}

StreamReaderForLoaderWithPrefix::StreamReaderForLoaderWithPrefix(
		ISelector * selector, std::string filename) :
		CommonStreamReaderForLoader(selector) {
	// The name of source file (without extension) is passed to Selector
	// which will concatenate this string for the beginning of the read lines.
	std::string prefix;
	size_t lastDotPos = filename.find_last_of(".");
	if (lastDotPos == std::string::npos) {
		prefix = filename;
	} else {
		prefix = filename.substr(0, lastDotPos);
	}
	selector->setPrefix(prefix);
}
