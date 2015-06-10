//============================================================================
// Name        : MonetDBLoader.cpp
// Author      : Janos Szalai-Gindl
// Version     :
// Copyright   : 
// Description : This is the loader toolkit for MonetDB.
//============================================================================

#include <iostream>
#include <exception>
#include <stdexcept>
#include <map>

#include "verbs/PropertiesAdapter.hpp"
//#include "verbs/ExampleVerb.hpp"
#include "mappers/Ref.hpp"
#include "load/FileUtils.hpp"
#include "services/BaseBulkInsertFileCreator.hpp"
#include "sql/SqlUtils.hpp"
#include "verbs/StartVerb.hpp"

using namespace std;

int main(int argc, char** argv) {
	BasePropertiesAdapter propAdapter;
	Ref * ref = new Ref();
	FileUtils * fileUtils = new FileUtils();
	std::vector<Mapper *> * mappings = new std::vector<Mapper *>();
	mappings->push_back(ref);
	DefaultBulkInsertFileCreator * bulkInsertFileCreator =
			new DefaultBulkInsertFileCreator(fileUtils, mappings);

	// The first argument contains the resource path where the settings file
	// are found.
	std::string resourcePath(argv[1]);

	// The second argument contains the settings file name. Lines of this file
	// contain property name and value separated by '='.
	std::string settingsfilename(argv[2]);

	// The following is the full file access for settings file.
	std::string settingsfile(resourcePath + "/" + settingsfilename);

	SqlUtils * sqlUtils = new SqlUtils(resourcePath);
	try {
		// The following only an example verb:
		/* ExampleVerb exampleVerb(propAdapter, settingsfile);
		 exampleVerb.printUsage();
		 exampleVerb.run();*/

		StartVerb startVerb(propAdapter, settingsfile, ref,
				bulkInsertFileCreator, sqlUtils);
		startVerb.printUsage();
		startVerb.run();
	} catch (runtime_error& re) {
		cerr << re.what();
	}
	return 0;
}
