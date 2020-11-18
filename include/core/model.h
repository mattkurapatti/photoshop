#pragma once
#include <fstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "image.h"

namespace naivebayes {

class Model {
 public:
  /**
   * Default constructor for Model, called specfically when loading model
   * from a file
   */
  Model();

  /**
   * Constructor model with data already read
   * @param class_to_image map of classes to vector of Images of specified class
   * @param image_count size_t representing number of images in training data
   * @param size size_t representing side length
   * @param k size_t representing k value for laplace smoothing
   */
  Model(const std::map<int, std::vector<Image>> &class_to_image,
        size_t image_count, size_t size, size_t k);

  /**
   * Constructor model with data already read
   * @param class_to_image map of classes to vector of Images of specified class
   * @param label_to_image_test map of labels to images in that class for
   * testing
   * @param image_count size_t representing number of images in training data
   * @param size size_t representing side length
   * @param k size_t representing k value for laplace smoothing
   */
  Model(const std::map<int, std::vector<Image>> &class_to_image,
        const std::map<int, std::vector<Image>> &label_to_image_test,
        size_t image_count, size_t size, size_t k);

  /**
   * Overloaded operator for reading in model from a file
   * @param input stream from which the model is read in
   * @param model specified model object
   * @return input stream
   */
  friend std::istream &operator>>(std::istream &input, Model &model);

  /**
   * Overloaded operator for outputting model to a file
   * @param output stream to which the model is outputted
   * @param model specified model object
   * @return output stream
   */
  friend std::ostream &operator<<(std::ostream &output, Model &model);

  /**
   * Returns map of class label to the probability for that class
   */
  double GetClassProbabilities(size_t label);

  /**
   * Returns map for probability at specific location
   */
  double GetLocationProbabilities(size_t label, size_t index);

  /**
   * Returns accuracy if model has been tested
   */
  double GetAccuracy();

  /**
   * Builds maps for class and location probabilities. For this function
   * to work, the class_to_images_ map must already be populated
   */
  void TrainModel();

  /**
   * After the model has been trained, this function will save the model to
   * a specified final name
   * @param filename string representing name of file to save to
   */
  void SaveModel(std::ostream &outfile);

  /**
   * Loads model from specified file name
   * @param filename Filename from which data should be loaded from
   */
  void LoadModel(std::istream &infile);

  /**
   * Tests model by classifying each image and verifying that the classification
   * is accurate to the label of the image
   */
  void TestModel();

  /**
   * Classifies the inputted image by finding max likelihood score
   * @param image which is to be classified
   * @return int representing the most likely classification label for the
   * inputted image
   */
  int ClassifyImage(const Image &image);

  /**
   * Returns map for likelihood score for each class for inputted image
   * @param image to get likelihood scores for
   * @return a map of labels to the likelihood score for the inputted image
   */
  double GetLikelihoodScores(const Image &image, int label);

 private:
  size_t image_count_;
  size_t size_;
  size_t k_;
  double model_accuracy_;
  std::map<int, std::vector<Image>> class_to_image_;
  std::map<int, std::vector<Image>> label_to_image_test_;
  std::map<int, double> class_to_probability_;
  std::map<int, std::vector<double>> location_to_shaded_probability_;
};
}  // namespace naivebayes
