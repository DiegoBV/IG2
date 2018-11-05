#include "IG2ApplicationContext.h"
#include <OgreAnimationState.h>
#include <OgreAnimationTrack.h>
#include <OgreMovableObject.h>
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>
#include <OgreSceneNode.h>
#include <OgreCameraMan.h>
#include <OgreAnimation.h>
#include <OgreSkeleton.h>
#include <OgreKeyFrame.h>
#include <OgreEntity.h>
#include <OgreTrays.h>
#include <OgreMesh.h>
#include <OgreBone.h>
#include <iostream>
#include <vector>

using namespace Ogre;
using namespace std;
#pragma once
class AppObj: public OgreBites::InputListener
{

public:
	enum Eventos {
		colision
	};

protected:
	Ogre::SceneNode* pNode;                                                                                                         //nodo padre del objeto

	std::vector<Ogre::SceneNode*> children;                                                                                        //lista de hijos del nodo padre

	static std::vector<AppObj*> appListeners;                                                                                        //lista de listeners


	virtual void receiveEvent(Eventos evnt, AppObj* sender) {};                                                                      //metodo virtual, cada objeto reaccionara o no a los eventos

public:

	AppObj() {};

	virtual ~AppObj() {};

	AppObj(Ogre::SceneNode* node): pNode(node) {};

	static void fireAppEvent(Eventos evnt, AppObj* sender) { for (AppObj* obj : appListeners) { obj->receiveEvent(evnt, sender); } }  //por cada listener, llama a su metodo "receiveEvent"

//------------------------------------------------------------ADDS-----------------------------------------------

	static void addAppListener(AppObj* obj) { appListeners.push_back(obj); };                                                  //metodo estatico que añade un listener de eventos

	Ogre::SceneNode* addChild(std::string name, std::string material);                                                          //anyade un hijo al padre (por ejemplo, el body o la cabeza del toy)

	Ogre::SceneNode* addChild(std::string name, std::string material, Ogre::SceneNode* father, Ogre::Entity* entidad = nullptr); //anyade un hijo al padre indicado (por ejemplo, los ojos de toy)

 //------------------------------------------------------------GETS-----------------------------------------------

	inline Ogre::Node* getChild(std::string name) { return pNode->getChild(name); };                                             //devuelve un hijo por el nombre

	inline Ogre::SceneNode* getMainNode() { return pNode; };                                                                     //devuelve el padre

//------------------------------------------------------------SETS-----------------------------------------------

	inline void setMaterial(std::string child, std::string material) {                                                           //cambia el material de un hijo por el nombre indicado
		pNode->getCreator()->getEntity(child)->setMaterialName(material); };    
};

