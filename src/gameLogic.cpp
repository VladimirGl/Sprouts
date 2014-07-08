// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include "src/matrixField.h"
#include "src/sproutsGraph.h"

#include "src/gameLogic.h"

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
	mLastValue(0)
{
	for (int i = 0; i < pointList.size(); i++) {
		QPoint temp = pointList.at(i);
		mField.set(kVertexPoint, temp.x(), temp.y());
	}
}

void GameLogic::doTurn(int vertexOne, int vertexTwo,
				  int xNew, int yNew,
				  const QVector<QPoint> &borderPoints) {
	mPoints.append(QPoint(xNew, yNew));

	mGraph.addVertex();
	mGraph.addConnection(vertexOne, mGraph.lastVertex());
	mGraph.addConnection(vertexTwo, mGraph.lastVertex());

	for (int i = 1; i < borderPoints.size(); i++) {
		QPoint p1 = borderPoints.at(i - 1);
		QPoint p2 = borderPoints.at(i);

		fillLine(p1, p2);
	}

	mField.set(kVertexPoint, xNew, yNew);

	if (mGraph.numberOfFaces() != mFaces) {
		mFaces++;

		mLastValue++;
		mField.floodFill(mLastValue, xNew, yNew);
	}

	mTurns++;
}

int GameLogic::lastPlayer() const {
	return mTurns % mPlayers;
}

void GameLogic::fillLine(const QPoint &p1, const QPoint &p2) {
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

	while (true) {
		mField.set(kBorderPoint, x1, y1);
		if ((x1 == x2) && (y1 == y2)) {
			return;
		}

		int e2 = error * 2;
		if (e2 > -dy) {
			error -= dy;
			x1 += sx;
		}
		if (e2 < dx) {
			error += dx;
			y1 += sy;
		}
	}
}

bool GameLogic::hasTurn() const {
	QVector<int> alive = mGraph.aliveVertices();
	QVector<QSet<int> > sets;

	for (int i = 0; i < alive.size(); i++) {
		QPoint temp = mPoints.at(alive.at(i));

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
