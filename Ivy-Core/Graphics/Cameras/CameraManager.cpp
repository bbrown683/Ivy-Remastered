#include "CameraManager.h"

void Ivy::Graphics::CameraManager::PushCamera(unsigned int layerID, ICamera* camera) {
    m_Cameras.push(std::pair<unsigned int, ICamera*>(layerID, camera));
}

void Ivy::Graphics::CameraManager::PopCamera() {
    m_Cameras.pop();
}
