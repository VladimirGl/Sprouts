// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include "src/matrixField.h"
#include "src/sproutsGraph.h"

#include "src/game.h"

namespace sprouts {

const int standardNumberOfEdges = 3;

Game::Game(int width, int height, const QVector<QPoint> &pointList) :
	mField(width, height),
	mGraph(pointList.size(), standardNumberOfEdges),
	mPoints(pointList),
	mFaces(1),
	mLastValue(0)
{
	for (int i = 0; i < pointList.size(); i++) {
		QPoint temp = pointList.at(i);
		mField.set(vertexPoint, temp.x(), temp.y());
	}
}

void Game::doTurn(int vertexOne, int vertexTwo, int xNew, int yNew) {
	mPoints.append(QPoint(xNew, yNew));

	mGraph.addVertex();
	mGraph.addConnection(vertexOne, mGraph.lastVertex());
	mGraph.addConnection(vertexTwo, mGraph.lastVertex());

	mField.set(vertexPoint, xNew, yNew);

	if (mGraph.numberOfFaces() != mFaces) {
		mFaces++;

		mLastValue++;
		mField.floodFill(mLastValue, xNew, yNew);
	}
}

bool Game::hasTurn() {
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
