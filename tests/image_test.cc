#include <core/image.h>

#include <catch2/catch.hpp>
#include <vector>

TEST_CASE("Constructor, Loading & Saving Surfaces") {
  SECTION("Constructor") {
    image_editor::Image image_(ci::loadImage("images/testgreen.png"));
    ci::Surface::Iter iter = image_.GetSurface().getIter();
    while (iter.line()) {
      while (iter.pixel()) {
        REQUIRE(iter.r() == 0);
        REQUIRE(iter.g() == 255);
        REQUIRE(iter.b() == 0);
      }
    }
  }
  SECTION("Loading Image") {
    image_editor::Image image_(ci::loadImage("images/default.jpg"));
    image_.LoadSurface("images/testgreen.png");
    ci::Surface::Iter iter = image_.GetSurface().getIter();
    while (iter.line()) {
      while (iter.pixel()) {
        REQUIRE(iter.r() == 0);
        REQUIRE(iter.g() == 255);
        REQUIRE(iter.b() == 0);
      }
    }
  }
  SECTION("Saving Image") {
    image_editor::Image image_(ci::loadImage("images/default.jpg"));
    image_.LoadSurface("images/testgreen.png");
    image_.SaveSurface("images/testgreensaved.png");
    // load image2 with the saved file above to test rgb values of saved file
    image_editor::Image image2(ci::loadImage("images/testgreensaved.png"));
    ci::Surface::Iter iter = image2.GetSurface().getIter();
    while (iter.line()) {
      while (iter.pixel()) {
        REQUIRE(iter.r() == 0);
        REQUIRE(iter.g() == 255);
        REQUIRE(iter.b() == 0);
      }
    }
  }
}

// test modifiers
TEST_CASE("Draw function") {
  SECTION("Draw function") {
    image_editor::Image image(ci::loadImage("images/default.jpg"));
    image.Draw(glm::vec2(5, 5), ci::Color("black"), 1);
    ci::Surface surface = image.GetSurface();
    REQUIRE(surface.getPixel(glm::vec2(5, 5)) == ci::Color(0, 0, 0));
    REQUIRE(surface.getPixel(glm::vec2(5, 6)) == ci::Color(0, 0, 0));
    REQUIRE(surface.getPixel(glm::vec2(0, 0)) == ci::Color(255, 255, 255));
  }
}

// test filters
TEST_CASE("Basic filters") {
  SECTION("Zero Blue") {
    image_editor::Image image(ci::loadImage("images/moon.png"));
    image.ZeroBlue();
    ci::Surface::Iter iter = image.GetSurface().getIter();
    while (iter.line()) {
      while (iter.pixel()) {
        REQUIRE(iter.b() == 0);
      }
    }
  }
  SECTION("Grayscale") {
    image_editor::Image image(ci::loadImage("images/testgreen.png"));
    image.Grayscale();
    ci::Surface::Iter iter = image.GetSurface().getIter();
    while (iter.line()) {
      while (iter.pixel()) {
        REQUIRE(iter.r() == 85);
        REQUIRE(iter.g() == 85);
        REQUIRE(iter.b() == 85);
      }
    }
  }
  SECTION("Negate") {
    image_editor::Image image(ci::loadImage("images/testgreen.png"));
    image.Negate();
    ci::Surface::Iter iter = image.GetSurface().getIter();
    while (iter.line()) {
      while (iter.pixel()) {
        REQUIRE(iter.r() == 255);
        REQUIRE(iter.g() == 0);
        REQUIRE(iter.b() == 255);
      }
    }
  }
  SECTION("Sepia Filter") {
    image_editor::Image image(ci::loadImage("images/testgreen.png"));
    image.FilterSepia();
    ci::Surface::Iter iter = image.GetSurface().getIter();
    while (iter.line()) {
      while (iter.pixel()) {
        REQUIRE(iter.r() == 196);
        REQUIRE(iter.g() == 174);
        REQUIRE(iter.b() == 136);
      }
    }
  }
  SECTION("Mirror") {
    image_editor::Image image(ci::loadImage("images/moon.png"));
    image.MirrorUD();
    ci::Surface surf = image.GetSurface();
    ci::Surface::Iter iter = surf.getIter();
    auto height = static_cast<float>(surf.getHeight());
    auto width = static_cast<float>(surf.getWidth());

    while (iter.line()) {
      while (iter.pixel()) {
        glm::vec2 pos = iter.getPos();
        ci::ColorA color = surf.getPixel(
            glm::vec2(glm::vec2(width - pos.x - 1, height - pos.y - 1)));
        REQUIRE(iter.r() == color.r);
        REQUIRE(iter.g() == color.g);
        REQUIRE(iter.b() == color.b);
      }
    }
  }
  SECTION("Posterize") {
    image_editor::Image image(ci::loadImage("images/testgreen.png"));
    image.Posterize();
    ci::Surface::Iter iter = image.GetSurface().getIter();
    while (iter.line()) {
      while (iter.pixel()) {
        REQUIRE(iter.r() == 37);
        REQUIRE(iter.g() == 255);
        REQUIRE(iter.b() == 37);
      }
    }
  }
  SECTION("Filter Sunset") {
    image_editor::Image image(ci::loadImage("images/testgreen.png"));
    image.FilterSunset();
    ci::Surface::Iter iter = image.GetSurface().getIter();
    // filter sunset multiplies g, b values by 0.8
    while (iter.line()) {
      while (iter.pixel()) {
        REQUIRE(iter.r() == 0);
        REQUIRE(iter.g() == 204);
        REQUIRE(iter.b() == 0);
      }
    }
  }
  SECTION("Reset") {
    image_editor::Image image(ci::loadImage("images/testgreen.png"));
    image.FilterSunset();
    image.Reset();
    ci::Surface::Iter iter = image.GetSurface().getIter();
    // after applying a filter, then resetting, each pixel should still be green
    while (iter.line()) {
      while (iter.pixel()) {
        REQUIRE(iter.r() == 0);
        REQUIRE(iter.g() == 255);
        REQUIRE(iter.b() == 0);
      }
    }
  }
}
