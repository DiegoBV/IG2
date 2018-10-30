#include "AppObj.h"

#pragma once
class Toy: public AppObj
{
private:
	const Ogre::Real vel = 100;
	Ogre::SceneNode* head;
	Ogre::SceneNode* body;

	Entity* bodyEnt = nullptr;
	
	Sphere bmb;

	bool on = false;
	int XX = 0;

	void movement(Ogre::Real time);
	void rotateDirection();
	void rotateBody_Head();
	bool check_collision();

public:
	Toy() {};
	virtual ~Toy() {};
	Toy(Ogre::SceneNode* node);
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	InputListener* getTrueSelf() { return this; };

	virtual void reciveEvent(Eventos evnt, AppObj* sender);

	void setBomb(const Sphere nBomb) { bmb = nBomb; };
};

// roll -> rota eje z
// pitch -> rota eje x
// yaw -> rota eje y

