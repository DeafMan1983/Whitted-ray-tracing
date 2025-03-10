# Whitted-ray-tracing
We implemented Turner Whitted's 1980 research paper(https://www.cs.drexel.edu/~david/Classes/Papers/p343-whitted.pdf) using C++

# Updated adding some:
- SDL3
- Support texture rasterization
- Support embedded color into texture
- Save to bmp
- Remove ppm because I worked on SDL3 :)

<h2>Turner-Whitted Ray tracing - breakthrough</h2>

<p>Before Whitted's paper,
most programs were already capable of simulating the look of diffuse and specular surfaces.
The famous Phong illumination model was already known.
    <b>Though, simulating complex reflections and refractions was yet to be done.</b> </p>


<h2>What did he propose?</h2>
<p><b>Whitted proposed to use ray-tracing to solve this problem</b>. His technique got a lot of success because it allowed to simulate photo-realistic reflections and refractions for the first time </p>
<h3>When a ray intersects an object, there are three possible cases</h3>
<ul>
    <li>Case 1: if the surface at the intersection point is opaque and diffuse, we use Phong's Illumination Model
    to cast a ray in the direction of each light in the scene to find if the point is in shadow.</li>
    <li>Case 2: If the surface is a mirror like surface, we simply trace another reflection ray at the intersection point.</li>
    <li>Case 3: if the surface is a transparent surface, we then cast another reflection and a refraction ray at the intersection point.</li>
</ul>
<p>Whitted proposed to use known optical laws to compute the reflection and refraction direction of rays
as they intersect reflective or transparent surfaces, and follow the path of these rays to find out the color
of the object they would intersect. </p>
<h2>Implementation</h2>
<ul>
    <li><p>Recursion: Each time a ray intersects a transparent surface, two new rays are generated (a reflection and a refraction ray).
If these rays intersect another transparent object, each ray will generate two more rays. This is simulated through recursion.
 to improve the efficiency of the algorithm, the maximum allowed depth of recursion is specified(maxdepth=5 in our code).</p></li>
    <li><p>Backward Tracing: Whitted's algorithm uses backward tracing to simulate reflection and refraction.</p>
<p>Let us consider three spheres P1, P2, and p3.
If P1 generates a secondary ray that intersects P2 and that another secondary ray is generated at P2
that intersects another object at P3, then the color at P3 becomes the color of P2 which in turn becomes the color of P1
    (assuming P1 and P2 belong to mirror like surfaces)</p></li>
<h2>Output and timing analysis</h2>
<p>Given below is the different outputs we got. We have produced the output for different samples per pixel,
    and the time taken for rendering for each with an <b>Intel i7 processor</b></p>
<p>spp: samples per pixel</p>
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;40 spp: 79 secs&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;500 spp: 812 secs</p>
<p float="left">

<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/sky40.jpeg" alt="drawing" width="350" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/sky500.jpeg" alt="drawing" width="350"/>
</p>
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;40 spp: 63 secs&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;500 spp: 709 secs</p>
<p float="left">
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/explicit.jpg?raw=true" alt="drawing" width="350" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/explicit%20(1).jpg?raw=true" alt="drawing" width="350" />
</p>
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;40 spp: 32 secs&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;500 spp: 556 seconds</p>
<p float="left">
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/wada4spp.jpg?raw=true" alt="drawing" width="350" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/wada40.jpg?raw=true" alt="drawing" width="350" />
</p>
<p>&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;40 spp: 85 seconds&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;500 spp: 1115 seconds</p>
<p float="left">
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/nightsky4.jpg?raw=true" alt="drawing" width="350" />
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/nightsky500.jpg?raw=true" alt="drawing" width="350" />
</p>
<h2>References</h2>
<ol>
    <li><a href="https://www.cs.drexel.edu/~david/Classes/Papers/p343-whitted.pdf">An Improved Illumination Model for Shaded Display</a></li>
    <li><a href="https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/light-transport-ray-tracing-whitted">An Overview of the Ray-Tracing Rendering Technique</a></li>
    <li><a href="https://cglab.gist.ac.kr/courses/2017_spring_CG/2017_05_17_Whitted_Ray_Tracing.pdf">Whitted ray tracing explanation</a></li>
    <li><a href="http://www.kevinbeason.com/smallpt/">Path tracing</a></li>
</ol>
