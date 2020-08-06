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

  // Set window title
  window_->SetTitle("Alcolator");

  // Go to the login page
  nextView_.reset(new LoginView(*window_.get()));

  // Set the view listener to the current view
  window_->set_listener(nextView_.get());
}

Alcolator::~Alcolator() {
  // Annul window listener
  window_->set_listener(nullptr);

  // Destroy view
  nextView_.reset();

  // Destroy the window and app instances
  window_ = nullptr;
  app_ = nullptr;
}

// Run the program
void Alcolator::Run() {
  // Run
  app_->Run();
}
