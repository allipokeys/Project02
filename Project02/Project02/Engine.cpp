#include "Engine.h"
 
//-------------------------------------------------------------------------------------
Engine::Engine(void)
{
}
//-------------------------------------------------------------------------------------
Engine::~Engine(void)
{
}
 
//-------------------------------------------------------------------------------------
void Engine::createScene(void)
{
	// Set the default lighting.
	mSceneMgr->setAmbientLight(Ogre::ColourValue(1.0f, 1.0f, 1.0f));

	// Create the entity
	TestHead = new GameObject( mSceneMgr );

	// Set the camera to look at our handiwork
	mCamera->setPosition(0.0f, 1000.0f, 0.0f);
	mCamera->pitch(Ogre::Degree(-90.0f));
	//mCamera->yaw(Ogre::Degree(-15.0f));
}

void Engine::createFrameListener(void){
	BaseApplication::createFrameListener();
}
 
bool Engine::frameRenderingQueued(const Ogre::FrameEvent &evt){

	TestHead->frameRenderingQueued(evt);

	return BaseApplication::frameRenderingQueued(evt);
}

bool Engine::keyPressed( const OIS::KeyEvent &arg )
{
	if (arg.key == OIS::KC_UP)
		TestHead->setDirection( 0 );
	else if (arg.key == OIS::KC_RIGHT)
		TestHead->setDirection( 1 );
	else if (arg.key == OIS::KC_DOWN)
		TestHead->setDirection( 2 );
	else if (arg.key == OIS::KC_LEFT)
		TestHead->setDirection( 3 );

	return BaseApplication::keyPressed( arg );
}
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif
 
#ifdef __cplusplus
extern "C" {
#endif
 
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
    INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
#else
    int main(int argc, char *argv[])
#endif
    {
        // Create application object
        Engine app;
 
        try {
            app.go();
        } catch( Ogre::Exception& e ) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
            MessageBox( NULL, e.getFullDescription().c_str(), "An exception has occured!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
            std::cerr << "An exception has occured: " <<
                e.getFullDescription().c_str() << std::endl;
#endif
        }
 
        return 0;
    }
 
#ifdef __cplusplus
}
#endif

