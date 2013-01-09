
#include "CrisisAlgorithm.h"
#include "FileReader.h"

#include <iostream>
#include <fstream>

using namespace std;
using namespace CrisisAlgorithmNamespace;

int main(void)
{
	ifstream input;
	input.open("test1");
	FileReader reader(input);

	if(reader.isParsingSuccess()) {
		cout<<"File parsing ok"<<endl;
		CrisisAlgorithm algorithm(reader.getNumberOfCities(), reader.getConnections(), reader.getCutPath(), reader.getCapitol());
		algorithm.execute();
		cout<<"Algorithm finished"<<endl;
	} else {
		cout<<"File parsing problem"<<endl;
	}
	return 0;
}
