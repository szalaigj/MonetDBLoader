/*
 * FileUtils.hpp
 *
 *  Created on: Jun 4, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef FILEUTILS_HPP_
#define FILEUTILS_HPP_

#include <string>

#include "../mappers/Mapper.hpp"

class FileUtils {
public:
	void close(Mapper * mapper);

	void deleteFile(std::string bulkDirectory, Mapper * mapper);

	void open(std::string bulkDirectory, Mapper * mapper);
};

#endif /* FILEUTILS_HPP_ */
