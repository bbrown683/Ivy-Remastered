#include "ElementBuffer.h"

void ElementBuffer::Bind(GLushort* indices) {
    glGenBuffers(1, &m_ElementBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_ElementBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(GLushort) * 3, &indices[0], GL_STATIC_DRAW);
}

void ElementBuffer::Unbind() {
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
    glDeleteBuffers(1, &m_ElementBuffer);
}

void ElementBuffer::Draw() {
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_SHORT, nullptr);
}
