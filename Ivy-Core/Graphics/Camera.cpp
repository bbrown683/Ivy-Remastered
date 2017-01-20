#include "Camera.h"

void Ivy::Graphics::Camera::Create() {
    m_UniformBuffer.GetViewLocation();
    m_UniformBuffer.GetProjectionLocation();
    
    m_UniformBuffer.SetViewMatrix(glm::lookAt(m_Position, m_Target, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_UniformBuffer.SetProjectionMatrix(glm::perspective(m_Fov, static_cast<float>(m_Width) / m_Height, 0.1f, 1000.0f));
}

void Ivy::Graphics::Camera::SetCameraPosition(glm::vec3 position) {
    m_Position = position;
    m_UniformBuffer.SetViewMatrix(glm::lookAt(m_Position, m_Target, glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Ivy::Graphics::Camera::SetTargetPosition(glm::vec3 position) {
    m_Target = position;
    m_UniformBuffer.SetViewMatrix(glm::lookAt(m_Position, m_Target, glm::vec3(0.0f, 1.0f, 0.0f)));
}
