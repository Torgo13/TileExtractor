// TileExtractor.cpp : Defines the entry point for the application.

#include "TileExtractor.h"

int main(int argc, char** argv)
{
    /*if (argc != 2)
    {
        printf("usage: TileExtractor.out <Image_Path>\n");
        return -1;
    }*/

    cv::Mat base, edge, overlay;
    base = cv::imread("D:\\source\\repos\\Assets\\Sprites\\MT_Terrains_Lite_1.0\\EXTRAS\\Skins.png", cv::IMREAD_UNCHANGED);
    edge = cv::imread(/*argv[1]*/ "D:\\source\\repos\\Assets\\Sprites\\MT_Terrains_Lite_1.0\\EXTRAS\\Autotiles A4 Transparent.png", cv::IMREAD_UNCHANGED);
    overlay = cv::imread("D:\\source\\repos\\Assets\\Sprites\\MT_Terrains_Lite_1.0\\EXTRAS\\Skins.png", cv::IMREAD_UNCHANGED);
    if (!base.data)
    {
        printf("No image data \n");
        return -1;
    }

    TileExtractor tileExtractor(base, edge, overlay);

    return 0;
}

TileExtractor::TileExtractor(cv::Mat Base, cv::Mat Edge, cv::Mat Overlay)
{
    bool grass = true;

    base = Base;
    edge = Edge;
    overlay = Overlay;

    // Final output image (pixels)
    cv::Mat outputTileset = cv::Mat(7 * 4 * tileSize, 7 * 4 * tileSize, CV_8UC4);

    // Top left corner of biome tileset (tiles)
    baseOffset = cv::Point(baseTilesetWidth * 0, baseTilesetHeight * 0);
    edgeOffset = cv::Point(edgeTilesetWidth * 0, edgeTilesetHeight * 0);

    // ROI encapsulating one biome of the tileset (pixels)
    cv::Rect baseTilesetROI = cv::Rect(baseOffset.x * tileSize, baseOffset.y * tileSize, tileSize * 3, tileSize * 3);
    cv::Rect edgeTilesetROI = cv::Rect(edgeOffset.x * tileSize, edgeOffset.y * tileSize, edgeTilesetWidth * tileSize, edgeTilesetHeight * tileSize);

    cv::Mat baseTileset = base(baseTilesetROI);
    cv::Mat edgeTileset = edge(edgeTilesetROI);

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

    unsigned int u = 0, v = 0;

    for (u = 0; u < 7 * 4; u++)
    {
        for (v = 0; v < 7 * 4; v++)
        {
            baseTileset(cv::Rect((u % 3) * tileSize, (v % 3) * tileSize, tileSize, tileSize)).copyTo(outputTileset(cv::Rect(u * tileSize, v * tileSize, tileSize, tileSize)));
        }
    }

    u = 0, v = 0;
    writeTile(getTile(edgeTileset, cv::Point(0, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(0, 4)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 2));
    
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 2));

    writeTile(getTile(edgeTileset, cv::Point(0, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 1, v = 0;
    writeTile(getTile(edgeTileset, cv::Point(0, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(0, 4)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 2));

    writeTile(getTile(edgeTileset, cv::Point(0, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 2, v = 0;
    writeTile(getTile(edgeTileset, cv::Point(1, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 3, v = 0;
    writeTile(getTile(edgeTileset, cv::Point(1, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    u = 4, v = 0;
    writeTile(getTile(edgeTileset, cv::Point(1, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    u = 5, v = 0;
    writeTile(getTile(edgeTileset, cv::Point(1, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 6, v = 0;
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 2));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));


    u = 0, v = 1;
    writeTile(getTile(edgeTileset, cv::Point(0, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(0, 4)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 2));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    writeTile(getTile(edgeTileset, cv::Point(5, 4)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 2));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 1, v = 1;
    writeTile(getTile(edgeTileset, cv::Point(0, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(1, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(0, 4)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 2));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    u = 2, v = 1;
    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 3, v = 1;
    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    u = 4, v = 1;

    u = 5, v = 1;
    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    
    u = 6, v = 1;
    writeTile(getTile(edgeTileset, cv::Point(5, 4)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 2));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));


    u = 0, v = 2;
    writeTile(getTile(edgeTileset, cv::Point(0, 4)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 2));
    writeTile(getTile(edgeTileset, cv::Point(0, 7)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 1, v = 2;
    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 2, v = 2;
    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    u = 3, v = 2;
    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));

    u = 4, v = 2;

    u = 5, v = 2;
    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 6, v = 2;
    writeTile(getTile(edgeTileset, cv::Point(5, 4)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 2));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));


    u = 0, v = 3;
    writeTile(getTile(edgeTileset, cv::Point(0, 4)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 2));
    writeTile(getTile(edgeTileset, cv::Point(0, 7)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    u = 1, v = 3;
    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    u = 2, v = 3;
    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 3, v = 3;
    writeTile(getTile(edgeTileset, cv::Point(1, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 4, v = 3;
    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 5, v = 3;
    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 6, v = 3;
    writeTile(getTile(edgeTileset, cv::Point(5, 4)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 2));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));


    u = 0, v = 4;
    writeTile(getTile(edgeTileset, cv::Point(0, 4)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 2));
    writeTile(getTile(edgeTileset, cv::Point(0, 7)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    u = 1, v = 4;

    u = 2, v = 4;
    writeTile(getTile(edgeTileset, cv::Point(5, 4)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 2));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 3, v = 4;
    writeTile(getTile(edgeTileset, cv::Point(0, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(1, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(0, 4)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 2));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 4, v = 4;
    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 2));

    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));

    u = 5, v = 4;
    writeTile(getTile(edgeTileset, cv::Point(0, 4)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 2));
    writeTile(getTile(edgeTileset, cv::Point(0, 7)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    writeTile(getTile(edgeTileset, cv::Point(5, 4)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 2));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 6, v = 4;
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 7)), outputTileset, cv::Point(u, v), cv::Point(0, 2));

    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 2));

    writeTile(getTile(edgeTileset, cv::Point(0, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));


    u = 0, v = 5;
    writeTile(getTile(edgeTileset, cv::Point(0, 4)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 2));
    writeTile(getTile(edgeTileset, cv::Point(0, 7)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 1, v = 5;
    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));

    u = 2, v = 5;
    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 3, v = 5;
    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 2)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 4, v = 5;
    writeTile(getTile(edgeTileset, cv::Point(1, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(1, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 5, v = 5;
    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 2)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    u = 6, v = 5;
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(5, 4)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 2));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 3));


    u = 0, v = 6;
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 7)), outputTileset, cv::Point(u, v), cv::Point(0, 2));

    writeTile(getTile(edgeTileset, cv::Point(0, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(1, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    u = 1, v = 6;
    writeTile(getTile(edgeTileset, cv::Point(1, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));

    u = 2, v = 6;
    writeTile(getTile(edgeTileset, cv::Point(1, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    u = 3, v = 6;
    writeTile(getTile(edgeTileset, cv::Point(1, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    writeTile(getTile(edgeTileset, cv::Point(3, 0)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 0)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    u = 4, v = 6;
    writeTile(getTile(edgeTileset, cv::Point(2, 3)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(3, 3)), outputTileset, cv::Point(u, v), cv::Point(1, 0));
    writeTile(getTile(edgeTileset, cv::Point(4, 3)), outputTileset, cv::Point(u, v), cv::Point(2, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 3)), outputTileset, cv::Point(u, v), cv::Point(3, 0));

    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 2));

    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 5, v = 6;
    writeTile(getTile(edgeTileset, cv::Point(0, 5)), outputTileset, cv::Point(u, v), cv::Point(0, 0));
    writeTile(getTile(edgeTileset, cv::Point(0, 6)), outputTileset, cv::Point(u, v), cv::Point(0, 1));
    writeTile(getTile(edgeTileset, cv::Point(0, 7)), outputTileset, cv::Point(u, v), cv::Point(0, 2));

    writeTile(getTile(edgeTileset, cv::Point(0, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(1, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    u = 6, v = 6;
    writeTile(getTile(edgeTileset, cv::Point(5, 5)), outputTileset, cv::Point(u, v), cv::Point(3, 0));
    writeTile(getTile(edgeTileset, cv::Point(5, 6)), outputTileset, cv::Point(u, v), cv::Point(3, 1));
    writeTile(getTile(edgeTileset, cv::Point(5, 7)), outputTileset, cv::Point(u, v), cv::Point(3, 2));

    writeTile(getTile(edgeTileset, cv::Point(2, 8)), outputTileset, cv::Point(u, v), cv::Point(0, 3));
    writeTile(getTile(edgeTileset, cv::Point(3, 8)), outputTileset, cv::Point(u, v), cv::Point(1, 3));
    writeTile(getTile(edgeTileset, cv::Point(4, 8)), outputTileset, cv::Point(u, v), cv::Point(2, 3));
    writeTile(getTile(edgeTileset, cv::Point(5, 8)), outputTileset, cv::Point(u, v), cv::Point(3, 3));

    /*std::string outputPath = "D:\\source\\repos\\Assets\\Sprites\\MT_Terrains_Lite_1.0\\EXTRAS\\" + baseOffset.x;
    outputPath += baseOffset.y;
    outputPath += ".png";*/
    cv::imwrite("D:\\source\\repos\\Assets\\Sprites\\MT_Terrains_Lite_1.0\\EXTRAS\\image.png", outputTileset);

    cv::namedWindow("Display Image", cv::WINDOW_KEEPRATIO);
    cv::imshow("Display Image", outputTileset);
    cv::waitKey(0);
}

cv::Mat TileExtractor::getTile(cv::Mat input, cv::Point offset, cv::Point coordinates)
{
    cv::Mat tile;

    input(cv::Rect((offset.x + coordinates.x) * tileSize, (offset.y + coordinates.y) * tileSize, tileSize, tileSize)).copyTo(tile);

    return tile;
}

cv::Mat TileExtractor::getTile(cv::Mat input, cv::Point coordinates)
{
    cv::Mat tile;

    input(cv::Rect(coordinates.x * tileSize, coordinates.y * tileSize, tileSize, tileSize)).copyTo(tile);

    return tile;
}

void TileExtractor::writeTile(cv::Mat input, cv::Mat& output, cv::Point offset, cv::Point coordinates)
{
    input.copyTo(output(cv::Rect((offset.x * 4 + coordinates.x) * tileSize, (offset.y * 4 + coordinates.y) * tileSize, tileSize, tileSize)));
}
