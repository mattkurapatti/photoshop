#include <core/parser.h>

#include <ios>

namespace naivebayes {

Parser::Parser() {
}

Parser::Parser(std::istream& images_file, std::istream& labels_file) {
  ReadFiles(images_file, labels_file);
}

void Parser::ReadFiles(std::istream& training_images_file,
                       std::istream& training_labels_file) {
  if (training_labels_file && training_images_file) {
    int counter = 0;

    while (training_labels_file) {
      counter++;

      int label_line = -1;
      training_labels_file >> label_line;
      if (label_line == -1) {
        return;
      }

      naivebayes::Image i(label_line);
      training_images_file >> i;
      size_ = i.GetSize();
      image_list_.push_back(i);
    }
  }
}

const std::map<int, std::vector<Image>> Parser::GetClassToImage() const {
  std::map<int, std::vector<Image>> class_to_image;

  for (const Image& image : image_list_) {
    class_to_image[image.GetLabel()].push_back(image);
  }
  return class_to_image;
}

size_t Parser::GetImageCount() const {
  return image_list_.size();
}

size_t Parser::GetSize() const {
  return size_;
}

}  // namespace naivebayes