#include <iostream>
#include <vector>
#include <string>

#include "Experiment.h"

using namespace std;

int main() {
    vector<Experiment> experiments;
    int choice;

    // const string filename = "results.CSV";
    const string filename = "results.CSV";

    loadFromCSV(experiments, filename);

    while (true) {
        showMenu();
        cin >> choice;

        if (choice == 1) {
            addExperiment(experiments);
            saveToCSV(experiments, filename);
        } else if (choice == 2) {
            showExperiments(experiments);
        } else if (choice == 3) {
            searchExperimentByModel(experiments);
        } else if (choice == 4) {
            saveToCSV(experiments, filename);
        } else if (choice == 5) {
            loadFromCSV(experiments, filename);
        } else if (choice == 6) {
            sortByASR(experiments);
        } else if (choice == 7) {
            deleteExperiment(experiments);
            saveToCSV(experiments, filename);
        } else if (choice == 8) {
            modifyExperiment(experiments);
            saveToCSV(experiments, filename);
        } else if (choice == 0) {
            saveToCSV(experiments, filename);
            cout << "系统已退出，实验记录已保存。" << endl;
            break;
        } else {
            cout << "输入错误，请重新选择。" << endl;
        }
    }

    return 0;
}