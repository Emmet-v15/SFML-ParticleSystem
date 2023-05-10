#include "Platform/Platform.hpp"

int main()
{
	util::Platform platform;

#if defined(_DEBUG)
	std::cout << "Hello World!" << std::endl;
#endif

	sf::RenderWindow window;
	// in Windows at least, this must be called before creating the window
	float screenScalingFactor = platform.getScreenScalingFactor(window.getSystemHandle());
	window.create(sf::VideoMode(500.0f * screenScalingFactor, 500.0f * screenScalingFactor), "Particle System", sf::Style::Default, sf::ContextSettings(0, 0, 4));

	sf::Font font;
	if (!font.loadFromFile("assets/fonts/Roboto.ttf"))
	{
		std::cout << "Error loading font" << std::endl;
	}

	sf::Text FPSlabel, FPSValue, particleCountLabel, particleCountValue;
	FPSlabel.setFont(font);
	FPSlabel.setString("FPS:");
	FPSlabel.setCharacterSize(24);
	FPSlabel.setFillColor(sf::Color::White);
	FPSlabel.setStyle(sf::Text::Regular);
	FPSlabel.setPosition(0.0f, 0.0f);

	// copy the label and change the text
	FPSValue = FPSlabel;
	FPSValue.setString("0");
	FPSValue.setPosition(FPSlabel.getLocalBounds().width + 5, 0.0f);

	particleCountLabel = FPSlabel;
	particleCountLabel.setString("Particles:");
	particleCountLabel.setPosition(0.0f, FPSlabel.getLocalBounds().height + 5);

	particleCountValue = FPSlabel;
	particleCountValue.setString("0");
	particleCountValue.setPosition(particleCountLabel.getLocalBounds().width + 5, particleCountLabel.getPosition().y);

	float deltaTime = 0.0f;
	float fps = 0.0f;
	int frameCounter = 0;
	float perSecondDT = 0.0f;
	sf::Clock clock;

	srand((unsigned)time(NULL));

	sf::Color backgroundColor(88, 84, 84);
	sf::Color particleColor(255, 255, 255, 64);

	// create a vector of particles
	std::vector<Particle> particles;

	// create a particle and add it to the vector
	Particle particle;
	particle.position = sf::Vector2f(100.0f, 100.0f);
	particle.velocity = sf::Vector2f(50.0f, 150.0f);
	particle.color = particleColor;
	particle.radius = 10.0f;
	particles.push_back(particle);

	// i want the particles to be a bit transparent, and when they overlap, i want the color to be additive
	// so i need to use the sf::BlendMode::Add blend mode

	sf::CircleShape shape(particle.radius);
	shape.setFillColor(particle.color);

	// set the blend mode;
	sf::BlendMode blendMode(sf::BlendMode::Factor::SrcAlpha, sf::BlendMode::Factor::DstAlpha);

	sf::Event event;

	while (window.isOpen())
	{
		deltaTime = clock.restart().asSeconds();

		// Calculate FPS using a clock over a second
		perSecondDT += deltaTime;
		frameCounter++;
		if (perSecondDT >= 1.0f)
		{
			fps = frameCounter / perSecondDT;
			frameCounter = 0;
			perSecondDT = 0.0f;
			FPSValue.setString(std::to_string(fps));
		}
		// draw text on screen

		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
				window.close();
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			{
				// create a particle and add it to the vector
				Particle& newParticle = particle;
				particle.position = sf::Vector2f(sf::Mouse::getPosition(window) - sf::Vector2i(10, 10));
				particle.velocity = sf::Vector2f(float(std::rand() % 100 - 50), float(std::rand() % 100 - 50));
				particles.push_back(newParticle);
				particleCountValue.setString(std::to_string(particles.size()));
			}
		}

		for (auto& p : particles)
		{
			p.position += p.velocity * deltaTime;
			borderCollide(p, window);
		}

		window.clear(backgroundColor);

		for (auto& p : particles)
		{
			shape.setPosition(p.position);
			window.draw(shape, blendMode);
		}

		window.draw(FPSlabel);
		window.draw(FPSValue);
		window.draw(particleCountLabel);
		window.draw(particleCountValue);
		window.display();
	}

	return 0;
}