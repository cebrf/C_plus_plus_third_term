#include "Trophy.h"

Trophy::Trophy(Point pos, char sym) :
    IGameObject(pos, sym) { }

Trophy::~Trophy() = default;

char Trophy::GetAction(WINDOW & win)
{
    return ' ';
}

void Trophy::Collide(IGameObject & other, Level & level)
{
    other.collideWith(*this, level);
}

void Trophy::collideWith(Player & player, Level & level)
{
    return player.collideWith(*this, level);
}

void Trophy::collideWith(Enemy & enemy, Level & level) { }

void Trophy::collideWith(Bullet & bullet, Level & level)
{
    return bullet.collideWith(*this, level);
}

void Trophy::collideWith(ShootingEnemy & shootingEnemy, Level & level) { }

void Trophy::collideWith(FirstAidKit & firstAidKit, Level & level) { }

void Trophy::collideWith(Trophy& trophy, Level& level) { }

void Trophy::Update(Level & level) { }