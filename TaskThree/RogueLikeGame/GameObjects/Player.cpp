#include "Player.h"

Player::Player() :
    IShootingCharacter(Point(-1, -1), ' ', -1, -1, -1, -1) { };

Player::Player(Point pos, char sym, int hp, int damage, int maxHp, int shootingDamage) :
    IShootingCharacter(pos, sym, hp, damage, maxHp, shootingDamage) { };

Player::~Player() = default;


char Player::GetAction(WINDOW& win)
{
    return wgetch(&win);
}

void Player::Collide(IGameObject& other, Level& level)
{
    other.collideWith(*this, level);
}

void Player::collideWith(Enemy& enemy, Level& level)
{
    enemy.SetHp(std::max(0, enemy.GetHp() - this->GetDamage()));
    if (enemy.GetHp() <= 0)
    {
        level.SetObj(enemy.GetPos(), ' ');
        level.enemies.erase(enemy.GetPos());
    }
}

void Player::collideWith(Player& player, Level& level) { }

void Player::collideWith(Bullet& bullet, Level& level)
{
    this->SetHp(std::max(0, this->GetHp() - bullet.GetDamage()));
    if (this->GetHp() <= 0)
    {
        level.SetObj(this->GetPos(), ' ');
        level.levelStatus = 1;
    }
    level.SetObj(bullet.GetPos(), ' ');
    level.bullets.erase(bullet.GetPos());
}

void Player::collideWith(ShootingEnemy& shootingEnemy, Level& level)
{
    shootingEnemy.SetHp(std::max(0, shootingEnemy.GetHp() - this->GetDamage()));
    if (shootingEnemy.GetHp() <= 0)
    {
        level.SetObj(shootingEnemy.GetPos(), ' ');
        level.enemies.erase(shootingEnemy.GetPos());
    }
}

void Player::collideWith(FirstAidKit& firstAidKit, Level& level)
{
    this->SetHp(std::min(this->GetMaxHp(), this->GetHp() + firstAidKit.GetHealingForce()));

    level.SetObj(firstAidKit.GetPos(), ' ');
    level.firstAidKits.erase(firstAidKit.GetPos());
}

void Player::collideWith(Trophy& trophy, Level& level)
{
    level.levelStatus = 2;
}

void Player::Update(Level& level)
{
    char action = this->GetAction(*level.levelWin);
    if (action == 27)
        level.EscMenu();

    bool isShoot = 0;
    Point direction = this->getDirection(action, isShoot);

    if (direction.x == 0 && direction.y == 0)
        return;
    Point newPos(this->GetPos().x + direction.x, this->GetPos().y + direction.y);
    if (newPos.x <= 0 || newPos.y <= 0 || newPos.x - 1 >= level.GetHeight())
        return;
    if (newPos.y >= level.GetWidth() || level.GetSym(newPos) == '#')
        return;

      
    if (level.GetSym(newPos) == ' ')
    {
        if (isShoot)
        {
            std::shared_ptr<Bullet> newBullet = std::shared_ptr<Bullet>(new Bullet(newPos, Point(direction.x, direction.y), this->GetShootingDamage()));
            level.bulletsContainer.push_back(newBullet);
            level.bullets.emplace(newPos, newBullet);
            level.SetObj(newBullet->GetPos(), newBullet->GetSym());
        }
        else
        {
            wattron(&*level.levelWin, COLOR_PAIR(1));

            level.SetObj(this->GetPos(), ' ');
            this->SetPos(newPos);
            level.SetObj(this->GetPos(), this->GetSym());

            wattroff(&*level.levelWin, COLOR_PAIR(1));
        }
    }
    else
    {
        std::shared_ptr<IGameObject> obj = level.GetObj(newPos);
        obj->Collide(*this, level);
    }    
}