#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

namespace naivebayes {
class Image {
 public:
  /**
   * Constructor for Image Object
   * @param label an int representing the class
   */
  explicit Image(int label);

  /**
   * Constructor which specified image string and size
   * @param size size_t representing side length size of image
   * @param image string representing image
   */
  Image(size_t size, std::string image);

  /**
   * overloaded operator to read in one image at a time from file
   * @param input stream which is being read from
   * @param image related Image object
   * @return stream being read from
   */
  friend std::istream &operator>>(std::istream &input, Image &image);

  /**
   * Returns private label field
   * @return int representing label of specified image
   */
  int GetLabel() const;

  /**
   * Returns size of image
   * @return size_t representing side length of image
   */
  size_t GetSize() const;

  /**
   * Returns private field representing image
   * @return string representing image
   */
  std::string GetImage() const;

  /**
   * Returns true if the image is "+" or "#" at the specified index
   */
  bool IsShaded(size_t index) const;

 private:
  std::string image_;
  int label_;
  size_t size_;
};
}  // namespace naivebayes