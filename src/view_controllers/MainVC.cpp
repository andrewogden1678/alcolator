#include "MainVC.h"

MainView::MainView(Ref<Window> window) : ViewController::ViewController(window) {
    // Create overlay
    overlay_ = Overlay::Create(window_, 900, 600, 0, 0);

    // Set load and view listeners, then load the page
    view()->set_load_listener(this);
    view()->set_view_listener(this);
    view()->LoadURL("file:///main.html");
}

MainView::~MainView() {
    // Destroy listener instances
    view()->set_load_listener(nullptr);
    view()->set_view_listener(nullptr);
}

void MainView::OnClose() {

}

void MainView::OnResize(uint32_t width, uint32_t height) {

}

void MainView::OnDOMReady(View* caller, uint64_t frame_id,
            bool is_main_frame, const String& url) {

}