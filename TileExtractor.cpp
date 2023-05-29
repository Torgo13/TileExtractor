// TileExtractor.cpp : Defines the entry point for the application.

#include "TileExtractor.h"

int main(int argc, char** argv)
{
    /*if (argc != 2)
    {
        printf("usage: TileExtractor.out <Image_Path>\n");
        return -1;
    }*/

    cv::Mat base, overlay;
    base = cv::imread(/*argv[1]*/ "D:\\source\\repos\\Assets\\Sprites\\MT_Terrains_Lite_1.0\\MV\\Autotiles A4.png", cv::IMREAD_UNCHANGED);
    overlay = cv::imread("D:\\source\\repos\\Assets\\Sprites\\MT_Terrains_Lite_1.0\\MV\\Autotiles_A2_0.png", cv::IMREAD_UNCHANGED);
    if (!base.data)
    {
        printf("No image data \n");
        return -1;
    }

    TileExtractor tileExtractor(base, overlay);

    return 0;
}

TileExtractor::TileExtractor(cv::Mat Base, cv::Mat Overlay)
{
    base = Base;
    overlay = Overlay;

    // Final output image (pixels)
    cv::Mat outputTileset = cv::Mat(7 * 4 * tileSize, 7 * 4 * tileSize, CV_8UC4);

    // loop index
    unsigned int i = 0;

    // Top left corner of biome tileset (tiles)
    baseOffset = cv::Point(baseTilesetWidth * (i % baseTilesetWidth), baseTilesetHeight * (i / baseTilesetWidth));
    overlayOffset = cv::Point(overlayTilesetWidth * (i % overlayTilesetWidth), overlayTilesetHeight * (i / overlayTilesetWidth));

    // ROI encapsulating one biome of the tileset (pixels)
    cv::Rect baseTilesetROI = cv::Rect(baseOffset.x * tileSize, baseOffset.y * tileSize, baseTilesetWidth * tileSize, baseTilesetHeight * tileSize);
    cv::Rect overlayTilesetROI = cv::Rect(overlayOffset.x * tileSize, overlayOffset.y * tileSize, tileSize * 3, tileSize * 3);

    cv::Mat overlayTileset = overlay(overlayTilesetROI);

    /*for (unsigned int u = 0; u < 7 * 2; u++)
    {
        for (unsigned int v = 0; v < 7 * 2; v++)
        {
            innerTileset.copyTo(outputTileset(cv::Rect(u * tileSize * 2, v * tileSize * 2, tileSize * 2, tileSize * 2)));
        }
    }*/

    /*for (unsigned int u = 0; u < 7 * 2; u++)
    {
        for (unsigned int v = 0; v < 7 * 2; v++)
        {
            overlayTileset.copyTo(outputTileset(cv::Rect(u * tileSize * 2, v * tileSize * 2, tileSize * 2, tileSize * 2)));
        }
    }*/

    for (unsigned int u = 0; u < 7 * 4; u++)
    {
        for (unsigned int v = 0; v < 7 * 4; v++)
        {
            overlayTileset(cv::Rect((u % 3) * tileSize, (v % 3) * tileSize, tileSize, tileSize)).copyTo(outputTileset(cv::Rect(u * tileSize, v * tileSize, tileSize, tileSize)));
        }
    }

    cv::namedWindow("Display Image", cv::WINDOW_AUTOSIZE);
    cv::imshow("Display Image", outputTileset);
    cv::waitKey(0);
}

cv::Mat TileExtractor::getTile(cv::Mat input, cv::Point offset, cv::Point coordinates)
{
    cv::Mat tile;

    input(cv::Rect((offset.x + coordinates.x) * tileSize, (offset.y + coordinates.y) * tileSize, tileSize, tileSize)).copyTo(tile);

    return tile;
}

void TileExtractor::writeTile(cv::Mat input, cv::Mat& output, cv::Point offset, cv::Point coordinates)
{
    input.copyTo(output(cv::Rect((offset.x + coordinates.x) * tileSize, (offset.y + coordinates.y) * tileSize, tileSize, tileSize)));
}
