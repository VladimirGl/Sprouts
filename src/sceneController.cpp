// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include "src/sceneController.h"

namespace scene {

SceneController::SceneController(QObject *parent) :
	QObject(parent)
{
}

void SceneController::addPoint(int x, int y) {
	mPoints.append(QPoint(x, y));
}

void SceneController::clear() {
	mPoints.clear();
}

void SceneController::drawEnds(int xNew, int yNew) {
	mNewPoint = QPoint(xNew, yNew);
}

}  // namespace scene
