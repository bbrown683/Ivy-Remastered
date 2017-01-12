#include "Camera.h"

void Ivy::Graphics::Camera::Create() {
    m_UniformBuffer.GetViewLocation();
    m_UniformBuffer.GetProjectionLocation();
    
    m_UniformBuffer.SetViewMatrix(glm::lookAt(m_Position, m_Target, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_UniformBuffer.SetProjectionMatrix(glm::perspective(glm::radians(45.0f), 1080.0f / 720.0f, 0.1f, 100.0f));
}

void Ivy::Graphics::Camera::SetCameraPosition(glm::vec3 position) {
    m_Position = position;
    m_UniformBuffer.SetViewMatrix(glm::lookAt(m_Position, m_Target, glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Ivy::Graphics::Camera::SetTargetPosition(glm::vec3 position) {
    m_Target = position;
    m_UniformBuffer.SetViewMatrix(glm::lookAt(m_Position, m_Target, glm::vec3(0.0f, 1.0f, 0.0f)));
}
