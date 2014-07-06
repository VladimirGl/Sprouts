// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include "src/floodFillStack.h"

namespace sprouts {

FloodFillStack::FloodFillStack(int imWidth) :
	mWidth(imWidth)
{
}

bool FloodFillStack::pop(int &x, int &y) {
	if (mStack.isEmpty()) {
		return false;
	}

	int temp = mStack.last();
	x = temp % mWidth;
	y = temp / mWidth;

	mStack.removeLast();

	return true;
}

void FloodFillStack::push(int x, int y) {
	mStack.append(y * mWidth + x);
}

void FloodFillStack::clear() {
	mStack.clear();
}

}  // namespace sprouts
