<p>&nbsp;</p>
<h3 style="text-align: center;"><strong>SPH Fluid Simulation</strong></h3>
<p><img style="display: block; margin-left: auto; margin-right: auto;" src="https://alexnasser.files.wordpress.com/2013/12/fluid1.gif?w=517" alt="" width="412" height="319" /></p>
<p>&nbsp;</p>
<p>The application uses a particle-based solver (Smoothed-particle hydrodynamics) for the Navier-Stokes equation and marching square for rendering purposes. I've written it all in C++ with some C++11 parallelism support.</p>
<p>Particle-based solver:</p>
<p><a href="https://github1s.com/consequencesunintended/SPH-Fluid-Simulation/blob/c6cc073523505225226749a6938f1b0c142ebeaf/fluid/SOURCE/PHYSICS/physics_fluid_sph_viscoelastic.cpp">SPH-Fluid-Simulation/fluid/SOURCE/PHYSICS/physics_fluid_sph_viscoelastic.cpp</a></p>
<p>Marching Squares:</p>
<p><a href="https://github1s.com/consequencesunintended/SPH-Fluid-Simulation/blob/291ff83b3e97945008da062ea958497f4f152aee/fluid/SOURCE/GRAPHICS/graphics_marching_squares.cpp">SPH-Fluid-Simulation/fluid/SOURCE/GRAPHICS/graphics_marching_squares.cpp</a></p>
<p>&nbsp;</p>
<h2>Prerequisites</h2>
<ul>
<li>C++11</li>
<li>Visual Studio 2019</li>
<li>GLFW</li>
</ul>
<h2>Citation</h2>
<h6><span style="color: #999999;"><em>1. Algorithm. (n.d.). Polytech Nice Sophia: Pages personnelles. Retrieved June 9, 2012, from http://users.polytech.unice.fr/~lingrand/MarchingCubes/algo.html</em></span><br /><span style="color: #999999;"><em>2. Auer, S. (2006) Realtime particle-based fluid simulation. Masterthesis in Informatik-Technische Universit&auml;t M&uuml;nchen , https://code.google.com/p/fluid-particles/downloads/list</em></span><br /><span style="color: #999999;"><em>3. Clavet S. , Beaudoin P., Poulin P. (2005) Particle-based viscoelastic fluid simulation. Proceedings of the 2005 ACM SIGGRAPH/Eurographics symposium on Computer animation, http://citeseerx.ist.psu.edu/viewdoc/download?doi=10.1.1.59.9379&amp;rep=rep1&amp;type=pdf, July 29-31, 2005, Los Angeles, California</em></span><br /><span style="color: #999999;"><em>4. Mielack, C. (n.d.). Isosurfaces. Isosurfaces. Retrieved January 11, 2011, from www.zib.de/mielack/isosurfaces.pdf</em></span></h6>
