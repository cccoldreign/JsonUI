#ifndef IJSONRENDERER_H
#define IJSONRENDERER_H

#include <memory>
#include <ftxui/component/component.hpp>
#include <nlohmann/json.hpp>


class IJsonRenderer {
public:
    virtual ~IJsonRenderer() = default;
    virtual ftxui::Component render(const nlohmann::json& json) = 0;
};

#endif