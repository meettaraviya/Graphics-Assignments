#ifndef _FRAME_HPP_
#define _FRAME_HPP_

#include "Include.hpp"
#include "main.hpp"

class Frame{
public:
  static int param_count;
  vector<GLfloat> params;
  Frame();
  static void count_params();
  void frame_capture();
  void frame_set();
  // void interpolate_frame();
};

void write_keyframes();
void load_keyframes();
void interpolate_frames();

extern vector<Frame> keyframes, allframes;
extern vector<int> frame_gaps;


#endif