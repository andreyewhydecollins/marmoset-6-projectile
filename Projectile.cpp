//////////////////////////////////////////////////////////////
//
// Your #includes here; make sure you are allowed them ...
//

#include <stdlib.h>
#include <cmath>

//////////////////////////////////////////////////////////////
//
// #includes and function declarations; do not remove
//

#ifndef MARMOSET_TESTING
#include <iostream>
using namespace std;
#endif

//////////////////////////////////////////////////////////////
//
// Function declarations; do not remove
//

bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY);
float angleConverter(const float theta);
bool basicErrorChecker(const float h, const float v, const float m,
                        const float theta, const float d,
                        const float t, const float b, const float w,
                        float& destX, float& destY);
float quadratic(const float a, const float b, const float c);
						

//////////////////////////////////////////////////////////////
//
// Your code here ...
//
// Return std::numeric_limits<float>::quiet_NaN() (comes from
// <limits>) if cannot compute the root for some reason
//

float angleConverter(const float theta){
/*transforms the angle into radian */
	float alpha =theta;    // angle from -180 to 180
	while ( (alpha <= -180) || (alpha > 180)){
		if (alpha > 180)
			alpha -= 360;
		if (alpha <= -180)
			alpha += 360;
	}
	// KEEP IN MIND THAT -180 degrees = 180 = pi
	return ((M_PI * alpha)/180);
}

float quadratic(const float a, const float b, const float c){
  float res1;
  float res2;
  float radical;
  radical = sqrt(b*b - 4 * a * c);
  res1 = (-b + radical) / (2*a);
  res2 = (-b - radical) / (2*a);
  if (res2 > res1){
    return res2;
  } else{
    return res1;
  }
}


bool basicErrorChecker(const float h, const float v, const float m,
                        const float theta, const float d,
                        const float t, const float b, const float w,
                        float& destX, float& destY){
                        
	
	enum side{LEFT, RIGHT, NONE}; //projectile motion side.
	side* pfiring = new side; //which side the bullet is flying
	float alpha  = angleConverter(theta);
	
	//speed is negative
	if (v < 0){
		cout << "negative speed" << endl;
		return false;
	}
	//speed is 0 check!
	if (v == 0){
	  cout << "speed = 0 no mvt" << endl;
	  destX = 0;
	  destY = h;
	  return true;
	}
	
	// time is negative or 0
	if (t <= 0){
		cout << "negative time dude" << endl;
		return false;
	}
	
	// mass is negative or 0
	if (m <= 0){
		cout << "negative mass" << endl;
		return false;
	}
	
	// distance to target building and distance to target point
	// needs to be the same sign
	if ( d * b < 0){
		cout << "d b not same sign" << endl;
		return false;
	}
	
	// target not on the platform
	if ( (b+w < d) || (d < b) ){
		cout << d-b << endl;
		cout << w << endl;
		return false;
		
	}
	// if shooting up or down ONLY
	if ( (alpha == M_PI /2) || (alpha == -M_PI / 2)){
	    cout << "shooting up or down" << endl;
	    destX = 0;
	    destY = h;
	    return true; //INTERESTING no movement
	}
	
	// check which side is bullet firing
	if ( (alpha > -(M_PI / 2)) && (alpha < (M_PI / 2))){
		
		*pfiring = RIGHT;
		cout << "shooting right" << endl;
	} else {
		*pfiring = LEFT;
		cout << "shooting left" << endl;
		//if shooting left, error triggers for this exercice
		//nvm
	}
	
	
	// checking if this concur with b and d (previously checked for equal sign)
	if ( (*pfiring == RIGHT) && (d < 0) ){
	    cout << "not same direction" << endl;
		return false;
	}
	if ( (*pfiring == LEFT) && (d >0) ){
        cout << "not same direction" << endl;
		return false;
	}
	
	
	
	return true; //NO ERROR!
	
	
}
				
		

	



bool projectileDestination(const float h, const float v, const float m,
                           const float theta, const float d,
                           const float t, const float b, const float w,
                           float& destX, float& destY) {
							   
	if (! basicErrorChecker(h,v,m,theta,d,t,b,w,destX,destY))
		// if error checking finds an error
		return false;
	
	enum position{GROUNDFRONT ,GROUNDBEYOND, GROUNDBACK, TOWER, WALL,UNKNOWN};
	position landing; ; // if h is negative , position gets bunker
	
	const float angle = angleConverter(theta);
	const float vx = v * cos(angle);
	const float vy = v * sin(angle);
	
	float myTimeGround; //deltax =  b
	float myTimeTower; //delta x = b+w---> b but before b+w
	float deltaYGround;
	float deltaYTower;
	
	const float deltaH = -h;
	
	const float g = -9.80000000;
	const float heightDifference = t-h; //final - initial
  
  
  // CALCULATING WHICH STAGE THE PROJECTILE IS
  
  //suppose the bullet fires a distance of b, where would it land;
  	myTimeGround = (b / vx);//till d
  	cout << "time required to reach d  " << myTimeGround << endl;
	deltaYGround = vy * myTimeGround + 0.5* g * myTimeGround * myTimeGround; //negative number for sure
	  cout << "delta y landing position  " << deltaYGround << endl;
	if ( (deltaYGround > deltaH) && (deltaYGround < heightDifference)){ //fired above means not good prob hit the tower
	  landing = WALL;//a guess
	  cout << "going above" << endl;
	}
	  
	else if (deltaYGround <= deltaH){
    landing = GROUNDFRONT; //pretty sure
    cout << "landing area found to be in front" << endl;
    
	}
	else{
	  landing = TOWER;
	  cout << "maybe hitting tower" << endl;
	}
  //---------------------------------
    
	myTimeTower = (b + w) / vx;
	deltaYTower = vy * myTimeTower + 0.5* g * myTimeTower* myTimeTower;
	if (deltaYTower > heightDifference){ //it shoots over the tower
	  landing = GROUNDBEYOND;
	  cout << "home RUN boy" << endl;
	}
	//deltay = vi * t + 1/2 a t * t
	
    cout << "normal termination" << endl;
    
   float landingTime; //time to land
    
  //NOW SWITCH TESTING FOR destX destY
    
    switch(landing){
      // delta y = vy * t + 1/2 * g * t * t
      // vf y = vy*t
      // delta x = vx* t
      
      case GROUNDFRONT:
        landingTime = quadratic(0.5*g,vy,deltaH);
        destY = 0;
        destX = vx * landingTime;
        break;
      case GROUNDBEYOND:
        landingTime = quadratic(0.5*g,vy,deltaH);
        destY = 0;
        destX = vx * landingTime;
        break;
      case TOWER:
        landingTime = quadratic(0.5*g,vy,heightDifference);
        //cout << landingTime << endl;
        destY = t;
        destX = vx * landingTime;
        break;
      case WALL:
        landingTime = b/vx;
        destX = b;
        destY = vy * landingTime + 0.5* g * landingTime * landingTime;
        break;
      
    }
	return true;
}

//////////////////////////////////////////////////////////////
//
// Test Driver
//
// Do not remove the #ifndef and its associated #endif
// This is required so that when you submit your code,
// this test driver will be ignored by Marmoset
//

#ifndef MARMOSET_TESTING

#define isNaN(X) (X != X)  // NaN is the only float that is not equal to itself

int main(const int argc, const char* const argv[]) {
  
  //Some test driver code here ....

  float h = 10;
  float v = 900;
  float m = 10;
  float theta = 45;        // Angle in degrees; will need to be converted by function
  float d = 17;
  float t = 2000;
  float b = 16.40677261837322;
  float w = 20;

  float hitsAtX;
  float hitsAtY;

  cout <<(projectileDestination(h,v,m,theta,d,t,b,w,hitsAtX,hitsAtY)) << endl;
  cout << hitsAtX << endl;
  cout << hitsAtY << endl;
    //cout << angleConverter(-180) << endl;
	//cout << angleConverter(720) << endl;
	return 0;
}

#endif
