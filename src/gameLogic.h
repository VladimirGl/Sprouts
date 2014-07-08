// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <QPoint>
#include <QVector>

namespace sprouts {

class MatrixField;
class SproutsGraph;

class GameLogic {
public:
	GameLogic(int width, int height, int players,
		 const QVector<QPoint> &pointList);

	// connect vertexOne and vertexTwo, and add point to (xNew, yNew).
	void doTurn(int vertexOne, int vertexTwo,
				int xNew, int yNew,
				const QVector<QPoint> &borderPoints);

	bool hasTurn() const;
	int lastPlayer() const;

protected:
	void fillLine(const QPoint &p1, const QPoint &p2);

private:
	MatrixField mField;
	SproutsGraph mGraph;

	QVector<QPoint> mPoints;

	int mTurns;
	int mPlayers;

	int mFaces;
	int mLastValue;
};

}  // namespace sprouts

#endif  // GAME_LOGIC_H
