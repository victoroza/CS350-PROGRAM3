#include "prog3.h"

void test(){
	cout << "Hello" << endl;
	Block b1(1, 1);
	b1.state = false;
	cout << b1.state << endl;
	Segment s1;
	cout << s1.numStale << endl;
	s1.addBlock(b1);
}

void addSegments() {
	for(int i = 0; i < NUM_SEGMENTS; i++){
		Segment s;
		disk.push_back(s);
		nodeOrder.push_back(i);
	}
}

void cleanUp() {

}

void create(string line){
	string type;
	int fileNum;
	stringstream(line) >> type >> fileNum;
	// istringstream(line) >> fileNum;
	cout << fileNum << endl;
}

int main() {
	//inputs here
	//Need: NUM_BLOCKS, NUM_SEGMENTS, SIZE_DISK
	//SIZE DISK SHOULD BE POWER OF 2 (16, 32, 64...)
	// NUM_BLOCKS SHOULD BE LESS THAN HALF OF SIZE DISK
	//  AND A POWER OF 2 (SHOULD DIVIDE SIZE DISK)
	// SET NUM SEGMENTS BY DIVIDING SIZE_DISK/NUM_BLOCKS



	//LEAVE HERE
	test();
	addSegments();
	cout << disk.size() << endl;

	ifstream myfile ("inputsmall.txt");
		string line;
		if (myfile.is_open()) {
			while ( getline (myfile,line) )	{
				string type;
				stringstream(line) >> type;
				if(type == "CREATE"){
					create(line);
				}
			}
		}
	return 0;
}