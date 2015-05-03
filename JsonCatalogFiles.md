# Introduction #

Cosmographia's native catalog files are stored in JSON (JavaScript Object Notation.) The very simple syntax of JSON is described at http://www.json.org/

# Example #

Here's a complete catalog file containing a single object.

```
{
     "version": "1.0",
     "name": "Cassini Solstice Mission",

     "items" :
     [
      	{
          "name" : "Cassini",
          "center" : "Saturn",
          "trajectoryFrame" : "EclipticJ2000",
          "trajectory" :
          {
              "type" : "InterpolatedStates",
              "source" : "cassini-solstice.xyzv"
          },
          "geometry" :
          {
              "type" : "Mesh",
              "size" : "5m",
              "source" : "models/cassini.obj"
          }
        }
    ]
}
```

# Units #

Many numeric properties can be written as strings with a unit suffix. The default units are assumed when the suffix is omitted (such as when the value of the property as a floating point literal.)

Examples:

```
    semiMajorAxis : 1.52098e8
    semiMajorAxis : "1.52098e8 km"
    semiMajorAxis : "1 au"
```

# Dates #

Dates may be specified as Julian day numbers or as ISO 8601 date and time strings. Some examples:
  * "2000-01-01 12:00:00"
  * 2451545.0 _(Julian day number representing the above date)_
  * "2011-03-11" _(time may be omitted indicating midnight on the given date)_

Dates are by default interpreted in the TDB time system; as of 2014, this is 67 seconds ahead of UTC. To specify a date in UTC, the date string may be suffixed with 'UTC', e.g. "2014-01-21 10:12:00 UTC". The suffix 'TDB' is also valid in a date string; while it doesn't alter the default behavior, it may be added to clarify that that the time system in use is TDB.

# Catalog File Properties #

  * version - version number of the catalog file (always 1.0 for now)
  * name - name of the catalog
  * require - a list of other catalog files that must be loaded first
  * items - an array of catalog file objects (for now, bodies and visualizers)

## require ##

```
   "require" :
    [
        "sun.json",
        "mercury.json",
        "venus.json",
        "earth.json"
    ]
```

The catalog files in the require list will be loaded in the specified order. Files that have already been loaded will not be loaded again. The files in the require list will be loaded from the same directory as the current catalog file.

# Body properties #

A body is identified by setting the value of type to "body"; this is the value assumed when the type isn't listed, so it may be omitted.

  * name
  * center - name of the center object; the position of the body is defined relative to the center object
  * trajectoryFrame - reference frame for position
  * bodyFrame - reference frame for orientation
  * trajectory - describes the position of the object over time
  * rotationModel - describes the orientation of the object over time

**Note:** The center, frames, trajectory, and rotation model collectively comprise an _arc_. If more than one arc is required, use the _arcs_ property to provide a list of them.

The default values for arc properties are:
  * trajectoryFrame and bodyFrame - ICRF (International Celestial Reference Frame)
  * trajectory - FixedPoint, at the origin
  * rotationModel - Fixed, identity rotation

# Geometry types #

## Mesh ##

```
 "geometry" :
{
     "type" : "Mesh",
      "size" : "4.2 km",
      "source" : "models/asteroid.3ds",
      "meshRotation" : [ 1, 0, 0, 0 ],
      "meshOffset" : [ 0, 0, 0 ]
}
```

The size of the mesh can be specified in two ways. If the _size_ property is present, the mesh will be scaled to fit into a sphere of that radius. Otherwise, the size of the mesh is determined by the coordinates of the vertices in the mesh file. If the _scale_ property is present, the mesh's coordinates will be scaled by that factor. If the units of the mesh file are meters, the value of _scale_ should be 0.001.

meshRotation can be used to orient a mesh with respect to its coordinate system. The value of the meshRotation is a quaternion, given as an array of four numbers in the order w, x, y, z. In the above example, the meshRotation is the default value, identity, indicating no rotation.

meshOffset moves the mesh with respect to the local origin defined by the reference frame and trajectory. This is useful when the mesh geometry isn't centered at the desired point, and you need to reposition it without editing the mesh file.

## Globe ##

  * radius
  * radii - 3-vector; may be provided instead of radius for non-spherical bodies
  * baseMap - texture (may be tiled)
  * normalMap
  * cloudMap - texture (may be tiled)
  * specularPower - float
  * specularColor - color
  * emissive - boolean

```
"geometry" :
{
    "type" : "Globe",
    "radius" : 3389,
    "baseMap" : "textures/mars.jpg"
}
```

## Axes ##

## Sensor ##

```
"geometry" :
{
    "type" : "Sensor",
    "range" : 10000,
    "shape" : "elliptical",
    "horizontalFov" : 5,
    "verticalFov" : 3,
    "frustumColor" : "#00ffff",
    "frustumBaseColor" : "#ffffff",
    "frustumOpacity" : 0.3,
    "gridOpacity" : 0.3
}
```

## KeplerianSwarm ##

This is a specialized geometry type used for representing large numbers of points in Keplerian orbits. The only data file format currently supported is _astorb_, which is used for Ted Bowell's minor planet catalogs and described completely at http://www.naic.edu/~nolan/astorb.html

```
"geometry" :
{
    "type" : "KeplerianSwarm",
    "format" : "astorb",
    "source" : "astorb.dat",
    "particleSize" : 1.0,
    "color" : "#aa8855",
    "opacity" : 0.5
}
```

## ParticleSystem ##

An example is given below, but check the separate [Particle Systems](ParticleSystem.md) page.

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

# Trajectory Types #

## Fixed Point ##

```
"trajectory" :
{
    "type" : "FixedPoint",
    "position" : [ 0.1, 0.2, 0.3 ]
}
```

A FixedPoint trajectory specifies a fixed position within the trajectory frame. The components of position are in kilometers.

## Fixed Spherical ##

```
    "type" : "FixedSpherical",
    "latitude" :  47.5,
    "longitude" : -122.5,
    "radius" : 6378.3
```

Similar to FixedPoint, a FixedSpherical trajectory specifies a constant position within the body's reference frame. Latitude and longitude are given in degrees, and radius has default units of kilometers. All three values must be provided.

Note that FixedSpherical has no notion of the IAU defined planetographic coordinate systems. It works as expected for placing objects on the surfaces of planets except for retrograde rotators, where north and south are reversed.

## Keplerian ##

```
"trajectory" :
{
    "type"                : "Keplerian",
    "epoch"               : 2455387.5,
    "period"              : "3.801940080524025 y",
    "semiMajorAxis"       : "2.435929475203178 au",
    "eccentricity"        : 0.1628635085186526,
    "inclination"         : 3.063744992999521,
    "ascendingNode"       : 80.89993758667205,
    "argumentOfPeriapsis" : 250.1880363237300,
    "meanAnomaly"         : 230.6845245681190
}
```

## Builtin ##

```
"trajectory" :
{
    "type" : "Builtin",
    "name" : "Mars"
}
```

## Interpolated States ##

Trajectory given by a list of time-tagged state vectors stored in a separate file. See the InterpolatedStates page for details on state vector files.

```
"trajectory" :
{
    "type" : "InterpolatedStates",
    "source" : "cassini-solstice.xyzv"
}
```


## Chebyshev Polynomials ##

Trajectory is loaded from a binary data file containing Chebyshev polynomial coefficients.

```
"trajectory" :
{
    "type": "ChebyshevPoly",
    "source": "saturn.cheb"
}
```


## Linear Combination ##

A linear combination trajectory is the weighted sum of two other trajectories. It is used in Cosmographia's default Solar System files convert barycentric orbit definitions to planet-centered.

```
"trajectory" :
{
    "type" : "LinearCombination",
    "period" : "2.736915552552733d",
    "weights" : [ 1.0, -1.0 ],
    "trajectories" : [
        {
            "type": "ChebyshevPoly",
            "source": "dione.cheb"
        },
        {
            "type": "ChebyshevPoly",
            "source": "saturn.cheb"
        }
    ]
}
```

## TLE ##

```
"trajectory" :
{
    "type" : "TLE",
    "name" : "ISS (ZARYA)",
    "line1" : "1 25544U 98067A   11042.40620627  .00065760  00000-0  48638-3 0  8024",
    "line2" : "2 25544  51.6440  85.8998 0004217 288.1282 194.3117 15.72311137701100",
    "source" : "http://celestrak.com/NORAD/elements/visual.txt"
}
```

# Rotation Model Types #

## Fixed ##

Defines a rotation that doesn't change over time (within the object's body frame). The orientation is specified as a quaternion. For hand-edited catalog files, it is generally easier to use the FixedEuler rotation model.

```
"rotationModel" :
{
    "type" : "Fixed",
    "quaternion" : [ 0.73305, -0.68017, 0.0, 0.0 ]
}
```

## FixedEuler ##

A fixed rotation built from a sequence of rotations about the principal axes.

  * sequence - string with a list of principal axes identifiers. Axes may be given as x, y, z or 1, 2, and 3. For example "zxz" and "313" represent the same sequence.
  * angles - array of angles (in degrees). The length of this array must match the length of the sequence string.

The example below rotates an object in the Earth-fixed frame so that it is aligned with Earth's magnetic
axis:

```
"rotationModel" :
{
    "type": "FixedEuler",
    "sequence": "zy",
    "angles" : [ 287.781, 9.985 ]
}
```

## Builtin ##

```
"rotationModel" :
{
    "type" : "Builtin",
    "name" : "IAU Moon"
}
```

## Uniform ##

```
"rotationModel" :
{
    "type" : "Uniform",
    "period" : 6.387206,
    "inclination" : 115.60,
    "ascendingNode" : 228.34,
    "meridianAngle" : 320.75,
    "epoch": "2001-05-26T19:30:00"
}
```

The only required property is period. The angle properties all default to zero, and the default epoch is J2000.0.

## Interpolated ##

```
"rotationModel" :
{
    "type" : "Interpolated",
    "source" : "attitude.q"
}
```

  * source - name of a file containing a list of time-tagged quaternions representing orientations
  * compatibility - if set to the string "celestia", the quaternions are converted to Celestia's conventions for orientation.

# Frame Types #

## Inertial ##

Built-in inertial frames can be specified by providing the name of the frame:
```
"trajectoryFrame" : "EclipticJ2000"
```

They can also be specified using the slightly more verbose obect syntax:
```
"trajectoryFrame" : { "type": "EclipticJ2000" }
```

The second syntax is more consistent with the style used for describing non-inertial frames.

The available inertial frames are:
  * ICRF (the default)
  * EquatorJ2000 (commonly called EME2000 elsewhere)
  * EclipticJ2000
  * EquatorB1950

## BodyFixed ##

```
"bodyFrame" :
{
    "type" : "BodyFixed",
    "body" : "CubeSat"
}
```

## TwoVector ##

```
"bodyFrame" :
{
    "type" : "TwoVector",
    "primaryAxis" : "x",
    "primary" :
    {
        "type" : "RelativePosition",
        "observer" : "CubeSat",
        "target" : "Ceres"
    },
    "secondaryAxis" : "-y",
    "secondary" :
    {
        "type" : "RelativeVelocity",
        "observer" : "CubeSat",
        "target" : "Ceres"
    }
}
```

# Arcs #

The arcs property can be used to create bodies with complex trajectories with multiple reference frames. For example, a rocket may defined with two arcs: one pre-launch arc, where it is at a fixed position in an Earth-fixed frame, and a flight arc where the trajectory is given in an inertial frame.

```
{
    "name" : "Huygens",

    "startTime" : "1997-10-15 09:27",

    "arcs" : [
       {
         "center" : "Cassini",
         "trajectoryFrame" : { "type" : "BodyFixed", "body" : "Cassini" },
         "trajectory" : { "type" : "FixedPoint", "position" : [ 0, 0, 0 ] },
         "bodyFrame" : { "type" : "BodyFixed", "body" : "Cassini" },
         "endTime" : "2004-12-25 02:01:05"
        },

        {
          "center" : "Titan",
          "trajectoryFrame" : "EclipticJ2000",
          "trajectory" : {
            "type" : "InterpolatedStates",
            "source" : "cassini-solstice.xyzv"
          },
          "bodyFrame" : "EclipticJ2000",
          "rotationModel" : {
            "type" : "Interpolated",
            "source" : "huygens-attitude.q"
          }
          "endTime" : "2005-01-14 09:07:00",
        }
    ],
          
     "geometry" :
     {
         "type" : "Mesh",
         "size" : "1m",
         "source" : "models/huygens.obj"
     }
}
```

# Label Properties #

  * color - the color of the label (defaults to white)
  * fadeSize - controls the distance at which the label is hidden

Example:
```
"label" :
{
    "color" : "#ff0000"
}
```

Cosmographia automatically hides some labels in order to avoid drawing too much clutter onscreen. For example, the labels for moons are not shown when the camera is positioned far away from the planet they orbit. The default fadeSize for an object is the approximate radius of a sphere that contains its trajectory. To delay fading, set fadeSize to a value larger than the objects mean distance to its central body.


# Trajectory Plot Properties #

It is possible to control the appearance of the plot of a body's trajectory.

  * color - the color of the plot (defaults to the label color)
  * duration - time window over which to plot the trajectory (in units of days)
  * lead - amount of time ahead of the current time to start the plot (units of days, defaults to zero)
  * fade - a value between 0 and 100 giving the fraction of the orbit over which the fade from opaqe to transparent occurs; defaults to 0, indicating no fading

Example:
```
"trajectoryPlot" :
{
    "color" : "#00ff00",
    "duration" : 0.5,
    "fade" : 0.5,
     "lead" : 0.1
}
```