
#include "../Inc/struct.h"
#include "../Inc/NoiseGenerator.h"
#include "../Inc/ChunkSection.h"
#include <cmath>

NoiseGenerator::NoiseGenerator()
{
    noiseParams.octaves = 7;
    noiseParams.amplitude = 70;
    noiseParams.smoothness = 235;
    noiseParams.heightOffset = -5;
    noiseParams.roughness = 0.53;
}

void NoiseGenerator::setSeed(int newSeed){
    this->seed = newSeed;
}

void NoiseGenerator::setParameters(const NoiseParameters &params)
{
    noiseParams = params;
}

double NoiseGenerator::getNoise(int n)
{
    n += seed;
    n = (n << 13) ^ n;
    auto newN = (n * (n * n * 60493 + 19990303) + 1376312589) & 0x7fffffff;

    return 1.0 - ((double)newN / 1073741824.0);
}

double NoiseGenerator::getNoise(double x, double z)
{
    return getNoise(x + z * 57.0);
}

double NoiseGenerator::lerp(double a, double b, double z)
{
    double mu2 = (1 - std::cos(z * 3.14)) / 2;
    return (a * (1 - mu2) + b * mu2);
}

double NoiseGenerator::noise(double x, double z)
{
    auto floorX = (double)((int)x); // This is kinda a cheap way to floor a double integer.
    auto floorZ = (double)((int)z);

    auto s = 0.0, t = 0.0, u = 0.0,
         v = 0.0; // Integer declaration

    s = getNoise(floorX, floorZ);
    t = getNoise(floorX + 1, floorZ);
    u = getNoise(
        floorX,
        floorZ + 1); // Get the surrounding values to calculate the transition.
    v = getNoise(floorX + 1, floorZ + 1);

    auto rec1 = lerp(s, t, x - floorX); // Interpolate between the values.
    auto rec2 = lerp(
        u, v,
        x - floorX); // Here we use x-floorX, to get 1st dimension. Don't mind
                     // the x-floorX thing, it's part of the cosine formula.
    auto rec3 =
        lerp(rec1, rec2,
             z - floorZ); // Here we use y-floorZ, to get the 2nd dimension.
    return rec3;
}

double NoiseGenerator::getHeight(int x, int z, int chunkX, int chunkZ)
{
    auto newX = (x + (chunkX * CHUNK_SIZE));
    auto newZ = (z + (chunkZ * CHUNK_SIZE));

    if (newX < 0) {
        newX = -newX;
    }
    if(newZ < 0){
        newZ = -newZ;
    }

    auto totalValue = 0.0;

    for (auto a = 0; a < noiseParams.octaves - 1;
         a++) // This loops through the octaves.
    {
        auto frequency = pow(
            2.0,
            a); // This increases the frequency with every loop of the octave.
        auto amplitude = pow(
            noiseParams.roughness,
            a); // This decreases the amplitude with every loop of the octave.
        totalValue +=
            noise(((double)newX) * frequency / noiseParams.smoothness,
                  ((double)newZ) * frequency / noiseParams.smoothness) *
            amplitude;
    }

    auto val = (((totalValue / 2.1) + 1.2) * noiseParams.amplitude) +
               noiseParams.heightOffset;

    return val > 0 ? val : 1;
}
