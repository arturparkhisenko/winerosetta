# Winerosetta Library
[![Build](https://github.com/Lifeisawful/winerosetta/actions/workflows/build.yml/badge.svg)](https://github.com/Lifeisawful/winerosetta/actions/workflows/build.yml)

Winerosetta is a library specifically designed for Apple Silicon, WINE, and the 32-bit versions of World of Warcraft (1.12.1, 2.4.3 and 3.3.5a). It works around the limitations of Rosetta 2 by providing support for certain instructions not natively supported.

## Installation

## With Rosettax87 (FAST!) 

To learn more about Rosettax87 and it's potential performance boost on Apple Silicon click [here](https://github.com/Lifeisawful/rosettax87).

### Running Turtle WoW Under CrossOver

#### Prerequisites

* **CrossOver** (Free Trial is sufficient)
* **Git**, **CMake**, and **sudo** access on your macOS machine

---

1. **Install CrossOver**

   * Download and install CrossOver (the free trial works fine).

2. **Prepare the Turtle WoW client**

   1. Download the **Full Client** from the Turtle WoW website.
   2. Extract it into `~/Desktop/wow/twmoa_1172`.

3. **Set up WineRosetta**

   1. Download `winerosetta.zip` from the [Lifeisawful/winerosetta v1.0.2 release](https://github.com/Lifeisawful/winerosetta/releases/download/v1.0.2/winerosetta.zip).
   2. Extract it.
   3. Copy `winerosetta.dll` into the same folder as `WoW.exe` (`~/Desktop/wow/twmoa_1172/`).
   4. Open `dlls.txt` in that folder and add the line:

      ```txt
      winerosetta.dll
      ```

4. **Build and install RosettaX87**

   1. Open Terminal and navigate to your “wow” folder:

      ```bash
      cd ~/Desktop/wow
      ```
   2. Clone the RosettaX87 repo:

      ```bash
      git clone https://github.com/Lifeisawful/rosettax87.git --recursive
      ```
   3. Enter the repo and configure the build:

      ```bash
      cd rosettax87
      cmake -B build
      ```
   4. Compile:

      ```bash
      cmake --build build
      ```
   5. Run the RosettaX87 helper (you’ll need to enter your password):

      ```bash
      cd build
      sudo ./rosettax87
      ```

5. **Patch and launch via CrossOver**

   1. Open a second Terminal window.
   2. Create a copy of CrossOver’s `wineloader` binary:

      ```bash
      cp /Applications/CrossOver.app/Contents/SharedSupport/CrossOver/CrossOver-Hosted\ Application/wineloader \
         /Applications/CrossOver.app/Contents/SharedSupport/CrossOver/CrossOver-Hosted\ Application/wineloader2
      ```
   3. Strip the code signature from the copy:

      ```bash
      codesign --remove-signature \
         /Applications/CrossOver.app/Contents/SharedSupport/CrossOver/CrossOver-Hosted\ Application/wineloader2
      ```
   4. Navigate back to your Turtle WoW folder:

      ```bash
      cd ~/Desktop/wow/twmoa_1172
      ```
   5. Launch WoW through RosettaX87 and your patched loader:

      ```bash
      ~/Desktop/wow/rosettax87/build/rosettax87 \
        /Applications/CrossOver.app/Contents/SharedSupport/CrossOver/CrossOver-Hosted\ Application/wineloader2 \
        ./wow.exe
      ```

---

> **Tip:** After completing the initial setup, you can relaunch Turtle WoW by repeating step 4.5 and step 5.5.

----

### Running Warmane Under CrossOver

Note: This is likely applicable to TBC.

#### Prerequisites

* **CrossOver** (Free Trial is sufficient)
* **Git**, **CMake**, and **sudo** access on your macOS machine

---

1. **Install CrossOver**

   * Download and install CrossOver (the free trial works fine).

2. **Prepare the Warmane WoW client**

   1. Download the client from the Warmane website
   2. Extract it into `~/Desktop/wow/warmane`.

3. **Set up WineRosetta**

   1. Download `winerosetta.zip` from the [Lifeisawful/winerosetta v1.0.2 release](https://github.com/Lifeisawful/winerosetta/releases/download/v1.0.2/winerosetta.zip).
   2. Extract it.
   3. Copy `winerosetta.dll` into the same folder as `WoW.exe` (`~/Desktop/wow/warmane/`).
   4. Rename `winerosetta.dll` to `d3d9.dll`

4. **Build and install RosettaX87**

   1. Open Terminal and navigate to your “wow” folder:

      ```bash
      cd ~/Desktop/wow
      ```
   2. Clone the RosettaX87 repo:

      ```bash
      git clone https://github.com/Lifeisawful/rosettax87.git --recursive
      ```
   3. Enter the repo and configure the build:

      ```bash
      cd rosettax87
      cmake -B build
      ```
   4. Compile:

      ```bash
      cmake --build build
      ```
   5. Run the RosettaX87 helper (you’ll need to enter your password):

      ```bash
      cd build
      sudo ./rosettax87
      ```

5. **Patch and launch via CrossOver**

   1. Open a second Terminal window.
   2. Create a copy of CrossOver’s `wineloader` binary:

      ```bash
      cp /Applications/CrossOver.app/Contents/SharedSupport/CrossOver/CrossOver-Hosted\ Application/wineloader \
         /Applications/CrossOver.app/Contents/SharedSupport/CrossOver/CrossOver-Hosted\ Application/wineloader2
      ```
   3. Strip the code signature from the copy:

      ```bash
      codesign --remove-signature \
         /Applications/CrossOver.app/Contents/SharedSupport/CrossOver/CrossOver-Hosted\ Application/wineloader2
      ```
   4. Navigate back to your Warmane WoW folder:

      ```bash
      cd ~/Desktop/wow/warmane
      ```
   5. Launch WoW through RosettaX87 and your patched loader:

      ```bash
      WINEDLLOVERRIDES="d3d9=n,b" ~/Desktop/wow/rosettax87/build/rosettax87 \
        /Applications/CrossOver.app/Contents/SharedSupport/CrossOver/CrossOver-Hosted\ Application/wineloader2 \
        ./wow.exe
      ```

---

> **Tip:** After completing the initial setup, you can relaunch Warmane WoW by repeating step 4.v and step 5.v.


## Without Rosettax87 (SLOW!)

### For Turtle-WoW:

1. Download the `winerosetta.dll` from the latest release.
2. Navigate to your Turtle-WoW installation directory.
3. Place `winerosetta.dll` into the folder.
4. Add `winerosetta.dll` into `dlls.txt`

For [Vanilla Fixes](https://github.com/hannesmann/vanillafixes/) 1.4+:

1. Download the `winerosetta.dll` from the latest release.
2. Extract to your WoW installation directory
3. Add `winerosetta.dll` to the `dlls.txt` file:
```
# Known mods for World of Warcraft 1.12
nampower.dll
SuperWoWhook.dll

# Add your own DLLs below
winerosetta.dll
```

----

### 1.12.1 / 2.4.3 / 3.3.5a:

1. Download the `winerosetta.dll` and `winerosettaldr.exe` from the latest release.
2. Navigate to your WoW installation directory.
3. Copy `winerosetta.dll` and `winerosettaldr.exe` here
4. Use `winerosettaldr.exe` to play.


----

# Optional OpenGL Configuration (1.12.1)

To get OpenGL working, you need to modify the `Config.WTF` file with the following settings:

```
SET gxApi "OpenGl"
SET gxColorBits "32"
SET gxDepthBits "32"
```

Then, set the environment variable ```GL_NV_vertex_program``` to ```0```.

Please note that from experience, Direct3D (d3d) tends to work better on M1 Mac.

## License

This project is licensed under the terms of the MIT license. 
