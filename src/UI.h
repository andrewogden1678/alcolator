#pragma once
#include <AppCore/AppCore.h>

using namespace ultralight;


class UI : public WindowListener,
            public LoadListener,
             public ViewListener {

    UI(Ref<Window> window);
    ~UI();

    
}
