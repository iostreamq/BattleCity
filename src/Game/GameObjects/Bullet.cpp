#include "Bullet.h"
#include "../../Resources/ResourceManager.h"
#include "../../Physics/PhysicsEngine.h"
Bullet::Bullet(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer):
	IGameObject(EtypeOfObject::Bullet,position,size,rotation,layer),
	m_pSprite(ResourceManager::getSprite("bullet")),
	m_isActivityBullet(false)
{
	m_bulletTimer.setCallback(
		[&]()
		{
			m_isActivityBullet = false;
		}
	);

	m_colliders.emplace_back(glm::vec2(0), m_size);
}

void Bullet::Render() const
{	
	if(m_isActivityBullet)
	m_pSprite->Render(m_position, m_size, m_rotation, m_layer);
}

void Bullet::update(const double& delta)
{
	if (!IsTimerLeft())
	m_bulletTimer.update(delta);
}

void Bullet::onCollision()
{
	setVelocity(0);
	m_isActivityBullet = false;
}

bool Bullet::IsTimerLeft()
{
	if (m_bulletTimer.checkCurrentTime() <= 0) return true;
	else return false;
}

// для проверки исключений
bool Bullet::checkColiders(EtypeOfObject typeOfObjectToCheck)
{
	if (typeOfObjectToCheck == EtypeOfObject::Water)  return false;
	else return true;
}

void Bullet::setDelay(const double& duration)
{
		m_bulletTimer.start(duration);
		m_isActivityBullet = true;
}



