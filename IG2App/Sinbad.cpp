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
	else if(follAnim_ == Suicide){
		
		suicideState->addTime(evt.timeSinceLastFrame);

		if (!suicideState->hasEnded()) {
			animState->addTime(evt.timeSinceLastFrame);
			animStateAux->addTime(evt.timeSinceLastFrame);
		}
		else {
			death();
			follAnim_ = Muerto;
			switchAnim();
		}

	}
	else if (follAnim_ == Muerto) {
		deathState->addTime(evt.timeSinceLastFrame);
	}
	else {
		animState->addTime(evt.timeSinceLastFrame);
		animStateAux->addTime(evt.timeSinceLastFrame);
		walkinState->addTime(evt.timeSinceLastFrame);
		if(suicideState != nullptr)
			suicideState->addTime(evt.timeSinceLastFrame);
	}
	
}

bool Sinbad::keyPressed(const OgreBites::KeyboardEvent & evt)
{
	switch (evt.keysym.sym)
	{
	case SDLK_r:
		switchAnim();
		break;
	case SDLK_b:
		suicide();
		follAnim_ = Suicide;
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
	case Sinbad::Suicide:
		animState->setEnabled(false);
		animStateAux->setEnabled(false);
		walkinState->setEnabled(false);

		animStateAux->setEnabled(false);
		animState->setEnabled(false);
		animState = entity->getAnimationState("RunBase");
		animState->setEnabled(true);
		animState->setLoop(true);
		animStateAux->setEnabled(true);
		animStateAux->setLoop(true);

		entity->detachObjectFromBone(swordR);
		entity->attachObjectToBone("Handle.R", swordR);

		suicideState->setEnabled(true);
		suicideState->setLoop(false);
		break;
	case Sinbad::Muerto:
		animState->setEnabled(false);
		animStateAux->setEnabled(false);
		walkinState->setEnabled(false);
		suicideState->setEnabled(false);

		entity->detachObjectFromBone(swordR);
		entity->attachObjectToBone("Sheath.R", swordR);

		deathState->setEnabled(true);
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

	Vector3 src(0, 0, 1);
	Vector3 dest(0, 0, 1);
	Quaternion quat = src.getRotationTo(dest);

	longitudPaso = animDuration / 8;
	int i = 0;
	kf = track->createNodeKeyFrame(longitudPaso * i++); //Primer Keyframe
	keyFramePos = Vector3(0, 0, 50); //Posicion inicial
	kf->setTranslate(keyFramePos);
	quat = src.getRotationTo(dest);
	kf->setRotation(quat);
	

	kf = track->createNodeKeyFrame(longitudPaso * i++); //2º Keyframe
	keyFramePos = Vector3(0, 0, 550);
	kf->setTranslate(keyFramePos);
	kf->setRotation(quat);

	kf = track->createNodeKeyFrame(longitudPaso * i++); //2º Keyframe
	keyFramePos = Vector3(-50, 0, 600);
	kf->setTranslate(keyFramePos);
	dest = { -1,0,0 };
	quat = src.getRotationTo(dest);
	kf->setRotation(quat);

	kf = track->createNodeKeyFrame(longitudPaso * i++); //3º Keyframe
	keyFramePos = Vector3(-750, 0, 600);
	kf->setTranslate(keyFramePos);
	kf->setRotation(quat);

	kf = track->createNodeKeyFrame(longitudPaso * i++); //4º Keyframe
	keyFramePos = Vector3(-800, 0, 550);
	dest = { 0, 0, -1};
	quat = src.getRotationTo(dest);
	kf->setRotation(quat);
	kf->setTranslate(keyFramePos);

	kf = track->createNodeKeyFrame(longitudPaso * i++); //4º Keyframe
	keyFramePos = Vector3(-800, 0, 50);
	kf->setTranslate(keyFramePos);
	kf->setRotation(quat);


	kf = track->createNodeKeyFrame(longitudPaso * i++); //4º Keyframe
	keyFramePos = Vector3(-750, 0, 0);
	dest = { 1, 0, 0 };
	quat = src.getRotationTo(dest);
	kf->setRotation(quat);
	kf->setTranslate(keyFramePos);
	kf->setRotation(quat);

	kf = track->createNodeKeyFrame(longitudPaso * i++); //4º Keyframe
	keyFramePos = Vector3(-50, 0, 0);
	kf->setTranslate(keyFramePos);
	kf->setRotation(quat);


	//El Loop se encarga de volver a la posicion inicial
	walkinState = pNode->getCreator()->createAnimationState("walk");
	//walkinState->setLoop(false);
	//walkinState->setEnabled(false);
}

void Sinbad::suicide()
{
	Vector3 src(0, 0, 1);

	suic = pNode->getCreator()->createAnimation("suicide", animDuration);
	suiTrack = suic->createNodeTrack(0);
	suiTrack->setAssociatedNode(sinbadNode);
	

	bombPos = { -400, 0, 300 };

	Vector3 currentPos = sinbadNode->getPosition() - Vector3(400, 100, -300);

	stepLeng = animDuration;

	sKf = suiTrack->createNodeKeyFrame(stepLeng * 0);
	sKf->setTranslate(currentPos);
	Vector3 ori = bombPos - currentPos;
	Quaternion quat = src.getRotationTo(ori);
    sKf->setRotation(quat);

	sKf = suiTrack->createNodeKeyFrame(stepLeng * 1);
	sKf->setTranslate(bombPos);
	sKf->setRotation(quat);

	suicideState = pNode->getCreator()->createAnimationState("suicide");
}

void Sinbad::death()
{
	deathAnim = pNode->getCreator()->createAnimation("death", deathDuration);
	deathTrack = deathAnim->createNodeTrack(0);
	deathTrack->setAssociatedNode(sinbadNode);

	deathPos = sinbadNode->getPosition() - Vector3(400, 200, -300); // 200 para que este a lvl suelo


	Vector3 src(0, 0, 1);
	Vector3 dst(0, 1, 0);
	Quaternion quat;

	deathLenght = deathDuration/2;
	//Primer frame
	deathKf = deathTrack->createNodeKeyFrame(deathLenght * 0);
	deathKf->setTranslate(deathPos);
	quat = src.getRotationTo(dst);
	deathKf->setRotation(quat);

	//Segundo frame
	deathKf = deathTrack->createNodeKeyFrame(deathLenght * 1);
	deathPos -= Vector3(-36000, 0, 0); //Movemos hacia la derecha
	deathKf->setTranslate(deathPos);//Movimiento
	deathKf->setRotation(quat); // rotacion

	deathState = pNode->getCreator()->createAnimationState("death");
}
