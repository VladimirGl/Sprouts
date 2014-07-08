// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include <QDebug>

#include "src/gameSceneController.h"

namespace scene {

GameSceneController::GameSceneController(QObject *parent) :
	QObject(parent)
{
}

void GameSceneController::addPoint(int x, int y) {
//	qDebug() << QPoint(x, y) << "\n";

	mPoints.append(QPoint(x, y));
}

void GameSceneController::clear() {
	mPoints.clear();
}

void GameSceneController::drawEnds(int xNew, int yNew) {
	qDebug() << "finishDraw\n";

	mNewPoint = nearestPoint(xNew, yNew);

	emit newLineAdded(mPoints, mNewPoint);
}

QPoint GameSceneController::nearestPoint(int xNew, int yNew) const {
	QPoint newPoint(xNew, yNew);
	QPoint nearestP = mPoints.first();

	int minDist = distance(newPoint, nearestP);

	for (int i = 1; i < mPoints.size(); i++) {
		QPoint temp = mPoints.at(i);
		int dist = distance(temp, newPoint);

		if (dist < minDist) {
			nearestP = temp;
			minDist = dist;
		}
	}

	return nearestP;
}

int GameSceneController::distance(const QPoint &p1, const QPoint &p2) const {
	QPoint temp = p1 - p2;

	return (temp.x() * temp.x() + temp.y() * temp.y());
}

}  // namespace scene
