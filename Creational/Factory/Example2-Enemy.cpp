#include <iostream>
#include <memory>

class Enemy {
   public:
    virtual void attack() = 0;
    virtual ~Enemy() = default;
};

class Zombie : public Enemy {
   public:
    void attack() override { std::cout << "Zombies bites \n"; }
};

class Alien : public Enemy {
   public:
    void attack() override { std::cout << "Alien shoots laser \n"; }
};

class EnemySpawner {
   public:
    virtual std::unique_ptr<Enemy> spawnEnemy() = 0;
    virtual ~EnemySpawner() = default;
};

class ZombieSpawner : public EnemySpawner {
   public:
    std::unique_ptr<Enemy> spawnEnemy() { return std::make_unique<Zombie>(); }
};

class AlienSpawner : public EnemySpawner {
   public:
    std::unique_ptr<Enemy> spawnEnemy() { return std::make_unique<Alien>(); }
};

int main() {
    AlienSpawner alienSpawner{};
    ZombieSpawner zombieSpawner{};

    auto alien1{alienSpawner.spawnEnemy()};
    auto alien2{alienSpawner.spawnEnemy()};

    auto zombie1{zombieSpawner.spawnEnemy()};
    auto zombie2{zombieSpawner.spawnEnemy()};

    alien1->attack();
    zombie1->attack();
    alien2->attack();
    zombie2->attack();

    return 0;
}
