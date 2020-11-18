#include <visualizer/image_editor_app.h>

using image_editor::visualizer::ImageEditorApp;

void prepareSettings(ImageEditorApp::Settings* settings) {
  settings->setResizable(false);
}

// This line is a macro that expands into an "int main()" function.
CINDER_APP(ImageEditorApp, ci::app::RendererGl, prepareSettings);
