#include "Mirror.h"
#include <iostream>


void Mirror::setReflection()
{
//-------------------------------Camera--------------------------
	camRef = pNode->getCreator()->createCamera("RefCam");
	camRef->setNearClipDistance(1);
	camRef->setFarClipDistance(10000);
	camRef->setAutoAspectRatio(true);

	Ogre::SceneNode* auxCam = pNode->getCreator()->getRootSceneNode()->createChildSceneNode("RefCam");
	auxCam->attachObject(camRef);

	auxCam->setPosition(0, 0, 0);
	auxCam->lookAt(Ogre::Vector3(0, 0, 1), Ogre::Node::TS_WORLD);

//-------------------------------MovablePlane--------------------------
	mp = new MovablePlane(Vector3::UNIT_Y, 0);
	mGridNode->attachObject(mp);
	camRef->enableReflection(mp);
	camRef->enableCustomNearClipPlane(mp);

//-------------------------------Texture--------------------------
	TexturePtr rttTex = TextureManager::getSingleton().createManual(
		"texRtt", // ejemplo
		ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		TEX_TYPE_2D,
		(Real)1080, // ejemplo ejemplo
		(Real)800, // ejemplo
		0, PF_R8G8B8, TU_RENDERTARGET);

	renderTexture = rttTex->getBuffer()->getRenderTarget();
	vpt = renderTexture->addViewport(camRef);
	vpt->setClearEveryFrame(true);
	vpt->setBackgroundColour(ColourValue::Black);

	tu = pNode->getCreator()->getEntity("mGrid")->getSubEntities()[0]->getMaterial()->getTechniques()[0]->getPasses()[0]->
		createTextureUnitState("texRtt");
	tu->setColourOperation(LBO_MODULATE); // backgroundColour -> black
										  // LBO_ADD / LBO_ALPHA_BLEND / LBO_REPLACE
	tu->setTextureAddressingMode(TextureUnitState::TAM_CLAMP);
	tu->setProjectiveTexturing(true, camRef);

	renderTexture->addListener(this); //?????????????
//-------------------------------FIN--------------------------
}

Mirror::Mirror()
{
}


Mirror::~Mirror()
{
	delete mp;
}

Mirror::Mirror(Ogre::SceneNode * node, std::string name, std::string material): AppObj(node)
{
	Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800", Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Ogre::Plane(Ogre::Vector3::UNIT_Y, 0), 1080, 800, 100, 80, true, 1, 1.0, 1.0, Ogre::Vector3::NEGATIVE_UNIT_Z); //crea el mesh
	mGridNode = addChild(name, "mPlane1080x800");
	setMaterial(name, material);

	setReflection();
}

void Mirror::preRenderTargetUpdate(const Ogre::RenderTargetEvent & evt) //??????????????????????
{
	mGridNode->setVisible(false);
	pNode->getCreator()->getLight("Luz")->setDiffuseColour(1, 1, 1);
}

void Mirror::postRenderTargetUpdate(const Ogre::RenderTargetEvent & evt) //???????????????????????
{
	mGridNode->setVisible(true);
	pNode->getCreator()->getLight("Luz")->setDiffuseColour(0.75, 0.75, 0.75);
}
