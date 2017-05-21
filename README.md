# OpenHaptics Visual Studio 2017 Example Project

## Introduction

This repository contains a Visual Studio 2017 solution and project aimed to be a starting point for development under Windows. Note that the utility library needs to be recompiled for use with recent versions of Visual Studio. 

Please obtain the new binaries from your course instructor.

## Usage

### Environment Variable

For the example project to build it is needed to add a environment variable (SENSABLE_3DTOUCH_BASE) which points to the install directory of the OpenHaptics SDK (usually C:\Program Files\SensAble\3DTouch). While installing there is already a environment variable created (3DTOUCH_BASE) but it seems to not be working with the Visual Studio macro system.

### Binaries

As mentioned the some binaries, namely the binaries of the utility library, need to be recompiled using the same version of Visual Studio which is used for development. Contact your instructor to obtain the binaries and put them in $(SENSABLE_3DTOUCH_BASE)\utility\lib (or compile them yourself using the source in the SDK).