#include "Sinbad.h"



Sinbad::Sinbad()
{
}

Sinbad::~Sinbad()
{
}

Sinbad::Sinbad(Ogre::SceneNode * node): AppObj(node)
{
	sinbadNode = addChild("nSinbad", "Sinbad.mesh");

	entity = pNode->getCreator()->getEntity("nSinbad");

	
	swordR = pNode->getCreator()->createEntity("swordR","Sword.mesh");
	entity->attachObjectToBone("Sheath.R", swordR);

	swordL = pNode->getCreator()->createEntity("swordL", "Sword.mesh");
	entity->attachObjectToBone("Sheath.L", swordL);

	createWalk();


	if (entity != nullptr) {
		follAnim_ = Run;
		animState = entity->getAnimationState("Dance");
		animStateAux = entity->getAnimationState("RunTop");
		animState->setEnabled(true);
		animState->setLoop(true);
	}
}

void Sinbad::frameRendered(const Ogre::FrameEvent & evt)
{
	if (follAnim_ == Run) {
		animState->addTime(evt.timeSinceLastFrame);
	}
	else {
		animState->addTime(evt.timeSinceLastFrame);
		animStateAux->addTime(evt.timeSinceLastFrame);
		walkinState->addTime(evt.timeSinceLastFrame);
	}
	
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_r:
		switchAnim();
		break;
	default:
		break;
	}
	return false;
}

void Sinbad::switchAnim()
{
	switch (follAnim_)
	{
	case Sinbad::Dance:
		animState->setEnabled(false);
		animStateAux->setEnabled(false);
		walkinState->setEnabled(false);

		animState = entity->getAnimationState("Dance");
		animState->setEnabled(true);
		animState->setLoop(true);

		entity->detachObjectFromBone(swordR);
		entity->attachObjectToBone("Sheath.R", swordR);

		follAnim_ = Run;
		break;
	case Sinbad::Run:
		animStateAux->setEnabled(false);
		animState->setEnabled(false);
		animState = entity->getAnimationState("RunBase");
		animState->setEnabled(true);
		animState->setLoop(true);
		animStateAux->setEnabled(true);
		animStateAux->setLoop(true);

		walkinState->setLoop(true);
		walkinState->setEnabled(true);

		entity->detachObjectFromBone(swordR);
		entity->attachObjectToBone("Handle.R", swordR);

		follAnim_ = Dance;
		break;
	default:
		break;
	}
}

void Sinbad::createWalk()
{
	
	sinbadNode->setPosition(400, 100, -300); //Colocamos a simbad
	sinbadNode->setScale(20, 20, 20); //Cambiamos la escala
	sinbadNode->setInitialState(); //Guardamos la posicion actual
	//Al guardar la nueva posicion creamos un nuevo sistema de coordenadas relativo a simbad.
	//Su posicion actual es 0,0,0

	anim = pNode->getCreator()->createAnimation("walk", animDuration);
	track = anim->createNodeTrack(0);
	track->setAssociatedNode(sinbadNode);

	longitudPaso = animDuration / 3;

	kf = track->createNodeKeyFrame(longitudPaso * 0); //Primer Keyframe
	keyFramePos = Vector3(0, 0, 0); //Posicion inicial
	kf->setTranslate(keyFramePos);

	kf = track->createNodeKeyFrame(longitudPaso * 1); //2º Keyframe
	keyFramePos = Vector3(0, 0, 600);
	kf->setTranslate(keyFramePos);

	kf = track->createNodeKeyFrame(longitudPaso * 2); //3º Keyframe
	keyFramePos = Vector3(-800, 0, 600);
	kf->setTranslate(keyFramePos);

	kf = track->createNodeKeyFrame(longitudPaso * 3); //4º Keyframe
	keyFramePos = Vector3(-800, 0, 00);
	kf->setTranslate(keyFramePos);

	//El Loop se encarga de volver a la posicion inicial

	walkinState = pNode->getCreator()->createAnimationState("walk");
	walkinState->setLoop(false);
	walkinState->setEnabled(false);
}
