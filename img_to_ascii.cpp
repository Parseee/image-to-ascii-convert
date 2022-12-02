#include <iostream>
#include <vector>
#include <string>
#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"


const std::string density = "N@#W9876543210?!abc;:+=-,. "; //size = 27

//0 - default RGB
//1 - grey scale
//2 - grey scale + alpha
//3 - RGB
//4 - RGB + alpha
//for this work i dont need to load RGB or alpha so i'll use single channel
bool loadImage(std::vector<unsigned char>& image, const std::string& filename, int& x, int& y)
{
    int n;
    unsigned char* data = stbi_load(filename.c_str(), &x, &y, &n, 1);
    if (data != nullptr)
    {
        image = std::vector<unsigned char>(data, data + x * y);
    }
    stbi_image_free(data);
    return (data != nullptr);
}


//donno how to refactor this so leaving as is
int getIndex (int n) {
    if (n > 246) return 0;
    if (n > 237) return 1;
    if (n > 228) return 2;
    if (n > 219) return 3;
    if (n > 210) return 4;
    if (n > 201) return 5;
    if (n > 192) return 6;
    if (n > 183) return 7;
    if (n > 174) return 8;
    if (n > 165) return 9;
    if (n > 156) return 10;
    if (n > 147) return 11;
    if (n > 138) return 12;
    if (n > 129) return 13;
    if (n > 120) return 14;
    if (n > 111) return 15;
    if (n > 93) return 16;
    if (n > 84) return 17;
    if (n > 75) return 18;
    if (n > 66) return 19;
    if (n > 57) return 20;
    if (n > 48) return 21;
    if (n > 39) return 22;
    if (n > 30) return 23;
    if (n > 21) return 24;
    if (n > 12) return 25;
    return 26;
}


void convertToAscii (std::vector<unsigned char>& image, int limit) {
    int cnt = 0;
    for (auto& elem : image) {
        std::cout << density[getIndex(static_cast<int>(elem))];
        ++cnt;
        if (cnt > limit - 1) {
            std::cout << '\n';
            cnt = 0;
        }
    }
}


int main() {
    std::string filename;
    std::cout << "enter name or full path to the source pic with extention: ";
    std::getline (std::cin, filename);

    int width, height;
    std::vector<unsigned char> image;
    bool success = loadImage(image, filename, width, height);
    if (!success) {
        std::cout << "Error loading image\n";
        return 1;
    }


    convertToAscii(image, width);
}