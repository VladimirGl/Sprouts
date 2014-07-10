// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#ifndef GAME_SCENE_CONTROLLER_H
#define GAME_SCENE_CONTROLLER_H

#include <QObject>
#include <QPoint>
#include <QVector>

class QPoint;

namespace scene {

class GameSceneController : public QObject
{
	Q_OBJECT
public:
	explicit GameSceneController(QObject *parent = 0);

signals:
	void newLineAdded(const QVector<QPoint> &points, const QPoint &newPoint);

public slots:
	void addPoint(int x, int y);
	void clear();

	void drawStarts(int xNew, int yNew);
	void drawEnds(int xNew, int yNew);

	QPoint nearestPoint(int xNew, int yNew) const;

protected:

	int distance(const QPoint &p1, const QPoint &p2) const;

private:
	QVector<QPoint> mPoints;
	QPoint mNewPoint;
};

}  // namespace scene

#endif  // GAME_SCENE_CONTROLLER_H
