#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include "pixel.h"
#include <sstream>
					 
void average_colors(const std::vector<Pixel>& pixel_list) {
float sum_r = 0.0f, sum_g = 0.0f, sum_b = 0.0f;
int pixel_count = pixel_list.size();

for (size_t i = 0; i < pixel_list.size(); ++i) {
sum_r += pixel_list[i].r;
sum_g += pixel_list[i].g;
sum_b += pixel_list[i].b;
}

float avg_r = sum_r / pixel_count;
float avg_g = sum_g / pixel_count;
float avg_b = sum_b / pixel_count;

std::cout << "Average R: " << avg_r << std::endl;
std::cout << "Average G: " << avg_g << std::endl;
std::cout << "Average B: " << avg_b << std::endl;
}

void flip_vertically(std::vector<Pixel> &pixel_list){
int height = 256; 
int width = 512;  
std::vector<Pixel> flipped_list(height * width);

for (int y = 0; y < height; y++) {
for (int x = 0; x < width ; x++) {
flipped_list[(height - 1 - y) * width + x] = pixel_list[y * width + x];
}
}
pixel_list = flipped_list;
}

int main() {
std::ifstream ifile("pixels.dat");
std::vector<Pixel> pixel_list;
std::string line;
std::stringstream ss;

if (!ifile.is_open()) {
std::cout << "file can't be opened" << std::endl;
return -1;
}

while (std::getline(ifile, line)) {
Pixel pixel;
size_t pos=0;
pos = line.find(',');
ss.str(line.substr(0, pos));
ss >> pixel.x;
line = line.substr(pos + 1);
ss.clear();


pos = line.find(',');
ss.str(line.substr(0, pos));
ss >> pixel.y;
line = line.substr(pos + 1);
ss.clear();

pos = line.find(',');
ss.str(line.substr(0, pos));
ss >> pixel.r;
line = line.substr(pos + 1);
ss.clear();

pos = line.find(',');
ss.str(line.substr(0, pos));
ss >> pixel.g;
line = line.substr(pos + 1);
ss.clear();

ss.str(line);
ss >> pixel.b;
ss.clear();

pixel_list.push_back(pixel);
}

ifile.close();

average_colors(pixel_list);

flip_vertically(pixel_list);


std::ofstream ofile("flipped.dat", std::ios::out);
if (!ofile.is_open()) {
std::cout << "can't open file for writing" << std::endl;
return -1;
}

for (size_t i=0; i<pixel_list.size();i++) {
Pixel& pixel=pixel_list[i];
ofile << pixel.x << "," << pixel.y << "," << pixel.r << "," << pixel.g << "," << pixel.b << std::endl;
}

ofile.close();

return 0;
}

