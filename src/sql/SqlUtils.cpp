/*
 * SqlUtils.cpp
 *
 *  Created on: Jun 10, 2015
 *      Author: Janos Szalai-Gindl
 */

#include "SqlUtils.hpp"
#include "../mappers/Ref.hpp"

#include <iostream>
#include <stdexcept>
#include <fstream>
#include <cstdlib>
#include <time.h>


// IMPORTANT NOTE: for the next command supposes you have ~/.monetdb file
// with admin user authentication properties, e.g.:
// user=monetdb
// password=monetdb
const std::string SqlUtils::cmdFirstPart = "mclient -d geneticdb";

// The following part of the executed command is important because
// we can measure elapsed time in this way
// (the original C timer does not work because this is an external command)
const std::string SqlUtils::timePart = "\\time -f %e ";

const std::string SqlUtils::logFilename = "out.log";

const std::string SqlUtils::loadFile = "load.sql";

const std::string SqlUtils::tableName = "tableName";

const std::string SqlUtils::datPlaceholder = "_Dat";

void SqlUtils::executeRefLoadCommand(std::string logPath, std::string bulkPath,
		std::string filename, Mapper * mapper) {
	std::string sql = determineSql(loadFile);
	std::string bulkDirectory = bulkPath + "/" + filename;

	sql = replacePlaceholder(sql, tableName, mapper->getTableName());
	sql = replacePlaceholder(sql, Ref::refIDColumn + datPlaceholder,
			"'" + mapper->getFilename(bulkDirectory, Ref::refIDColumn) + "'");
	sql = replacePlaceholder(sql, Ref::posColumn + datPlaceholder,
			"'" + mapper->getFilename(bulkDirectory, Ref::posColumn) + "'");
	sql = replacePlaceholder(sql, Ref::refNucColumn + datPlaceholder,
			"'" + mapper->getFilename(bulkDirectory, Ref::refNucColumn) + "'");
	executeCommand(logPath, sql, filename, mapper->getTableName());
}

std::string SqlUtils::determineSql(std::string sqlFilename) {
	std::string sql;
	std::string sqlFile(resourcePath + "/" + sqlFilename);
	std::ifstream sqlStream(sqlFile.c_str());
	if (sqlStream.good()) {
		std::getline(sqlStream, sql);
		sqlStream.close();
	} else {
		std::string errmsg("File ");
		errmsg.append(sqlFile);
		errmsg.append(" does not exist.\n");
		throw std::runtime_error(errmsg);
	}
	return sql;
}

std::string SqlUtils::replacePlaceholder(std::string inputSql,
		std::string placeholderName, std::string placeholderValue) {
	std::string outSql(inputSql);
	std::string placeholder("${" + placeholderName + "}");
	size_t startPos = outSql.find(placeholder);
	if (startPos == std::string::npos) {
		std::string errmsg("The placeholder ");
		errmsg.append(placeholderName);
		errmsg.append(" does not exist.\n");
		throw std::runtime_error(errmsg);
	}
	outSql.erase(startPos, placeholder.length());
	outSql.insert(startPos, placeholderValue);
	return outSql;
}

void SqlUtils::executeCommand(std::string logPath, std::string statement,
		std::string filename, std::string table) {
	std::cout << filename << " > Loading table: " << table << "..."
			<< std::endl;
	std::string cmdStr = timePart + cmdFirstPart + " -L " + logPath + logFilename
			+ " -s \"" + statement + "\"";
	FILE * f = popen(cmdStr.c_str(), "r");
	if (f == 0) {
		std::string errmsg("Could not execute mclient command\n");
		throw std::runtime_error(errmsg);
	}
	const int BUFSIZE = 1000;
	char buf[BUFSIZE];

	float elTime;
	int i = 0;
	while (fgets(buf, BUFSIZE, f)) {
		fprintf(stdout, "%s", buf);
		i++;
	}
	pclose(f);
}
