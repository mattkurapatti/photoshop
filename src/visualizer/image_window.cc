#include <visualizer/image_window.h>

namespace image_editor {

namespace visualizer {

using glm::vec2;

ImageWindow::ImageWindow(const vec2& top_left_corner, size_t num_pixels_per_side,
                     double sketchpad_size, double brush_radius)
    : top_left_corner_(top_left_corner),
      num_pixels_per_side_(num_pixels_per_side),
      pixel_side_length_(sketchpad_size / num_pixels_per_side),
      brush_radius_(brush_radius) {
  Clear();
}

void ImageWindow::Draw() const {
}

void ImageWindow::HandleBrush(const vec2& brush_screen_coords) {
}

void ImageWindow::Clear() {
}

}  // namespace visualizer

}  // namespace image_editor
