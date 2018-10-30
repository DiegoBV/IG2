#include "IG2ApplicationContext.h"
#include <OgreAnimationState.h>
#include <OgreAnimationTrack.h>
#include <OgreMovableObject.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreSceneNode.h>
#include <OgreCameraMan.h>
#include <OgreAnimation.h>
#include <OgreKeyFrame.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <iostream>
#include <vector>

using namespace Ogre;
using namespace std;
#pragma once
class AppObj: public OgreBites::InputListener
{

protected:
	Ogre::SceneNode* pNode;
	std::vector<Ogre::SceneNode*> children;

	enum Eventos {
		colision
	};

	static std::vector<AppObj*> appListeners;
	static void fireAppEvent(Eventos evnt, AppObj* sender) { for (AppObj* obj : appListeners) { obj->reciveEvent(evnt, sender); } }

	virtual void reciveEvent(Eventos evnt, AppObj* sender) {};

public:
	AppObj() {};
	virtual ~AppObj() {};
	static void addAppListener(AppObj* obj) { appListeners.push_back(obj); };
	AppObj(Ogre::SceneNode* node): pNode(node) {};
	Ogre::SceneNode* addChild(std::string name, std::string material);
	Ogre::SceneNode* addChild(std::string name, std::string material, Ogre::SceneNode* father, Ogre::Entity* entidad = nullptr);
	inline Ogre::Node* getChild(std::string name) { return pNode->getChild(name); };
	inline Ogre::SceneNode* getMainNode() { return pNode; };
	inline void setMaterial(std::string child, std::string material) { pNode->getCreator()->getEntity(child)->setMaterialName(material); };
};

