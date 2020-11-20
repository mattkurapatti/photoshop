#pragma once

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>

#include "cinder/gl/gl.h"

namespace image_editor {

namespace visualizer {

class ImageWindow {
 public:
  ImageWindow(const glm::vec2& top_left_corner, const glm::vec2& bottom_right_corner);

  void Draw() const;

  void HandleBrush(const glm::vec2& brush_screen_coords);

  void Clear();

 private:
  glm::vec2 top_left_corner_;

  glm::vec2 bottom_right_corner_;
};

}  // namespace visualizer

}  // namespace image_editor
