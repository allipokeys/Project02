
#ifndef __GameObject_h_
#define __GameObject_h_

#include <OgreCamera.h>
#include <OgreEntity.h>
#include <OgreLogManager.h>
#include <OgreRoot.h>
#include <OgreViewport.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <OgreConfigFile.h>

#include <OISEvents.h>
#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <SdkTrays.h>
#include <SdkCameraMan.h>

class GameObject
{
public:
	GameObject(Ogre::SceneManager *);
	virtual ~GameObject(void);

	virtual void frameRenderingQueued(const Ogre::FrameEvent &evt);
	virtual bool nextLocation(void);
	virtual void setDirection(int);

protected:

	void clearWalklist(void);

	int direction; // 0 up, 1 right, 2 down, 3 left
 
     Ogre::Real mDistance;                  // The distance the object has left to travel
     Ogre::Vector3 mDirection;              // The direction the object is moving
     Ogre::Vector3 mDestination;            // The destination the object is moving towards
 
     Ogre::Entity *mEntity;                 // The Entity we are animating
     Ogre::SceneNode *mNode;                // The SceneNode that the Entity is attached to
     std::deque<Ogre::Vector3> mWalkList;   // The list of points we are walking to
 
     Ogre::Real mWalkSpeed;                 // The speed at which the object is moving
};

#endif