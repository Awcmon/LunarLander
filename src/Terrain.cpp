#include "Terrain.h"

//Alan Duong, 05/16/19
//A Prop with an Octree.

void Terrain::update()
{
	Prop::update();
}

void Terrain::draw()
{
	Prop::draw();
	/*
	ofNoFill();
	oct.drawLeafNodes(oct.root);
	ofFill();
	*/
}
