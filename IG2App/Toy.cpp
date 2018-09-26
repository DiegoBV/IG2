#include "Toy.h"


Toy::Toy(Ogre::SceneNode * node): pNode(node)
{
	//cuerpo
	body = pNode->createChildSceneNode("body"); // se hace hijo del nodo padre (pNode)
	Ogre::Entity* b = pNode->getCreator()->createEntity("sphere.mesh"); //se crea una entidad accediendo al creador del nodo padre
	body->attachObject(b); //se vincula la entidad al nodo

	//cabeza
	head = pNode->createChildSceneNode("head");
	Ogre::Entity* h = pNode->getCreator()->createEntity("sphere.mesh");
	head->attachObject(h);
	head->setPosition(0, 140, 0);
	head->setScale(body->getInitialScale().x * 0.5, body->getInitialScale().y * 0.5, body->getInitialScale().z * 0.5);

	//ojo derecho
	rEye= head->createChildSceneNode("rEye");
	Ogre::Entity* rE = pNode->getCreator()->createEntity("sphere.mesh");
	rEye->attachObject(rE);
	rEye->setScale(.2, .2, .2);
	rEye->setPosition(25, 0, 100);

	//ojo izquierdo
	lEye = head->createChildSceneNode("lEye");
	Ogre::Entity* lE = pNode->getCreator()->createEntity("sphere.mesh");
	lEye->attachObject(lE);
	lEye->setScale(.2, .2, .2);
	lEye->setPosition(-25, 0, 100);

	//ombligo
	bButton= body->createChildSceneNode("bButton");
	Ogre::Entity* bB = pNode->getCreator()->createEntity("sphere.mesh");
	bButton->attachObject(bB);
	bButton->setPosition(0, 0, 100);
	bButton->setScale(.1, .1, .1);
}

void Toy::frameRendered(const Ogre::FrameEvent & evt)
{
	if (on) { //si esta en movimiento
		movement(evt.timeSinceLastFrame); //lo mueve de acuerdo al tiempo para velocidad constante
		rotateBody_Head(); //rota cabeza y cuerpo
	}
}

bool Toy::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_t:
		if (!on) { movement(1); rotateBody_Head(); } // si no está en movimiento, para el movimiento discreto
		break;
	case SDLK_y:
		on = !on; //activa el booleano
		break;
	case SDLK_v:
		rotateDirection(); //rota el nodo padre para que rote la direccion 
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
