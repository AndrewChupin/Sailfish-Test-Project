#ifdef QT_QML_DEBUG
#include <QtQuick>
#endif

#include <sailfishapp.h>
#include "presentation/firstpageviewmodel.h"
#include "presentation/secondpageviewmodel.h"
#include "di/diproduct.h"

ApplicationComponent *ApplicationComponent::instance = nullptr;

int main(int argc, char *argv[])
{
    qmlRegisterType<FirstPageViewModel>("com.a65apps.test", 1, 0, "FirstPageViewModel");
    qmlRegisterType<SecondPageViewModel>("com.a65apps.test", 1, 0, "SecondPageViewModel");

    QScopedPointer<QGuiApplication> app(SailfishApp::application(argc, argv));
    QSharedPointer<ApplicationComponent> appComponent(new ApplicationModule(app.data()));
    QScopedPointer<QQuickView> view(SailfishApp::createView());

    view->setSource(SailfishApp::pathToMainQml());
    view->showFullScreen();

    return app->exec();
}
