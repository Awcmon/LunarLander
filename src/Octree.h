#pragma once
#include "ofMain.h"
#include "box.h"
#include "ray.h"


class TreeNode {
public:
	Box box;
	vector<int> points;
	vector<TreeNode> children;
};

class Octree {
public:
	
	void create(const ofMesh & mesh, int numLevels);
	void subdivide(const ofMesh & mesh, TreeNode & node, int numLevels, int level);
	//bool intersect(const Ray &, const TreeNode & node, TreeNode & nodeRtn);
	bool intersect(const Ray &ray, TreeNode* node, std::vector<TreeNode*>* nodesRtn);
	bool intersectHelper(const Ray &ray, TreeNode* node, TreeNode & nodeRtn);
	void draw(TreeNode & node, int numLevels, int level);
	void draw(int numLevels, int level) {
		draw(root, numLevels, level);
	}
	void drawLeafNodes(TreeNode & node);
	static void drawBox(const Box &box);
	static Box meshBounds(const ofMesh &);
	int getMeshPointsInBox(const ofMesh &mesh, const vector<int> & points, Box & box, vector<int> & pointsRtn);
	void subDivideBox8(const Box &b, vector<Box> & boxList);
	ofVec3f trace(Ray ray);

	ofMesh mesh;
	TreeNode root;

	vector<ofColor> colors;
};