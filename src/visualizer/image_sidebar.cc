#include <visualizer/image_sidebar.h>

namespace image_editor {

namespace visualizer {

ImageSidebar::ImageSidebar(const glm::vec2& top_left_corner,
                           const glm::vec2& bottom_right_corner)
    : top_left_corner_(top_left_corner),
      bottom_right_corner_(bottom_right_corner) {
  selected_ = colors_.at(0);

  //  double num_buttons_per_row = std::floor(
  //      (bottom_right_corner.x - top_left_corner.x) / kPaintButtonWidth);
  //  double margin = (bottom_right_corner.x - top_left_corner.x) /
  //                  ((num_buttons_per_row - 1) * kPaintButtonWidth);
  float margin = 5;
  float top_left_x = top_left_corner.x;
  float top_left_y = top_left_corner.y;
  for (size_t index = 0; index < colors_.size(); index++) {
    if (top_left_x + kPaintButtonWidth > bottom_right_corner.x) {
      top_left_x = top_left_corner.x;
      top_left_y += static_cast<float>(kPaintButtonWidth) + margin;
    }
    float bottom_right_x = top_left_x + kPaintButtonWidth;
    float bottom_right_y = top_left_y + kPaintButtonWidth;

    ci::Rectf rect(top_left_x, top_left_y, bottom_right_x, bottom_right_y);
    buttons_.push_back(rect);

    top_left_x += kPaintButtonWidth + margin;
  }
}

void ImageSidebar::Draw() const {
  for (size_t index = 0; index < colors_.size(); index++) {
    ci::gl::color(colors_.at(index));
    ci::gl::drawSolidRect(buttons_.at(index));
    if (selected_ == colors_.at(index)) {
      ci::gl::color(ci::Color("black"));
      ci::gl::drawStrokedRect(buttons_.at(index));
    }
  }
}

void ImageSidebar::HandleBrush(const glm::vec2& brush_screen_coords) {
  for (size_t index = 0; index < colors_.size(); index++) {
    if (ButtonClicked(buttons_.at(index), brush_screen_coords)) {
      selected_ = colors_.at(index);
      return;
    }
  }
}

bool ImageSidebar::ButtonClicked(ci::Rectf rect, const glm::vec2& pos) {
  return (pos.x >= rect.x1 && pos.x <= rect.x2 && pos.y >= rect.y1 &&
          pos.y <= rect.y2);
}

ci::Color ImageSidebar::GetSelectedColor() {
  return selected_;
}

}  // namespace visualizer

}  // namespace image_editor
