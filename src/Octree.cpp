//  Kevin M. Smith - Basic Octree Class - CS134/235 4/18/18
//


#include "Octree.h"
 

// draw Octree (recursively)
//
void Octree::draw(TreeNode & node, int numLevels, int level) {
	if (level > numLevels+1) return;
	drawBox(node.box);
	level++;
	for (int i = 0; i < node.children.size(); i++) {
		ofSetColor(colors[level]);
		draw(node.children[i], numLevels, level);
	}
}

// draw only leaf Nodes
//
//RESOLVED: Complete
void Octree::drawLeafNodes(TreeNode & node) {
	if (node.children.size() == 0)
	{
		//ofSetColor(colors[3]);
		drawBox(node.box);
	}
	else
	{
		for (int i = 0; i < node.children.size(); i++) {
			drawLeafNodes(node.children[i]);
		}
	}

}


//draw a box from a "Box" class  
//
void Octree::drawBox(const Box &box) {
	Vector3 min = box.parameters[0];
	Vector3 max = box.parameters[1];
	Vector3 size = max - min;
	Vector3 center = size / 2 + min;
	ofVec3f p = ofVec3f(center.x(), center.y(), center.z());
	float w = size.x();
	float h = size.y();
	float d = size.z();
	ofDrawBox(p, w, h, d);
}

// return a Mesh Bounding Box for the entire Mesh
//
Box Octree::meshBounds(const ofMesh & mesh) {
	int n = mesh.getNumVertices();
	ofVec3f v = mesh.getVertex(0);
	ofVec3f max = v;
	ofVec3f min = v;
	for (int i = 1; i < n; i++) {
		ofVec3f v = mesh.getVertex(i);

		if (v.x > max.x) max.x = v.x;
		else if (v.x < min.x) min.x = v.x;

		if (v.y > max.y) max.y = v.y;
		else if (v.y < min.y) min.y = v.y;

		if (v.z > max.z) max.z = v.z;
		else if (v.z < min.z) min.z = v.z;
	}
	cout << "vertices: " << n << endl;
//	cout << "min: " << min << "max: " << max << endl;
	return Box(Vector3(min.x, min.y, min.z), Vector3(max.x, max.y, max.z));
}

// getMeshPointsInBox:  return an array of indices to points in mesh that are contained 
//                      inside the Box.  Return count of points found;
//
//RESOLVED: Complete
//RESOLVED: Test?
int Octree::getMeshPointsInBox(const ofMesh & mesh, const vector<int>& points,
	Box & box, vector<int> & pointsRtn)
{
	//pointsRtn.clear();
	for (size_t i = 0; i < points.size(); i++)
	{
		auto curVertex = mesh.getVertex(points[i]);
		//glm::vec3 curVertex = mesh.getVertices()[points[i]];
		if (box.inside(Vector3(curVertex.x, curVertex.y, curVertex.z)))
		{
			pointsRtn.push_back(points[i]);
		}
	}
	return (int)pointsRtn.size();
}



//  Subdivide a Box into eight(8) equal size boxes, return them in boxList;
//
void Octree::subDivideBox8(const Box &box, vector<Box> & boxList) {
	Vector3 min = box.parameters[0];
	Vector3 max = box.parameters[1];
	Vector3 size = max - min;
	Vector3 center = size / 2 + min;
	float xdist = (max.x() - min.x()) / 2;
	float ydist = (max.y() - min.y()) / 2;
	float zdist = (max.z() - min.z()) / 2;
	Vector3 h = Vector3(0, ydist, 0);

	//  generate ground floor
	//
	Box b[8];
	b[0] = Box(min, center);
	b[1] = Box(b[0].min() + Vector3(xdist, 0, 0), b[0].max() + Vector3(xdist, 0, 0));
	b[2] = Box(b[1].min() + Vector3(0, 0, zdist), b[1].max() + Vector3(0, 0, zdist));
	b[3] = Box(b[2].min() + Vector3(-xdist, 0, 0), b[2].max() + Vector3(-xdist, 0, 0));

	boxList.clear();
	for (int i = 0; i < 4; i++)
		boxList.push_back(b[i]);

	// generate second story
	//
	for (int i = 4; i < 8; i++) {
		b[i] = Box(b[i - 4].min() + h, b[i - 4].max() + h);
		boxList.push_back(b[i]);
	}
}

//RESOLVED: Complete
void Octree::create(const ofMesh & geo, int numLevels) {
	// initialize octree structure
	//
	mesh = geo;
	root.box = meshBounds(geo);
	for (size_t i = 0; i < geo.getNumVertices(); i++)
	{
		root.points.push_back(i);
	}
	subdivide(geo, root, numLevels, 0);

	colors.push_back(ofColor::white);
	colors.push_back(ofColor::dimGrey);
	colors.push_back(ofColor::red);
	colors.push_back(ofColor::orange);
	colors.push_back(ofColor::yellow);
	colors.push_back(ofColor::green);
	colors.push_back(ofColor::blue);
	colors.push_back(ofColor::indigo);
	colors.push_back(ofColor::violet);
}

//RESOLVED: Complete
//RESOLVED: Test
void Octree::subdivide(const ofMesh & mesh, TreeNode & node, int numLevels, int level) {
	if (level > numLevels) { return; }

	std::vector<Box> boxes;
	subDivideBox8(node.box, boxes);

	for (size_t i = 0; i < boxes.size(); i++)
	{
		cout << "level: " << level << " box: " << i << "\n";
		TreeNode childNode;
		childNode.box = boxes[i]; //update child node box
		getMeshPointsInBox(mesh, node.points, childNode.box, childNode.points); //update child node points
		if (childNode.points.size() > 1) { subdivide(mesh, childNode, numLevels, level + 1); }
		
		if (childNode.points.size() > 0) {
			node.children.push_back(childNode); //add child node to node children
		}
	}
}

//return all the leaf nodes that are intersected by the ray
bool Octree::intersect(const Ray & ray, TreeNode* node, std::vector<TreeNode*>* nodesRtn)
{
	if (!node->box.intersect(ray, -1000, 1000))
	{
		return false;
	}
	else
	{
		if (node->children.size() > 0)
		{
			for (size_t i = 0; i < node->children.size(); i++)
			{
				intersect(ray, &node->children[i], nodesRtn);
			}
		}
		else
		{
			//std::cout << "rip\n";
			//*nodeRtn = *node;
			nodesRtn->push_back(node);
			//return true;
		}
		return true;
	}
}

//TODO: Complete
/*
bool Octree::intersect(const Ray &ray, const TreeNode & node, TreeNode & nodeRtn) {
	if (!node.box.intersect(ray, -1000, 1000))
	{
		return false;
	}
	else
	{
		if (node.children.size() > 0)
		{
			bool rtn = false;
			std::vector<TreeNode> intersectedNodes;
			for (size_t i = 0; i < node.children.size(); i++)
			{
				bool result = intersect(ray, node.children[i], nodeRtn);
				
				if (result && !rtn)
				{
					rtn = result;
				}
				
				if (result)
				{
					intersectedNodes.push_back(node.children[i]);
				}
			}

			float closestDist = FLT_MAX;
			TreeNode closest;
			for (size_t i = 0; i < intersectedNodes.size(); i++)
			{
				//Vector3 rayOrigin(ray.origin.x, ray.origin.y, ray.origin.z);
				float curDist = (intersectedNodes[i].box.center() - ray.origin).length();
				if (curDist < closestDist)
				{
					closest = intersectedNodes[i];
					closestDist = curDist;
				}
			}
			nodeRtn = closest;

			return rtn;
		}
		else
		{
			nodeRtn = node;
			return true;
		}
	}
	
}
*/

//returns the closest vertex to the ray.
//get all the leaf nodes intersected by the ray, 
//then go through all the nodes and find the point closest to the ray origin.
ofVec3f Octree::trace(Ray ray)
{
	std::vector<TreeNode*> retNodes;
	intersect(ray, &root, &retNodes);
	//if (retNode == nullptr) { return ofVec3f(0.0f, 0.0f, 0.0f); }
	//int n = retNode.points.size();

	ofVec3f retPt;

	/*
	ofNoFill();
	for (int i = 0; i < retNodes.size(); i++)
	{
		drawBox(retNodes[i]->box);
	}
	ofFill();
	*/

	float distance = 0;
	for (int i = 0; i < retNodes.size(); i++)
	{
		for (int j = 0; j < retNodes[i]->points.size(); j++) {
			ofVec3f point = mesh.getVertex(retNodes[i]->points[j]);

			// In camera space, the camera is at (0,0,0), so distance from 
			// the camera is simply the length of the point vector
			//
			float curDist = (point - ofVec3f(ray.origin.x(), ray.origin.y(), ray.origin.z())).lengthSquared();

			if ((i == 0 && j == 0) || curDist < distance) {
				distance = curDist;
				retPt = point;
			}
		}
	}
	return retPt;
}

