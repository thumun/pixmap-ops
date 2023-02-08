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

   Image sub = image.subtract(swirl);
   sub.save("earth-sub.png");

   Image difference = image.difference(swirl);
   difference.save("earth-difference.png");

   Image lightest = image.lightest(invert);
   lightest.save("earth-lightest.png");

   Image darkest = image.darkest(invert);
   darkest.save("earth-darkest.png");

   // why : ( 
   Image screen = difference.screen(sub);
   screen.save("earth-screen.png");


   return 0;
}

