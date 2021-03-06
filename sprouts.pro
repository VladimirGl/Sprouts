TEMPLATE = app

QT += qml quick core

SOURCES += src/main.cpp \
    src/matrixField.cpp \
    src/sproutsGraph.cpp \
    src/floodFillStack.cpp \
    src/initSceneController.cpp \
    src/gameSceneController.cpp \
    src/gameLogic.cpp \
    src/gameLogicController.cpp

RESOURCES += \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

OTHER_FILES +=

HEADERS += \
    src/matrixField.h \
    src/sproutsGraph.h \
    src/floodFillStack.h \
    src/initSceneController.h \
    src/gameSceneController.h \
    src/gameLogic.h \
    src/gameLogicController.h \
    src/dist.h
