#include <unistd.h>
#include <iostream>
#include <fstream>
#include <stdlib.h>
#include <map>
#include <vector>
#include <sstream>
#include <time.h>
#include <deque>
#include <set>
using namespace std;

int main (int argc, char *argv[]) {
	srand(time(NULL));
	int degreeOfLocality = 1;
	int fileSize = 5;
	string outputFileName = "";
	int numFiles = 10;
	int operations = 1000;
	string prefer = "RAN"; //RAN, R, W

	int option;
	opterr = 0;
	while ((option = getopt(argc, argv, "uO:o:L:S:R:N:")) != -1) {
		char *errPtr;
		switch(option) {
			case 'u':
				fprintf(stderr, "Usage: ./program3_gen -u -o <output-file-name> -O <number-of-operations> -R <which-to-prefer> (R-read, W-write, RAN-random) -N <number-of-files> -S <file-size> where -u prints the usage\n");
				exit(0);
			case 'o':
				outputFileName = optarg;
				break;
			case 'O':
				stringstream(optarg) >> operations;
				break;
			case 'R':
				prefer = optarg;
				if(prefer != "RAN" && prefer != "R" && prefer != "W"){
					fprintf(stderr, "Error: Invalid value for <which-to-prefer>\n");
					exit(1);
				}
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
		// cout << outputFileName << endl;
		fprintf(stderr, "Error: Invalid value for <output-file-name>\n");
		exit(1);
	}

	ofstream outputFile;
	outputFile.open(outputFileName, ofstream::out);
	deque<int> filesLeft;
	if (outputFile.is_open()) {
		//create files
		for (int i = 0; i < numFiles; ++i) {
			outputFile << "CREATE " << (i+1) << endl;
			filesLeft.push_back(i+1);
		}
		map<int, set<int>> usedFileBlocks;
		deque<int> filesUsed;
		if(usedFileBlocks.size() == 0){
			int file = ((rand() % numFiles) + 1);
			int block = ((rand() % fileSize) + 1);
			set<int> temp;
			temp.insert(block);
			usedFileBlocks[file] = temp;
			filesUsed.push_back(file);
			outputFile << "WRITE " << file << " " << block << endl;
		}
		if(degreeOfLocality == 1) {
			for(int i = 1; i < operations; i++){
				int closeFileC = (rand() % 10000);
				// cout << "CLOSE: " << closeFileC << endl;
				if(closeFileC < 50 && filesLeft.size() > 1) {
					int indexFile = (rand() % filesUsed.size());
					int file = filesUsed[indexFile];
					// cout << filesUsed.size() << endl;
					filesUsed.erase(filesUsed.begin()+indexFile);
					int indexFL = -1;
					for(int j = 0; j < filesLeft.size(); j++){
						if(filesLeft[j] == file){
							indexFL = j;
							// cout << "INDEX: " << indexFL << endl;
						}
					}
					filesLeft.erase(filesLeft.begin()+indexFL);
					// cout << filesUsed.size() << endl;
					usedFileBlocks.erase(file);
					outputFile << "CLOSE " << file << endl;
				} else{
					if(prefer == "RAN") {
						int pick = (rand() % 2);
						if(pick == 0) {
							int file = filesUsed[(rand() % filesUsed.size())];
							set<int>::iterator it=(usedFileBlocks.at(file)).begin();
							// cout << ((usedFileBlocks.at(file)).size()) << endl;
							int val = (rand() % ((usedFileBlocks.at(file)).size()));
							advance(it, val);
							int block = *it;
							outputFile << "READ " << file << " " << block << endl;
						} else {
							int fileIn = (rand() % filesLeft.size());
							int file = filesLeft[fileIn];
							int block = ((rand() % fileSize) + 1);
							if(usedFileBlocks.count(file) > 0) {
								if(usedFileBlocks[file].count(block) > 0){
									outputFile << "WRITE " << file << " " << block << endl;
								} else {
									(usedFileBlocks[file]).insert(block);
									outputFile << "WRITE " << file << " " << block << endl;
								}
							} else {
								set<int> temp;
								temp.insert(block);
								usedFileBlocks[file] = temp;
								filesUsed.push_back(file);
								outputFile << "WRITE " << file << " " << block << endl;
							}
						}
					} else if (prefer == "R") {
						int pick = (rand() % 30);
						if(pick < 20) {
							int file = filesUsed[(rand() % filesUsed.size())];
							set<int>::iterator it=(usedFileBlocks.at(file)).begin();
							// cout << ((usedFileBlocks.at(file)).size()) << endl;
							int val = (rand() % ((usedFileBlocks.at(file)).size()));
							advance(it, val);
							int block = *it;
							outputFile << "READ " << file << " " << block << endl;
						} else {
							int fileIn = (rand() % filesLeft.size());
							int file = filesLeft[fileIn];
							int block = ((rand() % fileSize) + 1);
							if(usedFileBlocks.count(file) > 0) {
								if(usedFileBlocks[file].count(block) > 0){
									outputFile << "WRITE " << file << " " << block << endl;
								} else {
									(usedFileBlocks[file]).insert(block);
									outputFile << "WRITE " << file << " " << block << endl;
								}
							} else {
								set<int> temp;
								temp.insert(block);
								usedFileBlocks[file] = temp;
								filesUsed.push_back(file);
								outputFile << "WRITE " << file << " " << block << endl;
							}
						}
					} else {
						int pick = (rand() % 30);
						if(pick < 10) {
							int file = filesUsed[(rand() % filesUsed.size())];
							set<int>::iterator it=(usedFileBlocks.at(file)).begin();
							// cout << ((usedFileBlocks.at(file)).size()) << endl;
							int val = (rand() % ((usedFileBlocks.at(file)).size()));
							advance(it, val);
							int block = *it;
							outputFile << "READ " << file << " " << block << endl;
						} else {
							int fileIn = (rand() % filesLeft.size());
							int file = filesLeft[fileIn];
							int block = ((rand() % fileSize) + 1);
							if(usedFileBlocks.count(file) > 0) {
								if(usedFileBlocks[file].count(block) > 0){
									outputFile << "WRITE " << file << " " << block << endl;
								} else {
									(usedFileBlocks[file]).insert(block);
									outputFile << "WRITE " << file << " " << block << endl;
								}
							} else {
								set<int> temp;
								temp.insert(block);
								usedFileBlocks[file] = temp;
								filesUsed.push_back(file);
								outputFile << "WRITE " << file << " " << block << endl;
							}
						}
					}
				}
			}

		} 
		for(int i = 0; i < filesUsed.size(); i++){
			outputFile << "CLOSE " << filesUsed[i] << endl;
		}
	} else {
		fprintf(stderr, "Error: Failed to open output file\n");
		exit(1);
	}
	outputFile.close();
}
