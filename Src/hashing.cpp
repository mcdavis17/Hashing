//
//  hashing.cpp
//  Hashing
//
//
//

//CLASS TO CREATE HASHNODE OBJECTS TO STORE THE NECESSARY VALUES OF EACH NODE
class HashNode {
public:
    int key;
    std::string value;
    std::string lineNumbers;
    HashNode* next;
    
    HashNode() { key = -1; }
    
    HashNode(int k, std::string v, int lineNumber) {
        key = k;
        value = v;
        lineNumbers += std::to_string(lineNumber);
    }
    
};

//DJB2 HASH FUNCTION (http://www.cse.yorku.ca/~oz/hash.html)
unsigned long hash(char *str) {
    unsigned long hash = 5381;
    int c;
    
    while ( (c = *str++) ) {
        hash = ( (hash << 5) + hash) + c;
    }
    
    return hash;
}

//HANDLES COLLISIONS WHEN INSERTING & SEARCHING
int handleCollision(int currIndex, std::string word, std::string probeMethod, int i, int dhash) {
        if (probeMethod == "lp") {
            currIndex += i;
        }
        if (probeMethod == "qp") {
            currIndex = currIndex + (i * i);
        }
        if (probeMethod == "dh") {
            currIndex = ( (dhash - (currIndex % dhash)) * i ) + currIndex;
        }
    return currIndex;
}
