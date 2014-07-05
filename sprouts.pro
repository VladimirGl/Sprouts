TEMPLATE = app

QT += qml quick

SOURCES += src/main.cpp \
    src/matrixField.cpp \
    src/sproutsGraph.cpp

RESOURCES += \
    qml.qrc

# Additional import path used to resolve QML modules in Qt Creator's code model
QML_IMPORT_PATH =

# Default rules for deployment.
include(deployment.pri)

OTHER_FILES +=

HEADERS += \
    src/matrixField.h \
    src/sproutsGraph.h
