#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdlib.h>

using namespace std;

int NUM_BLOCKS = 8;
int NUM_SEGMENTS = 32;
int SIZE_DISK = 256;

class Block {
	public:
		int fileNumber;
		int blockNumber;
		bool state = true;
		Block(int x, int y) {
			fileNumber = x;
			blockNumber = y;
		}
};

class Segment {
  public:
  	int total = 0;
    int numStale = 0;
    int numGood = 0;
    vector<Block> blocks;
    int addBlock(Block b) {
    	if(total < NUM_BLOCKS){

    	}
    	return 0;
    }
};