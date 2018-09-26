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
	bButton->setScale(.1, .1, .1);

	/*head->setPosition(0, 100, 0);
	body->setPosition(0, 50, 0);*/
}

void Toy::frameRendered(const Ogre::FrameEvent & evt)
{
	if (on) {
		movement(evt.timeSinceLastFrame);
		rotateBody_Head();
	}
}

bool Toy::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_t:
		if (!on) { movement(1); rotateBody_Head(); }
		break;
	case SDLK_y:
		on = !on;
		break;
	case SDLK_v:
		rotateDirection();
		break;
	//more cases
	default:
		break;
	}
	return true;
}

void Toy::movement(Ogre::Real time)
{
	//movimiento del objeto completo
	pNode->translate(0, 0, vel * time, Ogre::Node::TS_LOCAL); //si no se hace en local, por defecto es relativo al padre y no se
	//aplican las rotaciones previas
}

void Toy::rotateDirection()
{
	pNode->yaw(Ogre::Degree(45)); //rotacion de 45 grados, local por defecto
}

void Toy::rotateBody_Head()
{
	//movimiento de la cabeza (giro hacia un lado)
	head->yaw(Ogre::Radian(0.2));

	//movimiento del cuerpo
	body->pitch(Ogre::Radian(0.1));
}
