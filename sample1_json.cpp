#include<bits/stdc++.h>
#include "json.hpp"

using namespace std;
using json = nlohmann::json;

struct ScheduleEntry {
    string wafer_id;
    string step;
    string machine;
    int start_time;
    int end_time;
};

int main() {
    /* ---------------- READ INPUT ---------------- */
    ifstream fin("input.json");
    if(!fin.is_open())
    {
        return 1;
    }

    json input;
    fin >> input;
    fin.close();

    /* ---------------- PARSE STEPS ---------------- */
    vector<string> steps;
    for(auto &s:input["steps"])
    {
        steps.push_back(s["id"]);
    }

    /* ---------------- PARSE MACHINES ---------------- */
    unordered_map<string, vector<string>> machines;
    for (auto &m : input["machines"]) {
        machines[m["step_id"]].push_back(m["machine_id"]);
    }

    /* ---------------- MACHINE AVAILABILITY ---------------- */
    unordered_map<string, int> machine_time;
    for (auto &p : machines) {
        for (auto &m : p.second) {
            machine_time[m] = 0;
        }
    }

    /* ---------------- SCHEDULING (MILESTONE-0) ---------------- */
    vector<ScheduleEntry> schedule;

    for (auto &w : input["wafers"]) {
        string type = w["type"];
        int qty = w["quantity"];
        auto proc = w["processing_times"];

        for (int i = 1; i <= qty; i++) {
            string wafer_id = type + "-" + to_string(i);
            int wafer_time = 0;

            for (auto &step : steps) {
                int duration = proc[step];

                // choose first available machine for this step
                string machine = machines[step][0];

                int start = max(wafer_time, machine_time[machine]);
                int end = start + duration;

                schedule.push_back({
                    wafer_id,
                    step,
                    machine,
                    start,
                    end
                });

                wafer_time = end;
                machine_time[machine] = end;
            }
        }
    }

    /* ---------------- BUILD OUTPUT ---------------- */
    json output;
    output["schedule"] = json::array();

    for (auto &e : schedule) {
        output["schedule"].push_back({
            {"wafer_id", e.wafer_id},
            {"step", e.step},
            {"machine", e.machine},
            {"start_time", e.start_time},
            {"end_time", e.end_time}
        });
    }

    /* ---------------- WRITE OUTPUT ---------------- */
    ofstream fout("output.json");
    if (!fout.is_open()) {
        return 1;
    }

    //fout << setw(2) << output << endl;
    //fout << output.dump() << endl;
    //ofstream fout("output.json");
    fout << "{ \"schedule\" : [\n";

    for (int i = 0; i < output["schedule"].size(); i++) {
        fout << output["schedule"][i].dump();
        if (i != output["schedule"].size() - 1)
            fout << ",";
        fout << "\n";
    }

    fout << "] }\n";
    fout.close();

    fout.close();

    return 0;
}
