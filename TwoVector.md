# Introduction #

The coordinate axes of a two-vector frame are determined by a primary and secondary direction vectors. The vectors must both be non-zero and they must not be exactly aligned.

# Direction Vectors #

The direction vectors may be one of three types:
  * RelativePosition
  * RelativeVelocity
  * ConstantVector

# Examples #

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