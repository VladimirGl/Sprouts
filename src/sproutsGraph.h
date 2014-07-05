// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#ifndef SPROUTS_GRAPH_H
#define SPROUTS_GRAPH_H

#include <QBitArray>
#include <QList>

namespace sprouts {

typedef QList<int> Adjacency;

class SproutsGraph {
public:
	SproutsGraph(int size, int maxEdges);

	void addConnection(int vertexOne, int vertexTwo);
	void addVertex();

	bool isContain(int vertex) const;
	bool isAlive(int vertex) const;

	int numberOfEdjes(int vertex) const;

	int numberOfVertices() const { return mAdjList.size(); }

	// returns the list of vertices, which have less then 3 edges.
	QList<int> aliveVertices() const;

	// compute number of faces using Euler's characteristic
	int numberOfFaces();

protected:
	int numberOfComponents() const;
	int numberOfEdjes() const;

	void dfs(QBitArray &visited, int curr) const;

private:
	QList<Adjacency> mAdjList;

	int mMaxEdges;

	int mFaces;
};

}  // namespace sprouts

#endif  // SPROUTS_GRAPH_H
