#ifndef NOISEGENERATOR_H_INCLUDED
#define NOISEGENERATOR_H_INCLUDED

#include"struct.h"

class NoiseGenerator {
  public:
    NoiseGenerator();

    double getHeight(int x, int z, int chunkX, int chunkZ);

    void setParameters(const NoiseParameters &params);

    void setSeed(int);

  private:
    double getNoise(int n);
    double getNoise(double x, double z);

    double lerp(double a, double b, double z);

    double noise(double x, double z);

    NoiseParameters noiseParams;

    int seed;
};

#endif // NOISEGENERATOR_H_INCLUDED
