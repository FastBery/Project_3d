#pragma once
#include "structs.h"
#include "Tree/functions.h"
#define STB_IMAGE_IMPLEMENTATION
#include "Tree/Tree_project2.cpp"
#include "Tree/ray.h"
#include "Tree/vec3.h"
#include "stb_image.h"
#include <optional>

color background;
vec3 light;

struct texture{
	color *map;
	int w, h, n;
};

texture loadtexture(const char *texturefile){
	int ok, w, h, n;
	ok = stbi_info(texturefile, &w, &h, &n);
	unsigned char* image = stbi_load(texturefile, &w, &h, &n, STBI_rgb_alpha);
	return {reinterpret_cast<color *>(image), w, h, n};
}

color getcolor(int w, int h, texture colors){
	return colors.map[w * colors.w + h];
}

color shade(Ray r, Tree box, color pxcolor){
	intersection sect = coordinate_of_intersection(box, r, i);
	if(sect == std::nullopt){
		return background;
	}

	vec3 AC = sect.tr.a - sect.tr.c;
	vec3 BC = sect.tr.b - sect.tr.c;
	vec3 a = AC * sect.tr.a;
	vec3 b = BC * sect.tr.b;
	float lc = length(sect.tr.c - sect.position);
	float lb = length(sect.position - sect.tr.a - sect.tr.b);
	float la = length(sect.position - sect.tr.a - sect.tr.b);

	vec3 norm = (sect.tr.n1 * la + sect.face.B.norm * lb + sect.face.C.norm * lc) / (la + lb + lc);
	ray shadow = {sect.position, normalize(light - sectpos)};

	intersection shadowray = coordinate_of_intersection(box, shadow, i);

	float brightness = happened(shadowray.i) ? 0 : std::max(0.f, dot(norm, sect.position - light));
	color lightcolor = {1, 1, 1};

	return(pxcolor * (lightcolor * brightness + background * 0.3));
}