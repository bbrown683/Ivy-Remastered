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

#include <assimp/material.h>

#include "ITexture.h"
#include "../Shaders/ShaderProgram.h"

// include after to avoid conflicts.
#include <FreeImage.h>

namespace Ivy {
    namespace Graphics {
        class IVY_API Texture2D : public ITexture {
        public:
            Texture2D(ShaderProgram* program, std::string filePath, GLuint textureSlot);

            virtual bool Create() override;
            virtual void MakeActive() override;
            virtual void MakeInactive() override;

            virtual GLuint GetTextureID() override;
            virtual GLuint GetSamplerLocation() override;
            virtual GLuint GetTextureWidth() override;
            virtual GLuint GetTextureHeight() override;
            virtual GLuint GetTexturePitch() override;

        private:

            ShaderProgram* m_Program;
            std::string m_FilePath;
            GLuint m_TextureSlot;

            GLuint m_TextureID;
            GLuint m_SamplerLocation;
            GLuint m_Width;
            GLuint m_Height;
            GLuint m_Pitch;
            GLubyte* m_Bitmap;
        };
    }
}

#endif // IVY_TEXTURE2D_H
