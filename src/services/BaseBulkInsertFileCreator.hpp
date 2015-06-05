/*
 * BaseBulkInsertFileCreator.hpp
 *
 *  Created on: Jun 2, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef BASEBULKINSERTFILECREATOR_HPP_
#define BASEBULKINSERTFILECREATOR_HPP_

#include <string>
#include <vector>

#include "../load/FileUtils.hpp"
#include "../streams/StreamReaderForLoader.hpp"

typedef std::vector<std::string> Strings;

class BaseBulkInsertFileCreator {
public:
	BaseBulkInsertFileCreator(FileUtils * fileUtils,
			std::vector<Mapper *> * mappings) :
			fileUtils(fileUtils), mappings(mappings) {
	}

	// virtual destructor is needed if subclass of this base class will be destroyed
	// otherwise if the subclass has a base class reference or pointer and it is destroyed
	// only the base class destructor will be invoked.
	virtual ~BaseBulkInsertFileCreator() {
	}

	void createFiles(std::string sourcePath, std::string filename,
			std::string bulkPath);

protected:
	BaseStreamReaderForLoader * initializeReader(std::string sourcePath,
			std::string filename);

	int doMapOnObjects(int q, Strings * objects);

	virtual BaseStreamReaderForLoader * instantiateReader(std::string filename) = 0;

private:
	FileUtils * fileUtils;
	std::vector<Mapper *> * mappings;

};

class DefaultBulkInsertFileCreator : public BaseBulkInsertFileCreator {
public:
	DefaultBulkInsertFileCreator(FileUtils * fileUtils,
			std::vector<Mapper *> * mappings) :
			BaseBulkInsertFileCreator(fileUtils, mappings) {
	}

protected:
	BaseStreamReaderForLoader * instantiateReader(std::string filename);
};

#endif /* BASEBULKINSERTFILECREATOR_HPP_ */
