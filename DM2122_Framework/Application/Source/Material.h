#ifndef MATERIAL_H
#define MATERIAL_H

struct Component
{
	float r, g, b;
	Component(float r = 0.1f, float g = 0.1f, float b = 0.1f)
	{
		Set(r, g, b);
	}
	void Set(float r, float g, float b)
	{
		this->r = r; this->g = g; this->b = b;
	}

};
struct Material
{
	Component kAmbient;
	Component kDiffuse;
	Component kSpecular;
	float kShininess;
	//to do: add a constructor
	Material()
	{
		kAmbient.Set(0.15f, 0.15f, 0.15f); //color of the darkness
		kDiffuse.Set(0.7f, 0.7f, 0.7f);
		kSpecular.Set(0.7f, 0.7f, 0.7f); // light color
		kShininess = 5.f;

	}
};

#endif