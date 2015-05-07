#include "prog3.h"

void test(){
	cout << "Hello" << endl;
	Block b1(1, 1);
	b1.state = false;
	cout << b1.state << endl;
	Segment s1;
	cout << s1.numStale << endl;
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
	return 0;
}