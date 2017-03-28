#include "Renderer.h"
#include "Sampler.h"

namespace Ivy {
namespace Graphics {
class Texture {
 public:
  Texture(std::string source, GLenum format, GLenum internal_format, GLenum target);

 private:
  GLenum format;
  GLenum internal_format;
  Sampler sampler;
  unsigned char* source;
  GLenum target;
  GLenum type;
};
}
}
