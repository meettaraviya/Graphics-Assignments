#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include "Include.hpp"
#include "main.hpp"

class Frame{
public:
  int nparams;  //total no of parts across all characters*16
  float* nframes;
  Frame(){
    nparams = 240;
    nframes = new float[nparams];
  }
  void frame_capture();
  void interpolate_frame();
};

#endif