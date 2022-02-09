#include "bloomFilter.h"
#include "hash.h"
#include "testHash.h"
#include "testBloomFilter.h"
#include <fstream>
#include <string>

using namespace std;

void testScaleFactor(ofstream &myFile, int testNum, float c, float d, string arr1[], string arr2[], string arr3[], string arr4[]);

// Make a chart about how scale factor affects efficiency
int main(int argc, char *argv[]) {

    std::ifstream myFile;
    string stringInput;
    float p(0), c(0), d(0);
    int m(0);
    myFile.open(argv[1]);

    std::cout << "Experiment for values of: " << std::endl;
    if ( getline(myFile, stringInput) )
    {
        p = std::stof(stringInput);
        std::cout << "p = " << p << std::endl;
    }

    if ( getline(myFile, stringInput) )
    {
        m = std::stoi(stringInput);
    }

    if ( getline(myFile, stringInput) )
    {
        c = std::stof(stringInput);
        std::cout << "c = " << c << std::endl;
    }

    if ( getline(myFile, stringInput) )
    {
        d = std::stof(stringInput);
        std::cout << "d = " << d << std::endl;
    }

    std::cout << "q = " << 97 << std::endl;
    std::cout << std::endl;

    myFile.close();


    myFile.open(argv[2]);
    string inputArray[10000];
    for ( int i = 0 ; i < 10000 ; i++ )
    {
        if (getline(myFile, stringInput))
            inputArray[i] = stringInput;
    }
    myFile.close();

    myFile.open(argv[3]);
    string successFind[1000];
    for ( int i = 0 ; i < 1000 ; i++ )
    {
        if (getline(myFile, stringInput))
            successFind[i] = stringInput;
    }
    myFile.close();

    myFile.open(argv[4]);
    string failFind[1000];
    for ( int i = 0 ; i < 1000 ; i++ )
    {
        if (getline(myFile, stringInput))
            failFind[i] = stringInput;
    }
    myFile.close();

    myFile.open(argv[5]);
    string removalList[1000];
    for ( int i = 0 ; i < 1000 ; i++ )
    {
        if (getline(myFile, stringInput))
            removalList[i] = stringInput;
    }
    myFile.close();

    int totalFalsePos(0), totalFalseNeg(0);
    int FalsePos(0), FalseNeg(0);
    for ( int i = 0 ; i < 10 ; i++ ) {
        std::cout << "Phase <" << i+1 << ">:" << endl;
        BloomFilter bFilter(p,m,c,d);
        for ( int j = 0 ; j < 1000 ; j++ )
            bFilter.insert(inputArray[1000*i + j]);
        
        for (int k = 0 ; k < 100 ; k++ )
        {
            if (!bFilter.find(successFind[100*i + k]))
                FalseNeg++;
            
            if (bFilter.find(failFind[100*i + k]))
                FalsePos++;
        }

        std::cout << "Number of false negatives:" << std::endl;
        std::cout << FalseNeg << std::endl;
        std::cout << "Number of false positives:" << std::endl;
        std::cout << FalsePos << std::endl;
        std::cout << "Probability of false positives:" << std::endl;
        std::cout << ((float)FalsePos / 100 ) << std::endl;

        for (int l = 0 ; l < 100 ; l++ )
        {
            if (bFilter.find(failFind[100*i + l]))
                std::cout << failFind[100*i + l] << std::endl;
        }

        for (int m = 0 ; m < 100 ; m++ )
        {
            bFilter.remove(removalList[100*i + m]);
        }

        totalFalseNeg += FalseNeg;
        totalFalsePos += FalsePos;

        FalsePos = 0;
        FalseNeg = 0;
        std::cout << std::endl;

    }

    std::cout << "Number of false negatives:" << std::endl;
    std::cout << totalFalseNeg << std::endl;
    std::cout << "Number of false positives:" << std::endl;
    std::cout << totalFalsePos << std::endl;
    std::cout << "Probability of false positives:" << std::endl;
    std::cout << ((float)totalFalsePos / 1000 ) << std::endl;

    // testBloomFilter(0.1, 7, 1, 1);
    // testHash(7);

    ofstream myFile2;
    for (int i = 0 ; i < 10 ; i++ )
    {
        testScaleFactor(myFile2,i,1,i+1,inputArray,successFind,failFind,removalList);
    }

    for (int i = 0 ; i < 10 ; i++ )
    {
        testScaleFactor(myFile2,i+10,i+1,1,inputArray,successFind,failFind,removalList);
    }


    cout << endl << " --- Program Runs Successfully --- " << endl;
    return 0;
}

void testScaleFactor(ofstream &myFile, int testNum, float c, float d, string arr1[], string arr2[], string arr3[], string arr4[]) {

    string fileName = "output";
    string number = to_string(testNum);
    fileName += number;
    fileName += ".txt";
    myFile.open(fileName);
    myFile << "c = " << c << " | " << " d = " << d << std::endl;
    int totalFalsePos(0), totalFalseNeg(0);
    int FalsePos(0), FalseNeg(0);
    for ( int i = 0 ; i < 10 ; i++ ) {
        myFile << "Phase <" << i+1 << ">:" << std::endl;
        BloomFilter bFilter(0.1,1000,c,d);
        for ( int j = 0 ; j < 1000 ; j++ )
            bFilter.insert(arr1[1000*i + j]);
        
        for (int k = 0 ; k < 100 ; k++ )
        {
            if (!bFilter.find(arr2[100*i + k]))
                FalseNeg++;
            
            if (bFilter.find(arr3[100*i + k]))
                FalsePos++;
        }

        myFile << "Number of false negatives:" << std::endl;
        myFile << FalseNeg << std::endl;
        myFile << "Number of false positives:" << std::endl;
        myFile << FalsePos << std::endl;
        myFile << "Probability of false positives:" << std::endl;
        myFile << ((float)FalsePos / 100 ) << std::endl;

        for (int l = 0 ; l < 100 ; l++ )
        {
            if (bFilter.find(arr3[100*i + l]))
                myFile << arr3[100*i + l] << std::endl;
        }

        for (int m = 0 ; m < 100 ; m++ )
        {
            bFilter.remove(arr4[100*i + m]);
        }

        totalFalseNeg += FalseNeg;
        totalFalsePos += FalsePos;

        FalsePos = 0;
        FalseNeg = 0;
        myFile << std::endl;

    }

    myFile << "Number of false negatives:" << std::endl;
    myFile << totalFalseNeg << std::endl;
    myFile << "Number of false positives:" << std::endl;
    myFile << totalFalsePos << std::endl;
    myFile << "Probability of false positives:" << std::endl;
    myFile << ((float)totalFalsePos / 1000 ) << std::endl;

    myFile.close();

}
