#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
using namespace std;

int main (int argc, char *argv[]) {
	int degreeOfLocality = 2;
	int fileSize = 10;
	string outputFileName = "";
	int numFiles = 3;

	int option;
	opterr = 0;
	while ((getopt(argc, argv, "uo:L:S:")) != -1) {
		char *errPtr;
		switch(option) {
			case 'u':
				fprintf(stderr, "Usage: ./program3_gen -u -o <output-file-name> -N <number-of-files> -L <degree-of-locality> -S <file-size> where -u prints the usage, <degree-of-locality> is a number from 1-3\n");
				exit(0);
			case 'o':
				outputFileName = optarg;
				break;
			case 'N':
				numFiles = strtoul(optarg, &errPtr, 10);
				if (*errPtr || (numFiles < 1)) {
					fprintf(stderr, "Error: Invalid value for <number-of-files>\n");
					exit(1);
				}
				break;
			case 'L':
				degreeOfLocality = strtoul(optarg, &errPtr, 10);
				if (*errPtr || (degreeOfLocality < 1 || degreeOfLocality > 3)) {
					fprintf(stderr, "Error: Invalid value for <degree-of-locality>\n");
					exit(1);
				}
				break;
			case 'S':
				fileSize = strtoul(optarg, &errPtr, 10);
				if (*errPtr || (fileSize < 1)) {
					fprintf(stderr, "Error: Invalid value for <file-size>\n");
					exit(1);
				}
				break;
			case '?':
				exit(1);
		}
	}

	if (outputFileName == "") {
		fprintf(stderr, "Error: Invalid value for <output-file-name>\n");
		exit(1);
	}

	ofstream outputFile;
	outputFile.open(outputFileName, ofstream::out);

	if (outputFile.is_open()) {
		 //create files
		 for (int i = 0; i < numFiles; ++i) {
		 	outputFile << "CREATE " << i << endl;
		 }
	} else {
		fprintf(stderr, "Error: Failed to open output file\n");
		exit(1);
	}

	outputFile.close();
}
