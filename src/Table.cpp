#include "Table.h"
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>
#include <ftxui/dom/elements.hpp>

using namespace ftxui;

Component JsonRenderer1::render(const nlohmann::json& json) {
  collectKeys(json, selections);

  FillingTabs();

  auto container =
    Container::Horizontal({
      cont
    }) | border | CatchEvent([ & ](Event event) {

      if (event == Event::ArrowDown) {
        if((selections[column].selected_index < selections[column].keys_json.size() - 1) && (column != selections.size() - 1 ))
        {
          cont->DetachAllChildren();
          ChangeDown(column);
          FillingTabs();
        }
        return false;

      } else if (event == Event::ArrowRight) {
        if(column < selections.size() - 1){
          ++column;
        }
        return false;

      } else if (event == Event::ArrowLeft) {
        if(column > 0){
          --column;
        }
        return false;

      } else if (event == Event::ArrowUp) {
        if((selections[column].selected_index > 0) && (column != selections.size() - 1))
        {
          cont->DetachAllChildren();
          ChangeUp(column);
          FillingTabs();
        }
        return false;
      }
      return true;
    });

    return container;
}