// Copyright (c) 2014 The Sprouts authors. All rights reserved.
// Use of this source file is governed by a MIT license that can be found in the
// LICENSE file.
// Author: Vladimir Glazachev <glazachev.vladimir@gmail.com>

#include "src/sproutsGraph.h"

namespace sprouts {

SproutsGraph::SproutsGraph(int size, int maxEdges) :
	mMaxEdges(maxEdges)
{
	for (int i = 0; i < size; i++) {
		mAdjList.append(Adjacency());
	}
}

void SproutsGraph::addConnection(int vertexOne, int vertexTwo) {
	if (!isContain(vertexOne) || ! isContain(vertexTwo)) {
		return;
	}

	mAdjList[vertexOne].append(vertexTwo);
	mAdjList[vertexTwo].append(vertexOne);
}

void SproutsGraph::addVertex() {
	mAdjList.append(Adjacency());
}

bool SproutsGraph::isContain(int vertex) const {
	return (vertex >= 0 && vertex < numberOfVertices());
}

bool SproutsGraph::isAlive(int vertex) const {
	return (isContain(vertex) && (numberOfEdjes(vertex) < mMaxEdges));
}

int SproutsGraph::numberOfEdjes(int vertex) const {
	if (isContain(vertex)) {
		return mAdjList.at(vertex).size();
	}

	return -1;
}

QVector<int> SproutsGraph::aliveVertices() const {
	QVector<int> alive;

	for (int i = 0; i < numberOfVertices(); i++) {
		if (isAlive(i)) {
			alive.append(i);
		}
	}

	return alive;
}

int SproutsGraph::numberOfFaces() {
	int faces = 0;

	// Euler's characteristic
	faces = 1 + numberOfComponents() + numberOfEdjes() - numberOfVertices();

	return faces;
}

int SproutsGraph::numberOfComponents() const {
	int counter = 0;

	QBitArray visited(numberOfVertices());

	for (int i = 0; i < numberOfVertices(); i++) {
		if (!visited[i]) {
			dfs(visited, i);
			counter++;
		}
	}

	return counter;
}

int SproutsGraph::numberOfEdjes() const {
	int counter = 0;

	for (int i = 0; i < numberOfVertices(); i++) {
		counter+= mAdjList.at(i).size();
	}

	return (counter / 2);
}

void SproutsGraph::dfs(QBitArray &visited, int curr) const {
	visited[curr] = true;

	for (int i = 0; i < numberOfEdjes(curr); i++) {
		int next = mAdjList.at(curr).at(i);

		if (!visited[next]) {
			dfs(visited, next);
		}
	}
}

}  // namespace sprouts
