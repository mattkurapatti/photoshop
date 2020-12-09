#include <visualizer/image_sidebar.h>
#include <visualizer/image_window.h>

#include <utility>

#include "cinder/ImageIo.h"
#include "cinder/Log.h"
#include "cinder/Surface.h"
#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/Texture.h"
#include "cinder/gl/gl.h"

namespace image_editor {

namespace visualizer {

ImageWindow::ImageWindow(const glm::vec2& top_left_corner,
                         const glm::vec2& dimensions)
    : top_left_corner_(top_left_corner),
      dimensions_(dimensions),
      image_(ci::loadImage("images/default.jpg")) {
}

void ImageWindow::Draw() const {
  // draw box around image
  ci::Rectf pixel_bounding_box(top_left_corner_,
                               top_left_corner_ + dimensions_);
  ci::gl::color(ci::Color("black"));
  ci::gl::drawStrokedRect(pixel_bounding_box);

  ci::gl::color(ci::Color("white"));

  ci::gl::Texture2dRef texture = ci::gl::Texture2d::create(image_.GetSurface());
  ci::gl::draw(texture, pixel_bounding_box);
}

void ImageWindow::HandleBrush(const glm::vec2& brush_screen_coords,
                              const cinder::Color& color) {
  glm::vec2 image_pos = brush_screen_coords - top_left_corner_;
  image_.HandleBrush(
      glm::vec2(image_pos.x / dimensions_.x, image_pos.y / dimensions_.y),
      color, 5);
}

void ImageWindow::Clear() {
}

void ImageWindow::LoadSurface(const ci::fs::path& path) {
  image_.LoadSurface(path);
}

void ImageWindow::SaveSurface(const ci::fs::path& path) {
  image_.SaveSurface(path);
}

void ImageWindow::ZeroBlue() {
  image_.ZeroBlue();
}

void ImageWindow::Negate() {
  image_.Negate();
}

void ImageWindow::FilterSepia() {
  image_.FilterSepia();
}

void ImageWindow::Mirror() {
  image_.MirrorUD();
}

Image& ImageWindow::GetImage() {
  return image_;
}

void ImageWindow::ResetImage() {
  image_.Reset();
}

}  // namespace visualizer

}  // namespace image_editor
