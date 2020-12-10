#pragma once

#include <core/image.h>

#include <glm/fwd.hpp>
#include <glm/vec2.hpp>

#include "cinder/gl/gl.h"

namespace image_editor {

namespace visualizer {

class ImageWindow {
 public:
  /**
   * Constructor for image window
   * @param top_left_corner vec2 representing top left corner
   * @param dimensions vec2 representing dimensions of image window
   */
  ImageWindow(const glm::vec2& top_left_corner, const glm::vec2& dimensions);

  /**
   * Draws box around window and image inside the box
   */
  void Draw() const;

  /**
   * Handles click with selected modifier
   * @param brush_screen_coords vec2 representing point of click
   * @param color Color representing current color if the user's current
   * modifier is to draw
   * @param brush_radius double representing area of effect
   */
  void HandleBrush(const glm::vec2& brush_screen_coords,
                   const cinder::Color& color, double brush_radius);

  /**
   * Loads default white image
   */
  void Clear();

  /**
   * Loads surface of new image specified by path
   * @param path path representing file path of new image
   */
  void LoadSurface(const ci::fs::path& path);

  /**
   * Saves surface to image file specified by path
   * @param path path representing file path where image is to be saved
   */
  void SaveSurface(const ci::fs::path& path);

  /**
   * Calls Image's ZeroBlue filter
   */
  void ZeroBlue();

  /**
   * Calls Image's Negate filter
   */
  void Negate();

  /**
   * Calls Image's Sepia filter
   */
  void FilterSepia();

  /**
   * Calls Image's Mirror filter
   */
  void Mirror();

  Image& GetImage();

  /**
   * Resets Image to most recently opened image file
   */
  void ResetImage();

 private:
  glm::vec2 top_left_corner_;

  glm::vec2 dimensions_;

  Image image_;
};

}  // namespace visualizer

}  // namespace image_editor
