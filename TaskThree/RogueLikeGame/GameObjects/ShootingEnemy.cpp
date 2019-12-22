#include "ShootingEnemy.h"

ShootingEnemy::ShootingEnemy(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage) :
    IShootingCharacter(pos, sym, hp, damage, maxHp, shootingDamage) { };

ShootingEnemy::~ShootingEnemy() = default;


char ShootingEnemy::GetAction(WINDOW * &win)
{
    std::vector<char> v = { 'w', 'a', 's', 'd', 'i', 'j', 'k', 'l', 'w', 'a', 's', 'd', 'w', 'a', 's', 'd', 'w', 'a', 's', 'd' };
    return v[rand() % v.size()];
}

void ShootingEnemy::Collide(IGameObject & other, Level& level)
{
    other.collideWith(*this, level);
}

void ShootingEnemy::collideWith(Enemy & enemy, Level& level)
{
    enemy.SetHp(std::max(0, enemy.GetHp() - this->GetDamage()));
    if (enemy.GetHp() <= 0)
    {
        level.SetObj(enemy.GetPos(), ' ');
        level.enemies.erase(enemy.GetPos());
    }
}

void ShootingEnemy::collideWith(Player & player, Level& level)
{
    player.SetHp(std::max(0, player.GetHp() - this->GetDamage()));
    if (player.GetHp() <= 0)
        level.SetObj(player.GetPos(), ' ');
}

void ShootingEnemy::collideWith(Bullet & bullet, Level& level)
{
    this->SetHp(std::max(0, this->GetHp() - bullet.GetDamage()));

    level.SetObj(bullet.GetPos(), ' ');
    level.bullets.erase(bullet.GetPos());
}

void ShootingEnemy::collideWith(ShootingEnemy& shootingEnemy, Level& level)
{
    shootingEnemy.SetHp(std::max(0, shootingEnemy.GetHp() - this->GetDamage()));
    if (shootingEnemy.GetHp() <= 0)
    {
        level.SetObj(shootingEnemy.GetPos(), ' ');
        level.enemies.erase(shootingEnemy.GetPos());
    }
}

void ShootingEnemy::collideWith(FirstAidKit& firstAidKit, Level& level)
{
    this->SetHp(std::min(this->GetMaxHp(), this->GetHp() + firstAidKit.GetHealingForce()));

    level.SetObj(firstAidKit.GetPos(), ' ');
    level.firstAidKits.erase(firstAidKit.GetPos());
}

void ShootingEnemy::Update(Level& level)
{
    char action = this->GetAction(level.levelWin);
    bool isShoot = 0;
    Point direction = level.player->getDirection(action, isShoot);
    if (direction.x != 0 || direction.y != 0)
    {
        if (isShoot)
        {
            /*bool needCollide = level.player->shoot(direction, *level.player);
            if (needCollide)
            {
                //makeMove({ 0, 0 }, **level.bulletsContainer.rbegin());
            }*/
        }
        else
        {
            Point newPos(this->GetPos().x + direction.x, this->GetPos().y + direction.y);

            if (newPos.x <= 0 || newPos.y <= 0 || newPos.x - 1 >= level.GetHeight())
                return;
            if (newPos.y >= level.GetWidth() || level.GetSym(newPos) == '#')
                return;

            if (level.GetSym(newPos) == ' ' && level.GetSym(newPos) == ' ')
            {
                level.enemies.emplace(newPos, level.enemies.find(this->GetPos())->second);
                level.SetObj(this->GetPos(), ' ');
                level.enemies.erase(this->GetPos());

                this->SetPos(newPos);
                level.SetObj(this->GetPos(), this->GetSym());
                return;
            }

            std::shared_ptr<IGameObject> obj = level.GetObj(newPos);
            obj->Collide(*this, level);

            if (this->GetHp() <= 0)
            {
                level.SetObj(this->GetPos(), ' ');
                level.enemies.erase(this->GetPos());
            }
        }
    }
}