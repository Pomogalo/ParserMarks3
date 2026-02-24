#include "processData.h"
#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <vector>
#include <numeric>
#include <iomanip>
#include <iterator>
using namespace std;
void processData::analyzePrograss(const string& path)
{
    cout << "Анализ успеваемости..." << endl;

    ifstream in(path);
    if (!in) {
        cerr << "Файл не найден." << endl;
        return;
    }

    string json_str((istreambuf_iterator<char>(in)), istreambuf_iterator<char>());

    map<string, vector<int>> stats;
    size_t pos = 0;

    while ((pos = json_str.find("\"spec_name\"", pos)) != string::npos) {
        size_t colon_pos = json_str.find(':', pos);
        if (colon_pos == string::npos) break;

        size_t quote1 = json_str.find('"', colon_pos + 1);
        if (quote1 == string::npos) break;

        size_t quote2 = json_str.find('"', quote1 + 1);
        if (quote2 == string::npos) break;

        string subject = json_str.substr(quote1 + 1, quote2 - quote1 - 1);

        size_t mark_pos = json_str.find("\"class_work_mark\"", quote2);
        if (mark_pos == string::npos) break;

        colon_pos = json_str.find(':', mark_pos);
        if (colon_pos == string::npos) break;

        size_t val_start = colon_pos + 1;
        while (val_start < json_str.size() && (json_str[val_start] == ' '  json_str[val_start] == '\t')) ++val_start;

        if (json_str.substr(val_start, 4) == "null") {
            // skip
        }
        else {
            size_t val_end = json_str.find_first_of(",}", val_start);
            if (val_end == string::npos) break;

            string mark_str = json_str.substr(val_start, val_end - val_start);
            int mark = stoi(mark_str);
            stats[subject].push_back(mark);
        }

        pos = val_start;
    }

    cout << "\nРезультаты" << endl;
    for (const auto& pair : stats) {
        const string& subject = pair.first;
        const vector<int>& marks = pair.second;
        if (!marks.empty()) {
            double average = accumulate(marks.begin(), marks.end(), 0.0) / marks.size();
            cout << subject << ": средний балл " << fixed << setprecision(2) << average
                << " (всего оценок: " << marks.size() << ")" << endl;
        }
    }
}