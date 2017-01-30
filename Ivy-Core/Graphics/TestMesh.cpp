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

#include "TestMesh.h"

void Ivy::Graphics::TestMesh::Create(void) {
    m_VertexBuffer.SetData(m_Vertices);
    m_ElementBuffer.SetData(m_Indices);

    m_VertexBuffer.Create();
    m_ElementBuffer.Create();

    m_UniformBuffer.GetModelLocation();

    if (m_Textures.size() > 0)
        m_Textures[0].CreateFromFile(m_Program);
}

void Ivy::Graphics::TestMesh::Draw(void) {
    m_Program->MakeActive();

    m_VertexBuffer.Bind();
    m_ElementBuffer.Bind();
    m_UniformBuffer.SetModelMatrix(m_Translation * m_Rotation * m_Scale);

    if (m_Textures.size() > 0)
        m_Textures[0].MakeActive();

    m_ElementBuffer.Draw();

    m_VertexBuffer.Unbind();
    m_ElementBuffer.Unbind();

    m_Program->MakeInactive();
}

void Ivy::Graphics::TestMesh::SetPosition(glm::vec3 position) {
    m_Translation = glm::translate(m_Translation, position);
}

void Ivy::Graphics::TestMesh::SetRotation(glm::vec3 rotation) {
    m_Rotation = glm::rotate(m_Rotation, 0.025f, rotation);
}

void Ivy::Graphics::TestMesh::SetScale(glm::vec3 scale) {
    m_Scale = glm::scale(m_Scale, scale);
}