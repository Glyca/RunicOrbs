#include "Me.h"

Me::Me()
{
	// Configuration de la caméra
	// Now set up our max values for the camera
	m_camera.m_MaxForwardVelocity = 3.0f;
	m_camera.m_MaxPitchRate = 5.0f;
	m_camera.m_MaxHeadingRate = 5.0f;
	m_camera.m_PitchDegrees = 0.0f;
	m_camera.m_HeadingDegrees = -45.0f;
	qDebug("Me created");
}
