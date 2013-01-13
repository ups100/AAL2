
#include "CrisisAlgorithm.h"
#include "CrisisAlgorithmResult.h"
#include "CrisisAlgorithmCaseGenerator.h"
#include "CrisisAlgorithmChecker.h"

#include "FileReader.h"

#include <iostream>
#include <fstream>
#include <ctime>
#include <cstdlib>

using namespace std;
using namespace CrisisAlgorithmNamespace;

/**
 * Usage:
 *
 * aal <size of problem> [-c option to check results with boost -s save size and time in file results]
 *
 * or
 *
 * aal <file name> [-c option to check results with boost -s save size and time in file results]
 *
 * or
 *
 * aal -help
 */
int main(int argc, char** argv )
{
	string usage("Help:");
	string fileName("test5");
	string resultsFileName("results");
	string checkParam("-c");
	string saveParam("-s");
	bool check = false;
	bool save = false;

	int size = 0;

	if(argc == 1) {
		cout<<usage<<endl;
		return -1;
	} else if(argc >= 2) {
		size = atoi(argv[1]);
		if(size != 0) {
			CrisisAlgorithmCaseGenerator gen;
			gen.generate(size);
			gen.saveGeneration(fileName);
		} else {
			fileName = string(argv[1]);
		}
	}

	if(argc == 3) {
		if(string(argv[2]) == checkParam) {
			check = true;
		} else if(string(argv[2]) == saveParam) {
			save = true;
		}
	}

	if(argc == 4) {
		if (string(argv[2]) == checkParam) {
			check = true;
		} else if (string(argv[2]) == saveParam) {
			save = true;
		}

		if (string(argv[3]) == checkParam) {
			if(check) {
				cout << usage << endl;
				return -1;
			} else {
				check = true;
			}
		} else if (string(argv[3]) == saveParam) {
			if (save) {
				cout << usage << endl;
				return -1;
			} else {
				save = true;
			}
		}
	}
	if(argc >4) {
		cout << usage << endl;
		return -1;
	}

	ifstream input;
	input.open(fileName.c_str());
	if(!input.is_open()) {
		cout<<"Unable to open file: "<<fileName<<endl;
		return -1;
	}

	FileReader reader(input);
	input.close();

	if(!reader.isParsingSuccess()) {
		cout << "File " << fileName <<"is not properly formated" << endl;
		return -1;
	}

	cout<<"File parsing successful!!!"<<endl;
	cout<<"Parameters: "<<endl<<"Number of cities:\t"<<reader.getNumberOfCities()<<endl
			<<"Capitol:\t\t"<<reader.getCapitol()<<endl;
	cout.flush();

	CrisisAlgorithmResult result(reader.getNumberOfCities());
	//block to auto-delete object to save memory
	{
		CrisisAlgorithm algorithm(reader.getNumberOfCities(), reader.getConnections(), reader.getCutPath(), reader.getCapitol());
		result = algorithm.execute();
	}

	cout<<"--------------------Algorithm finished--------------------"<<endl;
	for (int i = 0; i < result.getNumberOfCities(); ++i) {
		if(result[i] == -1) {
			cout<< "City number: " << i <<" was the capitol."<<endl;
		} else {
			cout << "City number: " << i << " was cut of from capitol after: "
							<< result[i] << " months." << endl;
		}

	}
	cout <<endl<< "Execution time = " << (result.getExecutionTime() * 1000.0)/CLOCKS_PER_SEC << " ms"
			<<" ( "<<(result.getExecutionTime() * 1.0)/CLOCKS_PER_SEC<< " s )"<< endl;

	if(check)
	{
		cout<<endl<<"--------------------Checking results--------------------"<<endl;

		CrisisAlgorithmChecker checker(reader.getNumberOfCities(), reader.getConnections(), reader.getCutPath(), reader.getCapitol());
		CrisisAlgorithmResult reference = checker.execute();

		bool difference = false;
		for (int i = 0; i < result.getNumberOfCities(); ++i) {
			if(result[i] != reference[i]) {
				cout <<"Results are different for city: "<<i<<endl<<"Algorithm: "<<result[i]<<" Reference: "<<reference[i]<<endl<<endl;
				difference = true;
			}
		}

		if(!difference) {
			cout<<endl<<"All results are that same, no differences found."<<endl;
		}

		cout <<endl<< "Checking time = " << (reference.getExecutionTime() * 1000.0)/CLOCKS_PER_SEC << " ms"
					<<" ( "<<(reference.getExecutionTime() * 1.0)/CLOCKS_PER_SEC<< " s )"<< endl<<endl;

		cout<<"--------------------Results checked--------------------"<<endl;

	}

	if(save)
	{
		ofstream resultsStream;
		resultsStream.open(resultsFileName.c_str(), ofstream::app);
		resultsStream<<reader.getNumberOfCities()<<"\t"<<(result.getExecutionTime() * 1000.0)/CLOCKS_PER_SEC<<endl;
		resultsStream.close();
	}

	return 0;
}
