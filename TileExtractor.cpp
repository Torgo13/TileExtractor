// TileExtractor.cpp : Defines the entry point for the application.
//

#include "TileExtractor.h"

int main(int argc, char** argv)
{
    /*if (argc != 2)
    {
        printf("usage: TileExtractor.out <Image_Path>\n");
        return -1;
    }*/

    cv::Mat image;
    image = cv::imread(/*argv[1]*/ "D:\\source\\repos\\Assets\\Sprites\\MT_Terrains_Lite_1.0\\MV\\Autotiles A4.png", cv::IMREAD_COLOR);
    if (!image.data)
    {
        printf("No image data \n");
        return -1;
    }

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    imshow("Display Image", image);
    cv::waitKey(0);

    return 0;
}
