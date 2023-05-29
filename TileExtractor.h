﻿// TileExtractor.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <opencv2/opencv.hpp>

class TileExtractor
{
private:
    const unsigned int tileSize = 16;
    const unsigned int baseTilesetWidth = 6;
    const unsigned int baseTilesetHeight = 9;
    const unsigned int overlayTilesetWidth = 6;
    const unsigned int overlayTilesetHeight = 15;
    cv::Mat base;
    cv::Mat overlay;
    cv::Mat output;
    cv::Point baseOffset;
    cv::Point overlayOffset;
    cv::Mat getTile(cv::Mat input, cv::Point offset, cv::Point coordinates);
    void writeTile(cv::Mat input, cv::Mat& output, cv::Point offset, cv::Point coordinates);
public:
    TileExtractor(cv::Mat Base, cv::Mat Overlay);
};

// TODO: Reference additional headers your program requires here.