#pragma once
#include <map>
#include <string>
#include <vector>

#include "cinder/gl/gl.h"

namespace image_editor {

class Image {
 public:
  /**
   * Constructs Image with surface
   * @param surface Surface representing image
   */
  explicit Image(ci::Surface surface);

  /**
   * Updates surface_ private field based on image from new path
   * @param path path to image file
   */
  void LoadSurface(const ci::fs::path& path);

  /**
   * Saved current surface_ field to image file
   * @param path path to image file
   */
  void SaveSurface(const ci::fs::path& path);

  ci::Surface GetSurface() const;

  /**
   * Handles touch input at specifies position by other drawing, fixing red eye,
   * or blurring
   * @param relative_pos floats between 0 and 1 representing relative position
   * of click
   * @param color color of change (for drawing only)
   * @param brush_radius radius of effect
   */
  void HandleBrush(const glm::vec2& relative_pos, const ci::Color& color,
                   double brush_radius);
  /**
   * Draws with specified color at position pos
   * @param pos vec2 representing position to be drawn at
   * @param color color to be drawn
   * @param brush_radius radius of click
   */
  void Draw(const glm::vec2& pos, const ci::Color& color, double brush_radius);

  /**
   * Replaces red-eye within area of effect
   * @param pos vec2 representing position clicked
   * @param brush_radius double representing area of effect
   */
  void CorrectRedEye(const glm::vec2& pos, double brush_radius);

  /**
   * Blurs image at clicked position
   * @param pos vec2 representing clicked position
   */
  void Blur(const glm::vec2& pos);

  /**
   * Filter which sets all b values at 0
   */
  void ZeroBlue();

  /**
   * Replaces r, g, and b values with 255 - current r, g, and b values
   */
  void Negate();

  /**
   * Sets r, g, and b to the average of the r, g, and b values at each pixel
   */
  void Grayscale();

  /**
   * Based on Microsoft's algorithm for the Sepia Filter:
   * sets r to .393 * r + .769 * g + .189 * b
   * sets g to .349 * r + .686 * g + .168 * b
   * sets b to .272 * r + .534 * g + .131 * b
   */
  void FilterSepia();

  /**
   * Mirrors top of image to bottom
   */
  void MirrorUD();

  /**
   * Replaces each r, g, b value with nearby r, g, b value
   * Ex: All r, g, and b values between 0 and 75 are set to 37
   */
  void Posterize();

  /**
   * If the pixel is red, replace r, g, and b with the average r, g, and b value
   */
  void ColorSplash();

  /**
   * For each 10x10 pixel block, replaces every pixel with the pixel of the top
   * left corner
   */
  void Pixelate();

  /**
   * Sets g and b values to 0.80 of their current g and b values
   */
  void FilterSunset();

  /**
   * If the distance between the pixel and its neighbors are large, sets the
   * pixel to black, otherwise white
   */
  void FillEdges();

  /**
   * Calls appropiate filter method based on string
   * @param filter string representing filter method to call
   */
  void HandleInputFilter(const std::string& filter);

  /**
   * Changes modifier_ priv field based on inputted string
   * @param modifier string representing modifier
   */
  void SetModifier(const std::string& modifier);

  /**
   * Sets surface to original surface (before any filter or modifier method)
   */
  void Reset();

  const int kPosterize = 75;
  const double kFillEdges = 10.0;
  const float kRedEyeRadius = 17.5;

 private:
  ci::Surface original_surface_;
  ci::Surface surface_;
  std::string modifier_;

  double Distance(const glm::vec2& vec1, const glm::vec2& vec2) const;

  void FillBlock(const glm::vec2& pos, const cinder::ColorAT<uint8_t>& color,
                 double side_len);

  bool ValidPixel(const glm::vec2& vec);

  const double ColorDistance(ci::Surface::Iter iter, int xOff, int yOff);
};

}  // namespace image_editor