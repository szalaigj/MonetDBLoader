/*
 * BaseBulkInsertFileCreator.cpp
 *
 *  Created on: Jun 2, 2015
 *      Author: Janos Szalai-Gindl
 */

#include <iostream>
#include <time.h>

#include "BaseBulkInsertFileCreator.hpp"

void BaseBulkInsertFileCreator::createFiles(std::string sourcePath,
		std::string filename, std::string bulkPath) {
	clock_t start = clock();
	std::string bulkDirectory = bulkPath + "/" + filename;
	std::string sourceFilename = sourcePath + "/" + filename;
	std::cout << filename << " > Preparing: " << sourceFilename << std::endl;
	for (std::vector<Mapper *>::iterator it = mappings->begin();
			it != mappings->end(); ++it) {
		Mapper * mapper = *it;
		fileUtils->open(bulkDirectory, mapper);
	}

	int q = 0;

	BaseStreamReaderForLoader * reader = initializeReader(sourcePath, filename);
	Strings * objects = reader->selectObjects();

	q = doMapOnObjects(q, objects);

	for (std::vector<Mapper *>::iterator iter = mappings->begin();
			iter != mappings->end(); ++iter) {
		Mapper * m = *iter;
		fileUtils->close(m);
	}

	clock_t end = clock();
	double elapsedSecs = double(end - start) / CLOCKS_PER_SEC;
	std::cout << filename << " > " << q << " rows written in " << elapsedSecs
			<< " sec." << std::endl;
}

BaseStreamReaderForLoader * BaseBulkInsertFileCreator::initializeReader(
		std::string sourcePath, std::string filename) {
	BaseStreamReaderForLoader * streamReaderForLoader = instantiateReader(
			filename);
	std::string path = sourcePath + "/" + filename;
	streamReaderForLoader->initializeInputStream(path);
	return streamReaderForLoader;
}

int BaseBulkInsertFileCreator::doMapOnObjects(int q, Strings * objects) {
	for (Strings::iterator iter = objects->begin(); iter != objects->end();
			++iter) {
		std::string obj = *iter;
		if (obj.compare("") != 0) {
			for (std::vector<Mapper *>::iterator subIter = mappings->begin();
					subIter != mappings->end(); ++subIter) {
				Mapper * m = *subIter;
				m->map(obj);
			}
			q++;
		}
	}
	return q;
}

BaseStreamReaderForLoader * DefaultBulkInsertFileCreator::instantiateReader(
		std::string filename) {
	DefaultSelector * selector = new DefaultSelector();
	StreamReaderForLoaderWithPrefix * retVal =
			new StreamReaderForLoaderWithPrefix(selector, filename);
	return retVal;
}
