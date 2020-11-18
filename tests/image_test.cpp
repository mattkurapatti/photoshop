#include <core/image.h>
#include <core/model.h>
#include <core/parser.h>

#include <catch2/catch.hpp>
#include <fstream>
#include <iostream>
#include <vector>

TEST_CASE(
    "Checking validity of class to image map which is populated through "
    "operator overloaded <<") {
  std::ifstream images_file("data/testimages");
  std::ifstream labels_file("data/testlabels");
  naivebayes::Parser processor(images_file, labels_file);
  std::map<int, std::vector<naivebayes::Image>> class_to_image =
      processor.GetClassToImage();

  SECTION("Class to image map has right size for keys and values") {
    REQUIRE(class_to_image.size() == 10);

    std::vector<size_t> test_sizes{1, 2, 1, 1, 1, 1, 1, 1, 1, 1};
    for (size_t index = 0; index < class_to_image.size(); index++) {
      REQUIRE(class_to_image.at(index).size() == test_sizes.at(index));
    }
  }

  SECTION("Check image value correct for random images") {
    REQUIRE(class_to_image.at(9).at(0).GetImage() ==
            "+#### #  # +##+    #    #");
    REQUIRE(class_to_image.at(1).at(1).GetImage() ==
            " +##    #    #    #  +###");
    REQUIRE(class_to_image.at(3).at(0).GetImage() ==
            "++##+    # +##    # #### ");
  }
}
