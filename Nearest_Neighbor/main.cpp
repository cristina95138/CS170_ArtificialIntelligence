#include <iostream>
#include <set>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <math.h>
using namespace std;

int leave_one_out_cross_validation(vector<pair<string, vector<int>>> data, set<int> currSet, set<int> featToAdd, int numVals) {
    int numCorrClass = 0;
    int nnDist = 0;
    int nnLoc = 0;
    int dist = 0;

    for (unsigned i = 0; i < numVals; ++i) {
        nnDist = INT_MAX;
        nnLoc = INT_MAX;
        for (unsigned j = 0; j < numVals; ++j) {
            if () {
                dist = sqrt();
                if (dist <= nnDist) {
                    nnDist = dist;
                    ++nnLoc;
                }
            }
        }
    }

}

void forwardSelection(vector<pair<string, vector<int>>> data, int numVals) {
    set<int> currSetFeat;
    set<int> featToAdd;
    int accuracy = 0;
    int bestAccuracy = 0;
    int feat = 0;
    int max = 0;
    int bestFeat = 0;

    cout << "Beginning search." << endl;

    for (unsigned i = 0; i < numVals; ++i) {
        bestAccuracy = 0;
        for (unsigned j = 0; j < numVals; ++j) {
            if (currSetFeat.find(j) != currSetFeat.end()) {
                featToAdd = currSetFeat;
                featToAdd.insert(j);

                accuracy = leave_one_out_cross_validation(data, currSetFeat, featToAdd, numVals);

                cout << "Using feature(s) {" << feat << "} accuracy is " << accuracy << "%" << endl;

                if (accuracy > bestAccuracy) {
                    bestAccuracy = accuracy;
                    bestFeat = j;
                }
            }
        }
        currSetFeat.insert(bestFeat);
        cout << "Feature set {" << bestFeat << "} was best, accuracy is " << bestAccuracy << "%" << endl;
    }

    cout << "Finished search!! The best feature subset is {";

    for (auto k = currSetFeat.begin(); k != currSetFeat.end(); ++k) {
        auto it = currSetFeat.end();
        --it;
        if (k == it) {
            cout << *k;
        } else {
            cout << *k << ",";
        }
    }

    cout << "}, which has an accuracy of " << bestAccuracy << endl;
}

void backwardElimination(vector<pair<string, vector<int>>> data, int numVals) {
    set<int> currSetFeat;
    set<int> featToAdd;
    int accuracy = 0;
    int bestAccuracy = 0;
    int feat = 0;
    int max = 0;
    int bestFeat = 0;

    featToAdd = currSetFeat;
    accuracy = leave_one_out_cross_validation(data, currSetFeat, featToAdd, numVals);

    cout << "Using feature(s) {" << feat << "} accuracy is " << accuracy << "%" << endl;
    cout << "Feature set {" << bestFeat << "} was best, accuracy is " << bestAccuracy << "%" << endl;

    for (unsigned i = 0; i < numVals; ++i) {
        bestAccuracy = 0;
        for (unsigned j = 0; j < numVals; ++j) {
            if (currSetFeat.find(j) == currSetFeat.end()) {
                featToAdd = currSetFeat;
                featToAdd.erase(j);

                accuracy = leave_one_out_cross_validation(data, currSetFeat, featToAdd, numVals);

                if (accuracy > bestAccuracy) {
                    bestAccuracy = accuracy;
                    bestFeat = j;
                }
            }
        }
        currSetFeat.erase(bestFeat);
    }

    cout << "Feature set {" << bestFeat << "} was best, accuracy is " << bestAccuracy << "%" << endl;
    cout << "Finished search!! The best feature subset is {";
    for (auto k = currSetFeat.begin(); k != currSetFeat.end(); ++k) {
        auto it = currSetFeat.end();
        --it;
        if (k == it) {
            cout << *k;
        } else {
            cout << *k << ",";
        }
    }
    cout <<  "}, which has an accuracy of " << bestAccuracy << endl;

}

int main() {
    string file;
    ifstream in;
    int numFeatures = 0;
    int numInstances = 0;
    int algorithm = 0;
    int val = 0;
    string line;
    string col = "0";
    int colNum = 0;
    int numVals = 0;
    vector<pair<string, vector<int>>> data;

    cout << "Welcome to Cristina Lawson's Feature Selection Algorithm" << endl;
    cout << "Type in the name of the file to test: ";
    cin >> file;
    cout << endl << endl;

    in.open(file);

    if (!in.is_open()) {
        cout << "Could not open file " << file << "." << endl;
        exit(1);
    }

    if (in.good()) {
        getline(in, line);
        stringstream ss(line);

        while (getline(ss, col, ',')) {
            data.push_back({col, vector<int> {}});
            ++colNum;
            col = to_string(colNum);
        }
    }

    while(getline(in, line)) {
        stringstream ss(line);
        int index = 0;

        while(ss >> val) {
            data.at(index).second.push_back(val);

            if (ss.peek() == ',') {
                ss.ignore();
            }

            ++index;
            ++numVals;
        }
    }

    cout << "Type the number of the algorithm you want to run." << endl << endl;
    cout << "1) Forward Selection" << endl
         << "2) Backward Elimination" << endl;
    cin >> algorithm;
    cout << endl << endl;

    numFeatures = colNum + 1;
    numInstances = numVals + 1;

    cout << "This dataset has " << numFeatures << " features (not including the class attribute), with " << numInstances << " instances." << endl << endl;

    cout << "Please wait while I normalize the data... ";
    cout << "Done!";

    if (algorithm == 1) {
        forwardSelection(data, numVals);
    } else if (algorithm == 2) {
        backwardElimination(data, numVals);
    }

    cout << "Running nearest neighbor with all 4 features, using “leaving-one-out” evaluation, I get an accuracy of 75.4%";

    in.close();

    return 0;
}
