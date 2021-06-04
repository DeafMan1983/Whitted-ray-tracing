# Whitted-ray-tracing
We implemented Turner Whitted's 1980 research paper(https://www.cs.drexel.edu/~david/Classes/Papers/p343-whitted.pdf) using C++

<h2>Turner-Whitted Ray tracing - breakthrough</h2>
<h3>What is Ray tracing?</h3>
<p>Ray tracing is a rendering technique for generating an image by tracing the path of light
as pixels in an image plane and simulating the effects of its encounters with virtual objects.
Whitted style ray-tracing is one of the most classical examples of light transport models based on ray tracing.</p>



<h3>What did he achieve?</h3>
<p>Before Whitted's paper,
most programs were already capable of simulating the look of diffuse and specular surfaces.
The famous Phong illumination model was already known.
*Though, simulating complex reflections and refractions was yet to be done.* </p>
<p>**Whitted proposed to use ray-tracing to solve this problem**. His technique got a lot of success because it allowed to simulate photo-realistic reflections and refractions for the first time </p>
<p>Whitted proposed to use known optical laws to compute the reflection and refraction direction of rays
as they intersect reflective or transparent surfaces, and follow the path of these rays to find out the color
of the object they would intersect. </p>
@section propose What did he propose?
<h2>When a ray intersects an object, there are three possible cases</h2>
<ol>
    <li>Case 1: if the surface at the intersection point is opaque and diffuse, we use Phong's Illumination Model
    to cast a ray in the direction of each light in the scene to find if the point is in shadow.</li>
    <li>Case 2: If the surface is a mirror like surface, we simply trace another reflection ray at the intersection point.</li>
    <li>Case 3: if the surface is a transparent surface, we then cast another reflection and a refraction ray at the intersection point.</li>
</ol>
>h2>References</h2>
<ol>
    <li>[An Improved Illumination Model for Shaded Display ](https://www.cs.drexel.edu/~david/Classes/Papers/p343-whitted.pdf)</li>
    <li>[An Overview of the Ray-Tracing Rendering Technique](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/light-transport-ray-tracing-whitted)</li>
    <li>[Whitted ray tracing explanation](https://cglab.gist.ac.kr/courses/2017_spring_CG/2017_05_17_Whitted_Ray_Tracing.pdf)</li>
    <li>[Path tracing](http://www.kevinbeason.com/smallpt/)</li>
</ol>
<ul>
 <li>
Output at 40 spp
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/sky40.jpeg" alt="drawing" width="500" /><br><br></li>

 
 <li>
Output at 500 spp
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/sky500.jpeg" alt="drawing" width="500"/><br><br>
  </li>

 <li>
Output at 40 spp
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/explicit.jpg" alt="drawing" width="500" /><br><br></li>
 <li>
Output at 500 spp
<img src="https://github.com/saloni-singh14/Whitted-ray-tracing/blob/main/doc_images/explicit%20(1).jpg" alt="drawing" width="500" /><br><br></li>
