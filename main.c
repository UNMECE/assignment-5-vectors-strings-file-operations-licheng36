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

void flip_vertically(std::vector<Pixel> &pixel_list, std::vector<Pixel> &flipped_list){
int height = 256;
int width = 512;

int max = flipped_list.size();

for (int y = 0; y < max; y += height) { 
int end = y + height;
int temp_itr = 0;
for (int x = y; x < end; x++) {
int clone_index = end - temp_itr - 1;
temp_itr++;

flipped_list[x].r = pixel_list[clone_index].r;
flipped_list[x].g = pixel_list[clone_index].g;
flipped_list[x].b = pixel_list[clone_index].b;

flipped_list[x].x = pixel_list[x].x;
flipped_list[x].y = pixel_list[x].y;
}
}
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
//ss.clear();

pixel_list.push_back(pixel);
}

//ifile.close();

average_colors(pixel_list);

std::vector<Pixel> flipped(pixel_list.size());
flip_vertically(pixel_list,flipped);


std::ofstream ofile("flipped.dat", std::ios::out);
if (!ofile.is_open()) {
std::cout << "can't open file for writing" << std::endl;
return -1;
}

for (size_t i=0; i<pixel_list.size();i++) {
Pixel& pixel=flipped[i];
ofile << pixel.x << "," << pixel.y << "," << pixel.r << "," << pixel.g << "," << pixel.b << std::endl;
}

ofile.close();

return 0;
}

