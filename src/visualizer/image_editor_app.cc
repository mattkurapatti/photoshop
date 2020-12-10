#include <core/image.h>
#include <visualizer/image_editor_app.h>

namespace image_editor {

namespace visualizer {

ImageEditorApp::ImageEditorApp()
    : image_window_(glm::vec2(kMargin, kMargin),
                    glm::vec2(kWindowSize * kImageSizeFactor - kMargin,
                              kWindowSize - 2 * kMargin)),
      image_sidebar_(
          glm::vec2(kWindowSize * kImageSizeFactor + kMargin, kMargin),
          glm::vec2(kWindowSize - kMargin / 2,
                    kWindowSize - kMargin)) {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
}

void ImageEditorApp::draw() {
  ci::Color8u background_color(192, 192, 192);  // silver
  ci::gl::clear(background_color);

  glm::vec2 mids((kWindowSize * kImageSizeFactor - kMargin) / 2.0f, -15.0);
  std::string message = "Press esc to reset image, delete for blank sheet";
  ci::gl::drawStringCentered(message, glm::vec2(kMargin, kMargin) + mids, ci::Color("black"));

  image_window_.Draw();
  image_sidebar_.Draw();
}

void ImageEditorApp::mouseDown(ci::app::MouseEvent event) {
  image_window_.HandleBrush(event.getPos(), image_sidebar_.GetSelectedColor());
  image_sidebar_.HandleBrush(event.getPos(), image_window_.GetImage());
}

void ImageEditorApp::mouseDrag(ci::app::MouseEvent event) {
  image_window_.HandleBrush(event.getPos(), image_sidebar_.GetSelectedColor());
}

void ImageEditorApp::fileDrop(ci::app::FileDropEvent event) {
  const ci::fs::path& path = event.getFile(0);
  image_window_.LoadSurface(path);
}

void ImageEditorApp::keyDown(ci::app::KeyEvent event) {
  switch (event.getCode()) {
    case ci::app::KeyEvent::KEY_ESCAPE: {
      image_window_.ResetImage();
      break;
    }
    case ci::app::KeyEvent::KEY_DELETE: {
      image_window_.Clear();
      break;
    }
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
  }
}

}  // namespace visualizer

}  // namespace image_editor
