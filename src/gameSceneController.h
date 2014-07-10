// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#ifndef GAME_SCENE_CONTROLLER_H
#define GAME_SCENE_CONTROLLER_H

#include <QObject>
#include <QPoint>
#include <QVariant>
#include <QVector>

class QPoint;

namespace scene {

class GameSceneController : public QObject
{
	Q_OBJECT

//	Q_PROPERTY(bool turn READ turn NOTIFY turnChanged)

public:
	explicit GameSceneController(QObject *parent = 0);

	void setDistances(int dist) { mMinDistance = dist; }

signals:
	void newLineAdded(int vertexOne, int vertexTwo,
					  const QVector<QPoint> &points,
					  const QPoint &newPoint);

	void gameStarts(int width, int height, const QVector<QPoint> &points);
	void turnEndss();

public slots:
	void turnEnds(bool turn);

	bool turnResult() const { return mTurn; }

	void addInitialPoint(int x, int y);

	void startGame(int width, int height);

	void addPoint(int x, int y);
	void clear();

	void drawStarts(int xNew, int yNew);
	void drawEnds(int vertexOne, int vertexTwo);

	void addVertex(int xNew, int yNew);

	QPoint nearestPoint(int xNew, int yNew) const;

protected:

	int distance(const QPoint &p1, const QPoint &p2) const;

private:
	QVector<QPoint> mPoints;
	QVector<QPoint> mInitPoints;
	QPoint mNewPoint;

	int mMinDistance;

	int mVertexOne;
	int mVertexTwo;

	bool mTurn;
};

}  // namespace scene

#endif  // GAME_SCENE_CONTROLLER_H
