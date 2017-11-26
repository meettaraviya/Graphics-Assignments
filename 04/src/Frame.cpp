#include "Frame.hpp"

using namespace std;

void Frame::frame_capture(){
  ofstream outfile;
  outfile.open("keyframes.txt",ios::app);
  nframes = new float[nparams];
  int x=0;
  int size = chararr[0].mats_relative_rot.size();
  for(int k=0;k<size;k++){
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        outfile << chararr[0].mats_relative_rot[k][i][j] << " ";
        nframes[x] = chararr[0].mats_relative_rot[k][i][j];
        x++;
      }
    }
  }
  int size1 = chararr[1].mats_relative_rot.size();
  for(int k=0;k<size1;k++){
    for(int i=0;i<4;i++){
      for(int j=0;j<4;j++){
        outfile << chararr[1].mats_relative_rot[k][i][j] << " ";
        nframes[x] = chararr[1].mats_relative_rot[k][i][j];
        x++;
      }
    }
  }
  outfile <<"\n";
  int nframe;
  cin>>nframe;
  if(nframe == -1){
    outfile <<"\n";
    outfile.close();
    interpolate_frame();
    exit(0);
  }
  else{
   outfile << nframe;
   numframe.push_back(nframe);
  }
  outfile <<"\n";
  outfile.close();
}

void Frame::interpolate_frame(){
  vector<Frame>finalframes;
  for(int i=0;i<numframe.size();i++){ //calculates the middle frames as well
    int temp=1;
    finalframes.push_back(keyframe[i]); //dont forget to push the finalkeyframe
    cout<<temp<<" "<<numframe[i]<<" "<<nparams<<endl;
    while(temp<=numframe[i]){
      finalframes.push_back(Frame());
      for(int j=0;j<nparams;j++){
        finalframes[finalframes.size()-1].nframes[j] = temp*((keyframe[i+1].nframes[j]-keyframe[i].nframes[j])/(numframe[i]+1));
      }
      temp++;
    }
  }
  finalframes.push_back(keyframe[keyframe.size()-1]);
  ofstream outfile;
  outfile.open("frames.txt",ios::app);
  for(int i=0;i<finalframes.size();i++){
    for(int j=0;j<240;j++){
      outfile << finalframes[i].nframes[j]<<" ";
    }
    outfile << "\n";
  }
}