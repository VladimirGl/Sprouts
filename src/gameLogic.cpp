// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include "src/gameLogic.h"

#include <QDebug>

namespace sprouts {

const int kStandardNumberOfEdges = 3;

GameLogic::GameLogic(int width, int height, int players,
		   const QVector<QPoint> &pointList) :
	mField(width, height),
	mGraph(pointList.size(), kStandardNumberOfEdges),
	mPoints(pointList),
	mTurns(0),
	mPlayers(players),
	mFaces(1),
	mLastValue(0),
	mIsIntersect(false)
{
	for (int i = 0; i < pointList.size(); i++) {
		QPoint temp = pointList.at(i);
		mField.set(kVertexPoint, temp.x(), temp.y());
	}

	mField.update();
}

bool GameLogic::doTurn(int vertexOne, int vertexTwo,
				  int xNew, int yNew,
				  const QVector<QPoint> &borderPoints) {
	mPoints.append(QPoint(xNew, yNew));

	for (int i = 1; i < borderPoints.size(); i++) {
		QPoint p1 = borderPoints.at(i - 1);
		QPoint p2 = borderPoints.at(i);

		bool isCheckedIntersect = true;
		fillLine(p1, p2, isCheckedIntersect);

		if (mIsIntersect) {
			mIsIntersect = false;
			mField.undo();
			mPoints.removeLast();
			return false;
		}
	}

	QPoint p1 = borderPoints.first();
	QPoint p2 = borderPoints.last();
	if (p1 == p2) {
		fillLine(p1, p2, false);
	}
	if (mIsIntersect) {
		mIsIntersect = false;
		mField.undo();
		mPoints.removeLast();
		return false;
	}

	mField.set(kVertexPoint, p1.x(), p1.y());
	mField.set(kVertexPoint, p2.x(), p2.y());
	mField.set(kVertexPoint, xNew, yNew);

	mGraph.addVertex();
	mGraph.addConnection(vertexOne, mGraph.lastVertex());
	mGraph.addConnection(vertexTwo, mGraph.lastVertex());

	if (mGraph.numberOfFaces() != mFaces) {
		qDebug() << "faces up";

		mFaces++;

		mLastValue++;
		mField.floodFill(mLastValue, xNew, yNew);
		mField.print();
	}

	mTurns++;

	mField.update();
	return true;
}

int GameLogic::lastPlayer() const {
	return mTurns % mPlayers;
}

void GameLogic::fillLine(const QPoint &p1, const QPoint &p2, bool isCheckIntersect) {
	int x1 = p1.x();
	int y1 = p1.y();
	int x2 = p2.x();
	int y2 = p2.y();

	int dx = abs(x1 - x2);
	int dy = abs(y1 - y2);

	int sx = 1;
	int sy = 1;
	if (x1 > x2) { sx = -1; }
	if (y1 > y2) { sy = -1; }

	int error = dx - dy;

	int x1temp = x1;
	int y1temp = y1;

	while (true) {
		if (mField.at(x1temp, y1temp) == kBorderPoint
			&& (x1temp != x1 && y1temp != y1)
			&& (x1temp != x2 && y1temp != y2)) {

			mIsIntersect = true;
			return;
		}

		mField.set(kBorderPoint, x1temp, y1temp);
		if ((x1temp == x2) && (y1temp == y2)) {
			return;
		}

		int e2 = error * 2;
		if (e2 > -dy) {
			error -= dy;
			x1temp += sx;
		}
		if (e2 < dx) {
			error += dx;
			y1temp += sy;
		}
	}
}

bool GameLogic::hasTurn() const {
	QVector<int> alive = mGraph.aliveVertices();

	QVector<QSet<int> > sets;

	for (int i = 0; i < alive.size(); i++) {
		QPoint temp = mPoints.at(alive.at(i));

		qDebug() << alive.at(i) << " " << mField.neighborValues(temp.x(), temp.y());

		sets.append(mField.neighborValues(temp.x(), temp.y()));
	}

	bool hasIntersect = false;

	for (int i = 0; i < sets.size(); i++) {
		for (int j = i + 1; j < sets.size(); j++) {
			if (!sets[i].intersect(sets.at(j)).isEmpty()) {
				hasIntersect = true;
				break;
			}
		}
	}

	return hasIntersect;
}

}  // namespace sprouts
