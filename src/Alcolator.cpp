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

  lv_.reset(new LoginView(*window_.get()));

  window_->set_listener(lv_.get());
  
}

Alcolator::~Alcolator() {
  window_->set_listener(nullptr);

  lv_.reset();

  window_ = nullptr;
  app_ = nullptr;
}

void Alcolator::Run() {
  app_->Run();
}
