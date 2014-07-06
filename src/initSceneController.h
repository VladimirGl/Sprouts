// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#ifndef INIT_SCENE_CONTROLLER_H
#define INIT_SCENE_CONTROLLER_H

#include <QObject>
#include <QPoint>
#include <QVector>

class InitSceneController : public QObject
{
	Q_OBJECT
public:
	explicit InitSceneController(QObject *parent = 0);

signals:
	void gameStarted(const QVector<QPoint> &points);

public slots:
	void addPoint(int x, int y);

	void clear();
	void startGame();

private:
	QVector<QPoint> mPoints;
};

#endif  // INIT_SCENE_CONTROLLER_H
