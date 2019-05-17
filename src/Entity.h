#pragma once

//Alan Duong, 05/16/19
//An entity class from which all game objects inherit from.
//The physics stuff is done here.

#include <vector>
#include <string>
#include <unordered_set>

#include "ofMain.h"
#include "ResourceManager.h"
#include "View.h"

//Define some basic layers.
#define LAYER_BG_BOTTOM 0
#define LAYER_BG_TOP 1
#define LAYER_FG_BOTTOM 2
#define LAYER_FG_MID 3
#define LAYER_FG_TOP 4

class EntitySystem; //class prototype

//Base class for game objects
//ToDo: Consider some method of static polymorphism?
//Use z position for render order
class Entity
{
public:
	Entity(std::string _id = "entity", ofVec3f _pos = ofVec3f(0.0f, 0.0f), float _scale = 1.0f, ofVec3f _ang = ofVec3f(0.0f, 0.0f, 0.0f), ofVec3f _vel = ofVec3f(0.0f, 0.0f));

	virtual void update();
	virtual void draw();
	void remove();
	void setEntitySystem(EntitySystem* _entSys);
	void setID(std::string _id);
	std::string getID();
	Entity* getOwner();
	void setOwner(Entity* _owner);
	void setVel(ofVec3f _vel);
	ofVec3f getVel();
	void setAng(ofVec3f _ang);
	ofVec3f getAng();
	void setPos(ofVec3f _pos);
	ofVec3f getPos();
	ofVec3f toWorld(ofVec3f _localpos);
	void setScale(float _scale);
	void setAlpha(float _alpha);
	void applyForce(ofVec3f _force);
	void setAngVel(float _angVel);
	void setColor(ofColor _color);
	ofVec3f forward(); //get forward vector
	void integrate();

	ofVec3f pos;
	ofVec3f size;
	float scale;
	ofVec3f vel;
	ofVec3f ang;
	ofColor color;
	int alpha;
	float mass;
	ofVec3f accel;
	float angVel;

	int lifespan; //in millis
	uint64_t createTime;

	Entity* owner;

	std::string id;

protected:
	EntitySystem * ents; //pointer to the entity system to handle deletion
};

//Manages all the entities
//ToDo: Use an object pool instead of a naive vector

struct AddInfo
{
	Entity* ent;
	int layer;
};

class EntitySystem
{
public:
	EntitySystem();
	~EntitySystem();

	void init(int numLayers = 5);

	void setResourceManager(ResourceManager* _rm);
	void setView(View* _view);

	void update();
	void draw();
	void add(Entity* ent, int layer = 0); //the layer determines render order. higher layer has higher priority.
	void remove(Entity* ent);
	void clear(); //deallocates (deletes) all entities.
	size_t size();

	std::vector<std::vector<Entity*>> entities;

	ResourceManager* rm;
	View* view;

private:
	std::unordered_set<Entity*> entitiesToRemove;
	std::vector<AddInfo> entitiesToAdd;
};
