// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include "src/matrixField.h"

namespace sprouts {

MatrixField::MatrixField(int width, int height) :
	mWidth(width),
	mHeight(height),
	mField(mWidth * mHeight, 0)
{
}

int MatrixField::at(int x, int y) {
	if (isCorrectPoint(x, y)) {
		return mField.at(y * mWidth + x);
	}

	return -1;
}

void MatrixField::set(int value, int x, int y) {
	if (isCorrectPoint(x, y)) {
		mField[y * mWidth + x] = value;
	}
}

bool MatrixField::isCorrectPoint(int x, int y) const {
	return ((x >= 0 && x < mWidth) && (y >= 0 && y < mHeight));
}


}  // namespace sprouts
