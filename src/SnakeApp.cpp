#ifdef _DEBUG
#include <iostream>
#endif // _DEBUG

#include "Apple.h"
#include "SnakeApp.h"
#include "Snake.h"
#include "Wall.h"

using namespace irr;

/*
SnakeApp::SnakeApp()
{
    //ctor
}
*/

int SnakeApp::run(int, char**)
{
    // ask user for driver



	char i;
	#ifdef _DEBUG
	std::cout << "Please select the driver you want for this example:\n"\
	" (a) OpenGL 1.5\n (b) Direct3D 9.0c\n (c) Direct3D 8.1\n"\
	" (d) Burning's Software Renderer\n (e) Software Renderer\n"\
	" (f) NullDevice\n (otherKey) exit\n\n";
	std::cin >> i;
	#endif // _DEBUG
	#ifdef NDEBUG
	i = 'b';
	#endif // NDEBUG
	switch(i)
	{
		case 'a': driverType = video::EDT_OPENGL;   break;
		case 'b': driverType = video::EDT_DIRECT3D9;break;
		case 'c': driverType = video::EDT_DIRECT3D8;break;
		case 'd': driverType = video::EDT_BURNINGSVIDEO;break;
		case 'e': driverType = video::EDT_SOFTWARE; break;
		case 'f': driverType = video::EDT_NULL;     break;
		default: return 1;
	}

	// create device and exit if creation failed

	windowSize = core::dimension2d<u32>(640, 480);
	device = createDevice(driverType, windowSize, 16,
                          false, false, false, &keyReceiver);

	if (device == nullptr)
		return 2; // could not create selected driver.

	/*
	Get a pointer to the video driver and the SceneManager so that
	we do not always have to call irr::IrrlichtDevice::getVideoDriver() and
	irr::IrrlichtDevice::getSceneManager().
	*/
	video::IVideoDriver* driver = device->getVideoDriver();
	scene::ISceneManager* smgr = device->getSceneManager();

	/*
	To display the Quake 3 map, we first need to load it. Quake 3 maps
	are packed into .pk3 files which are nothing else than .zip files.
	So we add the .pk3 file to our irr::io::IFileSystem. After it was added,
	we are able to read from the files in that archive as if they are
	directly stored on the disk.
	*/
	//device->getFileSystem()->addFileArchive("../../media/map-20kdm2.pk3");

	/*
	Now we can load the mesh by calling
	irr::scene::ISceneManager::getMesh(). We get a pointer returned to an
	irr::scene::IAnimatedMesh. As you might know, Quake 3 maps are not
	really animated, they are only a huge chunk of static geometry with
	some materials attached. Hence the IAnimatedMesh consists of only one
	frame, so we get the "first frame" of the "animation", which is our
	quake level and create an Octree scene node with it, using
	irr::scene::ISceneManager::addOctreeSceneNode().
	The Octree optimizes the scene a little bit, trying to draw only geometry
	which is currently visible. An alternative to the Octree would be a
	irr::scene::IMeshSceneNode, which would always draw the complete
	geometry of the mesh, without optimization. Try it: Use
	irr::scene::ISceneManager::addMeshSceneNode() instead of
	addOctreeSceneNode() and compare the primitives drawn by the video
	driver. (There is a irr::video::IVideoDriver::getPrimitiveCountDrawn()
	method in the irr::video::IVideoDriver class). Note that this
	optimization with the Octree is only useful when drawing huge meshes
	consisting of lots of geometry.
	*/
	scene::IAnimatedMesh* mesh = nullptr; //smgr->getMesh("20kdm2.bsp");
	scene::ISceneNode* node = 0;

	if (mesh)
		node = smgr->addOctreeSceneNode(mesh->getMesh(0), 0, -1, 1024);
//		node = smgr->addMeshSceneNode(mesh->getMesh(0));

	/*
	Because the level was not modelled around the origin (0,0,0), we
	translate the whole level a little bit. This is done on
	irr::scene::ISceneNode level using the methods
	irr::scene::ISceneNode::setPosition() (in this case),
	irr::scene::ISceneNode::setRotation(), and
	irr::scene::ISceneNode::setScale().
	*/
	if (node)
		node->setPosition(core::vector3df(-1300,-144,-1249));

	/*
	Now we only need a camera to look at the Quake 3 map.
	We want to create a user controlled camera. There are some
	cameras available in the Irrlicht engine. For example the
	MayaCamera which can be controlled like the camera in Maya:
	Rotate with left mouse button pressed, Zoom with both buttons pressed,
	translate with right mouse button pressed. This could be created with
	irr::scene::ISceneManager::addCameraSceneNodeMaya(). But for this
	example, we want to create a camera which behaves like the ones in
	first person shooter games (FPS) and hence use
	irr::scene::ISceneManager::addCameraSceneNodeFPS().
	*/
	auto camera =
	(smgr->addCameraSceneNodeMaya(nullptr, -1500.f, 200.f, 1500.f, -1,
                                  playSize * 2.5f));
	if (! camera) return 3;
	camera->bindTargetAndRotation(true);

//	static_cast<scene::ISceneNodeAnimatorCameraMaya *>
//	(*camera->getAnimators().begin())->setDistance(300.f);
    #ifdef _DEBUG
    auto upVect = camera->getUpVector();
    std::cout << camera->getScale().Z << std::endl;
    std::cout << upVect.X << upVect.Y << upVect.Z << std::endl;
    #endif // _DEBUG
	/*
	The mouse cursor needs not be visible, so we hide it via the
	irr::IrrlichtDevice::ICursorControl.
	*/
	device->getCursorControl()->setVisible(false);



//   scene::ILightSceneNode *light = smgr->addLightSceneNode(0, core::vector3df(-40,80,0));
//   video::SLight *ldata = &light->getLightData();
//   ldata->AmbientColor = video::SColorf(1.f, 1.f, 1.f, 0.1f);
//   ldata->DiffuseColor = video::SColorf(1.f, 1.0f, 1.0f, 1.f);
//   ldata->SpecularColor = video::SColorf(1.f, 1.f, 0.f, 0.f);
   //ldata->Attenuation = core::vector3df(1,0,0);

    smgr->setAmbientLight(video::SColorf(1.f, 1.f, 1.f, 1.f));
//
//    //scene::IMeshSceneNode *cube = smgr->addCubeSceneNode(10.0f, 0, 1);
//{
//    CubicShape cube (smgr, video::SColor(255, 255, 0, 255), 10.0f, nullptr, 1, core::vector3df(50, 40, 50));
//}
//    CubicShape cube (smgr, video::SColor(255, 255, 0, 255), 10.0f, nullptr, 1, core::vector3df(50, 40, 50));
//
////    if (cube)
////    {
////        //cube->setMaterialTexture(0, driver->getTexture("../../media/wall.bmp"));
////        //cube->setMaterialFlag(video::EMF_LIGHTING, false);
////        cube->setPosition(core::vector3df(50, 40, 50));
////        cube->getMaterial(0).AmbientColor = video::SColor(255, 255, 0, 255);
//////        cube->getMaterial(0).DiffuseColor = video::SColor(255, 255, 255, 255);
//////        cube->getMaterial(0).SpecularColor = video::SColor(255, 255, 255, 255);
//////        cube->getMaterial(0).Shininess = 20.f;
////    }
//
//	#ifdef _DEBUG
//	if (cube) std::cout << cube->getReferenceCount() << std::endl;
//	#endif // _DEBUG
//
//	//smgr->getSceneNodeFromId(1)->drop();
//	//cube->remove(); //cube = nullptr;
//	//smgr->addToDeletionQueue(cube);
//	//cube->drop(); cube = nullptr;
//	//cube->drop();
//
//    #ifdef _DEBUG
//	//if (cube) std::cout << cube->getReferenceCount() << std::endl;
//	std::cout << __LINE__ << std::endl;
//	//std::cout << cube->getAnimators().begin()->getRefernceCount() << std::endl;
//	#endif // _DEBUG

    //auto light =
    smgr->addLightSceneNode(nullptr,
         core::vector3df(.550f * playSize, .530f * playSize, .510f * playSize),
         video::SColorf(.7f,.7f,.7f));
//    light->setLightType(video::ELT_DIRECTIONAL);
    Snake snake (smgr, keyReceiver, camera, playSize);
    Wall  wall  (smgr, playSize);
    Apple apple (smgr, snake);

    //  video::ITexture *texture = driver->getTexture("../../media/wall.bmp");
    //smgr->addSkyBoxSceneNode(texture, texture, texture, texture, texture, texture);
//    smgr->addWaterSurfaceSceneNode(smgr->getGeometryCreator()->createPlaneMesh(core::dimension2d< f32 >(10,40)), 3.f, 300.f, 10.f, nullptr, -1, core::vector3df(50.f, 40.f, 50.f));

//    scene::IMesh *planeMesh = smgr->getGeometryCreator()->
//        createPlaneMesh(core::dimension2d< f32 >(100,400), core::dimension2du(3, 2));
//	smgr->addOctreeSceneNode(planeMesh, cube.get());
//	planeMesh->drop(); planeMesh = nullptr;

//    CubicShape cube1 (smgr, video::SColor(255, 75, 75, 75), 100.0f, nullptr, 1, core::vector3df(50, 50, 50));
//    cube1->getMaterial(0).SpecularColor = video::SColor(0, 255, 255, 255);
//    cube1->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
    //cube1->getMaterial(0).SpecularColor = video::SColor(0, 255, 255, 255);
//    CubicShape cube2 (smgr, video::SColor(0, 25, 25, 255), 50.0f, nullptr, 1, core::vector3df(50, 40, 50));
//    cube2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	/*
	We have done everything, so lets draw it. We also write the current
	frames per second and the primitives drawn into the caption of the
	window. The test for irr::IrrlichtDevice::isWindowActive() is optional,
	but prevents the engine to grab the mouse cursor after task switching
	when other programs are active. The call to
	irr::IrrlichtDevice::yield() will avoid the busy loop to eat up all CPU
	cycles when the window is not active.
	*/
	int lastFPS = -1;
	bool is_pause = false;
	bool esc_pressed = false;
	bool is_changed = false;

	bool died = false;
	auto then = device->getTimer()->getTime();

	while(device->run())
	{
		if (device->isWindowActive())
		{
			if (!esc_pressed && keyReceiver.IsKeyDown(KEY_ESCAPE)) {
                is_pause = !is_pause; // pause
                if (is_pause) {
                    device->getTimer()->stop();
                    device->yield();
                } else
                    device->getTimer()->start();
			}
			esc_pressed = keyReceiver.IsKeyDown(KEY_ESCAPE);
			const auto now = device->getTimer()->getTime();
			#ifdef _DEBUG
//			std::cout << now << std::endl;
			#endif // _DEBUG
			const bool change = (now - then) >= key_delay;
            if (!is_pause && !is_changed &&
                change) {
                then = now;
                #ifdef _DEBUG
//                auto upVect = camera->getUpVector();
//                auto upTarget = camera->getTarget();
//                auto outVect = camera->getRotation().rotationToDirection();
//                std::cout << upVect.X << upVect.Y << upVect.Z << std::endl;
//                std::cout << upTarget.X << upTarget.Y << upTarget.Z << std::endl;
//                std::cout << outVect.X << outVect.Y << outVect.Z << std::endl;
//                std::cout << std::endl;
                //std::cout << now << std::endl;
                //std::cout << keyReceiver.IsKeyDown(KEY_KEY_E) << std::endl;
                #endif // _DEBUG
                snake.changeDirection();
//                if (snake.move(core::vector3df(-2,4,123))) {
                if (snake.move(apple.getApple()->getPosition())) {
                    score += score_incr;
//                    scoreBar.setString(std::to_string(score));
                    apple.reset();
                    score_incr = init_score_incr * snake.accelerationRate();
                    #ifdef _DEBUG
                    std::cout << "Score: " << score << std::endl;
                    #endif // _DEBUG
                }
                if ((died = snake.is_died())) {
                    //Running = false; // TODO: You died, If we go to menu, comment this line
                    died = true;
                    smgr->addTextSceneNode(device->getGUIEnvironment()->
                                           getBuiltInFont(), L"You died.");
                }
            }
            is_changed = change;

            driver->beginScene(true, true, video::SColor(255, 0, 0, 0));
			smgr->drawAll();
			driver->endScene();

			int fps = driver->getFPS();

			if (lastFPS != fps)
			{
				core::stringw str = L"3D Snake [";
				str += driver->getName();
				str += "] FPS:";
				str += fps;

				device->setWindowCaption(str.c_str());
				lastFPS = fps;
			}
			if (died) {
                #ifdef _DEBUG
                died = false;
                #endif // _DEBUG
                #ifdef NDEBUG
                device->sleep(3000);
                device->closeDevice();
                #endif // NDEBUG
			}
		}
		else {
			device->yield();
			#ifdef _DEBUG
			//std::cout << device->getTimer()->isStopped() << std::endl;
			#endif // _DEBUG
		}
	}

	/*
	In the end, delete the Irrlicht device.
	*/
	device->drop();
	device = nullptr;
	return 0;
}
