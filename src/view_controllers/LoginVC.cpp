#include "LoginVC.h"

LoginView::LoginView(Ref<Window> window) : window_(window) {
    uint32_t width = App::instance()->window()->width();
    uint32_t height = App::instance()->window()->height();

    overlay_ = Overlay::Create(window_, 900, 600, 0, 0);

    view()->set_load_listener(this);
    view()->set_view_listener(this);
    view()->LoadURL("file:///login.html");
}

LoginView::~LoginView() {
    view()->set_load_listener(nullptr);
    view()->set_view_listener(nullptr);
}

void LoginView::OnClose() {

}

void LoginView::OnResize(uint32_t width, uint32_t height) {

}

void LoginView::OnDOMReady(View* caller, uint64_t frame_id,
            bool is_main_frame, const String& url) {

}