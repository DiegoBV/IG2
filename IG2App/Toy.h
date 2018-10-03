#include "AppObj.h"

#pragma once
class Toy: public AppObj
{
private:
	const Ogre::Real vel = 100;
	Ogre::SceneNode* head;
	Ogre::SceneNode* body;

	bool on = false;

	void movement(Ogre::Real time);
	void rotateDirection();
	void rotateBody_Head();

public:
	Toy() {};
	virtual ~Toy() {};
	Toy(Ogre::SceneNode* node);
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	InputListener* getTrueSelf() { return this; };
};

// roll -> rota eje z
// pitch -> rota eje x
// yaw -> rota eje y

