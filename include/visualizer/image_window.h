#pragma once

#include <core/image.h>

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>

#include "cinder/gl/gl.h"

namespace image_editor {

namespace visualizer {

class ImageWindow {
 public:
  ImageWindow(const glm::vec2& top_left_corner, const glm::vec2& dimensions);

  void Draw() const;

  void HandleBrush(const glm::vec2& brush_screen_coords, float brush_radius);

  void Clear();

  void LoadSurface(const ci::fs::path& path);

  void SaveSurface(const ci::fs::path& path);

  void ZeroBlue();

  void Negate();

  void FilterSepia();

  void Mirror();

 private:
  glm::vec2 top_left_corner_;

  glm::vec2 dimensions_;

  Image image_;
};

}  // namespace visualizer

}  // namespace image_editor
