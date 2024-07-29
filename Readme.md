<h1>Smooth Game of Life Simulation</h1>
<div align="center">
<a href="https://isocpp.org/"><img src="https://img.shields.io/badge/Made%20with-C%2B%2B-00599C?style=for-the-badge&logo=c%2B%2B" alt="Made with C++"></a>
<br>
<img src="https://img.shields.io/badge/contributions-welcome-brightgreen.svg?style=flat" alt="Contributions welcome">
<a href="https://github.com/yourusername/gameoflife-simulation/graphs/commit-activity"><img src="https://img.shields.io/badge/Maintained%3F-yes-green.svg" alt="Maintenance"></a>
<a href="https://opensource.org/licenses/MIT"><img src="https://img.shields.io/badge/License-MIT-blue.svg" alt="License: MIT"></a>
</div>

<h2>Demo</h2>

https://github.com/user-attachments/assets/0b7f68f5-4c87-404e-a8ff-fb904fdc002b
<hr>

<h2>🚀 Features</h2>
<ul>
<li>Real-time simulation of Smooth Conway's Game of Life</li>
<li>Parallel computation using SYCL oneAPI for optimal performance</li>
<li>Visualization using SDL2 and SDL2_image</li>
</ul>

<h2>🏗️ Project Structure</h2>
<pre>
Game of Life Simulation
├── 📄 Makefile
├── 📁 bin/
├── 📁 include/
│   ├── sdl_utils.hpp
│   ├── constant.hpp
│   └── game_of_life.hpp
├── 📁 src/
│   ├── main.cpp
│   ├── sdl_utils.cpp
│   └── game_of_life.cpp
├── 📁 images/
└── 📘 Readme.md
</pre>

<h2>🛠️ Technologies</h2>
<ul>
<li>C++</li>
<li>SYCL oneAPI</li>
<li>SDL2 and SDL2_image</li>
</ul>

<h2>📋 Prerequisites</h2>
<ul>
<li>Intel oneAPI DPC++/C++ Compiler (icpx)</li>
<li>SYCL-compatible runtime</li>
<li>SDL2 and SDL2_image development libraries</li>
<li>Make build automation tool</li>
<li>pkg-config</li>
</ul>

<h2>🛠️ Setting Up the Environment</h2>

<h3>1. Intel oneAPI DPC++/C++ Compiler</h3>
<p>To obtain and set up the Intel oneAPI DPC++/C++ Compiler:</p>
<ol>
<li>Visit the <a href="https://www.intel.com/content/www/us/en/developer/tools/oneapi/base-toolkit-download.html">Intel oneAPI Base Toolkit download page</a></li>
<li>Download and install the toolkit for your operating system</li>
<li>Set up the environment variables by running the following command in your terminal:
<pre><code>source /opt/intel/oneapi/setvars.sh</code></pre>
(Note: The exact path may vary depending on your installation location)
</li>
</ol>

<h3>2. SDL2 and SDL2_image Libraries</h3>
<p>To install SDL2 and SDL2_image development libraries:</p>

<h4>On Ubuntu/Debian:</h4>
<pre><code>sudo apt-get update
sudo apt-get install libsdl2-dev libsdl2-image-dev</code></pre>

<h4>On macOS (using Homebrew):</h4>
<pre><code>brew install sdl2 sdl2_image</code></pre>

<h4>On Windows:</h4>
<p>Download the development libraries for both SDL2 and SDL2_image from their respective websites and set up your project to include and link against these libraries.</p>

<h2>🚀 Building and Running the Project</h2>
<ol>
<li>Clone the repository:
<pre><code>git clone https://github.com/yourusername/gameoflife-simulation.git
cd gameoflife-simulation</code></pre>
</li>
<li>Ensure you have set up the Intel oneAPI environment:
<pre><code>source /opt/intel/oneapi/setvars.sh</code></pre>
</li>
<li>Build the project:
<pre><code>make</code></pre>
</li>
<li>Run the simulation:
<pre><code>./gameOfLife</code></pre>
</li>
</ol>

<h2>⚙️ Customizing the Build</h2>
<p>The Makefile is set up to use the Intel oneAPI compiler (icpx) with SYCL support. Key compilation flags include:</p>
<pre><code>CXX = icpx
CXXFLAGS = -fsycl -O3 -g $(shell sdl2-config --cflags) $(shell pkg-config --libs SDL2_image) -I include
LDFLAGS = -fsycl $(shell sdl2-config --libs) $(shell pkg-config --libs SDL2_image) -lm
</code></pre>
<p>These flags enable SYCL support, optimization, debugging symbols, and link against the necessary SDL2 and SDL2_image libraries.</p>

<h2>Ressources</h2>
<ul>
<li><a href="https://en.wikipedia.org/wiki/Conway%27s_Game_of_Life">Conway's Game of Life</a></li>
<li><a href="https://arxiv.org/abs/1111.1567">Conway's Smooth Game of Life</a></li>
<li><a href="https://www.intel.com/content/www/us/en/developer/tools/oneapi/overview.html">Intel oneAPI Toolkit</a></li>
<li><a href="https://www.libsdl.org/">SDL2 Library</a></li>
</ul>
