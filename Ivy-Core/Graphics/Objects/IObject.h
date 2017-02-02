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

#ifndef IVY_IOBJECT_H
#define IVY_IOBJECT_H

#include <glm/glm.hpp>

#include "../../Symbols.h"

namespace Ivy {
    namespace Graphics {
        struct IVY_API IObject {
            virtual glm::vec3 GetPosition(void) = 0;
            virtual glm::vec3 GetOrientation(void) = 0;
            virtual glm::vec3 GetScale(void) = 0;
            virtual float GetRotation(void) = 0;

            virtual void SetPosition(glm::vec3 position) = 0;
            virtual void SetOrientation(glm::vec3 orientation) = 0;
            virtual void SetScale(glm::vec3 scale) = 0;
            virtual void SetRotation(float rotation) = 0;
        };
    }
}

#endif // IVY_IOBJECT_H