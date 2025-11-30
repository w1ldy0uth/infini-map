#ifndef CONFIG_H
#define CONFIG_H
#pragma once

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

    // Blur
    static constexpr int BlurRadius = 1;

    // Color biomes
    static constexpr float SeaLevel       = 0.30f; // Ocean cutoff
    static constexpr float BeachEnd       = 0.32f;
    static constexpr float PlainsEnd      = 0.50f;
    static constexpr float ForestEnd      = 0.65f;
    static constexpr float MountainEnd    = 0.80f;

    // Random seed
    static constexpr int DefaultSeed = 1234;

    // View defaults
    static constexpr int WindowWidth  = 1600;
    static constexpr int WindowHeight = 900;
};

#endif
