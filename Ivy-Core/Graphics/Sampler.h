#ifndef __IVY_SAMPLER_H__
#define __IVY_SAMPLER_H__

#include <string>
#include "GraphicsInclude.h"

namespace Ivy {
namespace Graphics {
class Sampler {
 public:
  Sampler(std::string source, GLenum format, GLenum internal_format, GLenum target);

  GLenum get_texture_format();
  GLenum get_texture_internal_format();
  GLenum get_min_filter();
  void set_min_filter(GLenum min_filter);
  GLenum get_mag_filter();
  void set_mag_filter(GLenum mag_filter);
  GLenum get_wrap_s();
  void set_wrap_s(GLenum wrap_s);
  GLenum get_wrap_t();
  void set_wrap_t(GLenum wrap_t);
  GLfloat get_anistrophy();
  void set_anistrophy(GLfloat anistrophy);
  GLenum get_target();
  const unsigned char* get_texture();
  GLenum get_type();
 private:
  GLenum texture_format_;
  GLenum texture_internal_format_;
  GLenum mag_filter_;
  GLenum min_filter_;
  GLenum wrap_s_;
  GLenum wrap_t_;
  GLfloat anistrophy_;
  unsigned char* texture_;
  GLenum target_;
  GLenum type_;
};
}
}

#endif
