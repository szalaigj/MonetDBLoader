/*
 * BulkFileWriter.cpp
 *
 *  Created on: Jun 1, 2015
 *      Author: Janos Szalai-Gindl
 */

#include "BulkFileWriter.hpp"

void BulkFileWriter::writeInt(int value){
	(*outputBinaryWriter) << value;
}

void BulkFileWriter::writeBigInt(long value){
	(*outputBinaryWriter) << value;
}

void BulkFileWriter::writeTinyInt(unsigned char value){
	(*outputBinaryWriter) << value;
}

void BulkFileWriter::flush(){
	outputBinaryWriter->flush();
}
