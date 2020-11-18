#include <core/image.h>

#include <cmath>
#include <ios>
#include <utility>

namespace naivebayes {

Image::Image(int label) : label_(label) {
}

Image::Image(size_t size, std::string image)
    : size_(size), image_(std::move(image)) {
}

int Image::GetLabel() const {
  return label_;
}

size_t Image::GetSize() const {
  return size_;
}

std::string Image::GetImage() const {
  return image_;
}

bool Image::IsShaded(size_t index) const {
  return (image_.at(index) == '+' || image_.at(index) == '#');
}

std::istream &operator>>(std::istream &input, Image &image) {
  std::string image_string;
  std::string current_line;

  // get first line to check size
  std::getline(input, image_string);
  image.size_ = image_string.size();

  // start at index 1 since first line was already read in
  for (size_t index = 1; index < image.size_; index++) {
    std::getline(input, current_line);
    image_string += current_line;
  }
  image.image_ = image_string;
  return input;
}
}  // namespace naivebayes
