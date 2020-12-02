#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "image_window.h"

namespace image_editor {

namespace visualizer {

class ImageEditorApp : public ci::app::App {
 public:
  ImageEditorApp();

  void draw() override;
  void mouseDown(ci::app::MouseEvent event) override;
  void mouseDrag(ci::app::MouseEvent event) override;
  void ImageEditorApp::fileDrop(ci::app::FileDropEvent event) override;
  void keyDown(ci::app::KeyEvent event) override;

  // provided that you can see the entire UI on your screen.
  const double kWindowSize = 875;
  const double kMargin = 100;
  const double kImageSizeFactor = 2.0 / 3;

 private:
  ImageWindow image_window_;
};

}  // namespace visualizer

}  // namespace image_editor
