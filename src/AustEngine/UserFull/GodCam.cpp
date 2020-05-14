#include "GodCam.h"
#include "Tank.h"

GodCam::GodCam()
{
	petCamera = getCamera();

	petCamera->getUp(up3DCam);
	petCamera->getPos(pos3DCam);
	petCamera->getLookAt(lookAt3DCam);

	Updatable::SubmitSceneRegistration();
}

void GodCam::Update()
{
	// Camera translation movement
	// Fwd/Back
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_UP))
	{
		petCamera->getUp(up3DCam);
		petCamera->getPos(pos3DCam);
		petCamera->getLookAt(lookAt3DCam);
		pos3DCam += Vect(0.0f, 0.0f, speed) * Matrix(ROT_Y, petTank->getRot() - PI / 2);
		lookAt3DCam += Vect(0.0f, 0.0f, speed) * Matrix(ROT_Y, petTank->getRot() - PI / 2);
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_DOWN))
	{
		petCamera->getUp(up3DCam);
		petCamera->getPos(pos3DCam);
		petCamera->getLookAt(lookAt3DCam);
		pos3DCam -= Vect(0.0f, 0.0f, speed) * Matrix(ROT_Y, petTank->getRot() - PI / 2);
		lookAt3DCam -= Vect(0.0f, 0.0f, speed) * Matrix(ROT_Y, petTank->getRot() - PI / 2);
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
	//Left/Right
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_LEFT))
	{
		petCamera->getUp(up3DCam);
		petCamera->getPos(pos3DCam);
		petCamera->getLookAt(lookAt3DCam);
		pos3DCam += Vect(speed, 0.0f, 0.0f) * Matrix(ROT_Y, petTank->getRot() - PI / 2);
		lookAt3DCam += Vect(speed, 0.0f, 0.0f) * Matrix(ROT_Y, petTank->getRot() - PI / 2);
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_ARROW_RIGHT))
	{
		petCamera->getUp(up3DCam);
		petCamera->getPos(pos3DCam);
		petCamera->getLookAt(lookAt3DCam);
		pos3DCam -= Vect(speed, 0.0f, 0.0f) * Matrix(ROT_Y, petTank->getRot() - PI / 2);
		lookAt3DCam -= Vect(speed, 0.0f, 0.0f) * Matrix(ROT_Y, petTank->getRot() - PI / 2);
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
	//Up/Down
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_PAGE_UP))
	{
		petCamera->getUp(up3DCam);
		petCamera->getPos(pos3DCam);
		petCamera->getLookAt(lookAt3DCam);
		pos3DCam += Vect(0.0f, speed, 0.0f);
		lookAt3DCam += Vect(0.0f, speed, 0.0f);
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_PAGE_DOWN))
	{
		petCamera->getUp(up3DCam);
		petCamera->getPos(pos3DCam);
		petCamera->getLookAt(lookAt3DCam);
		pos3DCam -= Vect(0.0f, speed, 0.0f);
		lookAt3DCam -= Vect(0.0f, speed, 0.0f);
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}

	// Camera strafe movement
	// Left/Right
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_KP_4))
	{
		petCamera->getUp(up3DCam);
		petCamera->getPos(pos3DCam);
		petCamera->getLookAt(lookAt3DCam);
		pos3DCam -= lookAt3DCam;
		up3DCam *= Matrix(ROT_Y, -rotSpeed);
		pos3DCam *= Matrix(ROT_Y, -rotSpeed);
		pos3DCam += lookAt3DCam;
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_KP_6))
	{
		petCamera->getUp(up3DCam);
		petCamera->getPos(pos3DCam);
		petCamera->getLookAt(lookAt3DCam);
		pos3DCam -= lookAt3DCam;
		up3DCam *= Matrix(ROT_Y, rotSpeed);
		pos3DCam *= Matrix(ROT_Y, rotSpeed);
		pos3DCam += lookAt3DCam;
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
	// Up/Down
	if (Keyboard::GetKeyState(AZUL_KEY::KEY_KP_8))
	{
		Vect right;
		petCamera->getUp(up3DCam);
		petCamera->getRight(right);
		petCamera->getPos(pos3DCam);
		petCamera->getLookAt(lookAt3DCam);
		pos3DCam -= lookAt3DCam;
		up3DCam *= Matrix(ROT_AXIS_ANGLE, right, -rotSpeed);
		pos3DCam *= Matrix(ROT_AXIS_ANGLE, right, -rotSpeed);
		pos3DCam += lookAt3DCam;
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
	else if (Keyboard::GetKeyState(AZUL_KEY::KEY_KP_2))
	{
		Vect right;
		petCamera->getUp(up3DCam);
		petCamera->getRight(right);
		petCamera->getPos(pos3DCam);
		petCamera->getLookAt(lookAt3DCam);
		pos3DCam -= lookAt3DCam;
		up3DCam *= Matrix(ROT_AXIS_ANGLE, right, rotSpeed);
		pos3DCam *= Matrix(ROT_AXIS_ANGLE, right, rotSpeed);
		pos3DCam += lookAt3DCam;
		petCamera->setOrientAndPosition(up3DCam, lookAt3DCam, pos3DCam);
		petCamera->updateCamera();
	}
}