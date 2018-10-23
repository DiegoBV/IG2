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
#include <vector>
using namespace Ogre;

#pragma once
class AppObj: public OgreBites::InputListener
{

protected:
	Ogre::SceneNode* pNode;
	std::vector<Ogre::SceneNode*> children;

public:
	AppObj() {};
	virtual ~AppObj() {};
	AppObj(Ogre::SceneNode* node): pNode(node) {};
	Ogre::SceneNode* addChild(std::string name, std::string material);
	Ogre::SceneNode* addChild(std::string name, std::string material, Ogre::SceneNode* father, Ogre::Entity* entidad = nullptr);
	inline Ogre::Node* getChild(std::string name) { return pNode->getChild(name); };
	inline Ogre::SceneNode* getMainNode() { return pNode; };
	inline void setMaterial(std::string child, std::string material) { pNode->getCreator()->getEntity(child)->setMaterialName(material); };
};

