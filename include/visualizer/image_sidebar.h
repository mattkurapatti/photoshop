#pragma once

#include "cinder/gl/gl.h"

namespace image_editor {

namespace visualizer {

class ImageSidebar {
 public:
  ImageSidebar(const glm::vec2& top_left_corner,
              const glm::vec2& bottom_right_corner);

  void Draw() const;

 private:
  glm::vec2 top_left_corner_;

  glm::vec2 bottom_right_corner_;


};

}  // namespace visualizer

}  // namespace image_editor
