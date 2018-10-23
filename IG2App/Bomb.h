#pragma once
#include "AppObj.h"


class Bomb :
	public AppObj
{
private:
	void createAnim(); //Metodo que crea la animacion
	SceneNode* bomb = nullptr;

	Animation* anim = nullptr;
	AnimationState* animState = nullptr;
	NodeAnimationTrack* track = nullptr;
	Vector3 keyFramePos;
	Real longitudPaso;
	TransformKeyFrame* kf = nullptr;

	int animDuration = 5;
	int vel = 20;

public:
	Bomb();
	virtual ~Bomb();
	Bomb(Ogre::SceneNode* node);
	virtual void frameRendered(const Ogre::FrameEvent & evt);
};

