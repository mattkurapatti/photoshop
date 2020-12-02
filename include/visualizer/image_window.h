#pragma once

#include <core/image.h>

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>

#include "cinder/gl/gl.h"

namespace image_editor {

namespace visualizer {

class ImageWindow {
 public:
  ImageWindow(const glm::vec2& top_left_corner, const glm::vec2& bottom_right_corner);

  void Draw() const;

  void HandleBrush(const glm::vec2& brush_screen_coords, pixel pix,
                   float brush_radius);

  void Clear();

  void LoadSurface(const ci::fs::path& path);

  void SaveSurface(const ci::fs::path& path);

 private:
  glm::vec2 top_left_corner_;

  glm::vec2 dimensions_;

  ci::Surface surface_;

};

}  // namespace visualizer

}  // namespace image_editor
