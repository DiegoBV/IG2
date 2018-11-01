#pragma once
#include "AppObj.h"
#include <OgreMovablePlane.h>
#include <OgreTextureManager.h>
#include <OgreRenderTexture.h>
#include <OgreHardwarePixelBuffer.h>
#include <OgreSubEntity.h>
#include <OgreMaterial.h>
#include <OgreTechnique.h>
#include <OgrePass.h>
#include <OgreRenderTargetListener.h>

using namespace Ogre;

class Mirror :
	public AppObj, public RenderTargetListener
{
private:
	std::string name;

	Ogre::SceneNode* mGridNode = nullptr;

	Entity* planoAux = nullptr;

//----------------------------------------------------------------------REFLECTION-------------------------------------------

	Camera* camRef;

	MovablePlane* mp;

	RenderTexture* renderTexture;

	Viewport * vpt;

	TextureUnitState* tu;


	ColourValue def_Ambient;

	void setReflection(SceneNode* camNode);

public:
	Mirror();

	virtual ~Mirror();

	Mirror(Ogre::SceneNode* node, std::string name, std::string material, SceneNode* camNode = nullptr);

	inline SceneNode* getMirror() { return mGridNode; };

	virtual void preRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);                                //util para evitar que el espejo se refleje a s� mismo

	virtual void postRenderTargetUpdate(const Ogre::RenderTargetEvent& evt);
};

