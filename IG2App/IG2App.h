#ifndef __IG2App_H__
#define __IG2App_H__

#include "IG2ApplicationContext.h"
#include <OgreSceneManager.h>
#include <OgreCameraMan.h>
#include <OgreCompositorManager.h>
#include <OgreSceneNode.h>
#include <OgreTrays.h>
#include "AppObj.h"
#include <vector>
#include "Bomb.h"

using namespace Ogre;

class IG2App : public  OgreBites::IG2ApplicationContext, OgreBites::InputListener 
{
public:
  explicit IG2App() : IG2ApplicationContext("IG2App") { };  // new -> setup()  
  virtual ~IG2App() { };   // delete -> shutdown()  
 
protected:
  virtual void setup();
  virtual void shutdown();
  virtual void setupScene();

  virtual bool keyPressed(const OgreBites::KeyboardEvent& evt);  // InputListener
  virtual void frameRendered(const Ogre::FrameEvent& evt);
  void checkCollisions();

  void rotateGrid();
   
  //nodos del arbol de recursos
  SceneManager* mSM = nullptr;
  OgreBites::TrayManager* mTrayMgr = nullptr;    
  SceneNode* mLightNode = nullptr;
  SceneNode* mCamNode = nullptr;
  SceneNode* mSinbadNode = nullptr;
  SceneNode* mGridNode = nullptr;
  SceneNode* toy = nullptr;
  SceneNode* bomba = nullptr;
  OgreBites::CameraMan* mCamMgr = nullptr;

  std::vector<pair<AppObj*, Entity*>> colisionables;

  bool flag = false;

  std::vector<AppObj*> actors;
};

#endif
