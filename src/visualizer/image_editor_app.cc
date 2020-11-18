#include <core/image.h>
#include <visualizer/image_editor_app.h>

namespace image_editor {

namespace visualizer {

ImageEditorApp::ImageEditorApp()
    : image_window_(glm::vec2(kMargin, kMargin), kImageDimension,
                 kWindowSize - 2 * kMargin) {
  ci::app::setWindowSize((int)kWindowSize, (int)kWindowSize);
}

void ImageEditorApp::draw() {

}

void ImageEditorApp::mouseDown(ci::app::MouseEvent event) {
  image_window_.HandleBrush(event.getPos());
}

void ImageEditorApp::mouseDrag(ci::app::MouseEvent event) {
  image_window_.HandleBrush(event.getPos());
}

void ImageEditorApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_RETURN:
      break;
    case ci::app::KeyEvent::KEY_DELETE:
      break;
  }
}

}  // namespace visualizer

}  // namespace image_editor
