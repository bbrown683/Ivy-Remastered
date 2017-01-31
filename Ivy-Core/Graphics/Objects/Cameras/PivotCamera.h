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

#include "../IObject.h"
#include "ICamera.h"

namespace Ivy {
    namespace Graphics {
        class PivotCamera : public ICamera {
            virtual bool Create(void) override;
            virtual glm::vec3 GetCameraPosition(void) override;
            virtual void SetCameraPosition(glm::vec3 position) override;
            virtual glm::vec3 GetTargetPosition(void) override;
            virtual void SetTargetPosition(glm::vec3 position) override;
            virtual glm::vec3 GetCameraOrientation(void) override;
            virtual void SetCameraOrientation(glm::vec3 orientation) override;
        };
    }
}