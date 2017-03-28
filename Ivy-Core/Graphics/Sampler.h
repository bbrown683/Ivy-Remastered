#include "Renderer.h"

namespace Ivy {
namespace Graphics {
struct Sampler {
  GLenum mag_filter;
  GLenum min_filter;
  GLenum wrap_s;
  GLenum wrap_t;
};
}
}
