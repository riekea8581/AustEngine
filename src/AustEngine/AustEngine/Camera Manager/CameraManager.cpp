#include "CameraManager.h"
#include "..\AustEngine.h"
#include "..\EngineAttorney.h"

CameraManager::CameraManager()
{
	defaultCamera = new Camera(Camera::Type::PERSPECTIVE_3D);
	defaultCamera->setViewport(0, 0, AustEngine::GetWindowWidth(), AustEngine::GetWindowHeight());
	defaultCamera->setPerspective(35.0f, float(AustEngine::GetWindowWidth()) / float(AustEngine::GetWindowHeight()), 1.0f, 5000.0f);

	Vect up3DCam(0.0f, 1.0f, 0.0f);
	Vect pos3DCam(150.0f, 150.0f, 150.0f);
	Vect lookAt3DCam(0.0f, 0.0f, 0.0f);
	defaultCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
	defaultCamera->updateCamera();  // Note: if the camera moves/changes, we need to call update again
	currentCamera = defaultCamera;

	orthCamera = new Camera(Camera::Type::ORTHOGRAPHIC_2D);
	orthCamera->setViewport(0, 0, EngineAttorney::AustWindowSize::GetWidth(), EngineAttorney::AustWindowSize::GetHeight());
	orthCamera->setOrthographic(-0.5f*EngineAttorney::AustWindowSize::GetWidth(), 0.5f*EngineAttorney::AustWindowSize::GetWidth(),
		-0.5f*EngineAttorney::AustWindowSize::GetHeight(), 0.5f*EngineAttorney::AustWindowSize::GetHeight(),
		1.0f, 1000.0f);

	// Orient Camera
	Vect up2DCam(0.0f, 1.0f, 0.0f);
	Vect pos2DCam(0.0f, 0.0f, 0.0f);
	Vect lookAt2DCam(0.0f, 0.0f, -1.0f);
	orthCamera->setOrientAndPosition(up2DCam, lookAt2DCam, pos2DCam);

	orthCamera->updateCamera();
}

CameraManager::~CameraManager()
{
	delete defaultCamera;
	delete orthCamera;
}