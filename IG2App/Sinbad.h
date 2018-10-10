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
		Dance,Run
	};
	animations follAnim_;
	Ogre::SceneNode* sinbadNode;
	Ogre::Entity* entity = nullptr;
	Ogre::AnimationState* animState;
	Ogre::AnimationState* animStateAux;
	void switchAnim();
};

