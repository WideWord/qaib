#include <qaib/app/Application.hpp>

using namespace qaib;

int main()
{
    auto app = Application();
    DisposableBag bag;
    app.closeButtonClicked.subscribe(bag, [&app]{
        app.quit();
    });
    return app.exec();
}