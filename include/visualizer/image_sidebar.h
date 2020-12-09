#pragma once

#include "cinder/gl/gl.h"

namespace image_editor {

namespace visualizer {

class ImageSidebar {
 public:
  ImageSidebar(const glm::vec2& top_left_corner,
               const glm::vec2& bottom_right_corner);

  void Draw() const;
  void HandleBrush(const glm::vec2& brush_screen_coords);

  const float kPaintButtonWidth = 25.0;
  const float kInnerButtonMargin = 2.0;

  cinder::Color GetSelectedColor();

 private:
  glm::vec2 top_left_corner_;

  glm::vec2 bottom_right_corner_;

  bool ButtonClicked(ci::Rectf rect, const glm::vec2& pos);

  // red, orange, yellow, green, blue, indigo, violet, black, white
  std::vector<ci::Color> colors_ = {
      ci::Color(255, 0, 0),   ci::Color(255, 69, 0), ci::Color(255, 255, 0),
      ci::Color(0, 255, 0),   ci::Color(0, 0, 255),  ci::Color(46, 43, 95),
      ci::Color(139, 0, 255), ci::Color(0, 0, 0),    ci::Color(255, 255, 255)};

  std::vector<ci::Rectf> buttons_;

  ci::Color selected_;
};

}  // namespace visualizer

}  // namespace image_editor
