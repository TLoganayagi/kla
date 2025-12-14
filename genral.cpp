#include <bits/stdc++.h>
#include "json.hpp"   // nlohmann/json single header

using namespace std;
using json = nlohmann::json;

/* ========= GENERIC DATA STRUCTURES ========= */
struct Entity {
    string id;
    unordered_map<string, int> attributes;
};

struct Resource {
    string id;
    int available_time = 0;
};

struct OutputEntry {
    string entity_id;
    string action;
    string resource_id;
    int start_time;
    int end_time;
};

/* ========= CSV HELPER ========= */
vector<string> split(const string &line, char delim = ',') {
    vector<string> tokens;
    string token;
    stringstream ss(line);
    while (getline(ss, token, delim))
        tokens.push_back(token);
    return tokens;
}

int main() {
    /* ========= INPUT ========= */
    vector<Entity> entities;
    vector<Resource> resources;

    /* ---- JSON INPUT (optional) ---- */
    ifstream fin("input.json");
    json input;
    if (fin.is_open()) {
        fin >> input;
        fin.close();

        for (auto &e : input["entities"]) {
            Entity obj;
            obj.id = e["id"];
            for (auto &p : e["attributes"].items())
                obj.attributes[p.key()] = p.value();
            entities.push_back(obj);
        }

        for (auto &r : input["resources"]) {
            resources.push_back({r["id"], 0});
        }
    }

    /* ---- CSV INPUT (optional) ---- */
    ifstream csv("input.csv");
    if (csv.is_open()) {
        string line;
        getline(csv, line); // header
        while (getline(csv, line)) {
            auto t = split(line);
            Entity obj;
            obj.id = t[0];
            entities.push_back(obj);
        }
        csv.close();
    }

    /* ========= CORE LOGIC (PLACEHOLDER) ========= */
    vector<OutputEntry> result;
    int current_time = 0;

    for (auto &e : entities) {
        if (resources.empty()) break;

        Resource &r = resources[0]; // simple safe choice
        int start = max(current_time, r.available_time);
        int end = start + 10;       // dummy processing

        result.push_back({
            e.id,
            "PROCESS",
            r.id,
            start,
            end
        });

        r.available_time = end;
        current_time = end;
    }

    /* ========= OUTPUT ========= */
    json output;
    output["result"] = json::array();

    for (auto &o : result) {
        output["result"].push_back({
            {"entity_id", o.entity_id},
            {"action", o.action},
            {"resource_id", o.resource_id},
            {"start_time", o.start_time},
            {"end_time", o.end_time}
        });
    }

    ofstream fout("output.json");
    fout << output.dump();  // compact, validator-safe
    fout.close();

    return 0;
}
