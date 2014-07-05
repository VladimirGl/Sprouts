// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#ifndef MATRIX_FIELD_H
#define MATRIX_FIELD_H

#include <QVector>

namespace sprouts {

const int vertexPoint = -2;
const int borderPoint = -3;

class MatrixField {
public:
	MatrixField(int width, int height);

	int at(int x, int y);
	void set(int value, int x, int y);

protected:
	bool isCorrectPoint(int x, int y) const;

private:
	int mWidth;
	int mHeight;

	QVector<int> mField;
};

}  // namespace sprouts

#endif  // MATRIX_FIELD_H
