#ifndef IVY_ITEXTURE_H
#define IVY_ITEXTURE_H

#include "Renderer.h"

namespace Ivy {
    struct ITexture {
        virtual bool Create() = 0;
        virtual void MakeActive() = 0;
        virtual void MakeInactive() = 0;

        virtual GLuint GetSamplerID() = 0;
        virtual GLuint GetTextureWidth() = 0;
        virtual GLuint GetTextureHeight() = 0;
        virtual GLuint GetTexturePitch() = 0;
    };
}

#endif