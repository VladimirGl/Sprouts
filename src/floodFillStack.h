// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#ifndef FLOODFILL_STACK_H
#define FLOODFILL_STACK_H

#include <QVector>

namespace sprouts {

class FloodFillStack {
public:
	FloodFillStack(int imWidth);

	bool pop(int &x, int &y);
	void push(int x, int y);

	void clear();

private:
	QVector<int> mStack;

	int mWidth;
};

}  // namespace sprouts

#endif // FLOODFILL_STACK_H
