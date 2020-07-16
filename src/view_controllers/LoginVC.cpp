#include "LoginVC.h"

LoginView::LoginView(Ref<Window> window) : window_(window) {
    uint32_t width = App::instance()->window()->width();
    uint32_t height = App::instance()->window()->height():

    overlay_ = Overlay::Create(window_, width, height, 0, 0);

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

void LoginView::OnResize() {

}

void LoginView::OnDOMReady() {
    
}