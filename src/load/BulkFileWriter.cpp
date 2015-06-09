/*
 * BulkFileWriter.cpp
 *
 *  Created on: Jun 1, 2015
 *      Author: Janos Szalai-Gindl
 */

#include "BulkFileWriter.hpp"

void BulkFileWriter::writeInt(int value) {
	(*outputBinaryWriter).write((char *)&value, sizeof(int));
}

void BulkFileWriter::writeBigInt(long long value) {
	(*outputBinaryWriter).write((char *)&value, sizeof(long long));
}

void BulkFileWriter::writeTinyInt(unsigned char value) {
	(*outputBinaryWriter).write((char *)&value, sizeof(unsigned char));
}

void BulkFileWriter::writeChar(char value) {
	(*outputBinaryWriter) << value << lineDelimiterChar;
}

void BulkFileWriter::flush() {
	outputBinaryWriter->flush();
}
