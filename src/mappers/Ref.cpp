/*
 * Ref.cpp
 *
 *  Created on: Jun 1, 2015
 *      Author: Janos Szalai-Gindl
 */

#include <iostream>
#include <cstring>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include "Ref.hpp"

const std::string Ref::refIDColumn = "refID";
const std::string Ref::posColumn = "pos";
const std::string Ref::refNucColumn = "refNuc";

Ref::Ref() :
		Mapper(), columnNames(new Strings()), tableName("ref"), preferredSourceFileExt(
				".fa") {
	columnNames->push_back(refIDColumn);
	columnNames->push_back(posColumn);
	columnNames->push_back(refNucColumn);
}

Ref::~Ref() {
	delete columnNames;
}

Strings * Ref::getColumnNames() {
	return columnNames;
}

std::string Ref::getTableName() {
	return tableName;
}

std::string Ref::getPreferredSourceFileExt() {
	return preferredSourceFileExt;
}

void Ref::map(std::string obj) {
	/*		std::cout << obj << std::endl;*/
	Strings * objParts = new Strings();
	splitStrIntoParts(obj, objParts, '\t');

	Strings * firstTokenParts = new Strings();
	// If the fileName contains char '_' the original file is chunked to a lot of files
	// so the file index - which should be the refID - is obtained by splitting.
	// And the original file name is irrelevant.
	splitStrIntoParts((*objParts)[0], firstTokenParts, '_');

	long long firstPosOfLine = std::atoll((*objParts)[1].c_str());

	std::string partsOfNucSeq = (*objParts)[2];

	/*		std::cout << (*objParts)[0] << " " << (*objParts)[1] << " "
	 << (*objParts)[2] << " " << std::endl;

	 std::cout << (*firstTokenParts)[(*firstTokenParts).size() - 1] << std::endl;*/

	int sizeOfPartsOfNucSeq = partsOfNucSeq.size();
	char nucsOfLine[1024];
	std::strcpy(nucsOfLine, partsOfNucSeq.c_str());

	int currentRefID = atoi(
			(*firstTokenParts)[(*firstTokenParts).size() - 1].c_str());
	for (int index = 0; index < sizeOfPartsOfNucSeq; index++) {
		char nuc = nucsOfLine[index];

		// [refID] [int] NOT NULL PRIMARY KEY
		((*columnsToWriters)["refID"])->writeInt(currentRefID);

		// [pos] [bigint] NOT NULL PRIMARY KEY
		((*columnsToWriters)["pos"])->writeBigInt(firstPosOfLine);

		// [refNuc] [char] NULL
		((*columnsToWriters)["refNuc"])->writeChar(nuc);

		firstPosOfLine++;
	}

	delete objParts;
	delete firstTokenParts;
}

void Ref::splitStrIntoParts(const std::string& obj, Strings * objParts,
		char delimiter) {
	std::istringstream iss(obj);
	std::string token;
	while (std::getline(iss, token, delimiter)) {
		objParts->push_back(token);
	}
}
