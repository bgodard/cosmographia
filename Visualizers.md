# Introduction #

A visualizer is some bit of geometry that can be attached to body. A visualizer is distinct from an ordinary object in that it represents something other than the true shape of an object, such coordinate axes or a label.

# Visualizer Types #

## BodyAxes ##

## FrameAxes ##

## BodyDirection ##

BodyDirection is an arrow that points to some other object.

## Plane ##

```
{
      "type" : "Visualizer",
      "tag" : "equatorial plane",
      "body" : "Earth",
      "style" :
      {
          "type" : "Plane",
          "size" : 20000,
          "color" : "#99ffff",
          "frame" : "EclipticJ2000",
          "gridSubdivision" : 20
      }
}
```