#include "AppObj.h"
#include <iostream>

Ogre::SceneNode* AppObj::addChild(std::string name, std::string material)
{
	Ogre::SceneNode* child = pNode->createChildSceneNode(name); // se hace hijo del nodo padre (pNode)
	children.push_back(child);

	if (material != "") {
		Ogre::Entity* ent = pNode->getCreator()->createEntity(name, material); //se crea una entidad accediendo al creador del nodo padre
		child->attachObject(ent); //se vincula la entidad al nodo
	}

	return child;
}

Ogre::SceneNode * AppObj::addChild(std::string name, std::string material, Ogre::SceneNode * father, Ogre::Entity* entidad)
{
	Ogre::SceneNode* child = father->createChildSceneNode(name); // se hace hijo del nodo padre (pNode)
	children.push_back(child);

	if (material != "") {
		Ogre::Entity* ent = father->getCreator()->createEntity(material); //se crea una entidad accediendo al creador del nodo padre
		child->attachObject(ent); //se vincula la entidad al nodo
		entidad = ent;
	}

	return child;
}
