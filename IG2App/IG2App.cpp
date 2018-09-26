#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include "Toy.h"

using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_p) {
	  rotateGrid();
  }
  //else if (evt.keysym.sym == SDLK_???)
  
  return true;
}

void IG2App::rotateGrid()
{
	mGridNode->pitch(Ogre::Radian(0.1));
}

void IG2App::shutdown()
{
  mShaderGenerator->removeSceneManager(mSM);  
  mSM->removeRenderQueueListener(mOverlaySystem);  
					
  mRoot->destroySceneManager(mSM);  

  delete mTrayMgr;  mTrayMgr = nullptr;
  delete mCamMgr; mCamMgr = nullptr;
  
  // do not forget to call the base 
  IG2ApplicationContext::shutdown();
}

void IG2App::setup(void)
{
  // do not forget to call the base first
  IG2ApplicationContext::setup();

  mSM = mRoot->createSceneManager();  

  // register our scene with the RTSS
  mShaderGenerator->addSceneManager(mSM);

  mSM->addRenderQueueListener(mOverlaySystem);

  mTrayMgr = new OgreBites::TrayManager("TrayGUISystem", mWindow.render);  
  mTrayMgr->showFrameStats(OgreBites::TL_BOTTOMLEFT);
  addInputListener(mTrayMgr);

  addInputListener(this);   
  setupScene();
}

void IG2App::setupScene(void)
{
  // create the camera
  Camera* cam = mSM->createCamera("Cam");
  cam->setNearClipDistance(1); 
  cam->setFarClipDistance(10000);
  cam->setAutoAspectRatio(true);
  //cam->setPolygonMode(Ogre::PM_WIREFRAME); 

  mCamNode = mSM->getRootSceneNode()->createChildSceneNode("nCam");
  mCamNode->attachObject(cam);

  mCamNode->setPosition(0, 0, 1000);
  mCamNode->lookAt(Ogre::Vector3(0, 0, 0), Ogre::Node::TS_WORLD);
  //mCamNode->setDirection(Ogre::Vector3(0, 0, -1));  
  
  // and tell it to render into the main window
  Viewport* vp = getRenderWindow()->addViewport(cam);
  //vp->setBackgroundColour(Ogre::ColourValue(1, 1, 1));

  //------------------------------------------------------------------------

  // without light we would just get a black screen 

  Light* luz = mSM->createLight("Luz");
  luz->setType(Ogre::Light::LT_DIRECTIONAL);
  luz->setDiffuseColour(0.75, 0.75, 0.75);

  //mLightNode = mSM->getRootSceneNode()->createChildSceneNode("nLuz");
  mLightNode = mCamNode->createChildSceneNode("nLuz");
  mLightNode->attachObject(luz);

  mLightNode->setDirection(Ogre::Vector3(0, 0, -1));  //vec3.normalise();
  //lightNode->setPosition(0, 0, 1000);
 
  //------------------------------------------------------------------------

  // finally something to render

  Ogre::MeshManager::getSingleton().createPlane("mPlane1080x800", ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME, Plane(Vector3::UNIT_Y, 0), 1080, 800, 100, 80, true, 1, 1.0, 1.0, Vector3::NEGATIVE_UNIT_Z); //crea el mesh
  Ogre::Entity* plano = mSM->createEntity("mPlane1080x800"); //a�adimos a una entity el mesh

  mGridNode = mSM->getRootSceneNode()->createChildSceneNode("mGrid"); //crea hijo del arbol de recursos y se lo asigna al puntero del nodo
  mGridNode->attachObject(plano); //a�adir el objeto al nodo
  plano->setMaterialName("Plano");
  //mGridNode->showBoundingBox(true);

  Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

  mSinbadNode = mGridNode->createChildSceneNode("nSinbad"); //Asignamos mSinbadNode  como hijo de mGridNode con el valor de nSinbad 
  mSinbadNode->attachObject(ent);

  mSinbadNode->setPosition(400, 100, -300);
  mSinbadNode->setOrientation(0, 0, 180, 0);
  mSinbadNode->setScale(20, 20, 20);
  //mSinbadNode->yaw(Ogre::Degree(-45));
  //mSinbadNode->showBoundingBox(true);
  //mSinbadNode->setVisible(false);

  toy = mGridNode->createChildSceneNode("toy");
  Toy* t = new Toy(toy);
  toy->setPosition(0, 100, 0);
  addInputListener(t); //lo a�adimos como listener para que reciba los eventos de teclado

  //------------------------------------------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------

}

