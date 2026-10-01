#ifndef FACTORY_CREATOR_H
#define FACTORY_CREATOR_H

#include <string>

enum class ShapeKind { Box, Triangle };

struct ShapeConfig {
  ShapeKind kind;
  std::string outlineColor;
  std::string fillColor;
  int size;
};

bool isValid(const ShapeConfig& config);
std::string makePreview(const ShapeConfig& config);

#endif
