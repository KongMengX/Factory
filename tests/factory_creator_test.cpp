#include "../factory_creator.h"

#include <cassert>
#include <string>

int main() {
  const ShapeConfig validBox{ShapeKind::Box, "blue", "white", 5};
  assert(isValid(validBox));

  const ShapeConfig emptyOutline{ShapeKind::Box, "", "white", 5};
  assert(!isValid(emptyOutline));

  const ShapeConfig whitespaceFill{ShapeKind::Box, "blue", "   ", 5};
  assert(!isValid(whitespaceFill));

  const ShapeConfig unsupportedColor{ShapeKind::Box, "blue", "teal", 5};
  assert(!isValid(unsupportedColor));

  const ShapeConfig tooLarge{ShapeKind::Box, "blue", "white", 71};
  assert(!isValid(tooLarge));

  const std::string boxPreview = makePreview(validBox);
  assert(boxPreview.find("Outline color: blue") != std::string::npos);
  assert(boxPreview.find("Fill color: white") != std::string::npos);
  assert(boxPreview.find("Line thickness:") == std::string::npos);
  assert(boxPreview.find("\033[34m#\033[0m") != std::string::npos);
  assert(boxPreview.find("\033[37m.\033[0m") != std::string::npos);

  const ShapeConfig triangle{ShapeKind::Triangle, "red", "yellow", 4};
  const std::string trianglePreview = makePreview(triangle);
  assert(trianglePreview.find("Triangle preview") != std::string::npos);
  assert(trianglePreview.find("\033[31m#\033[0m") != std::string::npos);
  assert(trianglePreview.find("\033[33m.\033[0m") != std::string::npos);
}
