/*
 * Mapper.hpp
 *
 *  Created on: Jun 1, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef MAPPER_HPP_
#define MAPPER_HPP_

#include <string>
#include <vector>
#include <map>

#include "../load/BulkFileWriter.hpp"

typedef std::vector<std::string> Strings;

class Mapper {
public:
	Mapper() :
			columnsToWriters(new std::map<std::string, BulkFileWriter *>()) {
	}

	// virtual destructor is needed if subclass of this base class will be destroyed
	// otherwise if the subclass has a base class reference or pointer and it is destroyed
	// only the base class destructor will be invoked.
	virtual ~Mapper() {
		delete columnsToWriters;
	}

	virtual Strings * getColumnNames() = 0;
	virtual std::string getTableName() = 0;
	virtual std::string getPreferredSourceFileExt() = 0;
	virtual void map(std::string obj) = 0;

	std::map<std::string, BulkFileWriter *> * getColumnsToWriters();
	void setColumnsToWriters(
			std::map<std::string, BulkFileWriter *> * inputColumnsToWriters);
	std::string getFilename(std::string bulkDirectory, std::string columnName);
protected:
	std::map<std::string, BulkFileWriter *> * columnsToWriters;

};

#endif /* MAPPER_HPP_ */
