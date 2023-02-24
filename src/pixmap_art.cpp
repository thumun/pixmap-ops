#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{

   Image image;
   image.load("../images/earth.png");

   // Image swirl = image.swirl(); 
   // swirl.save("snake-swirl.png");

   // Image multiply = image.multiply(image); 
   // multiply.save("snake-multiply.png");

   // Image invert = image.invert();
   // invert.save("snake-invert.png");

   // Image add = image.add(image);
   // add.save("snake-add.png");

   // Image sub = image.subtract(swirl);
   // sub.save("snake-sub.png");

   // Image difference = image.difference(swirl);
   // difference.save("snake-difference.png");

   // Image lightest = image.lightest(invert);
   // lightest.save("snake-lightest.png");

   // Image darkest = image.darkest(invert);
   // darkest.save("snake-darkest.png");

   // Image screen = difference.screen(sub);
   // screen.save("snake-screen.png");

   // Image filmGrain = image.filmGrain();
   // filmGrain.save("snake-filmGrain.png");

   // Image overlay = image.overlay(image); 
   // overlay.save("snake-overlay.png");

   // Image sepia = image.sepia(); 
   // sepia.save("snake-sepia.png");

   // Image sepiagrain = sepia.filmGrain();
   // sepiagrain.save("snake-oldtimey.png");

   // // my image is super big so these ops look better on earth 

   Image soup;
   soup.load("../images/soup.png");
   // Image pixelateE = earth.pixelate(); 
   // pixelateE.save("earth-pixelate.png");

   // Image gauss = image.gaussianBlur(3);
   // gauss.save("snake-gauss.png");

   // images: 
   // Image invert = image.invert();

   // Image pixelate = image.pixelate();

   // Image blend = invert.alphaBlend(pixelate, 0.5f);

   // blend.save("blurryearth.png");

   // Image grain = invert.filmGrain(); 
   // Image screen = grain.screen(image); 

   // screen.save("lightgrain.png");

   // invert.save("snake-invert.png");

   Image blend = image.alphaBlend(soup, 0.5f);
   //Image difference = blend.difference(earth); 
   blend.save("test.png");

   return 0;
}

