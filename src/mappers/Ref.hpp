/*
 * Ref.hpp
 *
 *  Created on: Jun 10, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef REF_HPP_
#define REF_HPP_

#include <string>

#include "Mapper.hpp"

class Ref: public Mapper {
public:
	Ref();

	~Ref();

	const static std::string refIDColumn;
	const static std::string posColumn;
	const static std::string refNucColumn;

	Strings * getColumnNames();
	std::string getTableName();
	std::string getPreferredSourceFileExt();
	void map(std::string obj);

private:
	Strings * columnNames;
	std::string tableName;
	std::string preferredSourceFileExt;

	void splitStrIntoParts(const std::string& obj, Strings * objParts,
			char delimiter);
};

#endif /* REF_HPP_ */
