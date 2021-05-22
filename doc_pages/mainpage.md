@mainpage Introduction
@tableofcontents
@section s1 Turner-Whitted Ray tracing - breakthrough
@subsection w1 Ray tracing
Ray tracing is a rendering technique for generating an image by tracing the path of light
as pixels in an image plane and simulating the effects of its encounters with virtual objects.
Whitted style ray-tracing is one of the most classical examples of light transport models based on ray tracing.
@subsection w3 Need for simulating complex reflections and refractions
<ol>
    <li>If an object A is a mirror like surface, and that an object B seats on top of it,
    then we would like to see the reflection of B into A, as seen in the image below</li>
     <li> Mirror surfaces keep reflecting images
    of themselves causing the "infinity room" effect which is often seen in films.</li>
    <li> We should see though transparent surfaces.
    We should also see material such as water or glass bend light rays due to the phenomenon of refraction. </li>

</ol>
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="cat'.png" alt="drawing" width="200" />&nbsp;&nbsp;&nbsp;&nbsp;<img src="rt-whitted.png" alt="drawing" width="200" />

@subsection w2 What did he achieve?
&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;&nbsp;<img src="Whitted.jpg" alt="drawing" width="150" style="vertical-align:top"/>
<p>Before Whitted's paper,
most programs were already capable of simulating the look of diffuse and specular surfaces.
The famous Phong illumination model was already known.
*Though, simulating complex reflections and refractions was yet to be done.* </p>
<p>**Whitted proposed to use ray-tracing to solve this problem**. His technique got a lot of success because it allowed to simulate photo-realistic reflections and refractions for the first time </p>
<h3>Some known optical laws </h3>
<ol>
<li>The reflection direction only depends on the surface
    orientation and the incoming light direction.</li>
    <li>The refraction direction can be computed using Snell's law and depends on the surface orientation (the surface's normal),
    the incoming light direction and the material refractive index (around 1.3 for water and 1.5 for glass).</li>
</ol>
<p>Whitted proposed to use these laws to compute the reflection and refraction direction of rays
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
@section references References
<ol>
    <li>[An Improved Illumination Model for Shaded Display ](https://www.cs.drexel.edu/~david/Classes/Papers/p343-whitted.pdf)</li>
    <li>[An Overview of the Ray-Tracing Rendering Technique](https://www.scratchapixel.com/lessons/3d-basic-rendering/ray-tracing-overview/light-transport-ray-tracing-whitted)</li>
    <li>[Whitted ray tracing explanation](https://cglab.gist.ac.kr/courses/2017_spring_CG/2017_05_17_Whitted_Ray_Tracing.pdf)</li>
    <li>[Path tracing](http://www.kevinbeason.com/smallpt/)</li>
</ol>
