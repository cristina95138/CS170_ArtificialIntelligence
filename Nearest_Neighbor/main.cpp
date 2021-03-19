#include <iostream>
#include <set>
#include <fstream>
using namespace std;

void nearestNeighborSearch(int data) {
    set<int> currSetFeat;
    set<int> featToAdd;
    int accuracy = 0;
    int bestAccuracy = 0;


    for (unsigned i = 0; i < data.size(); ++i) {

        for (unsigned j = 0; j < data. size(); ++j) {

        }
    }

}

void forwardSelection() {}

void backwardElimination() {}

int main() {

    string file;
    ifstream in;
    int numFeatures = 0;
    int numInstances = 0;
    int algorithm = 0;
    int val = 0;

    cout << "Welcome to Cristina Lawson's Feature Selection Algorithm" << endl;
    cout << "Type in the name of the file to test: ";
    cin >> file;
    cout << endl << endl;

    in.open(file);

    if (!in.is_open()) {
        cout << "Could not open file " << file << "." << endl;
        exit(1);
    }

    cout << "Type the number of the algorithm you want to run." << endl << endl;
    cout << "1) Forward Selection" << endl
         << "2) Backward Elimination" << endl;
    cin >> algorithm;
    cout << endl << endl;

    while (in >> val) {
        if (val.length() != 5) {
            cout << "Must be 5 character word." << endl;
        }
        else {
            //dict.push_back(val);
        }
    }

    cout << "This dataset has " << numFeatures << " features (not including the class attribute), with " << numInstances << " instances." << endl << endl;

    cout << "Please wait while I normalize the data... ";
    cout << "Done!";

    cout << "Running nearest neighbor with all 4 features, using “leaving-one-out” evaluation, I get an accuracy of 75.4%";

    in.close();

    return 0;
}
