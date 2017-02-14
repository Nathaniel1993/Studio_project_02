#ifndef WEAPON_H
#define WEAPON_H

class Weapon
{
public:
	//Constructor & Destructor
	Weapon();
	~Weapon();
	//Functions
	int getAttackDMG();

protected:
	int kAttackDMG;
};

#endif // !WEAPON_H
