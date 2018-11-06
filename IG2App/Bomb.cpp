#include "Bomb.h"



void Bomb::createAnim()
{
	bomb->setScale(.5, .5, .5);
	bomb->setPosition(keyFramePos);
	bomb->setInitialState(); //Guardamos el estado inicial


	anim = pNode->getCreator()->createAnimation("vaiven", animDuration); //Creamos la animacion
	track = anim->createNodeTrack(0);
	track->setAssociatedNode(bomb);

	longitudPaso = animDuration/2; //Longitud = duracion / (numero anim)-1

	kf = track->createNodeKeyFrame(longitudPaso * 0); //Primer Keyframe
	keyFramePos += Vector3::UNIT_Y * vel; //Posicion
	kf->setTranslate(keyFramePos); //Movemos la bomba

	kf = track->createNodeKeyFrame(longitudPaso * 1); //2� Keyframe
	keyFramePos += Vector3::NEGATIVE_UNIT_Y * vel*2; // posicion
	kf->setTranslate(keyFramePos); //Movemos

	animState = pNode->getCreator()->createAnimationState("vaiven"); //A�adimos la posicion al AnimState
	animState->setLoop(true); 
	animState->setEnabled(true);
}

Bomb::Bomb()
{
}


Bomb::~Bomb()
{
}

Bomb::Bomb(Ogre::SceneNode* node):AppObj(node) {

	bomb = addChild("bomb", "uv_sphere.mesh");

	setMaterial("bomb", "Bomb");

	createAnim();

	smoke = pNode->getCreator()->createParticleSystem("Smoke", "Smoke");  //crea el sistema de particulas a partir del script

	bomb->attachObject(smoke);                                            //attach al objeto
	smoke->setEmitting(false);
}

void Bomb::frameRendered(const Ogre::FrameEvent & evt)
{
	animState->addTime(evt.timeSinceLastFrame);             //update de la animacion
}

bool Bomb::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	switch (evt.keysym.sym)
	{
	case 'b':
		smoke->setEmitting(true);                //activa el humo
		break;
	default:
		return false;
	}
	return false;
}

void Bomb::receiveEvent(Eventos evnt, AppObj * sender)
{
	switch (evnt)
	{
	case AppObj::colision:
		if (sender->getName() == this->name || sender->getName() == "toy") {
			smoke->setEmitting(true);        //activa el humo
		}
		break;
	default:
		break;
	}
}
