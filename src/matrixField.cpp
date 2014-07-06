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

void MatrixField::floodFill(int value, int x, int y) {
	int oldValue = at(x, y);

	if (oldValue == value) {
		return;
	}

	FloodFillStack stack(mWidth);

}


bool MatrixField::isCorrectPoint(int x, int y) const {
	return ((x >= 0 && x < mWidth) && (y >= 0 && y < mHeight));
}


}  // namespace sprouts
