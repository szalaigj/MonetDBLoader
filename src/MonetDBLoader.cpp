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
#include "verbs/StartVerb.hpp"
//#include "verbs/ExampleVerb.hpp"
#include "mappers/Ref.cpp"
#include "load/FileUtils.hpp"
#include "services/BaseBulkInsertFileCreator.hpp"

using namespace std;

int main(int argc, char** argv) {
	BasePropertiesAdapter propAdapter;
	Ref * ref = new Ref();
	FileUtils * fileUtils = new FileUtils();
	std::vector<Mapper *> * mappings = new std::vector<Mapper *>();
	mappings->push_back(ref);
	DefaultBulkInsertFileCreator * bulkInsertFileCreator =
			new DefaultBulkInsertFileCreator(fileUtils, mappings);

	// The (first) argument contains the path and file name of configuration file
	// where the properties are found. Lines of configuration file contain
	// property name and value separated by '='
	std::string settingsfilename(argv[1]);

	try {
		// The following only an example verb:
		/* ExampleVerb exampleVerb(propAdapter, settingsfilename);
		 exampleVerb.printUsage();
		 exampleVerb.run();*/

		StartVerb startVerb(propAdapter, settingsfilename, ref,
				bulkInsertFileCreator);
		startVerb.printUsage();
		startVerb.run();
	} catch (runtime_error& re) {
		cerr << re.what();
	}
	return 0;
}
