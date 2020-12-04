#pragma once
#include <map>
#include <string>
#include <vector>

#include "cinder/gl/gl.h"

namespace image_editor {

class Image {
 public:
  explicit Image(ci::Surface surface);
  void LoadSurface(const ci::fs::path& path);
  void SaveSurface(const ci::fs::path& path);

  ci::Surface GetSurface() const;

  void ZeroBlue();
  void Negate();
  void FilterSepia();
  void Mirror();
  void Posterize();
  void ColorSplash();
  void Pixelate();
  void FilterSunset();
  void CorrectRedEye();
  void FillEdges();

  const int kPosterize = 75;

 private:
  ci::Surface surface_;
};

}  // namespace image_editor