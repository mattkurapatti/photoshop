#include <core/image.h>
#include <core/model.h>
#include <core/parser.h>

#include <algorithm>
#include <fstream>
#include <ios>
#include <iostream>

int main(int argc, char *argv[]) {
  if (argc <= 1) {
    std::cout << "Input an argument!";
    return 0;
  }

  int naivebayes_k = 1;

  int train_images_idx = 1;
  int train_labels_idx = 2;

  int test_images_idx = 1;
  int test_labels_idx = 2;

  int load_file_idx = 1;

  int train_index = -1;
  int save_index = -1;
  int load_index = -1;
  int test_index = -1;
  int index = 1;

  // https://stackoverflow.com/questions/48333430/iterate-through-argv
  for (char **pargv = argv + 1; *pargv != argv[argc]; pargv++) {
    if (std::string(*pargv) == "train") {
      train_index = index;
    }
    if (std::string(*pargv) == "save") {
      save_index = index;
    }
    if (std::string(*pargv) == "load") {
      load_index = index;
    }
    if (std::string(*pargv) == "test") {
      test_index = index;
    }
    index++;
  }

  naivebayes::Model model;
  naivebayes::Parser processor;
  std::map<int, std::vector<naivebayes::Image>> class_to_image;

  if (train_index != -1) {
    std::string training_images_filename = argv[train_index + train_images_idx];
    std::string training_labels_filename = argv[train_index + train_labels_idx];
    std::ifstream training_images_file(training_images_filename);
    std::ifstream training_labels_file(training_labels_filename);

    if (!training_images_file || !training_labels_file) {
      std::cout << "You must put two valid filenames after the train parameter";
    }

    processor = naivebayes::Parser(training_images_file, training_labels_file);
    class_to_image = processor.GetClassToImage();

  } else if (load_index != -1 && argc == 6) {
    std::string test_images_filename = argv[test_index + test_images_idx];
    std::string test_labels_filename = argv[test_index + test_labels_idx];
    std::ifstream test_images_file(test_images_filename);
    std::ifstream test_labels_file(test_labels_filename);

    if (!test_images_file || !test_labels_file) {
      std::cout << "You must put two valid filenames after the test parameter";
      return 0;
    }

    naivebayes::Parser processor_test(test_images_file, test_labels_file);
    std::map<int, std::vector<naivebayes::Image>> label_to_image_test =
        processor_test.GetClassToImage();
    model = naivebayes::Model(class_to_image, label_to_image_test,
                              processor.GetImageCount(), processor.GetSize(),
                              naivebayes_k);

    std::string load_filename = argv[load_index + load_file_idx];
    std::ifstream infile(load_filename);
    model.LoadModel(infile);
    model.TestModel();
    std::cout << "Your model had an accuracy of " << model.GetAccuracy()
              << " with the loaded data!";
    return 0;

  } else {
    std::cout << "You must train or load a model before saving/testing it! "
                 "Make sure to put filenames after the test/load parameters";
    return 0;
  }

  if (test_index != -1) {
    std::string test_images_filename = argv[test_index + test_images_idx];
    std::string test_labels_filename = argv[test_index + test_labels_idx];
    std::ifstream test_images_file(test_images_filename);
    std::ifstream test_labels_file(test_labels_filename);
    naivebayes::Parser processor_test(test_images_file, test_labels_file);
    std::map<int, std::vector<naivebayes::Image>> label_to_image_test =
        processor_test.GetClassToImage();
    model = naivebayes::Model(class_to_image, label_to_image_test,
                              processor.GetImageCount(), processor.GetSize(),
                              naivebayes_k);

    model.TrainModel();
    model.TestModel();
  }
  if (save_index != -1) {
    model = naivebayes::Model(class_to_image, processor.GetImageCount(),
                              processor.GetSize(), naivebayes_k);
    model.TrainModel();

    int save_file_index = 1;
    std::string save_filename = argv[save_index + save_file_index];

    std::ofstream outfile;
    outfile.open(save_filename, std::ios::out | std::ios::trunc);
    model.SaveModel(outfile);
  }

  return 0;
}
