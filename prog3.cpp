#include "prog3.h"

void test(){
	cout << "Hello" << endl;
	Block b1(1, 1);
	b1.state = false;
	cout << b1.state << endl;
	Segment s1;
	cout << s1.numStale << endl;
}

int main(int argc, char *argv[]) {
	//inputs here
	//Need: NUM_BLOCKS, NUM_SEGMENTS, SIZE_DISK
	//SIZE DISK SHOULD BE POWER OF 2 (16, 32, 64...)
	//NUM_BLOCKS SHOULD BE LESS/EQUAL THAN HALF OF SIZE DISK
	//AND A POWER OF 2 (SHOULD DIVIDE SIZE DISK)
	//SET NUM SEGMENTS BY DIVIDING SIZE_DISK/NUM_BLOCKS
	
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
					fprintf(stderr, "Error: Invalid value for <Size-Disk>");
					exit(1);
				}
				break;
			case 'B':
				NUM_BLOCKS = strtoul(optarg, &errPtr, 10);
				if (*errPtr) {
					fprintf(stderr, "Error: Invalid value for <Num-Blocks>");
					exit(1);
				}
				break;
			case '?':
				exit(1);
		}
	}

	if (NUM_BLOCKS > SIZE_DISK / 2) {
		fprintf(stderr, "Error: Invalid value for <Num-Blocks>");
		exit(1);
	}

	//LEAVE HERE
	test();
	return 0;
}
