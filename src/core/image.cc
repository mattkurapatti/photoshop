#include <core/image.h>

#include <ios>

namespace image_editor {

Image::Image(size_t num_rows, size_t num_cols) {
  pixels_.resize(num_rows);
  for(std::vector<pixel> &col: pixels_) {
    col.resize(num_cols);
    for(pixel &pix: col) {
      // fills 2d vector with white pixels
      pix.r = 255;
      pix.g = 255;
      pix.b = 255;
    }
  }
}

Image::Image(std::vector<std::vector<pixel>> pixels) {
  pixels_ = std::move(pixels);
}
const std::vector<std::vector<pixel>> &Image::GetPixels() const {
  return pixels_;
}

}  // namespace image_editor