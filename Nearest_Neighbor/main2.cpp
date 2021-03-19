//
// Created by Cristina Lawson on 3/19/21.
//

#include <iostream>
#include <set>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <math.h>
#include <unordered_map>
#include <chrono>
using namespace std;

double leave_one_out_cross_validation(vector<pair<int, vector<double>>> data, set<int> featToAdd, int numVals, int rows) {
    double numCorrClass = 0.0;
    int nnDist = 0;
    int nnLoc = 0;
    int nnLab = 0;
    int dist = 0;
    double accuracy = 0.0;
    int sum = 0;

    for (unsigned k = 1; k <= numVals; ++k) {
        if (featToAdd.find(k) == featToAdd.end()) {
            for (unsigned l = 0; l < data[k].second.size(); ++l) {
                data[k].second[l] = 0;
            }
        }
    }

    for (unsigned i = 0; i < rows; ++i) {
        vector<double> objToClass;
        int labObjToClass = data[0].second[i];

        for (unsigned a = 1; a <= numVals; ++a) {
            objToClass.push_back(data[a].second[i]);
        }

        nnDist = INT_MAX;
        nnLoc = INT_MAX;
        for (unsigned j = 0; j < rows; ++j) {
            dist = 0;
            if (i != j) {
                for (unsigned b = 1; b <= numVals; ++b) {
                    sum += pow(objToClass[b] - data[b].second[j], 2);
                }
                dist = sqrt(sum);
                if (dist <= nnDist) {
                    nnDist = dist;
                    nnLoc = j + 1;
                    nnLab = data[0].second[nnLoc-1];
                }
            }
        }

        if (labObjToClass == nnLab) {
            ++numCorrClass;
        }
    }

    accuracy = (numCorrClass/rows) * 100;

    return accuracy;
}

void forwardSelectionThread1(vector<pair<int, vector<double>>> data, int numVals, int rows) {
    forwardSelectionTemplate(data, numVals, rows, 0, 100);
}

void forwardSelectionThread2(vector<pair<int, vector<double>>> data, int numVals, int rows) {

}

void forwardSelectionThread3(vector<pair<int, vector<double>>> data, int numVals, int rows) {

}

void forwardSelectionThread4(vector<pair<int, vector<double>>> data, int numVals, int rows) {

}

void forwardSelectionTemplate(vector<pair<int, vector<double>>> data, int numVals, int rows, int start, int end) {
    set<int> currSetFeat;
    set<int> featToAdd;
    vector<int> best;
    double accuracy = 0.0;
    double bestAccuracy = 0.0;
    double bestFeat = 0.0;
    unordered_map<int, set<int>> max;

    cout << "Beginning search." << endl << endl;

    for (unsigned i = 1; i <= numVals; ++i) {
        bestAccuracy = 0;
        for (unsigned j = 1; j <= numVals; ++j) {
            if (currSetFeat.find(j) == currSetFeat.end()) {
                featToAdd = currSetFeat;
                featToAdd.insert(j);

                accuracy = leave_one_out_cross_validation(data, featToAdd, numVals, rows);

                cout << "   Using feature(s) {";
                for (auto k = featToAdd.begin(); k != featToAdd.end(); ++k) {
                    auto it = featToAdd.end();
                    --it;
                    if (k == it) {
                        cout << *k;
                    } else {
                        cout << *k << ",";
                    }
                }
                cout << "} accuracy is " << accuracy << "%" << endl;

                if (accuracy >= bestAccuracy) {
                    bestAccuracy = accuracy;
                    bestFeat = j;
                }
            }
        }
        cout << endl;
        currSetFeat.insert(bestFeat);

        if (best.size() > 1) {
            if (best[i - 1] > bestAccuracy) {
                cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl << endl;
            }
        }

        cout << "Feature set {";
        for (auto k = currSetFeat.begin(); k != currSetFeat.end(); ++k) {
            auto it = currSetFeat.end();
            --it;
            if (k == it) {
                cout << *k;
            } else {
                cout << *k << ",";
            }
        }
        cout << "} was best, accuracy is " << bestAccuracy << "%" << endl << endl;
        max[bestAccuracy] = currSetFeat;
        best.push_back(bestAccuracy);
    }

    double maxAcc = *max_element(best.begin(), best.end());

    cout << "Finished search!! The best feature subset is {";
    for (auto k = max[maxAcc].begin(); k != max[maxAcc].end(); ++k) {
        auto it = max[maxAcc].end();
        --it;
        if (k == it) {
            cout << *k;
        } else {
            cout << *k << ",";
        }
    }
    cout << "}, which has an accuracy of " << maxAcc << "%" << endl << endl;

    cout << "Running nearest neighbor with all " << numVals << " features, using “leaving-one-out” evaluation, I get an accuracy of " << maxAcc << "%";
}


void forwardSelection(vector<pair<int, vector<double>>> data, int numVals, int rows) {
    set<int> currSetFeat;
    set<int> featToAdd;
    vector<int> best;
    double accuracy = 0.0;
    double bestAccuracy = 0.0;
    double bestFeat = 0.0;
    unordered_map<int, set<int>> max;

    cout << "Beginning search." << endl << endl;

    for (unsigned i = 1; i <= numVals; ++i) {
        bestAccuracy = 0;
        for (unsigned j = 1; j <= numVals; ++j) {
            if (currSetFeat.find(j) == currSetFeat.end()) {
                featToAdd = currSetFeat;
                featToAdd.insert(j);

                accuracy = leave_one_out_cross_validation(data, featToAdd, numVals, rows);

                cout << "   Using feature(s) {";
                for (auto k = featToAdd.begin(); k != featToAdd.end(); ++k) {
                    auto it = featToAdd.end();
                    --it;
                    if (k == it) {
                        cout << *k;
                    } else {
                        cout << *k << ",";
                    }
                }
                cout << "} accuracy is " << accuracy << "%" << endl;

                if (accuracy >= bestAccuracy) {
                    bestAccuracy = accuracy;
                    bestFeat = j;
                }
            }
        }
        cout << endl;
        currSetFeat.insert(bestFeat);

        if (best.size() > 1) {
            if (best[i - 1] > bestAccuracy) {
                cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl << endl;
            }
        }

        cout << "Feature set {";
        for (auto k = currSetFeat.begin(); k != currSetFeat.end(); ++k) {
            auto it = currSetFeat.end();
            --it;
            if (k == it) {
                cout << *k;
            } else {
                cout << *k << ",";
            }
        }
        cout << "} was best, accuracy is " << bestAccuracy << "%" << endl << endl;
        max[bestAccuracy] = currSetFeat;
        best.push_back(bestAccuracy);
    }

    double maxAcc = *max_element(best.begin(), best.end());

    cout << "Finished search!! The best feature subset is {";
    for (auto k = max[maxAcc].begin(); k != max[maxAcc].end(); ++k) {
        auto it = max[maxAcc].end();
        --it;
        if (k == it) {
            cout << *k;
        } else {
            cout << *k << ",";
        }
    }
    cout << "}, which has an accuracy of " << maxAcc << "%" << endl << endl;

    cout << "Running nearest neighbor with all " << numVals << " features, using “leaving-one-out” evaluation, I get an accuracy of " << maxAcc << "%";
}

void backwardElimination(vector<pair<int, vector<double>>> data, int numVals, int rows) {
    set<int> currSetFeat;
    set<int> featToAdd;
    double accuracy = 0.0;
    double bestAccuracy = 0.0;
    double bestFeat = 0.0;
    vector<int> best;
    unordered_map<int, set<int>> max;

    for (unsigned a = 1; a <= numVals; ++a) {
        currSetFeat.insert(a);
    }

    featToAdd = currSetFeat;
    accuracy = leave_one_out_cross_validation(data, featToAdd, numVals, rows);

    cout << "Beginning search." << endl << endl;

    cout << "   Using feature(s) {";
    for (auto k = featToAdd.begin(); k != featToAdd.end(); ++k) {
        auto it = featToAdd.end();
        --it;
        if (k == it) {
            cout << *k;
        } else {
            cout << *k << ",";
        }
    }
    cout << "} accuracy is " << accuracy << "%" << endl << endl;
    cout << "Feature set {";
    for (auto k = featToAdd.begin(); k != featToAdd.end(); ++k) {
        auto it = featToAdd.end();
        --it;
        if (k == it) {
            cout << *k;
        } else {
            cout << *k << ",";
        }
    }
    cout << "} was best, accuracy is " << accuracy << "%" << endl << endl;

    for (unsigned i = 1; i <= numVals; ++i) {
        bestAccuracy = 0;
        for (unsigned j = 1; j <= numVals; ++j) {
            if (currSetFeat.find(j) != currSetFeat.end()) {
                featToAdd = currSetFeat;
                featToAdd.erase(j);

                accuracy = leave_one_out_cross_validation(data, featToAdd, numVals, rows);

                cout << "   Using feature(s) {";
                for (auto k = featToAdd.begin(); k != featToAdd.end(); ++k) {
                    auto it = featToAdd.end();
                    --it;
                    if (k == it) {
                        cout << *k;
                    } else {
                        cout << *k << ",";
                    }
                }
                cout << "} accuracy is " << accuracy << "%" << endl;

                if (accuracy >= bestAccuracy) {
                    bestAccuracy = accuracy;
                    bestFeat = j;
                }
            }
        }
        cout << endl;
        currSetFeat.erase(bestFeat);

        if (best.size() > 1) {
            if (best[i - 1] > bestAccuracy) {
                cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl << endl;
            }
        }

        cout << "Feature set {";
        for (auto k = currSetFeat.begin(); k != currSetFeat.end(); ++k) {
            auto it = currSetFeat.end();
            --it;
            if (k == it) {
                cout << *k;
            } else {
                cout << *k << ",";
            }
        }
        cout << "} was best, accuracy is " << bestAccuracy << "%" << endl << endl;
        max[bestAccuracy] = currSetFeat;
        best.push_back(bestAccuracy);
    }

    double maxAcc = *max_element(best.begin(), best.end());

    cout << "Finished search!! The best feature subset is {";
    for (auto k = max[maxAcc].begin(); k != max[maxAcc].end(); ++k) {
        auto it = max[maxAcc].end();
        --it;
        if (k == it) {
            cout << *k;
        } else {
            cout << *k << ",";
        }
    }
    cout << "}, which has an accuracy of " << maxAcc << "%" << endl << endl;

    cout << "Running nearest neighbor with all " << numVals << " features, using “leaving-one-out” evaluation, I get an accuracy of " << maxAcc << "%";
}

int main() {
    string file;
    ifstream in;
    int numFeatures = 0;
    int numInstances = 0;
    int algorithm = 0;
    string val;
    double valDouble = 0.0;
    string num;
    string line;
    string col = "0";
    int colNum = 0;
    int numVals = 0;
    int index = 0;
    int rows = 0;
    vector<pair<int, vector<double>>> data;

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
        while(ss >> num) {
            data.push_back({colNum, vector<double>{}});
            ++colNum;
        }
    }

    in.clear();
    in.seekg(0, ios::beg);

    while(getline(in, line)) {
        stringstream ss(line);
        index = 0;

        while(ss >> val) {
            valDouble = stod(val);
            data.at(index).second.push_back(valDouble);

            if (ss.peek() == ',') {
                ss.ignore();
            }

            ++index;
            ++numVals;
        }
        ++rows;
    }

    cout << "Type the number of the algorithm you want to run." << endl << endl;
    cout << "1) Forward Selection" << endl
         << "2) Backward Elimination" << endl;
    cin >> algorithm;
    cout << endl << endl;

    numFeatures = colNum - 1;
    numInstances = numVals - rows;

    cout << "This dataset has " << numFeatures << " features (not including the class attribute), with " << numInstances << " instances." << endl << endl;

    cout << "Please wait while I normalize the data... ";
    cout << "Done!" << endl;

    auto start = chrono::steady_clock::now();

    if (algorithm == 1) {
        forwardSelection(data, numFeatures, rows);
    } else if (algorithm == 2) {
        backwardElimination(data, numFeatures, rows);
    }

    in.close();

    auto end = chrono::steady_clock::now();

    cout << "CPU time in nanoseconds: "
         << chrono::duration_cast<chrono::nanoseconds>(end - start).count()
         << " ns" << endl;

    cout << "CPU time in microseconds: "
         << chrono::duration_cast<chrono::microseconds>(end - start).count()
         << " µs" << endl;

    cout << "CPU time in seconds: "
         << chrono::duration_cast<chrono::seconds>(end - start).count()
         << " secs" << endl;

    cout << "CPU time in minutes: "
         << chrono::duration_cast<chrono::minutes>(end - start).count()
         << " mins" << endl;

    return 0;
}