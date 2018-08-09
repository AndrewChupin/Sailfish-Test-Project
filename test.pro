# NOTICE:
#
# Application name defined in TARGET has a corresponding QML filename.
# If name defined in TARGET is changed, the following needs to be done
# to match new name:
#   - corresponding QML filename must be changed
#   - desktop icon filename must be changed
#   - desktop filename must be changed
#   - icon definition filename in desktop file must be changed
#   - translation filenames have to be changed

# The name of your application
TARGET = test

CONFIG += sailfishapp c++11

SOURCES += src/test.cpp \
    src/domain/mainstate.cpp \
    src/domain/mainmodel.cpp \
    src/data/maindatasource.cpp \
    src/domain/liststate.cpp \
    src/domain/listmodel.cpp \
    src/data/listdatasource.cpp \
    src/presentation/firstpageviewmodel.cpp \
    src/presentation/secondpageviewmodel.cpp

DISTFILES += qml/test.qml \
    qml/cover/CoverPage.qml \
    qml/pages/FirstPage.qml \
    qml/pages/SecondPage.qml \
    rpm/test.changes.in \
    rpm/test.changes.run.in \
    rpm/test.spec \
    rpm/test.yaml \
    translations/*.ts \
    test.desktop \
    qml/pages/BasePage.qml

SAILFISHAPP_ICONS = 86x86 108x108 128x128 172x172

# to disable building translations every time, comment out the
# following CONFIG line
CONFIG += sailfishapp_i18n

# German translation is enabled as an example. If you aren't
# planning to localize your app, remember to comment out the
# following TRANSLATIONS line. And also do not forget to
# modify the localized app name in the the .desktop file.
TRANSLATIONS += translations/test-de.ts

HEADERS += \
    src/domain/mainsource.h \
    src/domain/mainstate.h \
    src/domain/interactor.h \
    src/domain/observable.h \
    src/domain/mainmodel.h \
    src/data/maindatasource.h \
    src/di/di.h \
    src/domain/maininteractor.h \
    src/di/diproduct.h \
    src/di/provider.h \
    src/domain/listinteractor.h \
    src/domain/liststate.h \
    src/domain/listmodel.h \
    src/domain/listsource.h \
    src/data/listdatasource.h \
    src/presentation/viewmodel.h \
    src/presentation/firstpageviewmodel.h \
    src/presentation/secondpageviewmodel.h
