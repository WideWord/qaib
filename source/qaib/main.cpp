#include <qaib/app/Application.hpp>

using namespace qaib;

int main()
{
    auto app = std::make_shared<Application>();
    
    app->closeButtonClicked.subscribe(app, [app]{
        app->quit();
    });
    return app->exec();
}