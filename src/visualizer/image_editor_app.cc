#include <core/image.h>
#include <visualizer/image_editor_app.h>

namespace image_editor {

namespace visualizer {

ImageEditorApp::ImageEditorApp()
    : image_window_(glm::vec2(kMargin, kMargin),
                    glm::vec2(kWindowSize * kImageSizeFactor - kMargin,
                              kWindowSize - 2 * kMargin)) {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
}

void ImageEditorApp::draw() {
  ci::Color8u background_color(255, 255, 255);  // white
  ci::gl::clear(background_color);

  image_window_.Draw();
}

void ImageEditorApp::mouseDown(ci::app::MouseEvent event) {
  image_window_.HandleBrush(event.getPos(), 20);
}

void ImageEditorApp::mouseDrag(ci::app::MouseEvent event) {
  image_window_.HandleBrush(event.getPos(), 20);
}

void ImageEditorApp::fileDrop(ci::app::FileDropEvent event) {
  const ci::fs::path& path = event.getFile(0);
  image_window_.LoadSurface(path);
}

void ImageEditorApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_o: {
      ci::fs::path path = getOpenFilePath("", ci::ImageIo::getLoadExtensions());
      image_window_.LoadSurface(path);
      break;
    }
    case ci::app::KeyEvent::KEY_s: {
      ci::fs::path path = getSaveFilePath();
      image_window_.SaveSurface(path);
      break;
    }
    case ci::app::KeyEvent::KEY_z: {
      image_window_.ZeroBlue();
      break;
    }
    case ci::app::KeyEvent::KEY_n: {
      image_window_.Negate();
      break;
    }
    case ci::app::KeyEvent::KEY_1: {
      image_window_.FilterSepia();
      break;
    }
    case ci::app::KeyEvent::KEY_DELETE:
      break;
  }
}

}  // namespace visualizer

}  // namespace image_editor
