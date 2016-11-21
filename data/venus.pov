#version 3.7;
#include "colors.inc"

global_settings{ assumed_gamma 1.0 }

#declare WorldTrans = transform {
  // ...
}

// BBOX: <-117.788398, -161.255094, -92.027669>, <117.788397, 161.255094, 92.027669>
camera {
  //orthographic
  location <0.000000, 0.000000, -742.142321>
  look_at <0, 0, 0>
}

light_source {
  <0.0, 742.142321, -1484.284643>
  color White
}
#include "venus.inc"
object {
  MODEL
  transform { WorldTrans }
  pigment{ color rgb <0.55,0.55,0.55> }
}
