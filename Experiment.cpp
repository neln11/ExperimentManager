#include "Experiment.h"

#include <iostream>
#include <fstream> // 用于文件读写
#include <sstream> // 用于解析CSV每一行
#include <limits> // 为了后面清理输入缓冲区
#include <algorithm>

using namespace std;

// 显示菜单
void showMenu() {
    cout << endl;
    cout << "====== C++ 实验日志管理器 ======" << endl;
    cout << "1. 添加实验记录" << endl;
    cout << "2. 查看所有实验记录" << endl;
    cout << "3. 按模型名查询实验记录" << endl;
    cout << "4. 保存到 CSV" << endl;
    cout << "5. 从 CSV 重新读取" << endl;
    cout << "6. 将实验结果按ASR从高到低排序" << endl;
    cout << "7. 删除实验记录" << endl;
    cout << "8. 修改实验记录" << endl;
    cout << "0. 退出系统" << endl;
    cout << "请选择功能: ";
}

// 添加实验记录
void addExperiment(vector<Experiment>& experiments) {
    Experiment exp;

    cout << "请输入实验名称: ";
    cin >> exp.name;

    cout << "请输入模型名称: ";
    cin >> exp.model;

    cout << "请输入数据集名称: ";
    cin >> exp.dataset;

    cout << "请输入 Clean SR: ";
    cin >> exp.cleanSR;

    cout << "请输入 ASR: ";
    cin >> exp.asr;

    cout << "请输入 Target SR: ";
    cin >> exp.targetSR;

    cout << "请输入备注: ";
    cin.ignore(numeric_limits<streamsize>::max(), '\n'); // cin.ignore(最多忽略多少个字符, 忽略到哪个字符为止);
    getline(cin, exp.note);

    experiments.push_back(exp);

    cout << "实验记录添加成功！" << endl;
}

// 查看所有实验记录
void showExperiments(const vector<Experiment>& experiments) {
    if (experiments.empty()) {
        cout << "当前没有任何实验记录。" << endl;
        return;
    }

    cout << endl;
    cout << "====== 所有实验记录 ======" << endl;

    for (int i = 0; i < experiments.size(); i++) {
        const Experiment& exp = experiments[i];

        cout << "编号: " << i + 1 << endl;
        cout << "实验名称: " << exp.name << endl;
        cout << "模型名称: " << exp.model << endl;
        cout << "数据集: " << exp.dataset << endl;
        cout << "Clean SR: " << exp.cleanSR << endl;
        cout << "ASR: " << exp.asr << endl;
        cout << "Target SR: " << exp.targetSR << endl;
        cout << "备注: " << exp.note << endl;
        cout << "------------------------" << endl;
    }
}

// 按模型名查找试验记录
void searchExperimentByModel(const vector<Experiment>& experiments) {
    cout << "The model you want to search in these experiments" << endl;
    
    string nmodel; // 模型名称
    cin >> nmodel;

    cout << "====== search results ======" << endl;

    for (int i = 0; i < experiments.size(); i++) {
        const Experiment& exp = experiments[i];
        
        if (exp.model == nmodel) {
            cout << "编号: " << i + 1 << endl;
            cout << "实验名称: " << exp.name << endl;
            cout << "模型名称: " << exp.model << endl;
            cout << "数据集: " << exp.dataset << endl;
            cout << "Clean SR: " << exp.cleanSR << endl;
            cout << "ASR: " << exp.asr << endl;
            cout << "Target SR: " << exp.targetSR << endl;
            cout << "备注: " << exp.note << endl;
        }
    }
}

// 把experiments所有实验记录保存至csv文件
void saveToCSV(const vector<Experiment>& experiments, const string& filename) {
    ofstream file(filename); // 打开一个文件，准备往里面写东西 ofstream是写文件

    if (!file.is_open()) {
        cout << "文件打开失败，无法保存: " << filename << endl;
        return; // 这里的return是在void里提前结束函数
    }

    // 写入表头
    file << "name,model,dataset,cleanSR,asr,targetSR,note\n"; // file是把内容写进文件

    // 写入每一条试验记录
    for (int i = 0; i < experiments.size(); i++) {
        const Experiment& exp = experiments[i];

        file << exp.name << ","
             << exp.model << ","
             << exp.dataset << ","
             << exp.cleanSR << ","
             << exp.asr << ","
             << exp.targetSR << ","
             << exp.note << "\n";
    }

    file.close();

    cout << "试验记录已保存到: " << filename << endl; 
}

// 读取 CSV 文件，将其放回 vector<Experiment> experiments
void loadFromCSV(vector<Experiment>& experiments, const string& filename) {
    ifstream file(filename); // 打开一个文件，准备从里面读取东西 ifstream是读文件

    if (!file.is_open()) {
        cout << "未找到历史 CSV 文件，将从空记录开始。" << endl;
        return; 
    }

    experiments.clear();

    string line;

    // 跳过第一行表头
    getline(file, line); // getline(file, line) 就是从文件里读一整行

    while (getline(file, line)) {
        if (line.empty()) {
            continue;
        }

        stringstream ss(line); // 把一行 CSV 拆开，相当于把一行放进一个可解析的流里面
        string item;
        Experiment exp;

        getline(ss, exp.name, ','); // 按照逗号一个字段一个字段地拆出来
        getline(ss, exp.model, ',');
        getline(ss, exp.dataset, ',');

        getline(ss, item, ',');
        exp.cleanSR = stod(item); // 从 CSV 里读出来的东西一开始都是字符串， stod() 就是把字符串转成 double
        
        getline(ss, item, ',');
        exp.asr = stod(item);

        getline(ss, item, ',');
        exp.targetSR = stod(item);

        getline(ss, exp.note);

        experiments.push_back(exp);
    }

    file.close();

    cout << "已从 " << filename << " 读取 " << experiments.size() << "条实验记录。"  << endl; 
}

// 按ASR从高到低排序
void sortByASR(vector <Experiment>& experiments) {
    if (experiments.empty()) {
        cout << "当前没有任何实验记录，无法排序" << endl;
        
        return;
    }
    /*
    sort内部解释
    对 experiments 这个列表进行排序
    排序范围：从第一个元素到最后一个元素
    排序规则：ASR 大的排前面
    */
    sort(experiments.begin(), experiments.end(),        // experiments.begin() 是experiments的开头位置 experiments.end() 是experiments的结尾后一个位置
         [](const Experiment& a, const Experiment& b) {   // 这个叫做 lambda 表达式，理解为一个临时写在这里的小函数，作用是告诉sort(),两个实验a和b谁应该排前面
            return a.asr > b.asr;
         });
    
         cout << "已按照ASR从高到低排序" << endl;
    /*
    lambda基本结构
    [](参数列表) {
         函数体
    }
    */
}

// 删除函数
void deleteExperiment(vector <Experiment>& experiments) {
    if (experiments.empty()) {
        cout << "当前没有任何实验记录，无法删除" << endl;
        return;
    }
    
    showExperiments(experiments);

    int index;
    cout << "请输入要删除的实验编号" << endl;
    cin >> index;

    if (index < 1 || index > experiments.size()) {
        cout << "编号无效，删除失败" << endl;
        return;
    }

    Experiment deletedExp = experiments[index - 1];

    experiments.erase(experiments.begin() + index - 1); // 从 experiments 这个 vector 里删除指定位置的元素 比如 experiments.erase(experiments.begin() + 2) 就是删除第三条

    cout << "已删除实验记录: " << deletedExp.name << endl;
}

// 修改实验记录
void modifyExperiment(vector <Experiment>& experiments) {
    if (experiments.empty()) {
        cout << "当前没有任何实验记录，无法修改" << endl;
        return;
    }

    showExperiments(experiments);

    int index;
    cout << "请输入要修改的实验编号: " << endl;
    cin >> index;

    if (index < 1 || index > experiments.size()) {
        cout << "编号无效，修改失败" << endl;
        return;
    }

    Experiment& exp = experiments[index - 1];

    cout << endl;
    cout << "当前选择的实验记录：" << endl;
    cout << "实验名称: " << exp.name << endl;
    cout << "模型名称: " << exp.model << endl;
    cout << "数据集: " << exp.dataset << endl;
    cout << "Clean SR: " << exp.cleanSR << endl;
    cout << "ASR: " << exp.asr << endl;
    cout << "Target SR: " << exp.targetSR << endl;
    cout << "备注: " << exp.note << endl;

     cout << endl;
    cout << "请选择要修改的字段：" << endl;
    cout << "1. 实验名称" << endl;
    cout << "2. 模型名称" << endl;
    cout << "3. 数据集名称" << endl;
    cout << "4. Clean SR" << endl;
    cout << "5. ASR" << endl;
    cout << "6. Target SR" << endl;
    cout << "7. 备注" << endl;
    cout << "0. 取消修改" << endl;
    cout << "请选择: ";

    int fieldChoice;
    cin >> fieldChoice;

    if (fieldChoice == 1) {
        cout << "请输入新的实验名称: ";
        cin >> exp.name;
    } else if (fieldChoice == 2) {
        cout << "请输入新的模型名称: ";
        cin >> exp.model;
    } else if (fieldChoice == 3) {
        cout << "请输入新的数据集名称: ";
        cin >> exp.dataset;
    } else if (fieldChoice == 4) {
        cout << "请输入新的 Clean SR: ";
        cin >> exp.cleanSR;
    } else if (fieldChoice == 5) {
        cout << "请输入新的 ASR: ";
        cin >> exp.asr;
    } else if (fieldChoice == 6) {
        cout << "请输入新的 Target SR: ";
        cin >> exp.targetSR;
    } else if (fieldChoice == 7) {
        cout << "请输入新的备注: ";
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        getline(cin, exp.note);
    } else if (fieldChoice == 0) {
        cout << "已取消修改。" << endl;
        return;
    } else {
        cout << "字段选择无效，修改失败。" << endl;
        return;
    }

    cout << "实验记录修改成功！" << endl;
}
