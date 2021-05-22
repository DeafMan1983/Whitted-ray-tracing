@page features Important features
@tableofcontents
@section hhhhh Salient features of Whitted Ray-tracing
@subsection f1 Recursivity
Each time a ray intersects a transparent surface, two new rays are generated (a reflection and a refraction ray).
If these rays intersect another transparent object, each ray will generate two more rays. This is simulated through recursion.
 to improve the efficiency of the algorithm, the maximum allowed depth of recursion is specified(maxdepth=5 in our code).

 <img src="recursive.png" alt="drawing" width="250" />
@subsection f2 Trees of rays
<p>All the secondary rays spawned by either the primary ray itself or other secondary rays can be represented as a tree.</p>
<p>Each level in the tree as you go down, corresponds to one level of recursion.</p>
<br><img src="tree.png" alt="drawing" width="250" />
@subsection f3  Backward Tracing
<p> Whitted's algorithm uses backward tracing to simulate reflection and refraction.</p>
<p>Let us consider three spheres P1, P2, and p3.
If P1 generates a secondary ray that intersects P2 and that another secondary ray is generated at P2
that intersects another object at P3, then the color at P3 becomes the color of P2 which in turn becomes the color of P1
(assuming P1 and P2 belong to mirror like surfaces)</p>
<img src="rt-reflection2.gif" alt="drawing" width="250" />
