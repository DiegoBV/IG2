#pragma once
#include "AppObj.h"
class Sinbad :
	public AppObj
{
private:

	enum animations                               //enum de las distintas animaciones de sinbad
	{
		Dance,Run,Suicide,Muerto
	};

	animations follAnim_;                       //variable que indica la siguiente animacion que sinbad tiene que realizar

	Ogre::SceneNode* sinbadNode;
	Ogre::Entity* entity = nullptr;
	
	Entity* swordR = nullptr;                    //Espada Derecha
	Entity* swordL = nullptr;                   //Espada Izquierda

	Ogre::AnimationState* animState;           //AnimStates, los usamos para bailar y para correr (parte de arriba y de abajo)
	Ogre::AnimationState* animStateAux;

	void switchAnim();                        //cambia entre las animaciones dependiendo de la variable "follAnim_"

//-----------------------------------------------------------------------Animacion de andar por el plano---------------------------------------

	void createWalk();                          //Metodo que crea la animacion
	Animation* anim = nullptr;                 //Animacion de andar
	AnimationState* walkinState = nullptr;    //estado Andando
	NodeAnimationTrack* track = nullptr;
	Vector3 keyFramePos;                    //Vector para las posiciones de la animacion
	Real longitudPaso; 
	TransformKeyFrame* kf = nullptr;
	Real animDuration = 10; //Duracion total de la animacion

//-----------------------------------------------------------------------Animacion suicidio (ir a la bomba)---------------------------------------

	void suicide();
	Animation* suic = nullptr;
	AnimationState* suicideState = nullptr;
	NodeAnimationTrack* suiTrack = nullptr;
	Vector3 bombPos;
	Real stepLeng;
	TransformKeyFrame* sKf = nullptr;

//-----------------------------------------------------------------------Animacion de muerto---------------------------------------

	void death();
	Animation* deathAnim = nullptr;
	AnimationState* deathState = nullptr;
	NodeAnimationTrack* deathTrack = nullptr;
	Vector3 deathPos;
	Real deathLenght;
	Real deathDuration = 300;
	TransformKeyFrame* deathKf;


public:
	Sinbad();

	virtual ~Sinbad();

	Sinbad(Ogre::SceneNode* node);

	Ogre::SceneNode* getSinbad() const { return sinbadNode; };

	virtual void frameRendered(const Ogre::FrameEvent & evt);

	virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);

	virtual void receiveEvent(Eventos evnt, AppObj* sender);
};


