
void borderCollide(Particle& p, sf::RenderWindow& window)
{
	// check and respond to border collisions with respect to the particle's size
	if (p.position.x < 0.0f)
	{
		p.velocity.x *= -1.0f;
		p.position.x = 0.0f;
	}
	if (p.position.x + p.radius * 2 > window.getSize().x)
	{
		p.velocity.x *= -1.0f;
		p.position.x = window.getSize().x - p.radius * 2;
	}
	if (p.position.y < 0.0f)
	{
		p.velocity.y *= -1.0f;
		p.position.y = 0.0f;
	}
	if (p.position.y + p.radius * 2 > window.getSize().y)
	{
		p.velocity.y *= -1.0f;
		p.position.y = window.getSize().y - p.radius * 2;
	}
}

void particleCollide(Particle& p1, Particle& p2)
{
	// check if the particles are colliding
	sf::Vector2f distance = p1.position - p2.position;
	float magnitude = sqrt(distance.x * distance.x + distance.y * distance.y);
	if (magnitude < p1.radius + p2.radius)
	{
		// calculate the collision response
		sf::Vector2f collisionVector = p1.position - p2.position;
		float vdot = p1.velocity.x * collisionVector.x + p1.velocity.y * collisionVector.y;
		float collisionScale = 2.0f * vdot / ((p1.radius + p2.radius) * (p1.radius + p2.radius));
		sf::Vector2f collision = collisionScale * collisionVector;
		p1.velocity -= collision;
		p2.velocity += collision;
	}
}