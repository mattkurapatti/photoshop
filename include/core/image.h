#pragma once
#include <map>
#include <string>
#include <vector>

#include "cinder/gl/gl.h"

namespace image_editor {

class Image {
 public:
  Image(ci::Surface surface, const glm::vec2& top_left_corner,
        const glm::vec2& bottom_right_corner);
  void LoadSurface(const ci::fs::path& path);
  void SaveSurface(const ci::fs::path& path);

  ci::Surface GetSurface() const;

  void ZeroBlue();
  void Negate();

 private:
  ci::Surface surface_;
  glm::vec2 top_left_corner_;
  glm::vec2 bottom_right_corner_;
};

}  // namespace image_editor