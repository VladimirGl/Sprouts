// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#ifndef MATRIX_FIELD_H
#define MATRIX_FIELD_H

#include <QSet>
#include <QVector>

namespace sprouts {

const int kVertexPoint = -2;
const int kBorderPoint = -3;

class MatrixField {
public:
	MatrixField(int width, int height);

	bool isCorrectPoint(int x, int y) const;

	int at(int x, int y) const;
	void set(int value, int x, int y);

	QSet<int> neighborValues(int x, int y) const;

	int width() { return mWidth; }
	int height() { return mHeight; }

	// for more info see http://lodev.org/cgtutor/floodfill.html
	void floodFill(int value, int x, int y);

	void update();
	void undo();

	void print() const;

protected:
	bool isValue(int value) const;

private:
	int mWidth;
	int mHeight;

	QVector<int> mField;
	QVector<int> mOldField;
};

}  // namespace sprouts

#endif  // MATRIX_FIELD_H
