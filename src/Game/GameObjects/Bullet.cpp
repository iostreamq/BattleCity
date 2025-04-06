#include "Bullet.h"


Bullet::Bullet(const glm::vec2& position, const glm::vec2& size, const float rotation, const float layer) :
	IGameObject(EtypeOfObject::Bullet, position, size, rotation, layer),
	m_pSprite(ResourceManager::getSprite("bullet")),
	m_isActivityBullet(false),
	m_pSprite_explosion(ResourceManager::getSprite("explosion")),
	m_SpriteAnimator_explosion(m_pSprite_explosion),
	m_isActivityExplosion(false)
{
	m_bulletTimer.setCallback(
		[&]()
		{
			m_velocity = 0;
			m_isActivityBullet = false;
		}
	);

	m_explosionTimer.setCallback(
		[&]()
		{
			m_isActivityExplosion = false;
			m_SpriteAnimator_explosion.reset();
		}
	);

	m_colliders.emplace_back(glm::vec2(0), m_size);
}

void Bullet::Render() const
{	
  	if (m_isActivityBullet)
		m_pSprite->Render(m_position, m_size, m_rotation, m_layer);

	if (m_isActivityExplosion)
	{
		if(m_rotation == 0.f)
			m_pSprite_explosion->Render(glm::vec2(m_position.x - 5.f, m_position.y), m_size * 2.f , m_rotation,m_layer, m_SpriteAnimator_explosion.getCurrentFrame());
	    
		else if(m_rotation == -90)
			m_pSprite_explosion->Render(glm::vec2(m_position.x, m_position.y - 3.f), m_size * 2.f, m_rotation, m_layer, m_SpriteAnimator_explosion.getCurrentFrame());
	    
		else if (m_rotation == -180)
			m_pSprite_explosion->Render(glm::vec2(m_position.x - 4.f, m_position.y), m_size * 2.f, m_rotation, m_layer, m_SpriteAnimator_explosion.getCurrentFrame());

		else if (m_rotation == -270)
			m_pSprite_explosion->Render(glm::vec2(m_position.x, m_position.y - 3.f), m_size * 2.f, m_rotation, m_layer, m_SpriteAnimator_explosion.getCurrentFrame());

		else m_pSprite_explosion->Render(m_position, m_size * 2.f, m_rotation, m_layer, m_SpriteAnimator_explosion.getCurrentFrame());
	}

}

void Bullet::update(const double& delta)
{

	if (IsTimerLeft())
	{
		m_bulletTimer.update(delta);
	}

	if (m_isActivityExplosion)
	{
		m_explosionTimer.update(delta);
		m_SpriteAnimator_explosion.update(delta);
	}

}

void Bullet::onCollisionDynamic()
{ 

	m_bulletTimer.update(10000);
	setVelocity(0);
	m_isActivityBullet = false;
	m_explosionTimer.start(m_SpriteAnimator_explosion.getTotalDuration());
	m_isActivityExplosion = true;	
}

bool Bullet::IsTimerLeft()
{
	if (m_bulletTimer.checkCurrentTime() > 0) return true;
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



