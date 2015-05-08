#include "prog3.h"

void addSegments() {
	for(int i = 0; i < NUM_SEGMENTS; i++){
		Segment s;
		disk.push_back(s);
		nodeOrder.push_back(i);
	}
}

void cleanUp() {
	cout << "CALLED CLEANUP" << endl;
	cleanSeeks++;
	seeks++;
	bool foundAllStale = false;
	int mostStale = -1;
	int index = -1;
	while((nodeOrder.size() <= (int)(NUM_SEGMENTS * .4)) || (nodeOrder.size() <= ((int)(NUM_SEGMENTS * .2) + 1))) {
		// while(!foundAllStale){
		mostStale = -1;
		index = -1;
		for(int i = 0; i < filled.size(); i++) {
			if(disk[filled[i]].numStale > mostStale) {
				mostStale = disk[filled[i]].numStale;
				index = filled[i];
				filled.erase(filled.begin()+i);
			}

		}
		if (mostStale == -1) {
			foundAllStale = true;
			int indexToGet = rand() % nodeOrder.size();
			index = nodeOrder[indexToGet];
			nodeOrder.erase(nodeOrder.begin()+indexToGet);
		}
		for(int i = 0; i < NUM_BLOCKS; i++) {
			if(((disk[index]).blocks)[i].state == true) {
				int keepChecking = -1;
				int blockNum = ((disk[index]).blocks)[i].blockNumber;
				int fileNum = ((disk[index]).blocks)[i].fileNumber;
				while(keepChecking == -1){
					Block b(fileNum, blockNum);
					int segIndex = (disk[headLoc]).addBlock(b);
					LocationN loc(headLoc, segIndex);
					nodeMap[fileNum][blockNum] = loc;
					cout << nodeMap[fileNum][blockNum].segmentIndex << endl;
					keepChecking = nodeMap[fileNum][blockNum].segmentIndex;
					if(nodeMap[fileNum][blockNum].segmentIndex == -1){
						filled.push_back(headLoc);
						headLoc = nodeOrder.front();
						nodeOrder.pop_front();
					}
				}
			}
		}
		Segment s;
		disk[index] = s;
		nodeOrder.push_back(index);


		// }
	}
}

void create(string line) {
	string type;
	int fileNum;
	stringstream(line) >> type >> fileNum;
	map<int, LocationN> temp;
	nodeMap[fileNum] = temp;
}

void write(string line) {
	string type;
	int fileNum;
	int blockNum;
	stringstream(line) >> type >> fileNum >> blockNum;
	cout << "WRITE: " << fileNum << " " << blockNum << endl;
	map<int,LocationN>::iterator itF = (nodeMap.at(fileNum)).find(blockNum);
	if(itF != (nodeMap.at(fileNum)).end()){
		cout << "FOUND" << endl;
		// cout << itF->second.segmentNum << endl;
		// cout << itF->second.segmentIndex << endl;
		disk[itF->second.segmentNum].markStale(itF->second.segmentIndex);
	} else {
		cout << "NOT FOUND AND ADDING" << endl;
	}
	int keepChecking = -1;
	while(keepChecking == -1){
		Block b(fileNum, blockNum);
		int segIndex = (disk[headLoc]).addBlock(b);
		LocationN loc(headLoc, segIndex);
		nodeMap[fileNum][blockNum] = loc;
		cout << nodeMap[fileNum][blockNum].segmentIndex << endl;
		keepChecking = nodeMap[fileNum][blockNum].segmentIndex;
		if(nodeMap[fileNum][blockNum].segmentIndex == -1){
			filled.push_back(headLoc);
			headLoc = nodeOrder.front();
			nodeOrder.pop_front();
		}
	}
	cout << "ADDING TO: " << headLoc << endl;
	cout << (int)(NUM_SEGMENTS * .2) << endl;
	if((nodeOrder.size() <= (int)(NUM_SEGMENTS * .2)) || (nodeOrder.size() <= ((int)(NUM_SEGMENTS * .2) + 1))) {
		cleanUp();
	}
}

void read(string line) {
	seeks++;
}

void close(string line) {
	string type;
	int fileNum;
	stringstream(line) >> type >> fileNum;
	for (map<int,LocationN>::iterator it=(nodeMap.at(fileNum)).begin(); it!=(nodeMap.at(fileNum)).end(); ++it) {
		// cout << it->first << " => " << it->second << endl;
	}
}

int main(int argc, char *argv[]) {
	srand (time(NULL));
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
				instCount++;
				write(line);

			} else if(type == "READ") {
				instCount++;
				read(line);

			} else if(type == "CLOSE") {
				instCount++;
				close(line);

			}
		}
	}
	cout << "Number of Seeks: " << seeks << endl;
	cout << "Number of Total Instructions: " << instCount << endl;
	return 0;
}