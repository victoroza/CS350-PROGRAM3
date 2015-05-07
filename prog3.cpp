#include "prog3.h"

void addSegments() {
	for(int i = 0; i < NUM_SEGMENTS; i++){
		Segment s;
		disk.push_back(s);
		nodeOrder.push_back(i);
	}
}

void cleanUp() {

}

void create(string line) {
	string type;
	int fileNum;
	stringstream(line) >> type >> fileNum;
	map<int, int> temp;
	nodeMap[fileNum] = temp;
}

void write(string line) {
	string type;
	int fileNum;
	int blockNum;
	stringstream(line) >> type >> fileNum >> blockNum;
	cout << "WRITE: " << fileNum << " " << blockNum << endl;
	map<int,int>::iterator itF = (nodeMap.at(fileNum)).find(blockNum);
	if(itF != (nodeMap.at(fileNum)).end()){
		cout << "FOUND" << endl;
		cout << itF->second << endl;
	} else {
		cout << "NOT FOUND AND ADDING" << endl;
	}
	Block b(fileNum, blockNum);
	int segIndex = (disk[headLoc]).addBlock(b);
	nodeMap[fileNum][blockNum] = segIndex;
}

void read(string line) {
	string type;
	int fileNum;
	int blockNum;
	stringstream(line) >> type >> fileNum >> blockNum;
	cout << "READ: " << fileNum << " " << blockNum << endl;
}

void close(string line) {
	string type;
	int fileNum;
	stringstream(line) >> type >> fileNum;
	for (map<int,int>::iterator it=(nodeMap.at(fileNum)).begin(); it!=(nodeMap.at(fileNum)).end(); ++it) {
		cout << it->first << " => " << it->second << endl;
	}
}

int main(int argc, char *argv[]) {
	//inputs here
	//Need: NUM_BLOCKS, NUM_SEGMENTS, SIZE_DISK
	//SIZE DISK SHOULD BE POWER OF 2 (16, 32, 64...)
	// NUM_BLOCKS SHOULD BE LESS THAN HALF OF SIZE DISK
	//  AND A POWER OF 2 (SHOULD DIVIDE SIZE DISK)
	// SET NUM SEGMENTS BY DIVIDING SIZE_DISK/NUM_BLOCKS

	int option;
	opterr = 0;
	while ((option = getopt(argc, argv, "uI:D:B:")) != -1) {
		char *errPtr;
		switch(option) {
			case 'u':
				fprintf(stderr, "Usage: ./program3 -u -I <Input-File-Name> -D <Size-Disk> -B <Num-Blocks> where -u prints the usage, <Size-Disk> must be between 16-1024, and Num-Blocks must be a power of 2 and should be <= than half of <Size-Disk>. All flags are optional, all specified flags (except u) require arguments\n");
				exit(0);
			case 'I':
				inputFileName = optarg;
				break;
			case 'D':
				SIZE_DISK = strtoul(optarg, &errPtr, 10);
				if (*errPtr || (SIZE_DISK < 16 || SIZE_DISK > 1024)) {
					fprintf(stderr, "Error: Invalid value for <Size-Disk>\n");
					exit(1);
				}
				break;
			case 'B':
				NUM_BLOCKS = strtoul(optarg, &errPtr, 10);
				if (*errPtr) {
					fprintf(stderr, "Error: Invalid value for <Num-Blocks>\n");
					exit(1);
				}
				break;
			case '?':
				fprintf(stderr, "Error: Invalid value for <Num-Blocks>");
				exit(1);
		}
	}
 
	if (NUM_BLOCKS > SIZE_DISK / 2) {
		fprintf(stderr, "Error: Invalid value for <Num-Blocks>\n");
		exit(1);
	}
	if (inputFileName == ""){
		fprintf(stderr, "Error: Invalid value for <Input-File-Name>\n");
		exit(1);
	}



	//LEAVE HERE
	addSegments();
	headLoc = nodeOrder.front();
	nodeOrder.pop_front();
	ifstream myfile (inputFileName);
	string line;
	if (myfile.is_open()) {
		while ( getline (myfile,line) )	{
			string type;
			stringstream(line) >> type;
			if(type == "CREATE") {
				create(line);

			} else if(type == "WRITE") {
				write(line);

			} else if(type == "READ") {
				read(line);

			} else if(type == "CLOSE") {
				close(line);

			}
		}
	}
	return 0;
}