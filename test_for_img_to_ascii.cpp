#include <iostream>
#include <vector>

extern "C" {
    #define STB_IMAGE_IMPLEMENTATION
    #include "stb_image.hpp"
}

const std::string density = "N@#W9876543210?!abc;:+=-,. "; //size = 27


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


// Loads as RGBA... even if file is only RGB
// Feel free to adjust this if you so please, by changing the 4 to a 0.
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


int greyScale (unsigned char a, unsigned char b, unsigned char c) {
    //std::cout << "a: " << static_cast<int>(a) << " b: " << static_cast<int>(b) << " c: " << static_cast<int>(c) << " sum: " << (static_cast<int>(a) + static_cast<int>(b) + static_cast<int>(c)) / 3 << std::endl;
    return (static_cast<int>(a) + static_cast<int>(b) + static_cast<int>(c)) / 3;
}


void makeGreyScaleRaw (std::vector<std::vector<int>>& pic, 
                                                int width, int height, 
                                                std::vector<unsigned char> image) {
    int tw = 0, th = 0;
    for (size_t i = 0; i < image.size(); i += 3) {
        int sum = greyScale(image[i], image[i + 1], image[i + 2]);
        //std::cout << sum << '\n';
        pic[tw][th] = sum;
        ++tw;
        if (tw >= width) {
            tw = 0;
            ++th;
        }
    }
}


void makeFinalPic (std::vector<std::vector<unsigned char>>& asci, std::vector<std::vector<int>> pic) {
    for (int i = 0; i < asci.size(); ++i) {
        for (int j = 0; j < asci[i].size(); ++j) {
            asci[i][j] = density[26 - getIndex(pic[i][j])];
        }
    }
}


void printImage (std::vector <unsigned char> image) {
    for (int i = 0; i < image.size() / 5; i += 3) {
        std::cout << static_cast<int>(image[i + 0]) << " " 
                  << static_cast<int>(image[i + 1]) << " "
                  << static_cast<int>(image[i + 2]) << '\n';
    }
    std::cout << image.size();
}


void printPic (std::vector<std::vector<int>> pic) {
    for (int i = 0; i < pic.size(); ++i) {
        for (int j = 0; j < pic.back().size(); ++j) {
            std::cout << pic[i][j] << " ";
        }
        std::cout << "\n";
    }
}


int main()
{
    std::string filename = "color.png";

    int width, height;
    std::vector<unsigned char> image;
    bool success = loadImage(image, filename, width, height);
    if (!success) {
        std::cout << "Error loading image\n";
        return 1;
    }

    
    std::vector<std::vector<int>> pic (width, std::vector<int> (height));
    makeGreyScaleRaw(pic, width, height, image);
    /*
    std::vector<std::vector<char>> asci (pic.size(), std::vector<char> (pic.back().size()));
    makeFinalPic(pic);
    for (int i = 0; i < asci.back().size(); ++i) {
        for (int j = 0; j < asci.size(); ++j) {
            std::cout << pic[i][j] << " ";
        }
        std::cout << '\n';
    }
    */
    int cnt = 0;
    for (auto& elem : image) {
        std::cout << density[getIndex(static_cast<int>(elem))];
        ++cnt;
        if (cnt > width - 1) {
            std::cout << '\n';
            cnt = 0;
        }
    }
}