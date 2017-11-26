#include "Frame.hpp"

using namespace std;

int Frame::param_count = 0;

vector<Frame> keyframes, allframes;
vector<int> frame_gaps;

void write_keyframes(){
  FILE* outfile = fopen("keyframes.txt", "w");
  fprintf(outfile, "%d %d\n", (int) keyframes.size(), Frame::param_count);
  int i;
  for(i=0; i<keyframes.size()-1; i++){
    for(int j=0; j<Frame::param_count; j++){
      fprintf(outfile, "%.3f ", keyframes[i].params[j]);
    }
    fprintf(outfile, "\n%d\n", frame_gaps[i]);
  }
  for(int j=0; j<Frame::param_count; j++){
      fprintf(outfile, "%.3f ", keyframes[i].params[j]);
    }
  fclose(outfile);
}

void load_keyframes(){
  FILE* infile = fopen("keyframes.txt", "r");
  int n,i;
  fscanf(infile, "%d %d", &n, &Frame::param_count);
  keyframes.resize(n, Frame());
  frame_gaps.resize(n-1, 0);
  for(i=0; i<keyframes.size()-1; i++){
    for(int j=0; j<Frame::param_count; j++){
      fscanf(infile, "%f ", &keyframes[i].params[j]);
    }
    fscanf(infile, "%d", &frame_gaps[i]);
  }
    // cout << i << endl;
  for(int j=0; j<Frame::param_count; j++){
      fscanf(infile, "%f ", &keyframes[i].params[j]);
    }
}

Frame::Frame(){
  params.resize(param_count,0);
}

void Frame::count_params(){
  param_count = 0;
  for(int i=0; i<characters.size(); i++){
    param_count += characters[i].val_rot.size()*3;
    param_count += 9;
  }
  cout << "Total parameters: " << param_count << endl;
}

void Frame::frame_capture(){
  int ix = 0;
  for(int i=0; i<characters.size(); i++){
    //     for(int i=0; i<params.size(); i++){
    //   cout << params[i] << " ";
    // }
    // cout << endl;
    characters[i].send_params(ix, params);
    //     for(int i=0; i<params.size(); i++){
    //   cout << params[i] << " ";
    // }
    // cout << endl;
  }
}
void Frame::frame_set(){
  int ix = 0;
  for(int i=0; i<characters.size(); i++){
    characters[i].get_params(ix, params);
    // for(int i=0; i<params.size(); i++){
    //   cout << params[i] << " ";
    // }
    // cout << endl;
  }
}

void interpolate_frames(){
    int n = 0;
    for(int i=0; i<frame_gaps.size(); i++){
      n += frame_gaps[i];
    }
    allframes.resize(n+keyframes.size());

  int x = 0;
  for(int i=0;i<frame_gaps.size();i++){ //calculates the middle frames as well
    for(int g=0; g<frame_gaps[i]; g++){
        float r = (float(g))/(frame_gaps[i]+1);
        cout << r << endl;
      for(int j=0;j<Frame::param_count;j++){
        allframes[x+g].params[j] = (1-r)*keyframes[i].params[j]+r*keyframes[i+1].params[j];
      }
    }
      x+=frame_gaps[i];
  }
  allframes.push_back(keyframes[keyframes.size()-1]);
  cout << "ip\n";
  // for(int i=0; i<allframes.size(); i++){
  //   for(int j=0; j<Frame::param_count; j++){
  //     cout << allframes[i].params[j] << " ";
  //   }
  //   cout << endl;
  // }
}