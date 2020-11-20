#include <visualizer/image_window.h>
#include <visualizer/image_sidebar.h>


namespace image_editor {

namespace visualizer {

ImageWindow::ImageWindow(const glm::vec2& top_left_corner,
                         const glm::vec2& bottom_right_corner)
    : top_left_corner_(top_left_corner),
      bottom_right_corner_(bottom_right_corner) {
}

void ImageWindow::Draw() const {
  // draw box around image
  ci::Rectf pixel_bounding_box(top_left_corner_, bottom_right_corner_);
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box);
}

void ImageWindow::HandleBrush(const glm::vec2& brush_screen_coords) {
}

void ImageWindow::Clear() {
}

}  // namespace visualizer

}  // namespace image_editor
