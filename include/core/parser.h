#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "image.h"

namespace naivebayes {

class Parser {

 public:
  /**
   * Default constructor
   */
  Parser();

  /**
   * Constructor for InputProcessor
   * @param training_images_filename string representing filename of images
   * @param training_labels_filename string representing filename of labels
   */
  Parser(std::istream& images_file, std::istream& labels_file);

  /**
   * Reads in files based on input names in private fields
   */
  void ReadFiles(std::istream& training_images_file,
                 std::istream& training_labels_file);

  /**
   * Returns class to image private field
   * @return a map of each class to the images in the class from the input
   */
  const std::map<int, std::vector<Image>> Parser::GetClassToImage() const;

  /**
   * Returns number of images in specified input
   * @return size_t representing number of images
   */
  size_t Parser::GetImageCount() const;

  /**
   * Returns side length of image
   * @return size_t representing side length of each image
   */
  size_t Parser::GetSize() const;

 private:
  size_t size_;
  std::vector<Image> image_list_;
};

}  // namespace naivebayes