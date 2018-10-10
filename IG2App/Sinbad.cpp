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
		animState = entity->getAnimationState("Dance");
		animState->setEnabled(true);
		animState->setLoop(true);
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
		follAnim_ = Dance;
		break;
	default:
		break;
	}
}
