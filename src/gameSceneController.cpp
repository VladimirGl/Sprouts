// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include "src/gameSceneController.h"

namespace scene {

GameSceneController::GameSceneController(QObject *parent) :
	QObject(parent)
{
}

void GameSceneController::addPoint(int x, int y) {
	mPoints.append(QPoint(x, y));
}

void GameSceneController::clear() {
	mPoints.clear();
}

void GameSceneController::drawEnds(int xNew, int yNew) {
	mNewPoint = QPoint(xNew, yNew);

	emit newLineAdded(mPoints, mNewPoint);
}

}  // namespace scene
