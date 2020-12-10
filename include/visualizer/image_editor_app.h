#pragma once

#include "cinder/app/App.h"
#include "cinder/app/RendererGl.h"
#include "cinder/gl/gl.h"
#include "image_window.h"
#include "image_sidebar.h"

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

  const double kBrushFactor = 2.0;

 private:
  ImageWindow image_window_;
  ImageSidebar image_sidebar_;

  double brush_radius_;
};

}  // namespace visualizer

}  // namespace image_editor
