#include <qaib/app/Application.hpp>

using namespace qaib;

int main()
{
    auto app = Application();
    
    app.closeButtonClicked.subscribe(&app, [&app]{
        app.quit();
    });
    return app.exec();
}