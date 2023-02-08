// Copyright 2021, Aline Normoyle, alinen

#include "image.h"

#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"
#include <cmath>

namespace agl {

// extension func since std::clamp not working 
float clamp(float val, float min, float max){
   return val < min ? min : (val > max ? max : val);
}

Image::Image() {
   m_channels = 3; 
   m_data = nullptr;
}

Image::Image(int width, int height)  {
   m_width = width;
   m_height = height;
   m_channels = 3; 
   m_data = new char[m_width * m_height * m_channels]; 

}

Image::Image(const Image& orig) {
   m_width = orig.m_width; 
   m_height = orig.m_height; 
   m_channels = orig.m_channels; 
   m_data = new char[m_width * m_height * m_channels];
   for (int i = 0; i < m_width * m_height * m_channels; i++){
      m_data[i] = orig.m_data[i];
   }
}

Image& Image::operator=(const Image& orig) {
  if (&orig == this) {
    return *this;
  }

  if (m_data != nullptr) {
   delete m_data;
  }
  
  m_width = orig.m_width; 
  m_height = orig.m_height; 
  m_channels = orig.m_channels; 
  m_data = new char[m_width * m_height * m_channels];
  for (int i = 0; i < m_width * m_height * m_channels; i++){
      m_data[i] = orig.m_data[i];
   }

  return *this;
}

Image::~Image() {
   if (m_data != nullptr) {
      delete m_data; 
   }
   
}

int Image::width() const { 
   return m_width;
}

int Image::height() const {
   return m_height;
}

char* Image::data() const {
   return m_data;
}

void Image::set(int width, int height, unsigned char* data) {
   
}

bool Image::load(const std::string& filename, bool flip) {
   stbi_set_flip_vertically_on_load(flip);
   char * tempData = (char *) stbi_load(filename.c_str(), 
      &m_width, &m_height, &m_channels, 3);

   if (m_data != nullptr){
      delete m_data;
   }

   if (tempData != nullptr){
      m_data = new char[m_width * m_height * m_channels]; 
      for (int i = 0; i < m_width * m_height * m_channels; i++){
         m_data[i] = tempData[i];
      }
      stbi_image_free(tempData);
      return true; 
   }

   m_data = nullptr;
   return false; 
}

bool Image::save(const std::string& filename, bool flip) const {
   stbi_flip_vertically_on_write(flip); 
   return stbi_write_png(filename.c_str(), m_width, m_height, 
      m_channels, m_data, m_width*m_channels);
}

Pixel Image::get(int row, int col) const {
   char red = m_data[m_channels*row*m_width + m_channels*col]; 
   char green = m_data[m_channels*row*m_width + m_channels*col +1]; 
   char blue = m_data[m_channels*row*m_width + m_channels*col +2]; 

  return Pixel{ (unsigned char)red,(unsigned char)green,(unsigned char)blue};
}

void Image::set(int row, int col, const Pixel& color) {

   m_data[m_channels*row*m_width + m_channels*col] = (char) color.r; 
   m_data[m_channels*row*m_width + m_channels*col +1] = (char) color.g; 
   m_data[m_channels*row*m_width + m_channels*col +2] = (char) color.b; 
 
}

Pixel Image::get(int i) const
{
   return Pixel{ 0, 0, 0 };
}

void Image::set(int i, const Pixel& c)
{

}

Image Image::resize(int w, int h) const {

   Image result(w, h); 

   float widthProp;
   float heightProp; 
   int origX;
   int origY;

   for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++){
         widthProp = j/(float)(w - 1); 
         heightProp = i/(float)(h - 1);

         origX = floor(heightProp * (m_height - 1));
         origY = floor(widthProp * (m_width - 1));

         result.set(i, j, get(origX, origY));

      }
   }

   
   return result;
}

Image Image::flipHorizontal() const {

   Image result(m_width, m_height);
   int mid = m_width/2; 

   for (int i = 0; i < m_height; i++){
      for (int j = 0; j < mid; j++){

         Pixel pixel = get(i, j);
         Pixel flipped = get(i, m_width-j-1);
        
         result.set(i, j, flipped);
         result.set(i, m_width-j-1, pixel);
      }
   }

   if (m_width % 2 != 0){
      for (int i = 0; i < m_height; i++){
         result.set(i, mid, get(i, mid)); 
      }
   }
   
   return result;

}

Image Image::flipVertical() const {
   Image result(0, 0);
   return result;
}

Image Image::rotate90() const {
   Image result(0, 0);
  
   return result;
}

Image Image::subimage(int startx, int starty, int w, int h) const {
  
   Image sub(w, h);

   for (int i = 0; i < h; i++) {
      for (int j = 0; j < w; j++) {
         Pixel pixel = get(startx+i, starty+j);
         sub.set(i, j, pixel);
      
      }
   }

    return sub;
}

void Image::replace(const Image& image, int startx, int starty) {

   for (int i = startx; i < startx+image.height(); i++) {
      for (int j = starty; j < starty+image.width(); j++) {
         // in case new img boundaries bigger than base img 
         if (i < m_height && j < m_width){
            set(i, j, image.get(i-startx, j-starty));
         }
      }
   }
  
}

// I think it works ?? 
Image Image::swirl() const {
   Image result(m_width, m_height);

   for (int i = 0; i < m_height; i++) {
      for (int j = 0; j < m_width; j++){
         Pixel curr = get(i, j); 

         curr.g = curr.b; 
         curr.b = curr.r; 
         curr.r = get(i, j).g;

         result.set(i, j, curr); 
      }
   }

   return result;
}

Image Image::add(const Image& other) const {
   Image result(m_width, m_height);

   for (int i = 0; i < other.height(); i++){
      for (int j = 0; j < other.width(); j++){
         Pixel currPx = get(i, j);
         Pixel otherPx = other.get(i, j);

         Pixel resultPx; 
         // resultPx.r = std::clamp(currPx.r + otherPx.r, 0, 255); 
         resultPx.r = currPx.r + otherPx.r < 0 ? 0 : (currPx.r + otherPx.r > 255 ? 255 : currPx.r + otherPx.r);
         resultPx.g = currPx.g + otherPx.g < 0 ? 0 : (currPx.g + otherPx.g > 255 ? 255 : currPx.g + otherPx.g);
         resultPx.b = currPx.b + otherPx.b < 0 ? 0 : (currPx.b + otherPx.b > 255 ? 255 : currPx.b + otherPx.b);

         result.set(i, j, resultPx);
      }
   }
  
   return result;
}

// not working : ( 
Image Image::subtract(const Image& other) const {
   Image result(m_width, m_height);

   for (int i = 0; i < other.height(); i++){
      for (int j = 0; j < other.width(); j++){
         Pixel currPx = get(i, j);
         Pixel otherPx = other.get(i, j);

         Pixel resultPx; 
         resultPx.r = clamp(currPx.r - otherPx.r, 0, 255);
         resultPx.g = clamp(currPx.g - otherPx.g, 0, 255);
         resultPx.b = clamp(currPx.b - otherPx.b, 0, 255);
         // resultPx.r = currPx.r - otherPx.r < 0 ? 0 : (currPx.r - otherPx.r > 255 ? 255 : currPx.r - otherPx.r);
         // resultPx.g = currPx.g - otherPx.g < 0 ? 0 : (currPx.g - otherPx.g > 255 ? 255 : currPx.g - otherPx.g);
         // resultPx.b = currPx.b - otherPx.b < 0 ? 0 : (currPx.b - otherPx.b > 255 ? 255 : currPx.b - otherPx.b);

         result.set(i, j, resultPx);
      }
   }
   
   return result;
}

Image Image::multiply(const Image& other) const {
   Image result(m_width, m_height);

   for (int i = 0; i < m_height; i++){
      for (int j = 0; j < m_width; j++){

         Pixel currPx = get(i, j);
         Pixel otherPx = other.get(i, j);

         Pixel multiplyPx; 
         multiplyPx.r = (currPx.r/(float)255) * otherPx.r;
         multiplyPx.g = (currPx.g/(float)255) * otherPx.g; 
         multiplyPx.b = (currPx.b/(float)255) * otherPx.b; 

         result.set(i, j, multiplyPx);

      }
   }
   
   return result;
}

Image Image::screen(const Image& other) const {
   Image result(m_width, m_height);

   // f(a,b)=1-(1-a)(1-b)

   for (int i = 0; i < m_height; i++){
      for (int j = 0; j < m_width; j++){
         Pixel currPx = get(i, j);
         Pixel otherPx = other.get(i, j);

         currPx.r = 1.0 - currPx.r/255.0;
         currPx.g = 1.0 - currPx.g/255.0; 
         currPx.b = 1.0 - currPx.b/255.0; 

         otherPx.r = 1.0 - otherPx.r/255.0; 
         otherPx.g = 1.0 - otherPx.g/255.0; 
         otherPx.b = 1.0 - otherPx.b/255.0; 

         Pixel screenPx; 
         screenPx.r = (1-(currPx.r*otherPx.r))*255; 
         screenPx.g = (1-(currPx.g*otherPx.g))*255; 
         screenPx.b = (1-(currPx.b*otherPx.b))*255; 

         // check pixels !! 
         // overflow issues or rounding issues ? 
         // check on feep (pixels)
         // maybe too much 

         result.set(i, j, screenPx); 

      }
   }

   return result; 
}

Image Image::difference(const Image& other) const {
   Image result(m_width, m_height);

   for (int i = 0; i < m_height; i++){
      for (int j = 0; j < m_width; j++){

         Pixel currPx = get(i, j);
         Pixel otherPx = other.get(i, j);

         Pixel resultPx; 

         resultPx.r = std::abs(currPx.r - otherPx.r);
         resultPx.g = std::abs(currPx.g - otherPx.g);
         resultPx.b = std::abs(currPx.b - otherPx.b);

         result.set(i, j, resultPx);

      }
   }
  
   return result;
}

Image Image::lightest(const Image& other) const {
   Image result(m_width, m_height);

   
  
   return result;
}

Image Image::darkest(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::gammaCorrect(float gamma) const {

   Image result(m_width, m_height);


   for (int i = 0; i < m_height; i++) {
      for (int j = 0; j < m_width; j++){

         Pixel pixel = get(i, j); 

         // used below link to figure out 
         // before did not have the 255 in equ which did not work at all 
         // https://stackoverflow.com/questions/16521003/gamma-correction-formula-gamma-or-1-gamma

         pixel.r = pow((float)pixel.r/255, 1.0/gamma) * 255;
         pixel.g = pow((float)pixel.g/255, 1.0/gamma) * 255;
         pixel.b = pow((float)pixel.b/255, 1.0/gamma) * 255;

         result.set(i, j, pixel);

      }
   }
 
   return result;
}

Image Image::alphaBlend(const Image& other, float alpha) const {
   Image result(m_width, m_height);
   for (int i = 0; i < m_height; i++){
      for (int j = 0; j < m_width; j++){
         Pixel otherPx = other.get(i, j);
         Pixel thisPx = get(i, j);

         Pixel resultPx; 
         resultPx.r = otherPx.r*alpha + thisPx.r*(1-alpha); 
         resultPx.g = otherPx.g*alpha + thisPx.g*(1-alpha); 
         resultPx.b = otherPx.b*alpha + thisPx.b*(1-alpha); 

         result.set(i, j, resultPx);
      }
   }

   return result;
}

Image Image::invert() const {
   Image result(m_width, m_height);

   for (int i = 0; i < m_height; i++) {
      for (int j = 0; j < m_width; j++) {
         Pixel curr = get(i, j); 

         curr.r = (1 - curr.r/255.0)*255.0; 
         curr.g = (1 - curr.g/255.0)*255.0; 
         curr.b = (1 - curr.b/255.0)*255.0; 

         result.set(i, j, curr);
      }
   }
   
   return result;
}

Image Image::grayscale() const {

   Image result(m_width, m_height);

   for (int i = 0; i < m_height; i++){
      for (int j = 0; j < m_width; j++){

         Pixel pixel = get(i, j); 

         // weighted avg 
         float avg = 0.299 * pixel.r + 0.587 * pixel.g + 0.114 * pixel.b;
         
         pixel.r = avg;
         pixel.g = avg;
         pixel.b = avg;

         result.set(i, j, pixel);

      }
   }


   return result;
}

Image Image::colorJitter(int size) const {
   Image image(0, 0);
  
   return image;
}

Image Image::bitmap(int size) const {
   Image image(0, 0);
   
   return image;
}

void Image::fill(const Pixel& c) {
  }

}  // namespace agl

