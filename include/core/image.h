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

  void HandleBrush(const glm::vec2& relative_pos, const ci::Color& color, double brush_radius);
  void Draw(const glm::vec2& pos, const ci::Color& color, double brush_radius);
  void CorrectRedEye(const glm::vec2& pos);
  void Blur(const glm::vec2& pos);

  void ZeroBlue();
  void Negate();
  void Grayscale();
  void FilterSepia();
  void MirrorUD();
  void MirrorLR();
  void Posterize();
  void ColorSplash();
  void Pixelate();
  void FilterSunset();
  void FillEdges();



  const int kPosterize = 75;
  const int kFillEdges = 20;

  void HandleInputFilter(const std::string& filter);

  void SetModifier(const std::string& modifier);

  void Reset();

 private:
  ci::Surface original_surface_;
  ci::Surface surface_;
  std::string modifier_;

  double Distance(const glm::vec2& vec1, const glm::vec2& vec2) const;
};

}  // namespace image_editor