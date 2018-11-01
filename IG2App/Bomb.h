#pragma once
#include "AppObj.h"
#include <OgreParticleSystem.h>

class Bomb :
	public AppObj
{
private:
	void createAnim(); //Metodo que crea la animacion
	SceneNode* bomb = nullptr;

//-------------------------------------ANIMATION-----------------------
	Animation* anim = nullptr;
	AnimationState* animState = nullptr;
	NodeAnimationTrack* track = nullptr;
	Vector3 keyFramePos = {0, 0, 0};
	Real longitudPaso;
	TransformKeyFrame* kf = nullptr;

	ParticleSystem* smoke = nullptr;

	int animDuration = 5;
	int vel = 20;

public:
	Bomb();

	virtual ~Bomb();

	Bomb(Ogre::SceneNode* node);

	virtual void frameRendered(const Ogre::FrameEvent & evt);

	virtual bool keyPressed(const OgreBites::KeyboardEvent & evt);

	virtual void receiveEvent(Eventos evnt, AppObj* sender);
};

