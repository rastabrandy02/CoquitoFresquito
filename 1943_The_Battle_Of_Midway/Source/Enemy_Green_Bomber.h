#include "Enemy.h"
#include "Path.h"

class Enemy_Green_Bomber : public Enemy
{
public:

	// Constructor (x y coordinates in the world)
	// Creates animation data and the collider
	Enemy_Green_Bomber(int x, int y);

	
	void Update() override;

private:

	int timer = 0;
	int fase[5] = { 0, 240, 300, 440, 500 };
	

	// The enemy animation
	Animation flyAnim;
	Animation downAnim;
	Animation stayAnim;
	Animation upAnim;

	Path path;
};

