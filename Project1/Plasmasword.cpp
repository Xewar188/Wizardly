#include "Plasmasword.h"
#include "Board.h"
#include "PlasmaswordProjectile.h"
#include "Entity.h"

Plasmasword::Plasmasword()
{
	avaliable = false;
	cooldown = 48;
	weaponColor = Color(128, 0, 64);
}

void Plasmasword::attack(Board& board, Entity& src)
{
	if (board.getTime() - src.getLastShootTime() >= std::max(cooldown - src.getAttackSpeed(), 40))
	{
		FloatRect hitArea;
		for (auto i = board.getEntityBeginPointer(); i != board.getEntityEndPointer(); i++)
		{
			switch (src.getDirection())
			{
			case 1:
				hitArea = FloatRect((float) src.getCenterX() - 20, (float) src.getCenterY() - 40 - src.getSize().y/2, 40.0f, 40.0f);
				break;
			case 2:
				hitArea = FloatRect((float) src.getCenterX() + src.getSize().x / 2, (float) src.getCenterY() - 20, 40.0f, 40.0f);
				break;
			case 3:
				hitArea = FloatRect((float) src.getCenterX() - 20, (float) src.getCenterY() + src.getSize().y / 2, 40.0f, 40.0f);
				break;
			case 4:
				hitArea = FloatRect((float) src.getCenterX() - 40 - src.getSize().x/2, (float) src.getCenterY() - 20, 40.0f, 40.0f);
				break;
			}
			if (!src.equals(*i))
				if ((*i)->getMode() * src.getMode() <= 0)
					if ((*i)->getBounds().intersects(hitArea))
						(*i)->dealDamage(50);
		}
		src.addProjectile(new PlasmaswordProjectile(&src, board, weaponColor));
		src.startCooldown();
	}
}