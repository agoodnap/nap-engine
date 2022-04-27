# zzd-engine

This is a very basic 2d engine built with SFML, created for an university assignment.

It can handle keyboard input, rendering sprites, playing audio, and 2D physics with simple AABB collisions.

## Building
You're gonna have to link up SFML, here's a quick little guide:
- Clone this repository
- Open the project with VisualStudio/Rider
- Add {your SFML path}/include to **Additional Include Directories**
- Add {your SFML path}/lib to **Additional Library Directories**
- Add sfml-graphics.lib, sfml-window.lib and sfml-system.lib or their debug-equivalent (depending on your configuration) to **Additional Dependencies**

That should allow you to build the project. Let me know if there's any problem.
