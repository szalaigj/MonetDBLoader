/*
 * FileUtils.cpp
 *
 *  Created on: Jun 4, 2015
 *      Author: Janos Szalai-Gindl
 */

#include <fstream>
#include <sys/types.h>
#include <sys/stat.h>

#include "FileUtils.hpp"

void FileUtils::close(Mapper * mapper) {
	Strings * columnNames = mapper->getColumnNames();
	for (Strings::iterator it = columnNames->begin(); it != columnNames->end();
			++it) {
		std::string columnName = *it;
		BulkFileWriter * bulkFileWriter =
				(*(mapper->getColumnsToWriters()))[columnName];
		delete bulkFileWriter;
	}
}

void FileUtils::deleteFile(std::string bulkDirectory, Mapper * mapper) {
	Strings * columnNames = mapper->getColumnNames();
	for (Strings::iterator it = columnNames->begin(); it != columnNames->end();
			++it) {
		std::string columnName = *it;
		std::string fileName = mapper->getFilename(bulkDirectory, columnName);
		std::ifstream columnFile(fileName.c_str());
		if (columnFile.good()) {
			columnFile.close();
			remove(fileName.c_str());
		}
	}
}

void FileUtils::open(std::string bulkDirectory, Mapper * mapper) {
	// create directory with read/write/search permissions for owner and group,
	// and with read/search permissions for others.
	mkdir(bulkDirectory.c_str(), S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);

	std::map<std::string, BulkFileWriter *> * columnsToWriters = new std::map<
			std::string, BulkFileWriter *>();

	Strings * columnNames = mapper->getColumnNames();
	for (Strings::iterator it = columnNames->begin(); it != columnNames->end();
			++it) {
		std::string columnName = *it;
		std::string fileName = mapper->getFilename(bulkDirectory, columnName);
		(*columnsToWriters)[columnName] = new BulkFileWriter(fileName);
	}
	mapper->setColumnsToWriters(columnsToWriters);
}
