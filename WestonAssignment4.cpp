#include <iostream>
#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/split.hpp>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <unordered_map>
#include "OptimalContainer.cpp"


/* Sets up data input files and populates collection of bids */
void setupFileInput(int &totalLength, vector<double> &bids);

/* Populates table by comparing prospective bid to alternatives */
void populateTable
        (int totalLength, vector<double> &bids,
         unordered_map<int, OptimalContainer> &optimumLookupTable);


using namespace std;


/**
 * This function is the driver for the WestonAssignment4 class.
 * It parses the shipping container's maximum length and
 * prospective bids, populates a dynamic programming table of
 * OptimalContainers, and prints key information about the specified
 * container.
 *
 * @return is an integer representing the exit code of the program.
 */
int main() {
    int totalLength = -1;
    vector<double> bids;

    setupFileInput(totalLength, bids);

    //dynamic programming table
    unordered_map<int, OptimalContainer> optimumLookupTable;

    populateTable(totalLength, bids, optimumLookupTable);

    optimumLookupTable.at(totalLength).printOptimalContainer();
}


/**
 * This function iteratively populates the dynamic programming table
 * to optimize a shipping container of specified length.
 *
 * @param totalLength represents the maximum possible length of the
 * shipping container.
 * @param bids is a collection of possible bids to include in the
 * shipping container.
 * @param optimumLookupTable is the data structure that maintains
 * previously optimized (smaller) containers for comparison.
 */
void populateTable(int totalLength,
                   vector<double> &bids,
                   unordered_map<int, OptimalContainer>
                   &optimumLookupTable) {
    //individually insert 1' bid (special case guaranteed to be best)
    OptimalContainer oneFootLength = OptimalContainer(1, bids.at(0));
    optimumLookupTable.insert(make_pair(1, oneFootLength));
    optimumLookupTable.at(1).setComponents(oneFootLength);

    //build lookup table
    for (int i = 2; i <= totalLength; i++) {

        //insert the bid for a given length as the max value to beat
        OptimalContainer initialContainer =
                OptimalContainer(i, bids.at(i - 1));
        initialContainer.setComponents(initialContainer);
        optimumLookupTable.insert(make_pair(i, initialContainer));

        //j initialized to avoid rechecking length combinations
        for (int j = ((i - 1) / 2) + 1; j > 0; j--) {
            if (optimumLookupTable.at(i).getValue() <
                optimumLookupTable.at(i - j).getValue() +
                optimumLookupTable.at(j).getValue()) {
                optimumLookupTable.erase(i);
                OptimalContainer betterContainer =
                        OptimalContainer
                                (i,
                                 optimumLookupTable.at(i - j).
                                         getValue() +
                                 optimumLookupTable.at(j).getValue());
                betterContainer.
                        setComponents(optimumLookupTable.at(i - j).
                                              getComponents(),
                                      optimumLookupTable.at(j).
                                              getComponents());

                optimumLookupTable.insert
                        (make_pair(i, betterContainer));
            }
        }
    }
}


/**
 * This function reads the length of the shipping container and
 * available bids from file.
 *
 * @param totalLength represents the maximum possible length of the
 * shipping container.
 * @param bids is a collection of possible bids to include in the
 * shipping container.
 */
void setupFileInput(int &totalLength, vector<double> &bids) {
    string line1;
    string line2;
    ifstream myfile;

    myfile.open("file8.txt");
    vector<string> temp;

    if (myfile.is_open()) {
        getline(myfile, line1);
        totalLength = (boost::lexical_cast<int>(line1));

        getline(myfile, line2);
        bids.clear();
        split(temp, line2, boost::is_any_of(" "));
        for (const auto &s: temp)
            bids.push_back(boost::lexical_cast<double>(s));
        myfile.close();
    } else {
        cout << "Unable to open file";
        myfile.close();
    }
}