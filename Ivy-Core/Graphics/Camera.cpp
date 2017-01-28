/*
MIT License

Copyright (c) 2017 Ben Brown

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
*/

#include "Camera.h"

void Ivy::Graphics::Camera::Create() {
    m_UniformBuffer.GetViewLocation();
    m_UniformBuffer.GetProjectionLocation();
    
    m_UniformBuffer.SetViewMatrix(glm::lookAt(m_Position, m_Target, glm::vec3(0.0f, 1.0f, 0.0f)));
    m_UniformBuffer.SetProjectionMatrix(glm::perspective(m_FieldOfView, static_cast<float>(m_Width) / m_Height, m_ClippingPlaneNear, m_ClippingPlaneFar));
}

void Ivy::Graphics::Camera::SetCameraPosition(glm::vec3 position) {
    m_Position = position;
    m_UniformBuffer.SetViewMatrix(glm::lookAt(m_Position, m_Target, glm::vec3(0.0f, 1.0f, 0.0f)));
}

void Ivy::Graphics::Camera::SetTargetPosition(glm::vec3 position) {
    m_Target = position;
    m_UniformBuffer.SetViewMatrix(glm::lookAt(m_Position, m_Target, glm::vec3(0.0f, 1.0f, 0.0f)));
}
