/*
 * BulkFileWriter.hpp
 *
 *  Created on: Jun 1, 2015
 *      Author: Janos Szalai-Gindl
 */

#ifndef BULKFILEWRITER_HPP_
#define BULKFILEWRITER_HPP_

#include <fstream>
#include <string>

class BulkFileWriter {
public:
	BulkFileWriter(std::string outputFilename) :
			outputBinaryWriter(
					new std::ofstream(outputFilename.c_str(),
							std::ios_base::out | std::ios_base::binary)) {
	}

	~BulkFileWriter() {
		flush();
		outputBinaryWriter->close();
		delete outputBinaryWriter;
	}

	void writeInt(int value);
	void writeBigInt(long value);
	void writeTinyInt(unsigned char value);
	void flush();
private:
	std::ofstream * outputBinaryWriter;
};

#endif /* BULKFILEWRITER_HPP_ */
