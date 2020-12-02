#pragma once
#include <map>
#include <string>
#include <vector>
#include "cinder/gl/gl.h"

#include "image.h"

namespace image_editor {

struct pixel {
  float r;
  float g;
  float b;
};

class Image {
 public:
  Image(size_t num_rows, size_t num_cols);
  Image(std::vector<std::vector<pixel>> pixels);
  const std::vector<std::vector<pixel>>& GetPixels() const;
private:
  std::vector<std::vector<pixel>> pixels_;
};

}  // namespace image_editor