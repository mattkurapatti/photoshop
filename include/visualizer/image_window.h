#pragma once

#include "cinder/gl/gl.h"

namespace image_editor {

namespace visualizer {

class ImageWindow {
 public:
  ImageWindow(const glm::vec2& top_left_corner, size_t num_pixels_per_side,
            double sketchpad_size, double brush_radius = 1.15);

  void Draw() const;

  void HandleBrush(const glm::vec2& brush_screen_coords);

  void Clear();

 private:
  glm::vec2 top_left_corner_;

  size_t num_pixels_per_side_;

  double pixel_side_length_;

  double brush_radius_;
};

}  // namespace visualizer

}  // namespace image_editor
