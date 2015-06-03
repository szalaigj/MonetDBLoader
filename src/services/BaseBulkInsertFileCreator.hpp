/*
 * BaseBulkInsertFileCreator.hpp
 *
 *  Created on: Jun 2, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef BASEBULKINSERTFILECREATOR_HPP_
#define BASEBULKINSERTFILECREATOR_HPP_

#include <string>

class BaseBulkInsertFileCreator {
public:
	BaseBulkInsertFileCreator() {

	}

	void createFiles(std::string sourcePath, std::string filename,
			std::string bulkPath);
};

#endif /* BASEBULKINSERTFILECREATOR_HPP_ */
