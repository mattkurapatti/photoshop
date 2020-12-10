#pragma once

#include <core/image.h>

#include "cinder/gl/gl.h"

namespace image_editor {

namespace visualizer {

class ImageSidebar {
 public:
  /**
   * Default constructor
   * @param top_left_corner vec2 representing top left corner of image sidebar
   * @param bottom_right_corner vec2 representing bottom right corner of image
   * sidebar
   */
  ImageSidebar(const glm::vec2& top_left_corner,
               const glm::vec2& bottom_right_corner);

  /**
   * Draws sidebar, which holds the paint buttons and filter/modifier buttons
   */
  void Draw() const;

  /**
   * Checks if any buttons on the sidebar have been clicked
   * @param brush_screen_coords vec2 representing the point clicked
   * @param image Image representing image
   */
  void HandleBrush(const glm::vec2& brush_screen_coords, Image& image);

  const float kPaintButtonWidth = 25.0;
  const float kInnerButtonMargin = 2.0;
  const float kButtonSeparation = 5.0;

  const float kFilterButtonHeight = 30.0;
  const float kMargin = 5.0;

  cinder::Color GetSelectedColor();

 private:
  glm::vec2 top_left_corner_;
  glm::vec2 mid_left_corner_;
  glm::vec2 bottom_right_corner_;

  bool ButtonClicked(ci::Rectf rect, const glm::vec2& pos);
  void CreatePaintButtons();
  void CreateFilterButtons();

  // red, orange, yellow, green, blue, indigo, violet, black, white
  std::vector<ci::Color> colors_ = {
      ci::Color(255, 0, 0),   ci::Color(255, 69, 0), ci::Color(255, 255, 0),
      ci::Color(0, 255, 0),   ci::Color(0, 0, 255),  ci::Color(46, 43, 95),
      ci::Color(139, 0, 255), ci::Color(0, 0, 0),    ci::Color(255, 255, 255)};

  std::vector<ci::Rectf> buttons_;

  std::vector<std::string> filters_ = {
      "ZeroBlue",  "Grayscale",    "Negate",   "Sepia Filter",  "Mirror",
      "Posterize", "Color Splash", "Pixelate", "Sunset Filter", "Fill Edges"};
  std::vector<ci::Rectf> filter_buttons_;

  std::vector<std::string> modifiers_ = {"Draw", "Blur", "Red-Eye"};
  std::vector<ci::Rectf> modifier_buttons_;

  ci::Color selected_;
};

}  // namespace visualizer

}  // namespace image_editor
