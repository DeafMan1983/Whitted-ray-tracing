#include <math.h>  // smallpt, a Path Tracer by Kevin Beason, 2009
#include <stdlib.h>  // Make : g++ -O3 -fopenmp explicit.cpp -o explicit 
#include <stdio.h>   //        Remove "-fopenmp" for g++ version < 4.2 
/*
  or if you want to use static SDL3 g++ -O3 explicit.cpp -o explicit -Wl,-Bstatic -lSDL3 -Wl,-Bdynamic -lm
  or if you want to use dynamic SDL3 g++ -O3 explicit.cpp -o explicit -lm $(pkg-config --cflags --libs sdl3)
*/
#include <random>
#include <string>
#include <iostream>
#include <filesystem>
#include <SDL3/SDL.h>

std::default_random_engine generator;
std::uniform_real_distribution<double> distr(0.0, 1.0);
double srand(short unsigned int *X)
{
  return distr(generator);
}

class Vec
{
public:
  // Usage: time ./explicit 16 && xv image.ppm
  double x, y, z; // position, also color (r,g,b)
  Vec(double x_ = 0, double y_ = 0, double z_ = 0)
  {
    x = x_;
    y = y_;
    z = z_;
  }

  Vec operator+(const Vec &b) const
  {
    return Vec(x + b.x, y + b.y, z + b.z);
  }

  Vec operator-(const Vec &b) const
  {
    return Vec(x - b.x, y - b.y, z - b.z);
  }

  Vec operator*(double b) const
  {
    return Vec(x *b, y *b, z *b);
  }

  Vec mult(const Vec &b) const
  {
    return Vec(x *b.x, y *b.y, z *b.z);
  }

  Vec &norm()
  {
    return *this = *this *(1 / sqrt(x *x + y *y + z *z));
  }

  double dot(const Vec &b) const
  {
    return x *b.x + y *b.y + z *b.z;
  } // cross:
  Vec operator%(Vec & b)
  {
    return Vec(y *b.z - z *b.y, z *b.x - x *b.z, x *b.y - y *b.x);
  }
};
class Ray
{
public:
  Vec o, d;
  Ray(Vec o_, Vec d_): o(o_), d(d_) {}
};
enum Refl_t
{
  DIFF, SPEC, REFR
};  // material types, used in radiance()
class Sphere
{
public:
    double rad; // radius
    Vec p, e, c;  // position, emission, color
    Refl_t refl;  // reflection type (DIFFuse, SPECular, REFRactive)
    bool hasTexture; // Flag to indicate if the sphere has a texture

    Sphere(double rad_, Vec p_, Vec e_, Vec c_, Refl_t refl_, bool hasTexture_ = false)
    {
        rad = rad_;
        p = p_;
        e = e_;
        c = c_;
        refl = refl_;
        hasTexture = hasTexture_; // Initialize texture flag
    }

    double intersect(const Ray &r) const
    {
        // returns distance, 0 if nohit
        Vec op = p - r.o; // Solve t^2*d.d + 2*t*(o-p).d + (o-p).(o-p)-R^2 = 0
        double t, eps = 1e-4,
               b = op.dot(r.d),
               det = b * b - op.dot(op) + rad * rad;
        if (det < 0) return 0;
        else det = sqrt(det);
        return (t = b - det) > eps ? t : ((t = b + det) > eps ? t : 0);
    }
};
//Island:
/*Vec Cen(50, -20, -860);
Sphere spheres[] = {  //Scene: radius, position, emission, color, material
  // center 50 40.8 62
  // floor 0
  // back  0
  //     rad       pos                   emis           col     refl

  Sphere(160, Cen + Vec(0, 600, -500), Vec(1, 1, 1) *2e2, Vec(), DIFF), // sun
  Sphere(800, Cen + Vec(0, -880, -9120), Vec(1, 1, 1) *2e1, Vec(), DIFF), // horizon
  Sphere(10000, Cen + Vec(0, 0, -200), Vec(0.0627, 0.188, 0.569) *1e0, Vec(1, 1, 1) *.4, DIFF), // sky

  //  Sphere(1000, Cen+Vec(0,-1080,-8020),Vec(1,1,1)*2e1, Vec(),  DIFF),  // horizon
  //  Sphere(10000,Cen+Vec(0,0,-200), Vec(0.0627, 0.188, 0.569)*1e0, Vec(1,1,1)*.3,  DIFF), // sky

  Sphere(800, Cen+Vec(0,-720,-200),Vec(),  Vec(0, 0.588, 0.8),  REFR),  // water
  Sphere(800, Cen+Vec(0,-720,-200),Vec(),  Vec(0.106, 0.725, 0.949),  REFR),  // water
  Sphere(800, Cen+Vec(0,-720,-200),Vec(),  Vec(0.110, 0.988, 0.945),  REFR),  // water
  Sphere(800, Cen + Vec(0, -720, -200), Vec(), Vec(0.110, 0.898, 1.00) *.996, REFR),  // water
  Sphere(790, Cen + Vec(0, -720, -200), Vec(), Vec(.4, .3, .04) *.6, DIFF), // earth
  Sphere(325, Cen + Vec(0, -255, -50), Vec(), Vec(.4, .3, .04) *.8, DIFF),  // island
  Sphere(275, Cen + Vec(0, -205, -33), Vec(), Vec(.02, .3, .02) *.75, DIFF),  // grass
};*/
//Cornell Box
Sphere spheres[] = {//Scene: radius, position, emission, color, material
  Sphere(1e5, Vec(1e5+1,40.8,81.6), Vec(),Vec(.75,.25,.25),DIFF, true),//Left red textured
  Sphere(1e5, Vec(-1e5+99,40.8,81.6),Vec(),Vec(.25,.25,.75),DIFF, true),//Rght blue textured
  Sphere(1e5, Vec(50,40.8, 1e5),     Vec(),Vec(.25,.75,.25),DIFF, true),//Back green textured
  Sphere(1e5, Vec(50,40.8,-1e5+170), Vec(),Vec(),           DIFF, false),//Frnt black
  Sphere(1e5, Vec(50, 1e5, 81.6),    Vec(),Vec(.75,.75,.75),DIFF, false),//Botm
  Sphere(1e5, Vec(50,-1e5+81.6,81.6),Vec(),Vec(.75,.75,.75),DIFF, false),//Top
  Sphere(16.5,Vec(27,16.5,47),       Vec(),Vec(1,1,1)*.999, SPEC, false),//Mirr
  Sphere(16.5,Vec(73,16.5,78),       Vec(),Vec(1,1,1)*.999, REFR, false),//Glas
  Sphere(1.5, Vec(50,81.6-16.5,81.6),Vec(4,4,4)*75,  Vec(), DIFF, false),//Light White
  Sphere(1.5, Vec(50,81.6-10.5,80.6),Vec(10,0,0)*100,  Vec(), DIFF, false),//Light Red
  Sphere(1.5, Vec(45,81.6-13.5,80.6),Vec(4,2,0)*100,  Vec(), DIFF, false),//Light orange
};
int numSpheres = sizeof(spheres) / sizeof(Sphere);
inline double clamp(double x)
{
  return x < 0 ? 0 : x > 1 ? 1 : x;
}

inline int toInt(double x)
{
  return int(pow(clamp(x), 1 / 2.2) *255 + .5);
}

inline bool intersect(const Ray &r, double &t, int &id)
{
  double n = sizeof(spheres) / sizeof(Sphere), d, inf = t = 1e20;
  for (int i = int(n); i--;)
    if ((d = spheres[i].intersect(r)) && d < t)
    {
      t = d;
      id = i;
    }

  return t < inf;
}

Vec generateCheckerboard(const Vec& pos, const Vec& normal, const Vec& baseColor, double scale = 1.0)
{
    // Determine the dominant axis of the normal
    double absX = std::abs(normal.x);
    double absY = std::abs(normal.y);
    double absZ = std::abs(normal.z);

    // Use the two non-dominant axes for texture coordinates
    int u, v;
    if (absX > absY && absX > absZ)
    {
        // Normal is mostly aligned with the X-axis: use Y and Z for texture coordinates
        u = static_cast<int>(std::floor(pos.y * scale));
        v = static_cast<int>(std::floor(pos.z * scale));
    }
    else if (absY > absX && absY > absZ)
    {
        // Normal is mostly aligned with the Y-axis: use X and Z for texture coordinates
        u = static_cast<int>(std::floor(pos.x * scale));
        v = static_cast<int>(std::floor(pos.z * scale));
    }
    else
    {
        // Normal is mostly aligned with the Z-axis: use X and Y for texture coordinates
        u = static_cast<int>(std::floor(pos.x * scale));
        v = static_cast<int>(std::floor(pos.y * scale));
    }

    // Alternate colors based on the sum of u and v
    Vec checkerColor;
    if ((u + v) % 2 == 0)
    {
        checkerColor = Vec(0.9, 0.9, 0.9); // Light color
    }
    else
    {
        checkerColor = Vec(0.1, 0.1, 0.1); // Dark color
    }

    // Multiply the checkerboard color by the base color
    return checkerColor.mult(baseColor);
}

Vec radiance(const Ray &r, int depth, unsigned short *Xi, int E = 1)
{
    double t; // distance to intersection
    int id = 0; // id of intersected object
    if (!intersect(r, t, id)) return Vec(); // if miss, return black
    const Sphere &obj = spheres[id];  // the hit object
    Vec x = r.o + r.d * t; // Intersection point
    Vec n = (x - obj.p).norm(); // Normal at intersection
    Vec nl = n.dot(r.d) < 0 ? n : n * -1; // Correct normal orientation
    Vec f = obj.c; // Base color of the object

    // Check if the object is the back wall and apply the checkerboard texture
    if (obj.hasTexture) // Assuming the back wall is the 3rd sphere in the array (index 2)
    {
        f = generateCheckerboard(x, n, obj.c, 0.1); // Apply checkerboard texture
    }

    double p = f.x > f.y && f.x > f.z ? f.x : f.y > f.z ? f.y : f.z;  // max refl
    if (++depth > 5 || !p)
    {
        if (srand(Xi) < p)
        {
            f = f * (1 / p);
        }
        else
        {
            return obj.e * E;
        }
    }

    // Rest of the radiance function remains the same
    if (obj.refl == DIFF)
    {
        // Ideal DIFFUSE reflection
        double r1 = 2 * M_PI * srand(Xi),
               r2 = srand(Xi),
               r2s = sqrt(r2);
        Vec w = nl,
            u = ((fabs(w.x) > .1 ? Vec(0, 1) : Vec(1)) % w).norm(),
            v = w % u;
        Vec d = (u * cos(r1) * r2s + v * sin(r1) * r2s + w * sqrt(1 - r2)).norm();

        // Loop over any lights
        Vec e;
        for (int i = 0; i < numSpheres; i++)
        {
            const Sphere &s = spheres[i];
            if (s.e.x <= 0 && s.e.y <= 0 && s.e.z <= 0) continue; // skip non-lights

            Vec sw = s.p - x, su = ((fabs(sw.x) > .1 ? Vec(0, 1) : Vec(1)) % sw).norm(), sv = sw % su;
            double cos_a_max = sqrt(1 - s.rad * s.rad / (x - s.p).dot(x - s.p));
            double eps1 = srand(Xi), eps2 = srand(Xi);
            double cos_a = 1 - eps1 + eps1 * cos_a_max;
            double sin_a = sqrt(1 - cos_a * cos_a);
            double phi = 2 * M_PI * eps2;
            Vec l = su * cos(phi) * sin_a + sv * sin(phi) * sin_a + sw * cos_a;
            l.norm();
            if (intersect(Ray(x, l), t, id) && id == i)
            {
                // shadow ray
                double omega = 2 * M_PI * (1 - cos_a_max);
                e = e + f.mult(s.e * l.dot(nl) * omega) * M_1_PI;  // 1/pi for brdf
            }
        }

        return obj.e * E + e + f.mult(radiance(Ray(x, d), depth, Xi, 0));
    }
    else if (obj.refl == SPEC)  // Ideal SPECULAR reflection
    {
        return obj.e + f.mult(radiance(Ray(x, r.d - n * 2 * n.dot(r.d)), depth, Xi));
    }
    else  // Ideal dielectric REFRACTION
    {
        Ray reflRay(x, r.d - n * 2 * n.dot(r.d)); // Ideal dielectric REFRACTION
        bool into = n.dot(nl) > 0;  // Ray from outside going in?
        double nc = 1, nt = 1.5, nnt = into ? nc / nt : nt / nc, ddn = r.d.dot(nl), cos2t;
        if ((cos2t = 1 - nnt * nnt * (1 - ddn * ddn)) < 0) // Total internal reflection
        {
            return obj.e + f.mult(radiance(reflRay, depth, Xi));
        }
        Vec tdir = (r.d * nnt - n * ((into ? 1 : -1) * (ddn * nnt + sqrt(cos2t)))).norm();
        double a = nt - nc, b = nt + nc, R0 = a * a / (b * b), c = 1 - (into ? -ddn : tdir.dot(n));
        double Re = R0 + (1 - R0) * c * c * c * c * c, Tr = 1 - Re, P = .25 + .5 * Re, RP = Re / P, TP = Tr / (1 - P);
        return obj.e + f.mult(depth > 2 ? (srand(Xi) < P ?  // Russian roulette
                                               radiance(reflRay, depth, Xi) * RP
                                                       : radiance(Ray(x, tdir), depth, Xi) * TP)
                                     : radiance(reflRay, depth, Xi) * Re + radiance(Ray(x, tdir), depth, Xi) * Tr);
    }
}

std::string generateUniqueFilename(const std::string& baseName, const std::string& extension)
{
    std::string filename = baseName + extension;
    int counter = 1;

    // Check if the file already exists
    while (std::filesystem::exists(filename))
    {
        filename = baseName + "_" + std::to_string(counter) + extension;
        counter++;
    }

    return filename;
}

int main(int argc, char *argv[])
{
  int w = 1024, h = 768, samps = argc == 2 ? atoi(argv[1]) / 8 : 64;  // # samples
  SDL_Init(SDL_INIT_VIDEO);

  uint32_t* pixels = new uint32_t[w * h * 3];
  Ray cam(Vec(50, 52, 295.6), Vec(0, -0.042612, -1).norm());  // cam pos, dir
  Vec cx = Vec(w *.5135 / h), cy = (cx % cam.d).norm() * -.5135, r, *c = new Vec[w *h];
  for (int y = 0; y < h; y++)
  {
    fprintf(stderr, "\rRasterizing (%d spp) %5.2f%% \n", samps, 100. * y / (h - 1));
    for (int x = 0; x < w; x++)
    {
      Vec r;
      unsigned short Xi[3] = {0, 0, (unsigned short)(y * y * y)};
      for (int s = 0; s < samps; s++)
      {
        double offsetX = srand(Xi) - 0.5;  // Random jitter between -0.5 and +0.5
        double offsetY = srand(Xi) - 0.5;
        Vec d = cx * ((x + 0.5 + offsetX) / w - 0.5) + cy * ((y + 0.5 + offsetY) / h - 0.5) + cam.d;
        r = r + radiance(Ray(cam.o + d * 140, d.norm()), 0, Xi) * (1.0 / samps);
      }
      c[y * w + x] = Vec(clamp(r.x), clamp(r.y), clamp(r.z));
      Uint8 r8 = toInt(c[y * w + x].x);
      Uint8 g8 = toInt(c[y * w + x].y);
      Uint8 b8 = toInt(c[y * w + x].z);
      pixels[y * w + x] = (r8 << 16) | (g8 << 8) | b8;
    }
  }

  SDL_Window* window = SDL_CreateWindow("Ray Tracing", w, h, 0);
  SDL_Renderer* renderer = SDL_CreateRenderer(window, "software");
  SDL_Texture* texture = SDL_CreateTexture(renderer, SDL_PIXELFORMAT_XRGB8888, SDL_TEXTUREACCESS_STREAMING, w, h);

  SDL_UpdateTexture(texture, NULL, pixels, w * 4);
  SDL_Event e;
  bool running = true;

  while (running)
  {
      while (SDL_PollEvent(&e))
      {
          if (e.type == SDL_EVENT_QUIT || e.type == SDL_EVENT_KEY_DOWN && e.key.key == SDLK_ESCAPE) running = false;
      }
      
      SDL_RenderClear(renderer);
      SDL_RenderTexture(renderer, texture, NULL, NULL);
      SDL_RenderPresent(renderer);
  }

  SDL_Surface* surface = SDL_CreateSurfaceFrom(w, h, SDL_PIXELFORMAT_XRGB8888, pixels, w * sizeof(uint32_t));
  if (!surface)
  {
      std::cerr << "Failed to create SDL surface: " << SDL_GetError() << std::endl;
      return 1;
  }

  // Generate a unique filename
  std::string filename = generateUniqueFilename("./output", ".bmp");

  // Save the surface as a BMP file
  if (SDL_SaveBMP(surface, filename.c_str()) != 0)
  {
      std::cerr << "Failed to save BMP: " << SDL_GetError() << std::endl;
  }
  else
  {
      std::cout << "Image saved as " << filename << std::endl;
  }

  SDL_DestroySurface(surface);
  delete[] pixels;
  delete[] c;
  SDL_DestroyTexture(texture);
  SDL_DestroyRenderer(renderer);
  SDL_DestroyWindow(window);
  SDL_Quit();
  return 0;
}
