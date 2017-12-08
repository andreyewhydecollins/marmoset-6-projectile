#include <iostream>
#include <limits>

#define NaN std::numeric_limits<double>::quiet_NaN()

using namespace std;

float f( float x){

  float s = (x+20)*(x-40);
  //some function of x
  return s;
}
float abs(float value){
  if (value >= 0){
    return value;
  }
  if (value < 0){
    return -1*value;
  }
}


float rootFind(float left, float right, float precision){
  if (left > right){
    return NaN;
  }
  if (precision < 0){
    return NaN;
  }
  enum state { INCREASING, DECREASING};
  const int maxLoop = 50;
  int loop = 1;
  float currLeft = left; // these curr are the values i change
  float currRight = right;
  float mid;
  float midValue = 10000;

  state myState;
  if ( f(currLeft) <= f(currRight) ){
    //cout << f(currLeft) << endl;
    //cout << f(currRight) << endl;
    myState = INCREASING;
  } else{
    myState = DECREASING;
  }
    
  //cout << myState << endl;
  while ( (loop <= maxLoop) && ( abs (midValue) > precision) ){
    mid = (currRight + currLeft)/2;
    cout << mid << endl;
    
    midValue = f(mid);
    cout << "midValue now" << midValue << endl;
    if (myState == INCREASING){
      if (midValue >= 0)
        currRight = mid;
      else
        currLeft = mid;
    } else{
      if (midValue >=0)
        currLeft = mid;
      else
        currRight = mid;
    }
    loop++;
    //cout << loop << endl;
  }
  if (loop >= 51){
    cerr<< "too many loops" << endl;
    return NaN;
  } else {
    return mid;
  }
}

//void nothing(){
//    return 5;
//}
int main(){

  cout << rootFind(-1,1,-54) << endl;

  return 0;
}

