#include "SimplexNoise.h"
#include <QApplication>
#include <QImage>
#include <QLabel>
#include <QPixmap>
#include <iostream>
#include <cmath>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <climits>

static const unsigned int width = 600;
static const unsigned int height = 96;
static const unsigned int nOctaves = 16;
static const float  persistence = .5;
static const float frequency = .007;
static const float low = 0;
static const float high = 255;

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    QImage img(width, height, QImage::Format_RGB32);
    QLabel lbl;
    QPixmap pixmap;
    
    std::srand(std::time(NULL));
    //if these values break the system, you probably shouldn't be using this noise in the first place
    int xOff = rand() % USHRT_MAX;
    int yOff = rand() % USHRT_MAX;

    for (unsigned int i = 0; i < width; i++) {
        for (unsigned int j = 0; j < height; j++) {
            int value = (int)SimplexNoise::octave(nOctaves, i + xOff, j + yOff, persistence, frequency, low, high);
            QRgb color = qRgb(value, value, value);
            img.setPixel(i, j, color);
        }
    }
    pixmap = QPixmap::fromImage(img);
    lbl.setPixmap(pixmap);
    lbl.show();
    pixmap.save("img.png");
    return app.exec();
}
