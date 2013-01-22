#ifndef __Engine_h_
#define __Engine_h_
 
#include "BaseApplication.h"
#include "GameObject.h"
#include <deque>
 
class Engine : public BaseApplication
{
public:
    Engine(void);
    virtual ~Engine(void);
 
protected:

	virtual void createScene(void);
	virtual void createFrameListener(void);
	virtual bool frameRenderingQueued(const Ogre::FrameEvent &evt);
	virtual bool keyPressed( const OIS::KeyEvent &arg );

	GameObject *TestHead;

};
 
#endif // #ifndef __Engine_h_

