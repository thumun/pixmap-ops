#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   
   // todo: make at least one artwork!


   Image image;
   image.load("../images/earth.png");

   Image swirl = image.swirl(); 
   swirl.save("earth-swirl.png");

   Image multiply = image.multiply(image); 
   multiply.save("earth-multiply.png");

   Image invert = image.invert();
   invert.save("earth-invert.png");

   Image add = image.add(image);
   add.save("earth-add.png");

   Image sub = image.subtract(image);
   sub.save("earth-sub.png");

   // why : ( 
   image.load("../images/feep.png");
   Image screen = image.screen(image);
   screen.save("feep-screen.png");


   return 0;
}

