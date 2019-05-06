In this version we refactored the main loop into a game manager with corresponding component. The (non-component) classes of Paddle and Ball are removed.

Note that in this version we don't use dynamic memory at all (except those in the basic framework such as audio, textures, etc.)
