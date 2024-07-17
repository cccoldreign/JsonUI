#ifndef JSONRENDERER_H
#define JSONRENDERER_H

#include <memory>
#include <ftxui/component/component.hpp>
#include <nlohmann/json.hpp>


class JsonRenderer {
public:
    virtual ~JsonRenderer() = default;
    virtual ftxui::Component render(const nlohmann::json& json) = 0;
};

#endif