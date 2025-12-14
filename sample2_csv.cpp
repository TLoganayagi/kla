#include <bits/stdc++.h>
using namespace std;

struct ScheduleEntry {
    string wafer_id;
    string step;
    string machine;
    int start_time;
    int end_time;
};

vector<string> split(const string &line, char delim = ',') {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, delim)) {
        tokens.push_back(token);
    }
    return tokens;
}

int main() {
    /* -------- READ STEPS CSV -------- */
    vector<string> steps;
    ifstream stepFile("steps.csv");
    string line;
    getline(stepFile, line); // skip header
    while (getline(stepFile, line)) {
        steps.push_back(line);
    }
    stepFile.close();

    /* -------- READ MACHINES CSV -------- */
    unordered_map<string, vector<string>> machines;
    ifstream machineFile("machines.csv");
    getline(machineFile, line); // header
    while (getline(machineFile, line)) {
        auto t = split(line);
        machines[t[1]].push_back(t[0]); // step -> machine
    }
    machineFile.close();

    /* -------- READ WAFERS CSV -------- */
    map<string, map<string, pair<int,int>>> wafers; 
    // type -> step -> (time, qty)

    ifstream waferFile("wafers.csv");
    getline(waferFile, line); // header
    while (getline(waferFile, line)) {
        auto t = split(line);
        wafers[t[0]][t[1]] = {stoi(t[2]), stoi(t[3])};
    }
    waferFile.close();

    /* -------- MACHINE AVAILABILITY -------- */
    unordered_map<string, int> machine_time;
    for (auto &p : machines)
        for (auto &m : p.second)
            machine_time[m] = 0;

    /* -------- SCHEDULING (MILESTONE-0) -------- */
    vector<ScheduleEntry> schedule;

    for (auto &w : wafers) {
        string type = w.first;
        int qty = w.second.begin()->second.second;

        for (int i = 1; i <= qty; i++) {
            string wafer_id = type + "-" + to_string(i);
            int wafer_time = 0;

            for (auto &step : steps) {
                int duration = w.second[step].first;
                string machine = machines[step][0];

                int start = max(wafer_time, machine_time[machine]);
                int end = start + duration;

                schedule.push_back({wafer_id, step, machine, start, end});

                wafer_time = end;
                machine_time[machine] = end;
            }
        }
    }

    /* -------- WRITE OUTPUT JSON (PPT STYLE) -------- */
    ofstream fout("output.json");
    fout << "{ \"schedule\" : [\n";

    for (int i = 0; i < schedule.size(); i++) {
        auto &e = schedule[i];
        fout << "{"
             << "\"wafer_id\":\"" << e.wafer_id << "\","
             << "\"step\":\"" << e.step << "\","
             << "\"machine\":\"" << e.machine << "\","
             << "\"start_time\":" << e.start_time << ","
             << "\"end_time\":" << e.end_time << "}";

        if (i != schedule.size() - 1)
            fout << ",";
        fout << "\n";
    }

    fout << "] }\n";
    fout.close();

    return 0;
}
