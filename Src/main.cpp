//
//  main.cpp
//
//
//

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

#include "hashing.cpp"

int main(int argc, char *argv[]) {
    
    //    DECLARING VARIABLES
    int numWords = 0;
    int lineNum = 0;
    int numCollisions = 0;
    int uniqueWords = 0;
    int count;
    int dh = -1;
    bool wordHandled;
    size_t hashIndex;
    size_t index;
    size_t size = atoi(argv[3]);
    std::ifstream file;
    std::string word;
    std::string inputLine;
    HashNode* hashTable[size];
    
    for (size_t i = 0; i < size; i++) { hashTable[i] = nullptr; }
    if (argc == 6) { dh = atoi(argv[5]); }
    
    file.open(argv[1]);
    if ( ! file.is_open() ) {
        std::cout << "Text file was not found\n";
        return -1;
    }
    
//    CREATING THE HASH TABLE
    while ( getline(file, inputLine) ) {
        lineNum++;
        std::stringstream stream(inputLine);
        while (stream >> word) {
            wordHandled = false;
            count = 0;
            hashIndex =  ( hash(&word[0u]) ) % size;
            index = hashIndex;
            numWords++;
            do {
                 count++;
                if ( argc<6 ) { index = index % size; }
                if ( hashTable[index] == nullptr ) {
                    uniqueWords++;
                    hashTable[index] = new HashNode((int)index, word, lineNum);
                    wordHandled = true;
                }
                else if ( hashTable[index]->value == word ) {
                    hashTable[index]->lineNumbers = hashTable[index]->lineNumbers + ", " + std::to_string(lineNum);
                    wordHandled = true;
                }
                else {
                    numCollisions++;
                    index = handleCollision( (int)hashIndex, word, argv[4], count, dh ) % size;
                }
            } while (!wordHandled);
        }
    }
    file.close();
    
    std::cout << "The number of words found in the file was " << numWords << std::endl;
    std::cout << "The number of unique words found in the file was " << uniqueWords << std::endl;
    std::cout << "The number of collisions was " << numCollisions << std::endl;
    
    file.open(argv[2]);
    if ( ! file.is_open() ) {
        std::cout << "Query file was not opened\n";
        return -1;
    }
    
//    SEARCHING FOR THE QUERY WORDS IN THE FILE
    while (file >> word) {
        wordHandled = false;
        hashIndex =  ( hash(&word[0u]) ) % size;
        index = hashIndex;
        count = 0;
        numCollisions = 0;
        do {
            count++;
            if ( argc < 6 ) { index = index % size; }
            if (hashTable[index] == nullptr) {
                wordHandled = true;
                std::cout << "\t" << word << " appears on lines []" << std::endl;
                std::cout << "\tThe search had " << numCollisions << " collisions" << std::endl;
            }
            else if (hashTable[index]->value == word) {
                wordHandled = true;
                std::cout << "\t" << word << " appears on lines [" << hashTable[index]->lineNumbers << "]" << std::endl;
                std::cout << "\tThe search had " << numCollisions << " collisions" << std::endl;
            }
            else {
                numCollisions++;
                index = handleCollision((int)hashIndex, word, argv[4], count, dh) % size;
            }
        } while (!wordHandled);
        std::cout << std::endl;
    }
    file.close();
    
//    DELETING THE HASH TABLE AT THE END OF THE PROGRAM
    for (size_t i = 0; i < size; i++) {
        delete hashTable[i];
    }
    
    return 0;
}
