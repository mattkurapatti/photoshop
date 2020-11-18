#include <core/image.h>
#include <core/model.h>
#include <core/parser.h>

#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("Class probabilities correctly calculated") {
  std::ifstream training_images_file("data/testimages");
  std::ifstream training_labels_file("data/testlabels");
  naivebayes::Parser processor(training_images_file, training_labels_file);
  std::map<int, std::vector<naivebayes::Image>> class_to_image =
      processor.GetClassToImage();

  int naivebayes_k = 1;
  naivebayes::Model model(class_to_image, processor.GetImageCount(),
                          processor.GetSize(), naivebayes_k);
  model.TrainModel();
  SECTION("Test image with one label") {
    REQUIRE(model.GetClassProbabilities(0) == Approx(0.15384615384));
  }
  SECTION("Test image with two labels") {
    REQUIRE(model.GetClassProbabilities(1) == Approx(0.23076923076));
  }
}

TEST_CASE("Point probabilities correctly calculated") {
  std::ifstream training_images_file("data/testimages");
  std::ifstream training_labels_file("data/testlabels");
  naivebayes::Parser processor(training_images_file, training_labels_file);
  std::map<int, std::vector<naivebayes::Image>> class_to_image =
      processor.GetClassToImage();

  int naivebayes_k = 1;
  naivebayes::Model model(class_to_image, processor.GetImageCount(),
                          processor.GetSize(), naivebayes_k);
  model.TrainModel();
  SECTION("Test probability at random point") {
    REQUIRE(model.GetLocationProbabilities(2, 3) == Approx(0.66666666666));
  }
  SECTION("Test probability at point with some empty space") {
    REQUIRE(model.GetLocationProbabilities(3, 23) == Approx(0.66666666666));
  }
  SECTION("Test probability at point semi-shaded point ('+') ") {
    REQUIRE(model.GetLocationProbabilities(5, 0) == Approx(0.66666666666));
  }
}

TEST_CASE("Validation of file of test images works correctly") {
  std::ifstream training_images_file("data/testimages");
  std::ifstream training_labels_file("data/testlabels");
  naivebayes::Parser processor(training_images_file, training_labels_file);
  std::map<int, std::vector<naivebayes::Image>> class_to_image =
      processor.GetClassToImage();

  std::ifstream test_images_file("data/validationimages");
  std::ifstream test_labels_file("data/validationlabels");
  naivebayes::Parser processor_test(test_images_file, test_labels_file);
  std::map<int, std::vector<naivebayes::Image>> label_to_image_test =
      processor_test.GetClassToImage();

  naivebayes::Model model(class_to_image, label_to_image_test,
                          processor.GetImageCount(), processor.GetSize(), 1);
  model.TrainModel();
  model.TestModel();

  SECTION(
      "Check each likelihood score for first image in file "
      "data/validationimages") {
    naivebayes::Image image(5, "  ##  #  ##   ##   # ### ");
    std::vector<double> likelihood_vector{
        -5.5162248286988698, -8.8610518863891237, -9.4296147723306251,
        -9.1285847766666439, -8.8275547810026627, -9.1285847766666439,
        -8.2254947896747002, -8.5265247853386814, -7.9244647940107197,
        -8.8275547810026627};

    for (size_t index = 0; index < likelihood_vector.size(); index++) {
      REQUIRE(model.GetLikelihoodScores(image, index) ==
              Approx(likelihood_vector.at(index)));
    }
  }
  SECTION("Check accuracy is correct to ensure TestModel works") {
    REQUIRE(model.GetAccuracy() == 0.7);
  }
}

TEST_CASE("Save/load model basic functionality") {
  std::ifstream training_images_file("data/testimages");
  std::ifstream training_labels_file("data/testlabels");
  naivebayes::Parser processor(training_images_file, training_labels_file);
  std::map<int, std::vector<naivebayes::Image>> class_to_image =
      processor.GetClassToImage();

  int naivebayes_v = 2;
  int naivebayes_k = 1;
  naivebayes::Model model(class_to_image, processor.GetImageCount(),
                          processor.GetSize(), naivebayes_k);
  model.TrainModel();

  std::ofstream outfile;
  outfile.open("data/save_test_model1", std::ios::out | std::ios::trunc);
  model.SaveModel(outfile);

  std::ifstream infile;
  infile.open("data/save_test_model1");
  int numLines = 0;
  std::string unused;
  while (std::getline(infile, unused)) {
    ++numLines;
  }
  SECTION("Test file has right number of lines") {
    REQUIRE(numLines == 21);
  }
}
