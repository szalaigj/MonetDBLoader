/*
 * SqlUtils.hpp
 *
 *  Created on: Jun 10, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef SQLUTILS_HPP_
#define SQLUTILS_HPP_

#include <string>

#include "../mappers/Mapper.hpp"

class SqlUtils {
public:
	SqlUtils(std::string resourcePath) :
			resourcePath(resourcePath) {
	}

	const static std::string cmdFirstPart;
	const static std::string timePart;
	const static std::string logFilename;
	const static std::string loadFile;
	const static std::string tableName;
	const static std::string datPlaceholder;

	void executeRefLoadCommand(std::string logPath, std::string bulkPath,
			std::string filename, Mapper * mapper);

private:
	std::string determineSql(std::string sqlFilename);
	std::string replacePlaceholder(std::string inputSql,
			std::string placeholderName, std::string placeholderValue);
	void executeCommand(std::string logPath, std::string statement,
			std::string filename, std::string table);

	std::string resourcePath;
};

#endif /* SQLUTILS_HPP_ */
