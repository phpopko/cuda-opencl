typedef struct {
    float x, y, z;
    float vx, vy, vz;
} Particle;

__kernel void simulate(__global Particle *particles,
                       const unsigned int count,
                       const float dt,
                       const float gravity)
{
    unsigned int i = get_global_id(0);
    if (i >= count) return;

    Particle p = particles[i];

    p.vx += 0.0f * dt;
    p.vy += gravity * dt;
    p.vz += 0.0f * dt;

    p.x += p.vx * dt;
    p.y += p.vy * dt;
    p.z += p.vz * dt;

    particles[i] = p;
}
