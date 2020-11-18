#include <core/model.h>
#include <core/parser.h>

#include <cstdlib>
#include <fstream>
#include <ios>
#include <limits>
#include <utility>

namespace naivebayes {

Model::Model() {
}

Model::Model(const std::map<int, std::vector<Image>> &class_to_image,
             size_t image_count, size_t size, size_t k)
    : class_to_image_(class_to_image),
      image_count_(image_count),
      size_(size),
      k_(k) {
}

Model::Model(const std::map<int, std::vector<Image>> &class_to_image,
             const std::map<int, std::vector<Image>> &label_to_image_test,
             size_t image_count, size_t size, size_t k)
    : class_to_image_(class_to_image),
      label_to_image_test_(label_to_image_test),
      image_count_(image_count),
      size_(size),
      k_(k) {
}

std::istream &operator>>(std::istream &input, Model &model) {
  std::string label;
  std::string class_probability;
  input >> label;

  if (label == "") {
    return input;
  }

  std::string next_line;
  std::getline(input, next_line);

  input >> class_probability;
  model.class_to_probability_[std::stoi(label)] = std::stod(class_probability);

  std::vector<double> vec;
  std::string location_probability;
  for (size_t index = 0; index < model.size_ * model.size_; index++) {
    input >> location_probability;
    vec.push_back(std::stod(location_probability));
  }
  model.location_to_shaded_probability_[stoi(label)] = vec;
  return input;
}

std::ostream &operator<<(std::ostream &output, Model &model) {
  output << model.size_ << std::endl;
  for (size_t class_key = 0;
       class_key < model.location_to_shaded_probability_.size(); class_key++) {
    output << class_key << std::endl;
    output << model.class_to_probability_[class_key] << " ";

    for (double probability :
         model.location_to_shaded_probability_[class_key]) {
      output << probability << " ";
    }

    output << std::endl;
  }
  return output;
}

double Model::GetClassProbabilities(size_t label) {
  return class_to_probability_.at(label);
}

double Model::GetLocationProbabilities(size_t label, size_t index) {
  return location_to_shaded_probability_.at(label).at(index);
}

void Model::TrainModel() {
  size_t laplace_smoothing_v = 2;

  for (size_t class_val = 0; class_val < class_to_image_.size(); class_val++) {
    double current_class_count = class_to_image_[class_val].size();

    double numerator = k_ + current_class_count;
    double denominator = k_ * laplace_smoothing_v + image_count_;
    class_to_probability_[class_val] = numerator / denominator;
  }

  for (size_t class_key = 0; class_key < class_to_image_.size(); class_key++) {
    std::vector<double> shaded_probabilities;

    for (size_t point_index = 0; point_index < size_ * size_; point_index++) {
      double shaded_number = 0;

      for (const Image &image : class_to_image_[class_key]) {
        if (image.IsShaded(point_index)) {
          shaded_number++;
        }
      }

      double num_class_images = class_to_image_[class_key].size();
      double numerator = k_ + shaded_number;
      double denominator = k_ * laplace_smoothing_v + num_class_images;
      shaded_probabilities.push_back(numerator / denominator);
    }

    location_to_shaded_probability_[class_key] = shaded_probabilities;
  }
}

void Model::SaveModel(std::ostream &outfile) {
  outfile << *this;
}

void Model::LoadModel(std::istream &infile) {
  infile >> size_;
  while (infile >> *this);
}

void Model::TestModel() {
  size_t count_correct_classification = 0;
  size_t count_total_classification = 0;

  for (size_t class_key = 0; class_key < class_to_probability_.size();
       class_key++) {
    for (const Image& image : label_to_image_test_[class_key]) {
      int max_label = ClassifyImage(image);

      if (max_label == class_key) {
        count_correct_classification++;
      }
      count_total_classification++;
    }
  }

  model_accuracy_ =
      1.0 * count_correct_classification / count_total_classification;
}

int Model::ClassifyImage(const Image &image) {
  size_ = image.GetSize();
  std::map<int, double> label_to_likelihoodscore;

  for (size_t label = 0; label < class_to_probability_.size(); label++) {
    double likelihood_score = GetLikelihoodScores(image, label);
    label_to_likelihoodscore[label] = likelihood_score;
  }

  int max_label = 0;
  double max_likelihood = -std::numeric_limits<double>::infinity();

  for (size_t label = 0; label < class_to_probability_.size(); label++) {
    if (label_to_likelihoodscore[label] > max_likelihood) {
      max_label = label;
      max_likelihood = label_to_likelihoodscore[label];
    }
  }
  return max_label;
}

double Model::GetLikelihoodScores(const Image &image, int label) {
  double likelihood_score = std::log10(class_to_probability_.at(label));

  for (size_t point_index = 0; point_index < size_ * size_; point_index++) {
    double shaded_probability =
        location_to_shaded_probability_.at(label).at(point_index);

    if (image.IsShaded(point_index)) {
      likelihood_score += std::log10(shaded_probability);
    } else {
      likelihood_score += std::log10(1 - shaded_probability);
    }
  }

  return likelihood_score;
}

double Model::GetAccuracy() {
  return model_accuracy_;
}
}  // namespace naivebayes