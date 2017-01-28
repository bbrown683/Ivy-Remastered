#ifndef IVY_CUBEMAP_H
#define IVY_CUBEMAP_H

#include "ITexture.h"

namespace Ivy {
    namespace Graphics {
        class IVY_API CubeMap : public ITexture {
        public:
            CubeMap(std::string* textures);

            bool Create() override;
            void MakeActive() override;
            void MakeInactive() override;

            GLuint GetSamplerID() override;
            GLuint GetTextureWidth() override;
            GLuint GetTextureHeight() override;
            GLuint GetTexturePitch() override;
        
        private:
            std::string* m_Textures;
        };
    }
}

#endif // IVY_CUBEMAP_H