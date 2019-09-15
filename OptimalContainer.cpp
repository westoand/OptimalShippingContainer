#include <string>
#include <vector>
#include <iostream>
#include <algorithm>
#include <iomanip>

using namespace std;


/**********************************************************************
* This class represents a shipping container of specified length.
* The shipping container is designed to be optimized for maximum value
* given bids for the sale of incremental lengths.  The object maintains
* a collection of "components" or other OptimalContainer objects
* that comprise "this" OptimalContainer (ex. a 4' container has both a
* 1' OptimalContainer and 3' OptimalContainer as "sub-components".
*
*
* @author Andrew Weston
* @version Spring 2019
**********************************************************************/
class OptimalContainer {

public:


/**
 * OptimalContainer objects represent shipping containers of specified
 * length and value.
 *
 * @param length represents the length of the shipping container.
 * @param value represents the total dollar value of component bids.
 */
    OptimalContainer(int length, double value) {
        this->length = length;
        this->value = value;
    }


/**
 * This function sets the collection of OptimalContainers that comprise
 * "this" OptimalContainer.
 *
 * @param subComponents1 is a collection of OptimalContainers in "this"
 * container.
 * @param subComponents2 is a collection of OptimalContainers in "this"
 * container.
 */
    void setComponents(const vector<OptimalContainer> &subComponents1,
                       const vector<OptimalContainer> &subComponents2) {
        for (const auto &e: subComponents1)
            components.push_back(e);

        for (const auto &e: subComponents2)
            components.push_back(e);

        sort(components.begin(), components.end());
    }

    /**
    * This function sets the collection of OptimalContainers in
    * "this" OptimalContainer.
    *
    * @param newlyAdded is an OptimalContainer component of "this"
    * OptimalContainer.
    */
    void setComponents(OptimalContainer &newlyAdded) {
        components.push_back(newlyAdded);
    }


/**
 * This function accesses the collection of OptimalContainers that
 * comprise an OptimalContainer.
 *
 * @return vector<OptimalContainer> representing the group of smaller
 * OptimalContainers that comprise "this" OptimalContainer.
 */
    vector<OptimalContainer> getComponents() {
        return components;
    }


/**
 * This function accesses the total dollar value of bids of an
 * OptimalContainer object.
 *
 * @return double representation of the total dollar value of the bids
 * in the specified OptimalContainer.
 */
    double getValue() {
        return value;
    }

/**
 * This function prints the value and combination of bids in an
 * OptimalContainer.
 *
 */
    void printOptimalContainer() {
        string containerStr = "Length(s): ";
        for (const auto &c:components)
            containerStr += to_string(c.length) + ", ";

        //remove excess space and comma
        containerStr = containerStr.substr
                (0, containerStr.length() - 2);

        cout << "The optimal set of bids is worth: $" <<
             fixed << setprecision(2) << value << endl;
        cout << containerStr << endl;
    }


/**
 * This function defines the ordering of OptimalContainers based
 * on length.
 *
 * @param rhs the target OptimalContainer for comparison.
 * @return bool representing whether "this" OptimalContainer is
 * less than the parameter OptimalContainer.
 */
    bool operator<(const OptimalContainer &rhs) const {
        return this->length < rhs.length;
    }

private:

    /* The OptimalContainer's length */
    int length;

    /* The OptimalContainer's total value of all bids */
    double value;

    /* The OptimalContainers that make-up "this OptimalContainer */
    vector<OptimalContainer> components;
};
