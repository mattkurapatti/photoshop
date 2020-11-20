#include <core/image.h>
#include <visualizer/image_editor_app.h>

namespace image_editor {

namespace visualizer {

ImageEditorApp::ImageEditorApp()
    : image_window_(
          glm::vec2(kMargin, kMargin),
          glm::vec2(kWindowSize * kImageSizeFactor, kWindowSize - kMargin)) {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
}

void ImageEditorApp::draw() {
  ci::Color8u background_color(255, 255, 255);  // white
  ci::gl::clear(background_color);

  image_window_.Draw();
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
