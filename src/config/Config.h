#pragma once

#include <type_traits>

// Global configuration for InfiniMap
struct Config
{
    // Map resolution
    static constexpr int MapWidth  = 2048;
    static constexpr int MapHeight = 2048;

    // Noise parameters
    static constexpr float NoiseScale       = 0.55f;  // Controls feature size
    static constexpr float NoiseFloor       = 0.272f; // Remap from
    static constexpr float NoiseCeil        = 0.714f; // Remap to
    static constexpr int   NoiseOctaves     = 5;
    static constexpr float NoiseLacunarity  = 2.0f;
    static constexpr float NoisePersistence = 0.6f;
    static constexpr float NoiseBaseFreq    = 0.002f; // Base frequency for fBm

    // Blur
    static constexpr int BlurRadius = 1;

    // Color biomes
    static constexpr float SeaLevel       = 0.30f;
    static constexpr float BeachEnd       = 0.32f;
    static constexpr float PlainsEnd      = 0.50f;
    static constexpr float ForestEnd      = 0.65f;
    static constexpr float MountainEnd    = 0.80f;

    // View defaults
    static constexpr int WindowWidth  = 1600;
    static constexpr int WindowHeight = 900;

    // Zoom controls
    static constexpr double ZoomInFactor  = 1.25;
    static constexpr double ZoomOutFactor = 1.0 / 1.25;
    static constexpr double MinZoomScale  = 0.1;
    static constexpr double MaxZoomScale  = 10.0;

    // Blur settings
    static constexpr float BlurSigmaDivisor = 3.0f; // sigma = radius / divisor

};

// Compile-time validation using static_assert
// Map dimensions must be positive and reasonable
static_assert(Config::MapWidth > 0 && Config::MapWidth <= 8192, "MapWidth must be between 1 and 8192");
static_assert(Config::MapHeight > 0 && Config::MapHeight <= 8192, "MapHeight must be between 1 and 8192");

// Noise parameters validation
static_assert(Config::NoiseOctaves >= 1 && Config::NoiseOctaves <= 12, "NoiseOctaves must be between 1 and 12");
static_assert(Config::NoisePersistence > 0.0f && Config::NoisePersistence <= 1.0f, "NoisePersistence must be in (0, 1]");
static_assert(Config::NoiseLacunarity >= 1.1f && Config::NoiseLacunarity <= 10.0f, "NoiseLacunarity must be in [1.1, 10]");
static_assert(Config::NoiseBaseFreq > 0.0f && Config::NoiseBaseFreq < 1.0f, "NoiseBaseFreq must be in (0, 1)");
static_assert(Config::NoiseFloor >= 0.0f && Config::NoiseFloor < Config::NoiseCeil, "NoiseFloor must be >= 0 and < NoiseCeil");
static_assert(Config::NoiseCeil > Config::NoiseFloor && Config::NoiseCeil <= 1.0f, "NoiseCeil must be > NoiseFloor and <= 1");

// Blur validation
static_assert(Config::BlurRadius >= 0 && Config::BlurRadius <= 10, "BlurRadius must be between 0 and 10");
static_assert(Config::BlurSigmaDivisor > 0.0f && Config::BlurSigmaDivisor <= 10.0f, "BlurSigmaDivisor must be in (0, 10]");

// Biome levels must be in ascending order within [0, 1]
static_assert(Config::SeaLevel >= 0.0f && Config::SeaLevel <= 1.0f, "SeaLevel must be in [0, 1]");
static_assert(Config::BeachEnd > Config::SeaLevel && Config::BeachEnd <= 1.0f, "BeachEnd must be > SeaLevel and <= 1");
static_assert(Config::PlainsEnd > Config::BeachEnd && Config::PlainsEnd <= 1.0f, "PlainsEnd must be > BeachEnd and <= 1");
static_assert(Config::ForestEnd > Config::PlainsEnd && Config::ForestEnd <= 1.0f, "ForestEnd must be > PlainsEnd and <= 1");
static_assert(Config::MountainEnd > Config::ForestEnd && Config::MountainEnd <= 1.0f, "MountainEnd must be > ForestEnd and <= 1");

// Window dimensions
static_assert(Config::WindowWidth >= 640 && Config::WindowWidth <= 3840, "WindowWidth must be between 640 and 3840");
static_assert(Config::WindowHeight >= 480 && Config::WindowHeight <= 2160, "WindowHeight must be between 480 and 2160");

// Zoom parameters
static_assert(Config::MinZoomScale > 0.0 && Config::MinZoomScale < 1.0, "MinZoomScale must be in (0, 1)");
static_assert(Config::MaxZoomScale > 1.0 && Config::MaxZoomScale <= 100.0, "MaxZoomScale must be in (1, 100]");
static_assert(Config::MinZoomScale < Config::MaxZoomScale, "MinZoomScale must be < MaxZoomScale");
static_assert(Config::ZoomInFactor > 1.0 && Config::ZoomInFactor <= 2.0, "ZoomInFactor must be in (1, 2]");
static_assert(Config::ZoomOutFactor > 0.5 && Config::ZoomOutFactor < 1.0, "ZoomOutFactor must be in (0.5, 1)");
