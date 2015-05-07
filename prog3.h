#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdlib.h>
#include <deque>

using namespace std;


int NUM_BLOCKS = 8;
int NUM_SEGMENTS = 32;
int SIZE_DISK = 256;

map<int, map<int, int>> nodeMap;

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
    int numStale = 0;
    int numGood = 0;
    vector<Block> blocks;
    int sizeUsed() {
    	return blocks.size();
    }
    void markStale(int i){
        blocks[i].state = false;
        numStale++;
        numGood--;
    }
    int addBlock(Block b) {
    	if(blocks.size() < NUM_BLOCKS){
    		numGood++;
    		blocks.push_back(b);
    	}
    	return blocks.size();
    }
};



vector<Segment> disk;
deque<int> nodeOrder;