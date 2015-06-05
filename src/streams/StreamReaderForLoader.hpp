/*
 * StreamReaderForLoader.hpp
 *
 *  Created on: Jun 5, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef STREAMREADERFORLOADER_HPP_
#define STREAMREADERFORLOADER_HPP_

#include <vector>
#include <string>
#include <stdexcept>
#include <fstream>

#include "Selector.hpp"

typedef std::vector<std::string> Strings;

class BaseStreamReaderForLoader {
public:
	BaseStreamReaderForLoader(ISelector * selector) :
			selector(selector) {
	}

	// virtual destructor is needed if subclass of this base class will be destroyed
	// otherwise if the subclass has a base class reference or pointer and it is destroyed
	// only the base class destructor will be invoked.
	virtual ~BaseStreamReaderForLoader() {
	}

	virtual void close() = 0;
	virtual void initializeInputStream(std::string path) = 0;
	virtual std::string getLineDelimiter() = 0;
	virtual Strings * selectObjects() = 0;

protected:
	ISelector * selector;
};

class CommonStreamReaderForLoader: public BaseStreamReaderForLoader {
public:
	CommonStreamReaderForLoader(ISelector * selector);

	~CommonStreamReaderForLoader();

	void close();
	void initializeInputStream(std::string path);
	std::string getLineDelimiter();
	Strings * selectObjects();

private:
	std::string lineDelimiterChar;
	std::ifstream * inputStream;
};

class StreamReaderForLoaderWithPrefix: public CommonStreamReaderForLoader {
public:
	StreamReaderForLoaderWithPrefix(ISelector * selector, std::string filename);
};

#endif /* STREAMREADERFORLOADER_HPP_ */
