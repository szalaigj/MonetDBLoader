/*
 * Ref.cpp
 *
 *  Created on: Jun 1, 2015
 *      Author: Janos Szalai-Gindl
 */

#include <cstring>
#include <cstdlib>
#include <sstream>
#include <fstream>

#include "Mapper.hpp"

class Ref: public Mapper {
public:
	Ref() :
			Mapper(), columnNames(new Strings()), tableName("ref"), preferredSourceFileExt(
					".fa") {
		columnNames->push_back("refID");
		columnNames->push_back("pos");
		columnNames->push_back("refNuc");
	}

	~Ref() {
		delete columnNames;
	}

	Strings * getColumnNames() {
		return columnNames;
	}

	std::string getTableName() {
		return tableName;
	}

	std::string getPreferredSourceFileExt() {
		return preferredSourceFileExt;
	}

	void map(std::string obj) {
		Strings * objParts = new Strings();
		splitStrIntoParts(obj, objParts, '\t');

		Strings * firstTokenParts = new Strings();
		// If the fileName contains char '_' the original file is chunked to a lot of files
		// so the file index - which should be the refID - is obtained by splitting.
		// And the original file name is irrelevant.
		splitStrIntoParts((*objParts)[0], firstTokenParts, '_');

		long firstPosOfLine = atol((*objParts)[1].c_str());

		std::string partsOfNucSeq = (*objParts)[2];

		int sizeOfPartsOfNucSeq = partsOfNucSeq.size();
		char nucsOfLine[1024];
		std::strcpy(nucsOfLine, partsOfNucSeq.c_str());

		for (int index = 0; index < sizeOfPartsOfNucSeq; index++) {
			char nuc = nucsOfLine[index];

			// [refID] [int] NOT NULL PRIMARY KEY
			int tmp = atoi(
					(*firstTokenParts)[(*firstTokenParts).size() - 1].c_str());
			(*columnsToWriters)["refID"].writeInt(tmp);

			// [pos] [bigint] NOT NULL
			(*columnsToWriters)["pos"].writeBigInt(firstPosOfLine);

			// [refNuc] [char] NULL
			(*columnsToWriters)["refNuc"].writeTinyInt((unsigned char) nuc);

			firstPosOfLine++;
		}

		delete objParts;
		delete firstTokenParts;
	}

private:
	Strings * columnNames;
	std::string tableName;
	std::string preferredSourceFileExt;

	void splitStrIntoParts(const std::string& obj, Strings * objParts,
			char delimiter) {
		std::istringstream iss(obj);
		std::string token;
		while (std::getline(iss, token, delimiter)) {
			objParts->push_back(token);
		}
	}
};
