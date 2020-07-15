#pragma once
#include <AppCore/AppCore.h>

class MainView : public LoadListener,
                public WindowListener,
                public ViewListener {

    public:
        MainView(Ref<Window> window_);
        ~MainView();     


    protected:
        Ref<Window> window_;
        Ref<Overlay> overlay_;           
}