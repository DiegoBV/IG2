#include "Toy.h"


Toy::Toy(Ogre::SceneNode * node): pNode(node)
{
	//pNode->setScale(15, 15, 15);

	body = pNode->createChildSceneNode("body"); //body
	Ogre::Entity* b = pNode->getCreator()->createEntity("sphere.mesh");
	body->attachObject(b);

	head = pNode->createChildSceneNode("head"); //head
	Ogre::Entity* h = pNode->getCreator()->createEntity("sphere.mesh");
	head->attachObject(h);
	head->setPosition(0, 140, 0);

	head->setScale(body->getInitialScale().x * 0.5, body->getInitialScale().y * 0.5, body->getInitialScale().z * 0.5);



	rEye= head->createChildSceneNode("rEye");//rEye
	Ogre::Entity* rE = pNode->getCreator()->createEntity("sphere.mesh");
	rEye->attachObject(rE);
	rEye->setScale(.2, .2, .2);
	rEye->setPosition(25, 0, 100);

	lEye = head->createChildSceneNode("lEye");//lEye
	Ogre::Entity* lE = pNode->getCreator()->createEntity("sphere.mesh");
	lEye->attachObject(lE);
	lEye->setScale(.2, .2, .2);
	lEye->setPosition(-25, 0, 100);

	bButton= body->createChildSceneNode("bButton");
	Ogre::Entity* bB = pNode->getCreator()->createEntity("sphere.mesh");
	bButton->attachObject(bB);
	bButton->setPosition(0, 0, 100);
	bButton->setScale(.3, .3, .3);

	/*head->setPosition(0, 100, 0);
	body->setPosition(0, 50, 0);*/
}
