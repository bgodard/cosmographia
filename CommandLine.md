# Introduction #

Cosmographia maybe launched from the command line with a list of arguments. The command lines is a list of catalog filenames and switches.

# Switches #

The only switch supported now is -u, which is used to supply a [state URL](StateUrl.md) that will be activated at start time.

```
cosmographia -u "cosmo:Dawn?frame=icrf&jd=2455803.595868&x=-0.007808&y=0.010616&z=-0.007165&qw=0.053027&qx=-0.572807&qy=0.640473&qz=0.508798&ts=1&fov=50"
```

# Files #

Any command line argument that is not a switch is treated as a catalog file to be loaded at start time. Catalog files may be either Cosmographia JSON files or SSC files from Celestia. The catalog files are loaded in the same order they are given on the command line.

This example command line will launch Cosmographia and load two extra catalog files:
```
cosmographia pluto-system.json newhorizons.json
```

All catalog files are loaded _before_ any state URL parameter, so a URL may refer to a body defined in one of the catalog files given on the command line.

