#include <vector>
#include "Particle.h"

class Physics
{
private:

public:
    std::vector<Particle> particles;
    void update(float dt);

    void addParticle(Particle p);
};