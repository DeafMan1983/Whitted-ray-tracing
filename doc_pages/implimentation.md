@page implementation Implementation of Whitted ray tracing
@tableofcontents
@section bvhghvhg Code explanation
We have implemented the main features given by Turner-Whitted in his 1979 paper. We used C++.
<p>The output is written onto a .ppm file</p>


@subsection main Main Function
In the main() function we have looped through all the pixels <br>
we casted ray from every pixel to get the colour of every pixel and called the radiance() function.<br>
We have then looped through the pixels to write in the ppm file <br>

<img src="ray1.png" alt="drawing" width="150" /><br>

@subsection radiance Radiance Function
We recursively increase the depth at each call till we reach a specified maximum depth.
In our code, the maximum depth is 5.
 After that the function will not be recursively called.
In the radiance() function  we check whether they intersect() with the sphere.<br>
We check which type of object this is.<br>
There are three types of Materials we have used <br>
	1.Dielectircs<br>
	2.Specular <br>
	3.Diffuse<br>
If the material is Specular it is metallic <br>
If the material is Dielectric we cast two rays reflected ray and the refracted ray <br>
If the material is Diffuse we just cast reflected ray <br>

<img src="shad2-lobe1.png" alt="drawing" width="150" /><br><br>

@subsection phong Phong Illumination Model
We have used the Phong illumination model for Lighting <br>
We have looped over all the lights and cast shadow rays <br>



@subsection intersection Intersection Calculation
In intersect() function we used have calculated the intersection of ray with the sphere.<br>
We have Implemented the following images in the intersection() function.
<img src="raysphereisect1.png" alt="drawing" width="350" /><br><br>
<img src="rayspherecases.png" alt="drawing" width="350" /><br><br>
