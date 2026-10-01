#include "factory_creator.h"

#include <cctype>
#include <optional>
#include <sstream>

namespace {
constexpr int kMaximumSize = 70;

bool hasVisibleCharacter(const std::string& text) {
  for (const unsigned char character : text) {
    if (!std::isspace(character)) {
      return true;
    }
  }
  return false;
}

std::optional<int> colorCode(const std::string& color) {
  std::string normalized;
  for (const unsigned char character : color) {
    if (!std::isspace(character)) {
      normalized += static_cast<char>(std::tolower(character));
    }
  }

  if (normalized == "black") return 30;
  if (normalized == "red") return 31;
  if (normalized == "green") return 32;
  if (normalized == "yellow" || normalized == "orange") return 33;
  if (normalized == "blue") return 34;
  if (normalized == "magenta" || normalized == "purple") return 35;
  if (normalized == "cyan") return 36;
  if (normalized == "white") return 37;
  if (normalized == "gray" || normalized == "grey") return 90;
  return std::nullopt;
}

std::string coloredCell(char cell, const std::string& color) {
  return "\033[" + std::to_string(*colorCode(color)) + "m" + cell +
         "\033[0m";
}

std::string makeBox(const ShapeConfig& config) {
  std::ostringstream output;
  for (int row = 0; row < config.size; ++row) {
    for (int column = 0; column < config.size; ++column) {
      const bool isBorder = row == 0 || row == config.size - 1 ||
                            column == 0 || column == config.size - 1;
      output << coloredCell(isBorder ? '#' : '.',
                            isBorder ? config.outlineColor : config.fillColor);
    }
    output << '\n';
  }
  return output.str();
}

std::string makeTriangle(const ShapeConfig& config) {
  std::ostringstream output;
  for (int row = 0; row < config.size; ++row) {
    for (int column = 0; column <= row; ++column) {
      const bool isBorder = row == 0 || row == config.size - 1 ||
                            column == 0 || column == row;
      output << coloredCell(isBorder ? '#' : '.',
                            isBorder ? config.outlineColor : config.fillColor);
    }
    output << '\n';
  }
  return output.str();
}
}  // namespace

bool isValid(const ShapeConfig& config) {
  return hasVisibleCharacter(config.outlineColor) &&
         hasVisibleCharacter(config.fillColor) && colorCode(config.outlineColor) &&
         colorCode(config.fillColor) && config.size > 0 &&
         config.size <= kMaximumSize;
}

std::string makePreview(const ShapeConfig& config) {
  std::ostringstream output;
  const bool isBox = config.kind == ShapeKind::Box;
  output << (isBox ? "Box" : "Triangle") << " preview\n"
         << "Outline color: " << config.outlineColor << '\n'
         << "Fill color: " << config.fillColor << '\n'
         << "Size: " << config.size << '\n';
  output << (isBox ? makeBox(config) : makeTriangle(config));
  return output.str();
}
