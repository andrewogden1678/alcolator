#include "Alcolator.h"
#include "view_controllers/LoginVC.h"

// Definitions
#define WINDOW_WIDTH  900
#define WINDOW_HEIGHT 600

Alcolator::Alcolator() {

  // Create app instance
  app_ = App::Create();

  // Create the app window
  window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
    false, kWindowFlags_Borderless);

  // Tell the app that this is the main window
  app_->set_window(*window_.get());

  login_.reset(new LoginView(*window_.get()));

  window_->set_listener(login_.get());

  ///
  /// Create our HTML overlay-- we don't care about its initial size and
  /// position because it'll be calculated when we call OnResize() below.
  ///
  overlay_ = Overlay::Create(*window_.get(), 1, 1, 0, 0);

  ///
  /// Force a call to OnResize to perform size/layout of our overlay.
  ///
  OnResize(window_->width(), window_->height());

  ///
  /// Load a page into our overlay's View
  ///
  view()->LoadURL("file:///login.html");

  ///
  /// Register our MyApp instance as an AppListener so we can handle the
  /// App's OnUpdate event below.
  ///
  app_->set_listener(this);

  ///
  /// Register our MyApp instance as a WindowListener so we can handle the
  /// Window's OnResize event below.
  ///
  window_->set_listener(this);

  ///
  /// Register our MyApp instance as a LoadListener so we can handle the
  /// View's OnFinishLoading and OnDOMReady events below.
  ///
  view()->set_load_listener(this);

  view()->set_view_listener(this);
  
}

Alcolator::~Alcolator() {
}

void Alcolator::Run() {
  app_->Run();
}

void Alcolator::OnUpdate() {
}

void Alcolator::OnClose() {
}

void Alcolator::OnResize(uint32_t width, uint32_t height) {
  overlay_->Resize(width, height);
}

void Alcolator::OnFinishLoading(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) {

}

void Alcolator::OnDOMReady(View* caller, uint64_t frame_id, bool is_main_frame, const String& url) {
  
}

void Alcolator::OnChangeCursor(View* caller, Cursor cursor) {

  window_->SetCursor(cursor);
}
