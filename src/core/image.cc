#include <core/image.h>

#include <ios>
#include <utility>

namespace image_editor {

Image::Image(ci::Surface surface)
    : original_surface_(surface.clone()),
      surface_(std::move(surface)),
      modifier_("Draw") {
}

void Image::LoadSurface(const ci::fs::path& path) {
  if (!path.empty()) {
    surface_ = ci::loadImage(path);
    original_surface_ = surface_.clone();
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

void Image::HandleBrush(const glm::vec2& relative_pos, const ci::Color& color,
                        double brush_radius) {
  glm::vec2 pos(relative_pos.x * surface_.getWidth(),
                relative_pos.y * surface_.getHeight());

  if (modifier_ == "Draw") {
    Draw(pos, color, brush_radius);
  } else if (modifier_ == "Blur") {
    Blur(pos);
  } else if (modifier_ == "Red-Eye") {
    CorrectRedEye(pos, brush_radius);
  }
}

void Image::Draw(const glm::vec2& pos, const cinder::Color& color,
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

void Image::Blur(const glm::vec2& pos) {
  float num_valid = 1.0f;
  ci::ColorA color(surface_.getPixel(pos));

  ci::ColorA color1(0, 0, 0);
  if (ValidPixel(glm::vec2(pos.x - 1, pos.y))) {
    num_valid++;
    color1 = surface_.getPixel(glm::vec2(pos.x - 1, pos.y));
  }

  ci::ColorA color2(0, 0, 0);
  if (ValidPixel(glm::vec2(pos.x + 1, pos.y))) {
    num_valid++;
    color2 = surface_.getPixel(glm::vec2(pos.x + 1, pos.y));
  }

  ci::ColorA color3(0, 0, 0);
  if (ValidPixel(glm::vec2(pos.x, pos.y - 1))) {
    num_valid++;
    color3 = surface_.getPixel(glm::vec2(pos.x, pos.y - 1));
  }

  ci::ColorA color4(0, 0, 0);
  if (ValidPixel(glm::vec2(pos.x, pos.y + 1))) {
    num_valid++;
    color4 = surface_.getPixel(glm::vec2(pos.x, pos.y + 1));
  }

  float avg_r = (color.r + color1.r + color2.r + color3.r + color4.r) / num_valid;
  float avg_g = (color.g + color1.g + color2.g + color3.g + color4.g) / num_valid;
  float avg_b = (color.b + color1.b + color2.b + color3.b + color4.b) / num_valid;

  surface_.setPixel(pos, ci::ColorA(avg_r, avg_g, avg_b));
}

void Image::CorrectRedEye(const glm::vec2& pos, double brush_radius) {
  ci::Surface::Iter iter = surface_.getIter();
  while (iter.line()) {
    while (iter.pixel()) {
      if (Distance(iter.getPos(), pos) < kRedEyeRadius * brush_radius) {
        iter.r() = 0;
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

void Image::Grayscale() {
  ci::Surface::Iter iter = surface_.getIter();
  while (iter.line()) {
    while (iter.pixel()) {
      int avg = (iter.r() + iter.g() + iter.b()) / 3;
      iter.r() = avg;
      iter.b() = avg;
      iter.g() = avg;
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

void Image::MirrorUD() {
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

void Image::MirrorLR() {
}

void Image::Posterize() {
  ci::Surface::Iter iter = surface_.getIter();
  while (iter.line()) {
    while (iter.pixel()) {
      for (int rgb = 0; rgb <= 255; rgb += kPosterize) {
        if (iter.r() >= rgb && iter.r() <= kPosterize) {
          iter.r() = std::min((rgb + rgb + kPosterize) / 2, 255);
        }
        if (iter.g() >= rgb && iter.g() <= kPosterize) {
          iter.g() = std::min((rgb + rgb + kPosterize) / 2, 255);
        }
        if (iter.b() >= rgb && iter.b() <= kPosterize) {
          iter.b() = std::min((rgb + rgb + kPosterize) / 2, 255);
        }
      }
    }
  }
}

void Image::ColorSplash() {
  ci::Surface::Iter iter = surface_.getIter();
  while (iter.line()) {
    while (iter.pixel()) {
      if (iter.r() < iter.g() + iter.b()) {
        int avg = (iter.r() + iter.g() + iter.b()) / 3;
        iter.r() = avg;
        iter.b() = avg;
        iter.g() = avg;
      }
    }
  }
}

void Image::Pixelate() {
  auto width = static_cast<float>(surface_.getWidth());
  auto height = static_cast<float>(surface_.getHeight());
  for (float x = 0; x <= width; x += kFillEdges) {
    for (float y = 0; y <= height; y += kFillEdges) {
      FillBlock(glm::vec2(x, y), surface_.getPixel(glm::vec2(x, y)),
                kFillEdges);
    }
  }
}

void Image::FillBlock(const glm::vec2& pos,
                      const cinder::ColorAT<uint8_t>& color, float side_len) {
  for (float x = pos.x; x < pos.x + side_len; x++) {
    for (float y = pos.y; y < pos.y + side_len; y++) {
      if (x < surface_.getWidth() && y < surface_.getHeight()) {
        surface_.setPixel(glm::vec2(x, y), color);
      }
    }
  }
}

void Image::FilterSunset() {
  ci::Surface::Iter iter = surface_.getIter();
  while (iter.line()) {
    while (iter.pixel()) {
      iter.g() = static_cast<uint8_t>(0.80 * iter.g());
      iter.b() = static_cast<uint8_t>(0.80 * iter.b());
    }
  }
}

void Image::FillEdges() {
}

void Image::HandleInputFilter(const std::string& filter) {
  if (filter == "ZeroBlue") {
    ZeroBlue();
  }
  if (filter == "Grayscale") {
    Grayscale();
  }
  if (filter == "Negate") {
    Negate();
  }
  if (filter == "Sepia Filter") {
    FilterSepia();
  }
  if (filter == "Mirror") {
    MirrorUD();
  }
  if (filter == "Posterize") {
    Posterize();
  }
  if (filter == "Color Splash") {
    ColorSplash();
  }
  if (filter == "Pixelate") {
    Pixelate();
  }
  if (filter == "Sunset Filter") {
    FilterSunset();
  }
  if (filter == "Fill Edges") {
    FillEdges();
  }
}

void Image::SetModifier(const std::string& modifier) {
  modifier_ = modifier;
}

void Image::Reset() {
  surface_ = original_surface_.clone();
}

bool Image::ValidPixel(const glm::vec2& vec) {
  return (vec.x < surface_.getWidth() && vec.x >= 0 &&
          vec.y < surface_.getHeight() && vec.y >= 0);
}

}  // namespace image_editor