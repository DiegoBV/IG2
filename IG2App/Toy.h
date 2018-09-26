#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>

#pragma once
class Toy: public OgreBites::InputListener
{
private:
	const Ogre::Real vel = 100;
	Ogre::SceneNode* pNode;
	Ogre::SceneNode* head;
	Ogre::SceneNode* body;
	Ogre::SceneNode* rEye;
	Ogre::SceneNode* lEye;
	Ogre::SceneNode* bButton;

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
};

// roll -> rota eje z
// pitch -> rota eje x
// yaw -> rota eje y

