#include "ElementBuffer.h"

void ElementBuffer::Bind(void) {
    glGenBuffers(1, &m_ElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_Indices.size() * 
        sizeof(unsigned short), m_Indices.data(), GL_STATIC_DRAW);
}

void ElementBuffer::SetIndices(std::vector<GLushort> indices) {
    this->m_Indices = indices;
}

void ElementBuffer::Unbind(void) {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_ElementBuffer);
}

void ElementBuffer::Draw(void) {
    glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_Indices.size()), GL_UNSIGNED_SHORT, nullptr);
}
