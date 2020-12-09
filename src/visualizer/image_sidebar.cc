#include <core/image.h>
#include <visualizer/image_sidebar.h>

namespace image_editor {

namespace visualizer {

ImageSidebar::ImageSidebar(const glm::vec2& top_left_corner,
                           const glm::vec2& bottom_right_corner)
    : top_left_corner_(top_left_corner),
      mid_left_corner_(
          top_left_corner.x,
          top_left_corner.y + (bottom_right_corner.y - top_left_corner.y) / 3),
      bottom_right_corner_(bottom_right_corner) {
  selected_ = colors_.at(0);
  CreatePaintButtons();
  CreateFilterButtons();
}

void ImageSidebar::CreatePaintButtons() {
  float top_left_x = top_left_corner_.x;
  float top_left_y = top_left_corner_.y;
  for (size_t index = 0; index < colors_.size(); index++) {
    if (top_left_x + kPaintButtonWidth > bottom_right_corner_.x) {
      top_left_x = top_left_corner_.x;
      top_left_y += static_cast<float>(kPaintButtonWidth) + kButtonSeparation;
    }
    float bottom_right_x = top_left_x + kPaintButtonWidth;
    float bottom_right_y = top_left_y + kPaintButtonWidth;

    ci::Rectf rect(top_left_x, top_left_y, bottom_right_x, bottom_right_y);
    buttons_.push_back(rect);

    top_left_x += kPaintButtonWidth + kButtonSeparation;
  }
}

void ImageSidebar::CreateFilterButtons() {
  float top_left_x = mid_left_corner_.x + kMargin;
  float bottom_right_x = mid_left_corner_.x +
                         (bottom_right_corner_.x - mid_left_corner_.x) / 2.0f -
                         kMargin;
  float top_left_y = mid_left_corner_.y + kMargin;
  for (size_t index = 0; index < filters_.size(); index++) {
    ci::Rectf rect(top_left_x, top_left_y, bottom_right_x,
                   top_left_y + kFilterButtonHeight);
    filter_buttons_.push_back(rect);

    if (index < modifiers_.size()) {
      float half_dist = (bottom_right_corner_.x - mid_left_corner_.x) / 2.0f;
      ci::Rectf rect2(top_left_x + half_dist, top_left_y,
                      bottom_right_x + half_dist,
                      top_left_y + kFilterButtonHeight);
      modifier_buttons_.push_back(rect2);
    }

    top_left_y += kFilterButtonHeight + kButtonSeparation;
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

  for (size_t index = 0; index < filters_.size(); index++) {
    ci::gl::color(ci::Color("black"));
    ci::Rectf rect = filter_buttons_.at(index);
    ci::gl::drawStrokedRect(rect);
    glm::vec2 mids((rect.x2 - rect.x1) / 2.0f, (rect.y2 - rect.y1) / 2.0f);
    ci::gl::drawStringCentered(filters_.at(index),
                               glm::vec2(rect.x1, rect.y1) + mids,
                               ci::Color("black"));
  }

  for (size_t index = 0; index < modifiers_.size(); index++) {
    ci::gl::color(ci::Color("black"));
    ci::Rectf rect = modifier_buttons_.at(index);
    ci::gl::drawStrokedRect(rect);
    glm::vec2 mids((rect.x2 - rect.x1) / 2.0f, (rect.y2 - rect.y1) / 2.0f);
    ci::gl::drawStringCentered(modifiers_.at(index),
                               glm::vec2(rect.x1, rect.y1) + mids,
                               ci::Color("black"));
  }
}

void ImageSidebar::HandleBrush(const glm::vec2& brush_screen_coords,
                               Image& image) {
  for (size_t index = 0; index < colors_.size(); index++) {
    if (ButtonClicked(buttons_.at(index), brush_screen_coords)) {
      selected_ = colors_.at(index);
      return;
    }
  }

  for (size_t index = 0; index < filters_.size(); index++) {
    if (ButtonClicked(filter_buttons_.at(index), brush_screen_coords)) {
      image.HandleInputFilter(filters_.at(index));
      return;
    }
  }

  for (size_t index = 0; index < modifiers_.size(); index++) {
    if (ButtonClicked(modifier_buttons_.at(index), brush_screen_coords)) {
      image.SetModifier(modifiers_.at(index));
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
