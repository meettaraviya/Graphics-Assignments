#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include "Include.hpp"
#include "main.hpp"

class Frame{
public:
  int nparams;
  float* nframes;
  Frame();
  void frame_capture();
  void interpolate_frame();
};

#endif