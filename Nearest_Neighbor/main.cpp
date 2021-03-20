#include <iostream>
#include <set>
#include <fstream>
#include <sstream>
#include <vector>
#include <utility>
#include <math.h>
#include <unordered_map>
#include <algorithm>
#include <chrono>

using namespace std;

double leave_one_out_cross_validation(vector<pair<int, vector<double>>> data, set<int> featToAdd, int numVals, int rows) {
    double numCorrClass = 0.0;
    double nnDist = 0.0;
    double nnLoc = 0.0;
    double nnLab = 0.0;
    double dist = 0.0;
    double accuracy = 0.0;
    double sum = 0.0;

    // Makes non-included columns 0.0
    for (double k = 1; k <= numVals; ++k) {
        if (featToAdd.find(k) == featToAdd.end()) {
            for (double l = 0; l < data[k].second.size(); ++l) {
                data[k].second[l] = 0.0;
            }
        }
    }

    // Iterate thorough all rows and compute the Euclidean Distance
    for (double i = 0; i < rows; ++i) {
        // Assign object labels and attributes
        vector<double> objToClass;
        double labObjToClass = data[0].second[i];

        for (double a = 1; a <= numVals; ++a) {
            objToClass.push_back(data[a].second[i]);
        }

        nnDist = INT_MAX;
        nnLoc = INT_MAX;

        for (double j = 0; j < rows; ++j) {
            dist = 0;
            sum = 0;

            // If the rows aren't equal then compute the distance
            if (i != j) {
                vector<double> obj;

                for (double b = 1; b <= numVals; ++b) {
                   obj.push_back(data[b].second[j]);
                }

                // Euclidean Distance computation
                for (double c = 0; c < objToClass.size(); ++c) {
                    sum += pow(objToClass[c] - obj[c], 2);
                }
                dist = sqrt(sum);

                // Find closest neighbor based on distance
                if (dist <= nnDist) {
                    nnDist = dist;
                    nnLoc = j + 1;
                    nnLab = data[0].second[nnLoc-1];
                }
            }
        }

        // Check if the class labels are the same
        if (labObjToClass == nnLab) {
            ++numCorrClass;
        }
    }

    // Compute accuracy based on the percentage of correct labels
    accuracy = (numCorrClass/rows) * 100.0;

    return accuracy;
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
            // If the column is not in the data structure then add it
            if (currSetFeat.find(j) == currSetFeat.end()) {
                featToAdd = currSetFeat;
                // Add the row
                featToAdd.insert(j);

                // Calculate distance accuracy
                accuracy = leave_one_out_cross_validation(data, featToAdd, numVals, rows);

                // Output all possible accuracies
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
                cout << "} accuracy is " << fixed << setprecision(1) << accuracy << "%" << endl;

                // Find best accuracy
                if (accuracy >= bestAccuracy) {
                    bestAccuracy = accuracy;
                    bestFeat = j;
                }
            }
        }
        cout << endl;
        // Insert best accuracy
        currSetFeat.insert(bestFeat);

        // Output that the accuracy has lowered
        if (best.size() > 1) {
            if (best[i - 1] > bestAccuracy) {
                cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl << endl;
            }
        }

        // Output the best of the calculated sets iterated above
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
        cout << "} was best, accuracy is " << fixed << setprecision(1) << bestAccuracy << "%" << endl << endl;

        // Unordered map of best accuracies from above
        max[bestAccuracy] = currSetFeat;
        // Vector so that we can find the best accuracy for output once the map is fully populated
        best.push_back(bestAccuracy);
    }

    // Find the maximum accuracy
    double maxAcc = *max_element(best.begin(), best.end());

    // Output the absolute best accuracy
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
    cout << "}, which has an accuracy of " << fixed << setprecision(1) << maxAcc << "%" << endl << endl;

    // Output the absolute best accuracy again
    cout << "Running nearest neighbor with all " << numVals << " features, using “leaving-one-out” evaluation, I get an accuracy of " << fixed << setprecision(1) << maxAcc << "%";
}

void backwardElimination(vector<pair<int, vector<double>>> data, int numVals, int rows) {
    set<int> currSetFeat;
    set<int> featToAdd;
    double accuracy = 0.0;
    double bestAccuracy = 0.0;
    double bestFeat = 0.0;
    vector<int> best;
    unordered_map<int, set<int>> max;

    // Add columns to vector
    for (unsigned a = 1; a <= numVals; ++a) {
        currSetFeat.insert(a);
    }

    featToAdd = currSetFeat;

    // Calculate distance accuracy
    accuracy = leave_one_out_cross_validation(data, featToAdd, numVals, rows);

    cout << "Beginning search." << endl << endl;

    // Output all possible accuracies
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
    cout << "} accuracy is " << fixed << setprecision(1) << accuracy << "%" << endl << endl;

    // Output the best of the calculated sets iterated above
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
    cout << "} was best, accuracy is " << fixed << setprecision(1) << accuracy << "%" << endl << endl;

    for (unsigned i = 2; i <= numVals; ++i) {
        bestAccuracy = 0;
        for (unsigned j = 1; j <= numVals; ++j) {
            // If the column is in the data structure then add it
            if (currSetFeat.find(j) != currSetFeat.end()) {
                featToAdd = currSetFeat;
                // Erase the row
                featToAdd.erase(j);

                // Calculate distance accuracy
                accuracy = leave_one_out_cross_validation(data, featToAdd, numVals, rows);

                // Output all possible accuracies
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
                cout << "} accuracy is " << fixed << setprecision(1) << accuracy << "%" << endl;

                // Find worst accuracy
                if (accuracy >= bestAccuracy) {
                    bestAccuracy = accuracy;
                    bestFeat = j;
                }
            }
        }
        cout << endl;
        // Erase worst accuracy
        currSetFeat.erase(bestFeat);

        // Output that the accuracy has lowered
        if (best.size() > 1) {
            if (best[i - 1] > bestAccuracy) {
                cout << "(Warning, Accuracy has decreased! Continuing search in case of local maxima)" << endl << endl;
            }
        }

        // Output the best of the calculated sets iterated above
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
        cout << "} was best, accuracy is " << fixed << setprecision(1) << bestAccuracy << "%" << endl << endl;

        // Unordered map of best accuracies from above
        max[bestAccuracy] = currSetFeat;
        // Vector so that we can find the best accuracy for output once the map is fully populated
        best.push_back(bestAccuracy);
    }

    // Find the maximum accuracy
    double maxAcc = *max_element(best.begin(), best.end());

    // Output the absolute best accuracy
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
    cout << "}, which has an accuracy of " << fixed << setprecision(1) << maxAcc << "%" << endl << endl;

    // Output the absolute best accuracy again
    cout << "Running nearest neighbor with all " << numVals << " features, using “leaving-one-out” evaluation, I get an accuracy of " << fixed << setprecision(1) << maxAcc << "%";
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
    vector<pair<int, vector<double>>> data; // Data structure for file data

    cout << "Welcome to Cristina Lawson's Feature Selection Algorithm" << endl;
    cout << "Type in the name of the file to test: ";
    cin >> file;
    cout << endl;

    // Reading in the file
    // Referenced https://www.gormanalysis.com/blog/reading-and-writing-csv-files-with-cpp/
    in.open(file);

    if (!in.is_open()) {
        cout << "Could not open file " << file << "." << endl;
        exit(1);
    }

    // Creating column in data vector data structure
    if (in.good()) {
        getline(in, line);
        stringstream ss(line);
        while(ss >> num) {
            data.push_back({colNum, vector<double>{}});
            ++colNum;
        }
    }

    // Restarting getline
    in.clear();
    in.seekg(0, ios::beg);

    // Reading in rows data into the data structure
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
    cout << endl;

    numFeatures = colNum - 1;
    numInstances = numVals - rows;

    cout << "This dataset has " << numFeatures << " features (not including the class attribute), with " << numInstances << " instances." << endl << endl;

    cout << "Please wait while I normalize the data... ";
    cout << "Done!" << endl << endl;

    // Program timer
    auto start = chrono::steady_clock::now();

    if (algorithm == 1) {
        forwardSelection(data, numFeatures, rows);
    } else if (algorithm == 2) {
        backwardElimination(data, numFeatures, rows);
    }

    in.close();

    auto end = chrono::steady_clock::now();

    cout << endl << endl;

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