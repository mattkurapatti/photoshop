#include <core/image.h>

#include <ios>
#include <utility>

namespace image_editor {

Image::Image(cinder::Surface surface, const glm::vec2& top_left_corner,
             const glm::vec2& bottom_right_corner)
    : surface_(std::move(surface)),
      top_left_corner_(top_left_corner),
      bottom_right_corner_(bottom_right_corner) {
}

void Image::LoadSurface(const ci::fs::path& path) {
  if (!path.empty()) {
    surface_ = ci::loadImage(path);
  }
}
void Image::SaveSurface(const ci::fs::path& path) {
  if (!path.empty()) {
    writeImage(ci::writeFile(path), surface_);
  }
}

ci::Surface Image::GetSurface() const {
  return surface_;
}

void Image::ZeroBlue() {
  ci::Area area(top_left_corner_, bottom_right_corner_);
  ci::Surface::Iter iter = surface_.getIter(area);
  while (iter.line()) {
    while (iter.pixel()) {
      iter.b() = 0;
    }
  }
}

void Image::Negate() {
  ci::Area area(top_left_corner_, bottom_right_corner_);
  ci::Surface::Iter iter = surface_.getIter(area);
  while (iter.line()) {
    while (iter.pixel()) {
      iter.r() = 255 - iter.r();
      iter.g() = 255 - iter.g();
      iter.b() = 255 - iter.b();
    }
  }
}

}  // namespace image_editor