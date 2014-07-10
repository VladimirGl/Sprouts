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
#include "src/gameLogicController.h"

#include <QVector>
#include <QPoint>

int main(int argc, char *argv[]) {
	QGuiApplication app(argc, argv);

//	QQmlEngine engine;

	scene::GameSceneController controller;

	sprouts::GameLogicController gameController;

//	engine.rootContext()->setContextProperty("game", &controller);

	QObject::connect(&controller, SIGNAL(gameStarts(int, int, QVector<QPoint>)),
					 &gameController, SLOT(init(int, int, QVector<QPoint>)));

	QObject::connect(&controller, SIGNAL(newLineAdded(int,int,QVector<QPoint>,QPoint)),
					 &gameController, SLOT(doTurn(int,int,QVector<QPoint>,QPoint)));


	QObject::connect(&gameController, SIGNAL(turnEnds(bool)),
					 &controller, SLOT(turnEnds(bool)));

	QQmlApplicationEngine engine;
	engine.rootContext()->setContextProperty("game", &controller);
	engine.load(QUrl(QStringLiteral("qrc:///qml/main.qml")));

	return app.exec();
}
