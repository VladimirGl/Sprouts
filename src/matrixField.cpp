// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include <QDebug>
#include <iostream>
#include <fstream>

#include "src/floodFillStack.h"

#include "src/matrixField.h"

namespace sprouts {

MatrixField::MatrixField(int width, int height) :
	mWidth(width),
	mHeight(height),
	mField(mWidth * mHeight, 0)
{
}

int MatrixField::at(int x, int y) const {
	return mField.at(y * mWidth + x);
}

void MatrixField::set(int value, int x, int y) {
	mField[y * mWidth + x] = value;
}

QSet<int> MatrixField::neighborValues(int x, int y) const {
	if (at(x, y) != kVertexPoint) {
		qDebug() << x << " " << y;
		qDebug() << "not vertex";
		qDebug() << at(x, y);
		return QSet<int>();
	}

	QSet<int> set;

	for (int i = -3; i <= 3; i++) {
		for (int j = -3; j <= 3; j++) {
			int value = at(x + j, y + i);

			if (isValue(value)) {
				set.insert(value);
			}
		}
	}

	if (set.isEmpty()) {
		qDebug() << "NOCOLOR";
	}
	return set;
}

void MatrixField::floodFill(int value, int x, int y) {
//	qDebug() << "fill";

	int oldValue = at(x, y);
//	qDebug() << "old:" << oldValue;

//	qDebug() << x << "  " << y;

	if (oldValue == kVertexPoint) {
		for (int i = -1; i <= 1; i++) {
			for (int j = -1; j <= 1; j++) {
				oldValue = at(x + j, y + i);

//				qDebug() << i << " " << j << " " << oldValue;
				if (isValue(oldValue)) {
					x = x + j;
					y = y + i;
					break;
				}
			}
			if (isValue(oldValue)) {
				break;
			}
		}
	}

//	qDebug() << "new:" << oldValue;

//	qDebug() << x << "  " << y;

	int x1;

	bool spanTop = false;
	bool spanBot = false;

	FloodFillStack stack(mWidth);
	stack.push(x, y);

	while (stack.pop(x, y)) {
		x1 = x;
		while (x1 >= 0 && at(x1, y) == oldValue) {
			x1--;
		}
		x1++;

		spanTop = false;
		spanBot = false;

		while (x1 < mWidth && at(x1, y) == oldValue) {
			set(value, x1, y);

			if (!spanTop && y > 0 && at(x1, y - 1) == oldValue) {
				stack.push(x1, y - 1);
				spanTop = true;
			} else if (spanTop && y > 0 && at(x1, y - 1) != oldValue) {
				spanTop = false;
			}

			if (!spanBot && y < mHeight - 1 && at(x1, y + 1) == oldValue) {
				stack.push(x1, y + 1);
				spanBot = true;
			} else if (spanBot && y < mHeight - 1 && at(x1, y + 1) != oldValue) {
				spanBot = false;
			}

			x1++;
		}
	}
}

void MatrixField::update() {
	mOldField = mField;
}

void MatrixField::undo() {
	mField = mOldField;
}

void MatrixField::print() const {
	std::ofstream mfile;
	mfile.open("D:/matr.csv");

	for (int i = 0; i < mHeight; i++) {
		for (int j = 0; j < mWidth; j++) {
			mfile << at(j, i) << ",";
		}
		mfile << "\n";
	}
	mfile.close();
}

bool MatrixField::isValue(int value) const {
	return (value != kVertexPoint && value != kBorderPoint);
}

bool MatrixField::isCorrectPoint(int x, int y) const {
	return ((x >= 0 && x < mWidth) && (y >= 0 && y < mHeight));
}


}  // namespace sprouts
