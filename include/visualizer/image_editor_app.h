#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "image_sidebar.h"
#include "image_window.h"

namespace image_editor {

namespace visualizer {

class ImageEditorApp : public ci::app::App {
 public:
  /**
   * Default constructor, initializes sidebar and image window
   */
  ImageEditorApp();

  /**
   * Draws image sidebar, image window, and strings for instructions to the user
   */
  void draw() override;

  /**
   * Recognizes when the user has clicked and either modifies the image, applies
   * the clicked filter, or changes the modifier based on where the button is
   * pressed
   * @param event MouseEvent which holds information such as position clicked
   */
  void mouseDown(ci::app::MouseEvent event) override;

  /**
   * Recognizes when the user has dragged their mouse and either modifies the
   * image, applies the clicked filter, or changes the modifier based on where
   * the button is pressed
   * @param event MouseEvent holding information such as position
   */
  void mouseDrag(ci::app::MouseEvent event) override;

  /**
   * Loads new image when new file is detected
   * @param event FileDropEvent which contains path information
   */
  void ImageEditorApp::fileDrop(ci::app::FileDropEvent event) override;

  /**
   * Recognizes when the user presses a key and handles the input appropiately
   * @param event KeyEvent holding information about which key was pressed
   */
  void keyDown(ci::app::KeyEvent event) override;

  // provided that you can see the entire UI on your screen.
  const double kWindowSize = 875;
  const double kMargin = 100;
  const double kImageSizeFactor = 2.0 / 3;

  const double kBrushFactor = 2.0;

 private:
  ImageWindow image_window_;
  ImageSidebar image_sidebar_;

  double brush_radius_;
};

}  // namespace visualizer

}  // namespace image_editor
