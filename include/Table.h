#ifndef TABLE_H
#define TABLE_H

#include "JsonRenderer.h"
#include <fstream>
#include <string>
#include <vector>
#include <memory>

#include <ftxui/component/captured_mouse.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

#include <nlohmann/json.hpp>

using namespace ftxui;
using json = nlohmann::json;

class JsonRenderer1 : public JsonRenderer {
    
private:
    struct Selection {
        json current_json;
        int selected_index;
        std::vector<std::string> keys_json;
        std::string valStr;
    };

    Component cont = Container::Horizontal({});
    std::vector<std::string> temp;
    std::vector<Selection> selections;
    int column = 0;

    void collectKeys(const json& j, std::vector<Selection>& selections) {
        Selection S;
        S.current_json = j;

        if (j.is_object()) {
            for (auto it = j.begin(); it != j.end(); ++it) {
                S.keys_json.push_back(it.key());
            }
            S.selected_index = 0;
            S.valStr = "";
            selections.push_back(S);
            if (!S.keys_json.empty()) {
                auto first_key = S.keys_json[0];
                collectKeys(j[first_key], selections);
            }
        } else if (j.is_array()) {
            for (size_t i = 0; i < j.size(); ++i) {
                S.keys_json.push_back(std::to_string(i));
            }
            S.selected_index = 0;
            S.valStr = "";
            selections.push_back(S);
            if (!j.empty()) {
                collectKeys(j[0], selections);
            }
        } else {
            auto it = j.begin();
            S.valStr = to_string(it.value());
            selections.push_back(S);
        }
    }

    void FillingTabs() {
    for (auto &it: selections) {
        cont -> Add(Container::Vertical({
        Menu( & it.keys_json, & it.selected_index) | vscroll_indicator | frame 
        }));
        if(it.valStr == ""){
        cont -> Add(Renderer([] {
        return separator();
        }));
        }
    }
        temp.clear();
        temp.push_back(selections.back().valStr);
        cont -> Add(Container::Vertical({
        Menu(&temp, &selections.back().selected_index) | vscroll_indicator | frame 
        }));
    }

    void ChangeDown(int column) {
        if (column < selections.size()) {
            Selection S = selections[column];
            if (S.selected_index < S.keys_json.size() - 1) {
                S.selected_index++;
                std::string key = S.keys_json[S.selected_index];
                json newLine = S.current_json.is_array() ? S.current_json[std::stoi(key)] : S.current_json[key];
                selections.erase(selections.begin() + 1 + column, selections.end());
                collectKeys(newLine, selections);
            }
        }
    }

    void ChangeUp(int column) {
        if (column < selections.size()) {
            Selection S = selections[column];
            if (S.selected_index > 0) {
                S.selected_index--;
                std::string key = S.keys_json[S.selected_index];
                json newLine = S.current_json.is_array() ? S.current_json[std::stoi(key)] : S.current_json[key];
                selections.erase(selections.begin() + 1 + column, selections.end());
                collectKeys(newLine, selections);
            }
        }
    }

public:

    ftxui::Component render(const json& json) override;

};

#endif  // JSONRENDERER1_H
