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
	Ogre::SceneNode* pNode;
	Ogre::SceneNode* head;
	Ogre::SceneNode* body;
	Ogre::SceneNode* rEye;
	Ogre::SceneNode* lEye;
	Ogre::SceneNode* bButton;

public:
	Toy() {};
	virtual ~Toy() {};
	Toy(Ogre::SceneNode* node);
};

