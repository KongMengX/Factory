#include "factory_creator.h"

#include <cctype>
#include <chrono>
#include <cstdlib>
#include <iostream>
#include <optional>
#include <sstream>
#include <string>
#include <thread>

namespace {
constexpr char kColorOptions[] =
    "black, red, green, yellow, blue, magenta, cyan, white, gray, purple, or "
    "orange";

[[noreturn]] void closeFactory() {
  std::cout << "\nInput ended. The factory is closing.\n";
  std::exit(0);
}

std::optional<std::string> normalizeColor(const std::string& color) {
  std::string normalized;
  for (const unsigned char character : color) {
    if (!std::isspace(character)) {
      normalized += static_cast<char>(std::tolower(character));
    }
  }

  if (normalized == "black" || normalized == "red" ||
      normalized == "green" || normalized == "yellow" ||
      normalized == "blue" || normalized == "magenta" ||
      normalized == "cyan" || normalized == "white" ||
      normalized == "gray" || normalized == "grey" ||
      normalized == "purple" || normalized == "orange") {
    return normalized;
  }
  return std::nullopt;
}

int readNumber(const std::string& prompt, int minimum, int maximum = 0) {
  while (true) {
    std::cout << prompt;
    std::string input;
    if (!std::getline(std::cin, input)) {
      closeFactory();
    }

    std::istringstream parser(input);
    int value;
    char extraCharacter;
    if ((parser >> value) && !(parser >> extraCharacter) &&
        value >= minimum && (maximum == 0 || value <= maximum)) {
      return value;
    }
    if (maximum == 0) {
      std::cout << "Please enter a positive whole number.\n";
    } else {
      std::cout << "Please enter a whole number from " << minimum << " to "
                << maximum << ".\n";
    }
  }
}

std::string readColor(const std::string& prompt) {
  while (true) {
    std::cout << prompt;
    std::string color;
    if (!std::getline(std::cin, color)) {
      closeFactory();
    }
    if (const std::optional<std::string> normalized = normalizeColor(color)) {
      return *normalized;
    }
    std::cout << "Choose " << kColorOptions << ".\n";
  }
}
}  // namespace

int main() {
  std::cout << "Welcome to the Factory.\n\n";
  std::cout << "What would you like to make?\n1. Box\n2. Triangle\n";
  const int shapeChoice = readNumber("Choose 1 or 2: ", 1, 2);

  std::cout << "Available colors: " << kColorOptions << ".\n";
  const std::string outlineColor = readColor("Outline color: ");
  const std::string fillColor = readColor("Fill color: ");
  const int size = readNumber("Size (1-70): ", 1, 70);

  const ShapeConfig config{shapeChoice == 1 ? ShapeKind::Box : ShapeKind::Triangle,
                           outlineColor, fillColor, size};
  std::cout << "\nCreating your "
            << (config.kind == ShapeKind::Box ? "box" : "triangle")
            << "...\n";
  std::this_thread::sleep_for(std::chrono::seconds(3));
  std::cout << "Your creation is ready!\n\n" << makePreview(config);
}
