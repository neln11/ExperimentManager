#ifndef EXPERIMENT_H
#define EXPERIMENT_H

#include <string>
#include <vector>

struct Experiment {
    std::string name;        // 实验名称
    std::string model;       // 模型名称
    std::string dataset;     // 数据集名称
    double cleanSR;     // 干净任务成功率
    double asr;         // 攻击成功率
    double targetSR;    // 目标任务成功率
    std::string note;        // 备注
};

// 菜单
void showMenu();

// 基本功能
void addExperiment(std::vector<Experiment>& experiments);
void showExperiments(const std::vector<Experiment>& experiments);
void searchExperimentByModel(const std::vector<Experiment>& experiments);

// CSV 文件读写
void saveToCSV(const std::vector<Experiment>& experiments, const std::string& filename);
void loadFromCSV(std::vector<Experiment>& experiments, const std::string& filename);

// 排序、删除、修改
void sortByASR(std::vector<Experiment>& experiments);
void deleteExperiment(std::vector<Experiment>& experiments);
void modifyExperiment(std::vector<Experiment>& experiments);

#endif