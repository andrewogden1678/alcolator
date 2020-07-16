#include <AppCore/AppCore.h>
#include "view_controllers/LoginVC.h"

using namespace ultralight;

class Alcolator {

  public:
    Alcolator();

    virtual ~Alcolator();

    // Start the run loop.
    virtual void Run();

  protected:
    RefPtr<App> app_;
    RefPtr<Window> window_;
};
