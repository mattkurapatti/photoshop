#include <visualizer/image_sidebar.h>
#include <visualizer/image_window.h>

#include "cinder/Surface.h"

namespace image_editor {

namespace visualizer {

ImageWindow::ImageWindow(const glm::vec2& top_left_corner,
                         const glm::vec2& dimensions)
    : top_left_corner_(top_left_corner),
      dimensions_(dimensions) {

  surface_ = ci::loadImage("images/moon.jpg");

}

void ImageWindow::Draw() const {
  // draw box around image
  ci::Rectf pixel_bounding_box(top_left_corner_,
                               top_left_corner_ + dimensions_);
  //ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box);

  ci::gl::Texture2dRef texture = ci::gl::Texture2d::create(surface_);
  ci::gl::draw(texture, pixel_bounding_box);
}

void ImageWindow::HandleBrush(const glm::vec2& brush_screen_coords, pixel pix,
                              float brush_radius) {
}

void ImageWindow::Clear() {
}

}  // namespace visualizer

}  // namespace image_editor
