// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#ifndef SPROUTS_GRAPH_H
#define SPROUTS_GRAPH_H

#include <QBitArray>
#include <QVector>

namespace sprouts {

typedef QVector<int> Adjacency;

class SproutsGraph {
public:
	SproutsGraph(int size, int maxEdges);

	void addConnection(int vertexOne, int vertexTwo);
	void addVertex();

	bool isContain(int vertex) const;
	bool isAlive(int vertex) const;

	bool hasNewVerteces() const;

	int numberOfEdjes(int vertex) const;

	int numberOfVertices() const { return mAdjList.size(); }
	int lastVertex() const { return numberOfVertices() - 1; }

	// returns the list of vertices, which have less then 3 edges.
	QVector<int> aliveVertices() const;

	// compute number of faces using Euler's characteristic
	int numberOfFaces();

protected:
	int numberOfComponents() const;
	int numberOfEdjes() const;

	bool canLoop(int vertex) const;

	void dfs(QBitArray &visited, int curr) const;

private:
	QVector<Adjacency> mAdjList;

	int mMaxEdges;
};

}  // namespace sprouts

#endif  // SPROUTS_GRAPH_H
