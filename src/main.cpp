// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include <QGuiApplication>
#include <QQuickView>
#include <QQmlEngine>
#include <QQmlContext>

#include <QQmlApplicationEngine>

#include "src/gameSceneController.h"

int main(int argc, char *argv[]) {
	QGuiApplication app(argc, argv);

//	QQmlEngine engine;

	scene::GameSceneController controller;

//	engine.rootContext()->setContextProperty("game", &controller);


	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("game", &controller);
	engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

	return app.exec();
}
