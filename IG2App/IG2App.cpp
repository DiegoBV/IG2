#include "IG2App.h"

#include <OgreEntity.h>
#include <OgreInput.h>
#include <SDL_keycode.h>
#include <OgreMeshManager.h>
#include "Toy.h"
#include "Mirror.h"
#include "Sinbad.h"



using namespace Ogre;

bool IG2App::keyPressed(const OgreBites::KeyboardEvent& evt)
{
  if (evt.keysym.sym == SDLK_ESCAPE)
  {
    getRoot()->queueEndRendering();
  }
  else if (evt.keysym.sym == SDLK_p) {        //rotamos el plano
	  rotateGrid();
  }
  else if ((evt.keysym.sym == SDLK_c)) {    //cambiamos el target de la camara

	  flag = !flag;
	  if(flag){mCamMgr->setTarget(mSinbadNode);  }
	  else mCamMgr->setTarget(mSM->getRootSceneNode());  

  }
  //else if (evt.keysym.sym == SDLK_???)
  
  return true;
}

void IG2App::frameRendered(const Ogre::FrameEvent & evt)
{
	checkCollisions();
}

void IG2App::checkCollisions()                                     //si se da colision entre dos objetos en el vector, lanza el evento de que se ha producido una colision
{
	int  i = 0;
	int j = 1;
	for (i = 0; i < colisionables.size() - 1; j++) {
		//comprobacion J
		if (colisionables[i].second->isVisible()) {
			Sphere sphere = colisionables[i].second->getWorldBoundingSphere();
			if (sphere.intersects(colisionables[j].second->getWorldBoundingSphere())) {
				AppObj::fireAppEvent(AppObj::colision, colisionables[i].first);
			}
		}

		if (j = colisionables.size()) {
			i++;
			j = i + 1;
		}
	}
}

void IG2App::rotateGrid() //rota el plano
{
	mGridNode->pitch(Ogre::Radian(0.1));
}

void IG2App::shutdown()
{
	for (AppObj* obj : actors) {
		delete obj;
	}

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

//-------------------------------------------PLANO---------------------------------------

  actors.push_back(new Mirror(mSM->getRootSceneNode(), "mGrid", "Plano", mCamNode));
  mGridNode = dynamic_cast<Mirror*>(actors.back())->getMirror();
  //mGridNode->showBoundingBox(true);


 //-------------------------------------------SINBAD---------------------------------------

  //Ogre::Entity* ent = mSM->createEntity("Sinbad.mesh");

  //mSinbadNode = mGridNode->createChildSceneNode("nSinbad"); //Asignamos mSinbadNode  como hijo de mGridNode con el valor de nSinbad 
  //mSinbadNode->attachObject(ent);

  Sinbad* sin = new Sinbad(mGridNode);
  actors.push_back(sin);
  mSinbadNode = sin->getSinbad();
  AppObj::addAppListener(actors.back());  //añadimos como listener de eventos --> colision
  addInputListener(actors.back());
 
 //-------------------------------------------BOMBA---------------------------------------

  bomba = mGridNode->createChildSceneNode("bomba");
  actors.push_back(new Bomb(bomba));
  addInputListener(actors.back());
  AppObj::addAppListener(actors.back());
  colisionables.push_back({ actors.back(), mSM->getEntity("bomb") });       //guardamos la entity de bomba en el vector de colisionables

//-------------------------------------------TOY---------------------------------------
  toy = mGridNode->createChildSceneNode("toy");  //cuello, nodo vacio
  actors.push_back(new Toy(toy));
  toy->setPosition(-400, 100, 0);
  addInputListener(actors.back()); //lo añadimos como listener para que reciba los eventos de teclado
  AppObj::addAppListener(actors.back());
  colisionables.push_back({ actors.back(), mSM->getEntity("body") });     //guardamos la entity del cuerpo en el vector de colisionables

//----------------------------------CAMARA--------------------------------------

  mCamMgr = new OgreBites::CameraMan(mCamNode);
  addInputListener(mCamMgr);
  mCamMgr->setStyle(OgreBites::CS_ORBIT);  
  //mCamMgr->setTarget(mSinbadNode);  
  //mCamMgr->setYawPitchDist(Radian(0), Degree(30), 100);

  //------------------------------------------------------------------------
}

