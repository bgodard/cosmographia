# Introduction #

Particle systems can be used to represent a wide range of phenomena:
  * Rocket engine exhaust
  * Smoke
  * Explosions
  * Volcanoes and geysers
  * Aurora

A particle system consists of one or more particle _emitters_. Each emitter has a _generator_ that determines the initial positions and velocities of the randomly generated particles. Other emitter properties specify how long each particle persists after it is generated and the appearance of the particle over its lifetime. The particle size changes from startSize to endSize, and the color and opacity is interpolated between the values in the colors list.

Example of a ParticleSystem geometry definition:

```
"geometry" :
{
    "type" : "ParticleSystem",
    "emitters" :
    [
      {
        "texture" : "gaussian.jpg",
        "generator" :
        {
          "type" : "Point",
          "velocity" : [ 0, 0, 0.1 ]
        },
        "velocityVariation" : 2.5,
        "force" : [ 0, 0, 0 ],
        "spawnRate" : 100,
        "lifetime" : 10.0,
        "startSize" : 0.0,
        "endSize" : 5.0,
        "colors" : [ "#10eeff", 0.6, "blue", 0.0 ],
        "endTime" : 3451545.0
      }
   ]
}
```

# Emitter Properties #

  * texture
  * generator
  * velocityVariation - magnitude of random variations in initial particle velocity
  * force - constant force affecting all particles (typically set to the local direction of gravity)
  * spawnRate - the number of particles emitted per second
  * lifetime - the lifetime of a particle in seconds
  * startSize - size of particles when they are generated (in kilometers)
  * endSize - the size of particles at the end of their lifetimes
  * colors - a list of color and opacity values
  * startTime - date when the first particle is emitted (default is 1 Jan 2000)
  * endTime - date when the last particle is emitted

As with all dates in catalog files, the startTime and endTime may be given as Julian Dates or ISO 8601 date strings (e.g. "2011-03-15T15:36:14")

# Generators #

## Point ##

## Box ##

## Disc ##