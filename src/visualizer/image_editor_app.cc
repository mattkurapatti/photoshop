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
          glm::vec2(kWindowSize - kMargin / 2, kWindowSize - kMargin)),
      brush_radius_(kBrushFactor) {
  ci::app::setWindowSize(static_cast<int>(kWindowSize),
                         static_cast<int>(kWindowSize));
}

void ImageEditorApp::draw() {
  ci::Color8u background_color(192, 192, 192);  // silver
  ci::gl::clear(background_color);

  glm::vec2 mids((kWindowSize * kImageSizeFactor - kMargin) / 2.0f, -15.0);
  std::string message =
      "Press esc to reset image, press delete for blank sheet";
  ci::gl::drawStringCentered(message, glm::vec2(kMargin, kMargin) + mids,
                             ci::Color("black"));

  // https://stackoverflow.com/questions/13686482/c11-stdto-stringdouble-no-trailing-zeros
  std::string rounded_val =
      std::to_string(std::ceil(brush_radius_ / 2.0 * 100.0) / 100.0);
  rounded_val.erase(rounded_val.find_last_not_of('0') + 1, std::string::npos);
  rounded_val.erase(rounded_val.find_last_not_of('.') + 1, std::string::npos);
  std::string message_brush_size =
      "Use numbers 0-9 to adjust brush size. Current Size: " + rounded_val;
  ci::gl::drawStringCentered(
      message_brush_size,
      glm::vec2(kMargin, kWindowSize - kMargin + 25.0) + mids,
      ci::Color("black"));

  image_window_.Draw();
  image_sidebar_.Draw();
}

void ImageEditorApp::mouseDown(ci::app::MouseEvent event) {
  image_window_.HandleBrush(event.getPos(), image_sidebar_.GetSelectedColor(),
                            brush_radius_);
  image_sidebar_.HandleBrush(event.getPos(), image_window_.GetImage());
}

void ImageEditorApp::mouseDrag(ci::app::MouseEvent event) {
  image_window_.HandleBrush(event.getPos(), image_sidebar_.GetSelectedColor(),
                            brush_radius_);
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
    case ci::app::KeyEvent::KEY_1: {
      brush_radius_ = kBrushFactor * 1;
      break;
    }
    case ci::app::KeyEvent::KEY_2: {
      brush_radius_ = kBrushFactor * 2;
      break;
    }
    case ci::app::KeyEvent::KEY_3: {
      brush_radius_ = kBrushFactor * 3;
      break;
    }
    case ci::app::KeyEvent::KEY_4: {
      brush_radius_ = kBrushFactor * 4;
      break;
    }
    case ci::app::KeyEvent::KEY_5: {
      brush_radius_ = kBrushFactor * 5;
      break;
    }
    case ci::app::KeyEvent::KEY_6: {
      brush_radius_ = kBrushFactor * 6;
      break;
    }
    case ci::app::KeyEvent::KEY_7: {
      brush_radius_ = kBrushFactor * 7;
      break;
    }
    case ci::app::KeyEvent::KEY_8: {
      brush_radius_ = kBrushFactor * 8;
      break;
    }
    case ci::app::KeyEvent::KEY_9: {
      brush_radius_ = kBrushFactor * 9;
      break;
    }
  }
}

}  // namespace visualizer

}  // namespace image_editor
