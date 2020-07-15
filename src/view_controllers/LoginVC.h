#pragma once
#include <AppCore/AppCore.h>

class LoginView : public LoadListener,
                public WindowListener,
                public ViewListener {

    public:
        LoginView(Ref<Window> window_);
        ~LoginView();     


    protected:
        Ref<Window> window_;
        Ref<Overlay> overlay_;           
}