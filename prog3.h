#include <vector>
#include <map>
#include <iostream>
#include <fstream>
#include <sstream>
#include <queue>
#include <stdlib.h>
#include <deque>
#include <unistd.h>
#include <time.h>

using namespace std;


int NUM_BLOCKS = 8;
int NUM_SEGMENTS = 32;
int SIZE_DISK = 256;
string inputFileName = "";

int seeks = 0;
int cleanSeeks = 0;
int instCount = 0;

int headLoc = -1;

class LocationN {
    public:
        int segmentNum = -1;
        int segmentIndex = -1;
        LocationN(){

        }
        LocationN(int x, int y) {
            segmentNum = x;
            segmentIndex = y;
        }
};

map<int, map<int, LocationN>> nodeMap;

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
    	}  else {
            return -1;
        }
    	return (blocks.size() - 1);
    }
};



vector<Segment> disk;
deque<int> nodeOrder;
deque<int> filled;