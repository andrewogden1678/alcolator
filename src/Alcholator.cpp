#include "Alcholator.h"

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

Alcholator::Alcholator() {
  ///
  /// Create our main App instance.
  ///
  app_ = App::Create();

  ///
  /// Create a resizable window by passing by OR'ing our window flags with
  /// kWindowFlags_Resizable.
  ///
  window_ = Window::Create(app_->main_monitor(), WINDOW_WIDTH, WINDOW_HEIGHT,
    false, kWindowFlags_Resizable );

  ///
  /// Set the title of our window.
  ///
  window_->SetTitle("Alcholator v0.1");

  ///
  /// Tell our app to use 'window' as our main window.
  ///
  /// This call is required before creating any overlays or calling App::Run
  ///
  app_->set_window(*window_.get());

  ///
  /// Create our HTML overlay-- we don't care about its initial size and
  /// position because it'll be calculated when we call OnResize() below.
  ///
  overlay_ = Overlay::Create(*window_.get(), 1, 1, 0, 0);

  ///
  /// Load a page into our overlay's View
  ///
  overlay_->view()->LoadURL("file:///app.html");

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
  overlay_->view()->set_load_listener(this);
}

Alcholator::~Alcholator() {
}

void Alcholator::Run() {
  app_->Run();
}

void Alcholator::OnUpdate() {
}

void Alcholator::OnClose() {
}

void Alcholator::OnResize(uint32_t width, uint32_t height) {
  overlay_->Resize(width, height);
}

void Alcholator::OnFinishLoading(View* caller) {
}

void Alcholator::OnDOMReady(View* caller) {
}
