#include "Toy.h"


Toy::Toy(Ogre::SceneNode * node): AppObj(node)                                          //crea todos los nodos y entidades de toy
{
	//cuerpo
	body = addChild("body", "sphere.mesh");                      //crea el nodo del cuerpo, con padre pNode (pNode en toy es un nodo hijo vacio del plano)
	bodyEnt = pNode->getCreator()->getEntity("body");           //guardamos la entidad de body para las colisiones

	//cabeza
	head = addChild("head", "sphere.mesh");                    //igual que el body
	head->setPosition(0, 140, 0);
	head->setScale(body->getInitialScale().x * 0.5, body->getInitialScale().y * 0.5, body->getInitialScale().z * 0.5);    //cambios en escala y posicion para que adquiera la forma que queremos

	//ojo derecho
	Ogre::SceneNode* rEye = addChild("rEye", "sphere.mesh", head);    //crea el nodo del ojo derecho con padre head
	rEye->setScale(.2, .2, .2);
	rEye->setPosition(25, 0, 100);

	//ojo izquierdo
	Ogre::SceneNode* lEye = addChild("lEye", "sphere.mesh", head);   //igual que el ojo derecho    
	lEye->setScale(.2, .2, .2);
	lEye->setPosition(-25, 0, 100);

	//ombligo
	Ogre::SceneNode* bButton = addChild("bButton", "sphere.mesh", body);  //crea el nodo del ombligo con padre body
	bButton->setPosition(0, 0, 100);
	bButton->setScale(.1, .1, .1);

	setBomb(pNode->getCreator()->getEntity("bomb")->getWorldBoundingSphere());   //accedemos a la entidad de la bomba para guardar sus coordenadas
}

void Toy::frameRendered(const Ogre::FrameEvent & evt)
{
	if (on) {                                   //si esta en movimiento
		movement(evt.timeSinceLastFrame);       //lo mueve de acuerdo al tiempo para velocidad constante
		rotateBody_Head();                     //rota cabeza y cuerpo
	}

	if (check_collision()) {
		fireAppEvent(colision, this);         //si se da colision entre body y bomb, lanza el evento de que se ha producido una colision
	}
}

bool Toy::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_t:
		if (!on) { movement(1); rotateBody_Head(); }          // si no está en movimiento, para el movimiento discreto
		break;
	case SDLK_y:
		on = !on;                                            //activa el booleano
		break;
	case SDLK_v:
		rotateDirection();                                  //rota el nodo padre para que rote la direccion 
		break;
	//more cases
	default:
		break;
	}
	return true;
}

void Toy::receiveEvent(Eventos evnt, AppObj * sender)
{
	switch (evnt)
	{
	case AppObj::colision:                                           //hacemos invisible el objeto entero
		pNode->getCreator()->getEntity("body")->setVisible(false);
		pNode->getCreator()->getEntity("head")->setVisible(false);
		pNode->getCreator()->getEntity("rEye")->setVisible(false);
		pNode->getCreator()->getEntity("lEye")->setVisible(false);
		pNode->getCreator()->getEntity("bButton")->setVisible(false);
		on = false;
		break;
	default:
		break;
	}
}

void Toy::movement(Ogre::Real time)
{
	//movimiento del objeto completo
	getMainNode()->translate(0, 0, vel * time, Ogre::Node::TS_LOCAL); //si no se hace en local, por defecto es relativo al padre y no se
	//aplican las rotaciones previas
}

void Toy::rotateDirection()
{
	getMainNode()->yaw(Ogre::Degree(45)); //rotacion de 45 grados, local por defecto
}

void Toy::rotateBody_Head()
{
	//movimiento de la cabeza (giro hacia un lado)
	head->yaw(Ogre::Radian(0.2));

	//movimiento del cuerpo
	body->pitch(Ogre::Radian(0.1));
}

bool Toy::check_collision()
{
	if (bodyEnt->isVisible()) {
		Sphere sphere = bodyEnt->getWorldBoundingSphere();
		return sphere.intersects(bmb);
	}
	else return false;
}
