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

#ifndef IVY_TEXTURE2D_H
#define IVY_TEXTURE2D_H

#include "ITexture.h"
#include "../Program.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API Texture2D : public ITexture {
        public:
            Texture2D(Program* program, std::string* textures);

            bool Create() override;
            void MakeActive() override;
            void MakeInactive() override;

            GLuint GetSamplerID() override;
            GLuint GetTextureWidth() override;
            GLuint GetTextureHeight() override;
            GLuint GetTexturePitch() override;

        private:

            Program* m_Program;
            std::string* m_Textures;
        };
    }
}

#endif // IVY_TEXTURE2D_H
