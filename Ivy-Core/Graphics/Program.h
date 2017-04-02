// MIT License
//
// Copyright (c) 2017 Ben Brown
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#ifndef __PROGRAM_H__
#define __PROGRAM_H__

#include "Shader.h"

namespace Ivy {
namespace Graphics {
struct Attribute {
  std::string name;
  GLuint location;
  GLenum type;
  GLsizei size;
};

struct Uniform {
  std::string name;
  GLuint location;
  GLenum type;
  GLsizei size;
};

struct UniformBlock {
  std::string name;
  GLuint location;
  std::vector<Uniform> uniforms;
};

class Program {
 public:
  Program();
  bool Link();
  bool Validate();

  GLuint get_id() { return id; }
  std::vector<Attribute> get_attributes() { return attributes_; }
  std::vector<Uniform> get_uniforms() { return uniforms_; }
  std::vector<UniformBlock> get_uniform_blocks() { return uniform_blocks_; }
 private:
  GLuint id;
  std::vector<Attribute> attributes_;
  std::vector<Uniform> uniforms_;
  std::vector<UniformBlock> uniform_blocks_;
};
}
}

#endif
