# C++ Complex Fourier Series Visualizer/SVG Compiler  .version 1.0
## Project Explanation
In simple terms, this project has two modes:
- Compiler: Takes SVG files, and compiles them into a **Spirograph**.
- Viewer: Takes that **Spirograph**, animates it, and displays it through a sfml GUI.

**For Further Studies**, I have a video from YouTube by famous mathematics content creator [@3blue1brown](https://www.youtube.com/@3blue1brown) that explains everything about this project, including what it is, how it works, the math/logic behind it, and all that such. This is also the video from which I got my inspiration.
### - >[But what is a Fourier series? From heat flow to drawing with circles | DE4](https://www.youtube.com/watch?v=r6sGWTCMz2k&list=PLZHQObOWTQDN52m7Y21ePrTbvXkPaWVSg)
##  How to use
Note: all following instructions are designed for Linux systems, if you are using other systems, please only use them as a reference, as the process might be similar
- Make sure you have `sfml`(gui support) and `tinyxml2`(raw info extract) installed.
- In the same folder with the executable file `fourierDrawer`, run the commands:
  - To compile, run `./fourierDrawer c <svg/file/path.svg>`, then at the same folder of the SVG file, a `.dc` file designed to store spirograph should be generated, named by adding `.dc` to the SVG file name.
  - To animate the compiled spirograph, run `./fourierDrawer o <spirograph/file/path.svg.dc>`, then expect a GUI!
## Source File Dependencies
- Spirograph animation/GUI control: [C++ Spirograph Visualizer .version 1.0](https://github.com/tonystdeng/cpp-spirograph-visualizer)
- SVG file information extraction: [C++ Scalable Vector Graphics utilities library .version 1.0](https://github.com/tonystdeng/cpp-svg-utility)

(they are all made by me btw)
 
## Licence
This project is licensed under the GPL License - see the [LICENCE](LICENCE.txt) file for details.
