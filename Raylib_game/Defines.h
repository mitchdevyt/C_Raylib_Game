#ifndef DEFINES_H
#define DEFINES_H

#if defined(PLATFORM_DESKTOP)
#define GLSL_VERSION            330
#else   // PLATFORM_RPI, PLATFORM_ANDROID, PLATFORM_WEB
#define GLSL_VERSION            100
#endif

#define SCREEN_WIDTH 1280
#define SCREEN_HEIGHT 720

#endif