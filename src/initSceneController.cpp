// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include "src/initSceneController.h"

InitSceneController::InitSceneController(QObject *parent) :
	QObject(parent)
{
}

void InitSceneController::addPoint(int x, int y) {
	mPoints.append(QPoint(x, y));
}

void InitSceneController::clear() {
	mPoints.clear();
}

void InitSceneController::startGame() {
	emit gameStarted(mPoints);
}
