// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#ifndef MATRIX_FIELD_H
#define MATRIX_FIELD_H

#include <QVector>
#include <QSet>

namespace sprouts {

const int vertexPoint = -2;
const int borderPoint = -3;

class MatrixField {
public:
	MatrixField(int width, int height);

	bool isCorrectPoint(int x, int y) const;

	int at(int x, int y) const;
	void set(int value, int x, int y);

	QSet<int> neighborValues(int x, int y);

	// for more info see http://lodev.org/cgtutor/floodfill.html
	void floodFill(int value, int x, int y);

protected:
	bool isValue(int value) const;

private:
	int mWidth;
	int mHeight;

	QVector<int> mField;
};

}  // namespace sprouts

#endif  // MATRIX_FIELD_H
