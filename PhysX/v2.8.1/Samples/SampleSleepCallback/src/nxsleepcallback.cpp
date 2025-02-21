/**
 * SampleSleepCallback, a simple sample demonstrating the usage of callback for
 * sleeping actors
 */

#include <stdio.h>
#include <GL/glut.h>

#include "NxPhysics.h"
#include "ErrorStream.h"
#include "PerfRenderer.h"
#include "Utilities.h"
#include "SamplesVRDSettings.h"

static const int		gSleepFlag =  (1<<31);

// Physics
static NxPhysicsSDK*	gPhysicsSDK = NULL;
static NxScene*			gScene = NULL;
static PerfRenderer    gPerfRenderer;

// Rendering
static NxVec3	gEye(50.0f, 50.0f, 50.0f);
static NxVec3	gDir(-0.6f,-0.2f,-0.7f);
static NxVec3	gViewY;
static int		gMouseX = 0;
static int		gMouseY = 0;


struct MyCallback : public NxUserNotify
{
	virtual bool onJointBreak(NxReal breakingImpulse, NxJoint & brokenJoint){return true;}
	virtual void onSleep(NxActor **actors, NxU32 count)
	{
		NX_ASSERT(count > 0);
		while (count--)
		{
			NxActor *thisActor = *actors;
			//Tag the actor as sleeping
			size_t currentFlag = (size_t)thisActor->userData;
			currentFlag |= gSleepFlag;
			thisActor->userData = (void*)currentFlag;

			actors++;
		}
	}

	virtual void onWake(NxActor **actors, NxU32 count)
	{
		NX_ASSERT(count > 0);
		while (count--)
		{
			NxActor *thisActor = *actors;
			//Tag the actor as non-sleeping
			size_t currentFlag = (size_t)thisActor->userData;
			currentFlag &= ~gSleepFlag;
			thisActor->userData = (void*)currentFlag;

			actors++;
		}
	}
} sleepCallback;

static bool InitNx()
{
	// Initialize PhysicsSDK
	NxPhysicsSDKDesc desc;
	NxSDKCreateError errorCode = NXCE_NO_ERROR;
	gPhysicsSDK = NxCreatePhysicsSDK(NX_PHYSICS_SDK_VERSION, NULL, new ErrorStream(), desc, &errorCode);
	if(gPhysicsSDK == NULL) 
	{
		printf("\nSDK create error (%d - %s).\nUnable to initialize the PhysX SDK, exiting the sample.\n\n", errorCode, getNxSDKCreateError(errorCode));
		return false;
	}
#if SAMPLES_USE_VRD
	// The settings for the VRD host and port are found in SampleCommonCode/SamplesVRDSettings.h
	if (gPhysicsSDK->getFoundationSDK().getRemoteDebugger() && !gPhysicsSDK->getFoundationSDK().getRemoteDebugger()->isConnected())
		gPhysicsSDK->getFoundationSDK().getRemoteDebugger()->connect(SAMPLES_VRD_HOST, SAMPLES_VRD_PORT, SAMPLES_VRD_EVENTMASK);
#endif

	gPhysicsSDK->setParameter(NX_SKIN_WIDTH, 0.05);

	// Create a scene
	NxSceneDesc sceneDesc;
	sceneDesc.gravity				= NxVec3(0.0f, -9.81f, 0.0f);
	sceneDesc.userNotify			= &sleepCallback;
	gScene = gPhysicsSDK->createScene(sceneDesc);
	if(gScene == NULL) 
	{
		printf("\nError: Unable to create a PhysX scene, exiting the sample.\n\n");
		return false;
	}

	// Set default material
	NxMaterial* defaultMaterial = gScene->getMaterialFromIndex(0);
	defaultMaterial->setRestitution(0.0f);
	defaultMaterial->setStaticFriction(0.5f);
	defaultMaterial->setDynamicFriction(0.5f);

	// Create ground plane
	NxPlaneShapeDesc planeDesc;
	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&planeDesc);
	gScene->createActor(actorDesc);

	return true;
}

static void ReleaseNx()
{
	if(gPhysicsSDK != NULL)
	{
		if(gScene != NULL) gPhysicsSDK->releaseScene(*gScene);
		gScene = NULL;
		NxReleasePhysicsSDK(gPhysicsSDK);
		gPhysicsSDK = NULL;
	}
}

static void CreateCube(const NxVec3& pos, int size=2, const NxVec3* initialVelocity=NULL)
{
	if(gScene == NULL) return;	

	// Create body
	NxBodyDesc bodyDesc;
	bodyDesc.angularDamping	= 0.5f;
	if(initialVelocity) bodyDesc.linearVelocity = *initialVelocity;

	NxBoxShapeDesc boxDesc;
	boxDesc.dimensions = NxVec3((float)size, (float)size, (float)size);

	NxActorDesc actorDesc;
	actorDesc.shapes.pushBack(&boxDesc);
	actorDesc.body			= &bodyDesc;
	actorDesc.density		= 10.0f;
	actorDesc.globalPose.t  = pos;
	gScene->createActor(actorDesc)->userData = (void*)size_t(size);
	//printf("Total: %d actors\n", gScene->getNbActors());
}

static void CreateCubeFromEye(int size)
{
	NxVec3 t = gEye;
	NxVec3 vel = gDir;
	vel.normalize();
	vel*=200.0f;
	CreateCube(t, size, &vel);
}

static void CreateStack(int size)
{
	const float cubeSize = 2.0f;
	const float spacing = 0.0001f;
	NxVec3 pos(0.0f, cubeSize, 0.0f);
	float offset = -size * (cubeSize * 2.0f + spacing) * 0.5f;
	while(size)
	{
		for(int i=0;i<size;i++)
		{
			pos.x = offset + (float)i * (cubeSize * 2.0f + spacing);
			CreateCube(pos, (int)cubeSize);
		}

		offset += cubeSize;
		pos.y += (cubeSize * 2.0f + spacing);
		size--;
	}
}

static void CreateTower(int size)
{
	const float cubeSize = 2.0f;
	const float spacing = 0.01f;
	NxVec3 pos(0.0f, cubeSize, 0.0f);
	while(size)
	{
		CreateCube(pos, (int)cubeSize);
		pos.y += (cubeSize * 2.0f + spacing);
		size--;
	}
}

static void KeyboardCallback(unsigned char key, int x, int y)
{
	switch(key)
	{
		case 27:	exit(0); break;
		case '0':	gPerfRenderer.toggleEnable(); break;
		case ' ':	CreateCube(NxVec3(0.0f, 20.0f, 0.0f),1); break;
		case 's':	CreateStack(10); break;
		case 'b':	CreateStack(30); break;
		case 't':	CreateTower(30); break;
		case 'w':	CreateCubeFromEye(8); break;
		case 'q':
			{
				NxActor** actors = gScene->getActors();
				if(gScene->getNbActors() > 1){
					gScene->releaseActor(*actors[gScene->getNbActors()-1]);
				}
			}
			break;		
		case GLUT_KEY_UP:	case '8':	gEye += gDir*2.0f; break;
		case GLUT_KEY_DOWN: case '2':	gEye -= gDir*2.0f; break;
		case GLUT_KEY_LEFT:	case '4':	gEye -= gViewY*2.0f; break;
		case GLUT_KEY_RIGHT: case '6':	gEye += gViewY*2.0f; break;
	}
}

static void ArrowKeyCallback(int key, int x, int y)
{
	KeyboardCallback(key,x,y);
}

static void MouseCallback(int button, int state, int x, int y)
{
	gMouseX = x;
	gMouseY = y;
}

static void MotionCallback(int x, int y)
{
	int dx = gMouseX - x;
	int dy = gMouseY - y;
	
	gDir.normalize();
	gViewY.cross(gDir, NxVec3(0,1,0));

	NxQuat qx(NxPiF32 * dx * 20/ 180.0f, NxVec3(0,1,0));
	qx.rotate(gDir);
	NxQuat qy(NxPiF32 * dy * 20/ 180.0f, gViewY);
	qy.rotate(gDir);

	gMouseX = x;
	gMouseY = y;
}

static void RenderCallback()
{
	if(gScene == NULL) return;
	
	// Start simulation (non blocking)
	gScene->simulate(1.0f/60.0f);

	// Clear buffers
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);

	// Setup projection matrix
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0f, (float)glutGet(GLUT_WINDOW_WIDTH)/(float)glutGet(GLUT_WINDOW_HEIGHT), 1.0f, 10000.0f);

	// Setup modelview matrix
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	gluLookAt(gEye.x, gEye.y, gEye.z, gEye.x + gDir.x, gEye.y + gDir.y, gEye.z + gDir.z, 0.0f, 1.0f, 0.0f);

	// Render all actors
	int nbActors = gScene->getNbActors();
	NxActor** actors = gScene->getActors();
	while(nbActors--)
	{
		NxActor* actor = *actors++;
		if(!actor->userData) continue;

		// Get some data
		NxU32 boxSize = (size_t)actor->userData & ~gSleepFlag;
		bool isSleeping = ((size_t)actor->userData & gSleepFlag) != 0;

		// Render actor
		glPushMatrix();
		float glMat[16];
		actor->getGlobalPose().getColumnMajor44(glMat);
		glMultMatrixf(glMat);
		
		if (isSleeping)
			glColor4f(1.0f, 0.2f, 0.2f, 1.0f);
		else
			glColor4f(0.2f, 1.0f, 0.2f, 1.0f);

		glutSolidCube(float(boxSize)*2.0f);
		glPopMatrix();

		// Render shadow
		glPushMatrix();
		const static float shadowMat[]={ 1,0,0,0, 0,0,0,0, 0,0,1,0, 0,0,0,1 };
		glMultMatrixf(shadowMat);
		glMultMatrixf(glMat);
		glDisable(GL_LIGHTING);
		glColor4f(0.1f, 0.2f, 0.3f, 1.0f);
		glutSolidCube(float(boxSize)*2.0f);
		glEnable(GL_LIGHTING);
		glPopMatrix();
	}

	// Fetch simulation results
	gScene->flushStream();
	gScene->fetchResults(NX_RIGID_BODY_FINISHED, true);
	
	// Print profile results (if enabled)
	gPerfRenderer.render(gScene->readProfileData(true), glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));

	glutSwapBuffers();
}

static void ReshapeCallback(int width, int height)
{
	glViewport(0, 0, width, height);
}

static void IdleCallback()
{
	glutPostRedisplay();
}

int main(int argc, char** argv)
{
	// Initialize glut
	printf("Use the arrow keys or 2, 4, 6 and 8 to move the camera.\n");
	printf("Use the mouse to rotate the camera.\n");
	printf("Press the keys w, t, s, b and space to create various things.\n");
	printf("Press q to destroy the last thing created.\n");
	printf("Press 0 to toggle the frame rate display.\n");
	glutInit(&argc, argv);
	glutInitWindowSize(512, 512);
	glutInitDisplayMode(GLUT_RGB|GLUT_DOUBLE|GLUT_DEPTH);
	int mainHandle = glutCreateWindow("SampleSleepCallback");
	glutSetWindow(mainHandle);
	glutDisplayFunc(RenderCallback);
	glutReshapeFunc(ReshapeCallback);
	glutIdleFunc(IdleCallback);
	glutKeyboardFunc(KeyboardCallback);
	glutSpecialFunc(ArrowKeyCallback);
	glutMouseFunc(MouseCallback);
	glutMotionFunc(MotionCallback);
	MotionCallback(0,0);
	atexit(ReleaseNx);

	// Setup default render states
	glClearColor(0.3f, 0.4f, 0.5f, 1.0);
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_COLOR_MATERIAL);

	// Setup lighting
	glEnable(GL_LIGHTING);
	float ambientColor[]	= { 0.0f, 0.1f, 0.2f, 0.0f };
	float diffuseColor[]	= { 1.0f, 1.0f, 1.0f, 0.0f };		
	float specularColor[]	= { 0.0f, 0.0f, 0.0f, 0.0f };		
	float position[]		= { 100.0f, 100.0f, 400.0f, 1.0f };		
	glLightfv(GL_LIGHT0, GL_AMBIENT, ambientColor);
	glLightfv(GL_LIGHT0, GL_DIFFUSE, diffuseColor);
	glLightfv(GL_LIGHT0, GL_SPECULAR, specularColor);
	glLightfv(GL_LIGHT0, GL_POSITION, position);
	glEnable(GL_LIGHT0);

	// Initialize physics scene and start the application main loop if scene was created
	if (InitNx()) 
		glutMainLoop();

	return 0;
}
