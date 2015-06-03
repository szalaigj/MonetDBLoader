/*
 * Mapper.cpp
 *
 *  Created on: Jun 1, 2015
 *      Author: Janos Szalai-Gindl
 */

#include "Mapper.hpp"

std::string Mapper::getFilename(std::string bulkDirectory,
		std::string columnName) {
	std::string filename = bulkDirectory + "/" + getTableName();
	filename += "_" + columnName;
	filename += ".dat";
	return filename;
}

std::map<std::string, BulkFileWriter> * Mapper::getColumnsToWriters() {
	return columnsToWriters;
}

void Mapper::setColumnsToWriters(
		std::map<std::string, BulkFileWriter> * inputColumnsToWriters) {
	columnsToWriters = inputColumnsToWriters;
}
