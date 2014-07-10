// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include <QDebug>

#include "src/gameSceneController.h"

namespace scene {

const int kMinDistance = 400;

GameSceneController::GameSceneController(QObject *parent) :
	QObject(parent),
	mPoints(),
	mMinDistance(kMinDistance)
{
}

void GameSceneController::addPoint(int x, int y) {
//	qDebug() << QPoint(x, y) << "\n";

//	qDebug() << "canva";

	mPoints.append(QPoint(x, y));
}

void GameSceneController::clear() {
	mPoints.clear();
}

void GameSceneController::drawStarts(int xNew, int yNew) {
	qDebug() << yNew << "\n";
}

void GameSceneController::drawEnds(int xNew, int yNew) {
	qDebug() << yNew << "\n";

	mNewPoint = nearestPoint(xNew, yNew);

//	emit newLineAdded(mPoints, mNewPoint);
}

QPoint GameSceneController::nearestPoint(int xNew, int yNew) const {
	if (mPoints.isEmpty()) {
		return QPoint();
	}

	QPoint newPoint(xNew, yNew);
	QPoint nearestP = mPoints.first();

	bool isSet = false;
	int turnDist = mMinDistance;

	int minDist = distance(newPoint, nearestP);

	for (int i = 1; i < mPoints.size(); i++) {
		QPoint temp = mPoints.at(i);

		if (distance(mPoints.first(), temp) > turnDist &&
			distance(mPoints.last(), temp) > turnDist) {
			int dist = distance(temp, newPoint);

			if (!isSet) {
				minDist = dist;
				nearestP = temp;
				isSet = true;
			}

			if (dist < minDist) {
				nearestP = temp;
				minDist = dist;
			}
		}
	}

	return nearestP;
}

int GameSceneController::distance(const QPoint &p1, const QPoint &p2) const {
	QPoint temp = p1 - p2;

	return (temp.x() * temp.x() + temp.y() * temp.y());
}

}  // namespace scene
