// Copyright 2021, Aline Normoyle, alinen

#include "image.h"

#include <cassert>
#define STB_IMAGE_WRITE_IMPLEMENTATION
#include "stb/stb_image_write.h"
#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace agl {


Image::Image() {
}

Image::Image(int width, int height)  {

}

Image::Image(const Image& orig) {
  
}

Image& Image::operator=(const Image& orig) {
  if (&orig == this) {
    return *this;
  }

  return *this;
}

Image::~Image() {
   if (m_data != nullptr) {
      stbi_image_free(m_data); 
   }
   
   // free img 
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
   // flip w/ this stbi_set_flip_vertically_on_load
   stbi_set_flip_vertically_on_load(flip);
   m_data = (char *) stbi_load(filename.c_str(), &m_width, &m_height, &m_channels, 3);
   // std::cout << m_data << std::endl;

   return m_data!=nullptr; 
   
}

bool Image::save(const std::string& filename, bool flip) const {
   stbi_flip_vertically_on_write(flip); 
   return stbi_write_png(filename.c_str(), m_width, m_height, m_channels, m_data, m_width*3);
}

Pixel Image::get(int row, int col) const {
   char red = m_data[m_channels*row*m_width + m_channels*col]; 
   char green = m_data[m_channels*row*m_width + m_channels*col +1]; 
   char blue = m_data[m_channels*row*m_width + m_channels*col +2]; 

  return Pixel{ (unsigned char)red, (unsigned char)green, (unsigned char)blue};
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

// I imagine this eliminates the alpha (?) 
void Image::set(int i, const Pixel& c)
{

}

Image Image::resize(int w, int h) const {
   Image result(w, h);
   return result;
}

Image Image::flipHorizontal() const {
   Image result(0, 0);
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
  
   Image sub(0, 0);
    return sub;
}

void Image::replace(const Image& image, int startx, int starty) {
  
}

Image Image::swirl() const {
   Image result(0, 0);
   return result;
}

Image Image::add(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::subtract(const Image& other) const {
   Image result(0, 0);
   
   return result;
}

Image Image::multiply(const Image& other) const {
   Image result(0, 0);
   
   return result;
}

Image Image::difference(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::lightest(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::darkest(const Image& other) const {
   Image result(0, 0);
  
   return result;
}

Image Image::gammaCorrect(float gamma) const {

   Image result(0, 0);
 
   return result;
}

Image Image::alphaBlend(const Image& other, float alpha) const {
   Image result(0, 0);

   return result;
}

Image Image::invert() const {
   Image image(0, 0);
   
   return image;
}

Image Image::grayscale() const {
   Image result(0, 0);
   
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

