// This file is a repurposed Tutorial file (Ogre3d wiki Intermediate Tutorial 1).
// There are some vestigial sections of code that broke the program when removed, though
// they don't look like they would serve any purpose. If there's time, I will try to remove
// what I can and compact the code to be more readable.
//		-Marc

#include "GameObject.h"

GameObject::GameObject(Ogre::SceneManager *mSceneMgr)
{
	mEntity = mSceneMgr->createEntity("Head", "ogrehead.mesh");
 
	// Create the scene node
	mNode = mSceneMgr->getRootSceneNode()->
		createChildSceneNode("HeadNode", Ogre::Vector3(0.0f, 0.0f, 0.0f));
	mNode->attachObject(mEntity);

	mNode->pitch( Ogre::Degree( -90 ) );

	// Set default values for variables
	mWalkSpeed = 140.0f;
	mDirection = Ogre::Vector3::ZERO;

	// Create objects so we can see movement
	Ogre::Entity *ent;
	Ogre::SceneNode *node;
 
	ent = mSceneMgr->createEntity("Knot1", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot1Node",
		Ogre::Vector3(500.0f, -10.0f,  400.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);
 
	ent = mSceneMgr->createEntity("Knot2", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot2Node",
		Ogre::Vector3(-500.0f, -10.0f, 400.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);
 
	ent = mSceneMgr->createEntity("Knot3", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot3Node",
		Ogre::Vector3(500.0f, -10.0f,  -400.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);
 
	ent = mSceneMgr->createEntity("Knot4", "knot.mesh");
	node = mSceneMgr->getRootSceneNode()->createChildSceneNode("Knot4Node",
		Ogre::Vector3(-500.0f, -10.0f, -400.0f));
	node->attachObject(ent);
	node->setScale(0.1f, 0.1f, 0.1f);
}

GameObject::~GameObject(void)
{
}

bool GameObject::nextLocation(void){

	if (mWalkList.empty())
             return false;

	mDestination = mWalkList.front();  // this gets the front of the deque
        mWalkList.pop_front();             // this removes the front of the deque
 
        mDirection = mDestination - mNode->getPosition();
        mDistance = mDirection.normalise();

		 Ogre::Vector3 src = mNode->getOrientation() * Ogre::Vector3::UNIT_X;
        if ((1.0f + src.dotProduct(mDirection)) < 0.0001f) 
        {
            //mNode->yaw(Ogre::Degree(180));
        }
        else
        {
            //Ogre::Quaternion quat = src.getRotationTo(mDirection);
            //mNode->rotate(quat);
        } // else

	return true;
}

void GameObject::frameRenderingQueued(const Ogre::FrameEvent &evt)
{
	if (mDirection == Ogre::Vector3::ZERO) 
        {
            if ( nextLocation() ) 
            {
                // blank
            }
        }
	else
         {
             Ogre::Real move = mWalkSpeed * evt.timeSinceLastFrame;
             mDistance -= move;

			 if (mDistance <= 0.0f)
             {
                 mNode->setPosition(mDestination);
                 mDirection = Ogre::Vector3::ZERO;
				 // Set animation based on if the robot has another point to walk to. 
                if ( ! nextLocation() )
                {
                    // blank
                } 
            }
			 else
             {
                 mNode->translate(mDirection * move);
             } // else
         } // if
}

void GameObject::setDirection(int dirIn)
{
	// if the int in is not a valid direction (0 - 3), it returns and does nothing.
	if ( ( ( dirIn < 0 ) || ( dirIn > 3 ) ) || ( dirIn == direction ) )
		return;
	
	direction = dirIn;
	clearWalklist();

	// Change next Walklist target
	if ( direction == 0 ){
		mWalkList.push_back(Ogre::Vector3( ( mNode->getPosition().x ), 0.0f,-400.0f ));
	} else if ( direction == 1 ){
		mWalkList.push_back(Ogre::Vector3( 500.0f, 0.0f, ( mNode->getPosition().z ) ));
	} else if ( direction == 2 ){
		mWalkList.push_back(Ogre::Vector3( ( mNode->getPosition().x ), 0.0f, 400.0f ));
	} else if ( direction == 3 ){
		mWalkList.push_back(Ogre::Vector3(-500.0f, 0.0f, ( mNode->getPosition().z ) ));
	}
	
	// Update location
	nextLocation();
}

void GameObject::clearWalklist(void)
{
	if ( mWalkList.empty() )
		return;

	mWalkList.pop_front();
	clearWalklist();
}