// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include "src/matrixField.h"

#include "src/floodFillStack.h"

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

QSet<int> MatrixField::neighborValues(int x, int y) {
	if (at(x, y) != vertexPoint) {
		return QSet<int>();
	}

	QSet<int> set;

	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			int value = at(x + j, y + i);

			if (isValue(value)) {
				set.insert(value);
			}
		}
	}

	return set;
}

void MatrixField::floodFill(int value, int x, int y) {
	int oldValue = at(x, y);

	if (oldValue == value) {
		return;
	}

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

bool MatrixField::isValue(int value) const {
	return (value != vertexPoint && value != borderPoint);
}

bool MatrixField::isCorrectPoint(int x, int y) const {
	return ((x >= 0 && x < mWidth) && (y >= 0 && y < mHeight));
}


}  // namespace sprouts
