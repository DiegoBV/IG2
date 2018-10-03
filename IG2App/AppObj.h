#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include <OgreCameraMan.h>
#include <OgreEntity.h>
#include <OgreMeshManager.h>
#include <vector>

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
	Ogre::SceneNode* addChild(std::string name, std::string material, Ogre::SceneNode* father);
	inline Ogre::Node* getChild(std::string name) { return pNode->getChild(name); };
	inline Ogre::SceneNode* getMainNode() { return pNode; };
	inline void setMaterial(std::string child, std::string material) { pNode->getCreator()->getEntity(child)->setMaterialName(material); };
};

