// Copyright 2021, Aline Normoyle, alinen

#include <iostream>
#include "image.h"
using namespace std;
using namespace agl;

int main(int argc, char** argv)
{
   Image image;
   if (!image.load("../images/feep.png")) {
      std::cout << "ERROR: Cannot load image! Exiting...\n";
      exit(0);
   }

   for (int i = 0; i < image.height(); i++) {
      for (int j = 0; j < image.width(); j++) {
         Pixel c = image.get(i, j);
         std::cout << "(" << (int)c.r << "," << (int)c.g << "," << (int)c.b << ") ";
      }
      std::cout << std::endl;
   }
   image.save("feep-test-save.png"); // should match original
   
   // should print 4 4
   cout << "loaded feep: " << image.width() << " " << image.height() << endl;

   // test: copy constructor
   Image copy = image; 
   copy.save("feep-test-copy.png"); // should match original and load into gimp

   // test: assignment operator
   copy = image; 
   copy.save("feep-test-assignment.png"); // should match original and load into gimp

   // should print r,g,b
   Pixel pixel = image.get(1, 1);
   cout << (int) pixel.r << " " << (int) pixel.g << " " << (int) pixel.b << endl;

   // test: setting a color
   pixel.r = 255;
   image.set(1, 1, pixel);
   image.save("feep-test-newcolor.png");

   // test a non-trivial image
   if (!image.load("../images/earth.png")) {
      std::cout << "ERROR: Cannot load image! Exiting...\n";
      exit(0);
   }

   // should print 400 400
   cout << "loaded earth: " << image.width() << " " << image.height() << endl;

   // resize
   Image resize = image.resize(200,300);
   resize.save("earth-200-300.png");

   // grayscale
   Image grayscale = image.grayscale(); 
   grayscale.save("earth-grayscale.png");

   // flip horizontal
   Image flip = image.flipHorizontal(); 
   flip.save("earth-flip.png"); 

   // sub image
   Image sub = image.subimage(200, 200, 100, 100); 
   sub.save("earth-subimage.png"); 

   // gamma correction
   Image gamma = image.gammaCorrect(0.6f); 
   gamma.save("earth-gamma-0.6.png"); 

   gamma = image.gammaCorrect(2.2f);
   gamma.save("earth-gamma-2.2.png"); 

   // alpha blend
   Image soup;
   soup.load("../images/soup.png");

   int y = (int) (0.5f * (image.width() - soup.width()));
   int x = (int) (0.5f * (image.height() - soup.height()));
   Image background = image.subimage(x, y, soup.width(), soup.height());
   background.save("background-test.png");
   Image blend = background.alphaBlend(soup, 0.5f);
   image.replace(blend, x, y);
   image.save("earth-blend-0.5.png");

   return 0; 
}

