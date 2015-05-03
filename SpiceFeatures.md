# Introduction #

Support for JPL's SPICE system in Cosmographia is currently in development

# Building #

At the current time, SPICE support is disabled in the default build. It can be turned on by uncommenting one line in the project file (cosmographia.pro):

```
CONFIG += spice
```

# SPICE Kernels #

The spiceKernels property lists all the kernels required by objects in a Cosmographia catalog file.

Example:
```
"spiceKernels" :
[
     "de421.bsp",
     "sat341.bsp",
     "pck00010.tpc"
]
```

# SPICE Trajectories #

A Cosmographia trajectory may be linked to the position of a SPICE object.

```
"trajectory" :
{
    "type" : "Spice",
    "target" : "Ymir",
    "center" : "Saturn",
    "frame" : "ECLIPJ2000"
}
```

  * The target and center properties may be a recognized SPICE name or a NAIF integer code
  * The frame is a string giving the name of either a built-in inertial frame, or a frame defined in a SPICE frame kernel
  * If the frame is omitted, it defaults to EME J2000

# SPICE Rotation Model #

A Cosmographia rotation model may be linked to a named SPICE frame. At a given instant, the SPICE rotation model will give the rotation that transforms coordinates from _fromFrame_ to _toFrame_. In general, the toFrame should match whatever the body frame of the object is. toFrame defaults to "J2000", which is the same as the default body frame.

```
"rotationModel" :
{
    "type" : "Spice",
    "fromFrame" : "IAU_SATURN",
    "toFrame" : "ECLIPJ2000"
}
```