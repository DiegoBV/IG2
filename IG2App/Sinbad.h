#pragma once
#include "AppObj.h"
class Sinbad :
	public AppObj
{
public:
	Sinbad();
	virtual ~Sinbad();
	Sinbad(Ogre::SceneNode* node);
	Ogre::SceneNode* getSinbad() const { return sinbadNode; };
	virtual void frameRendered(const Ogre::FrameEvent & evt);
	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);
private: 
	enum animations
	{
		Dance,Run,Suicide,Muerto
	};
	animations follAnim_;
	Ogre::SceneNode* sinbadNode;
	Ogre::Entity* entity = nullptr;
	
	Entity* swordR = nullptr; //Espada Derecha
	Entity* swordL = nullptr; //Espada Izquierda
	Ogre::AnimationState* animState;
	Ogre::AnimationState* animStateAux;
	void switchAnim();

	void createWalk(); //Metodo que crea la animacion
	Animation* anim = nullptr; //Animacion de andar
	AnimationState* walkinState = nullptr; //estado Andando
	NodeAnimationTrack* track = nullptr;
	Vector3 keyFramePos; //Vector para las posiciones de la animacion
	Real longitudPaso; 
	TransformKeyFrame* kf = nullptr;

	Real animDuration = 10; //Duracion total de la animacion

	void suicide();
	Animation* suic = nullptr;
	AnimationState* suicideState = nullptr;
	NodeAnimationTrack* suiTrack = nullptr;
	Vector3 bombPos;
	Real stepLeng;
	TransformKeyFrame* sKf = nullptr;


	void death();
	Animation* deathAnim = nullptr;
	AnimationState* deathState = nullptr;
	NodeAnimationTrack* deathTrack = nullptr;
	Vector3 deathPos;
	Real deathLenght;
	Real deathDuration = 300;
	TransformKeyFrame* deathKf;





	//int vel = 20;
};

