#include <core/image.h>

#include <ios>
#include <utility>

namespace image_editor {

Image::Image(ci::Surface surface) : surface_(std::move(surface)) {
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

void Image::Draw(const glm::vec2& pos, const ci::Color& color,
                 double brush_radius) {
  ci::Surface::Iter iter = surface_.getIter();
  while (iter.line()) {
    while (iter.pixel()) {
      if (Distance(iter.getPos(), pos) < brush_radius) {
        iter.r() = static_cast<uint8_t>(color.r);
        iter.g() = static_cast<uint8_t>(color.g);
        iter.b() = static_cast<uint8_t>(color.b);
      }
    }
  }
}

double Image::Distance(const glm::vec2& vec1, const glm::vec2& vec2) const {
  return std::sqrt(std::pow(vec1.x - vec2.x, 2) + std::pow(vec1.y - vec2.y, 2));
}

void Image::ZeroBlue() {
  ci::Surface::Iter iter = surface_.getIter();
  while (iter.line()) {
    while (iter.pixel()) {
      iter.b() = 0;
    }
  }
}

void Image::Negate() {
  ci::Surface::Iter iter = surface_.getIter();
  while (iter.line()) {
    while (iter.pixel()) {
      iter.r() = 255 - iter.r();
      iter.g() = 255 - iter.g();
      iter.b() = 255 - iter.b();
    }
  }
}

void Image::FilterSepia() {
  ci::Surface::Iter iter = surface_.getIter();

  // based on Microsoft's algorithm for the Sepia Filter:
  // sets r to .393 * r + .769 * g + .189 * b
  // sets g to .349 * r + .686 * g + .168 * b
  // sets b to .272 * r + .534 * g + .131 * b
  while (iter.line()) {
    while (iter.pixel()) {
      int r = static_cast<int>(0.393 * iter.r() + 0.769 * iter.g() +
                               0.189 * iter.b());
      int g = static_cast<int>(0.349 * iter.r() + 0.686 * iter.g() +
                               0.168 * iter.b());
      int b = static_cast<uint8_t>(0.272 * iter.r() + 0.534 * iter.g() +
                                   0.131 * iter.b());

      iter.r() = 255;
      iter.g() = 255;
      iter.b() = 255;

      if (r < 255) {
        iter.r() = r;
      }
      if (g < 255) {
        iter.g() = g;
      }
      if (b < 255) {
        iter.b() = b;
      }
    }
  }
}

void Image::Mirror() {
  ci::Surface::Iter iter = surface_.getIter();

  while (iter.line()) {
    while (iter.pixel()) {
      if (iter.getPos().y <= std::floor(iter.getHeight() / 2.0)) {
        ci::ColorA color1 = surface_.getPixel(iter.getPos());
        int x1 = iter.getPos().x;
        int y1 = iter.getPos().y;

        int x2 = x1;
        int y2 = surface_.getHeight() - y1 - 1;

        surface_.setPixel(glm::vec2(x1, y1),
                          surface_.getPixel(glm::vec2(x2, y2)));
        surface_.setPixel(glm::vec2(x2, y2), color1);
      }
    }
  }
}

void Image::Posterize() {
}

void Image::ColorSplash() {
}

void Image::Pixelate() {
}

void Image::FilterSunset() {
}

void Image::CorrectRedEye() {
}

void Image::FillEdges() {
}

}  // namespace image_editor