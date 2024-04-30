#include "game.h"

void runGame()
{

    sf::Color black = sf::Color::Black;
    sf::Color white = sf::Color::White;
    std::string namePlayer = "";
    std::string nameEnemy = "";
    float velocityPlayer = 0;
    float velocityEnemy = 0;
    float distancePlayer = 0;
    float distanceEnemy = 0;
    sf::Font font;
    sf::Font text;
    sf::Text title;
    sf::Text winner;
    sf::Text loser;
    title.setFont(font);
    title.setCharacterSize(42);
    title.setPosition(275, 5);
    winner.setFont(font);
    loser.setFont(font);
    sf::Text paragraph;
    paragraph.setFont(text);
    paragraph.setCharacterSize(15);



    sf::SoundBuffer buffer;
    buffer.loadFromFile("assets/music.ogg");


    font.loadFromFile("assets/Daydream.ttf");
    text.loadFromFile("assets/bookfont.ttf");



    sf::Sound sound;
    sound.setBuffer(buffer);
    sound.play();


    sf::Texture buttonTexture;
    buttonTexture.loadFromFile("assets/arrow.png");


    sf::RenderWindow window(sf::VideoMode(800, 600), "Ship Racing Game");


    sf::Texture sandTexture;
    sandTexture.loadFromFile("assets/sand.png");
    sf::Texture backgroundTexture;
    backgroundTexture.loadFromFile("assets/BackGround.png");
    sf::Texture cloudTexture;
    cloudTexture.loadFromFile("assets/Cloud.png");
    sf::Texture seaTexture;
    seaTexture.loadFromFile("assets/Sea.png");
    sf::Texture mountainTexture;
    mountainTexture.loadFromFile("assets/mountain.png");
    sf::Texture shipTexture;
    sf::Texture diceTexture;
    sf::Texture mapTexture;
    sf::Texture backgroundMap;

    diceTexture.loadFromFile("assets/dice.png");
    backgroundMap.loadFromFile("assets/fondo.png");
    shipTexture.loadFromFile("assets/ship.png");
    mapTexture.loadFromFile("assets/mapa.png");

    sf::Sprite backgroundSpriteMap(backgroundMap);
    backgroundSpriteMap.setScale(1.0f, 1.0f);
    backgroundSpriteMap.setPosition(0, 420);


    sf::Texture shipTexture2;
    shipTexture2.loadFromFile("assets/ship2.png");
    sf::Sprite diceSprite(diceTexture, sf::IntRect(0, 0, 16, 16));
    diceSprite.setScale(2.8f, 2.8f);
    diceSprite.setPosition(250, 465);

    sf::Sprite diceSprite2(diceTexture, sf::IntRect(0, 0, 16, 16));
    diceSprite2.setScale(2.8f, 2.8f);
    diceSprite2.setPosition(515, 465);

    sf::Sprite mapSprite(mapTexture);
    mapSprite.setScale(0.85f, 0.43f);
    mapSprite.setPosition(45, 410);
    Button button(253, 520, "assets/arrow.png", 1);
    Button nitroButton(370, 475, "assets/rocket.png", 2);
    Ship ship1({ 100.0f, 290.0f }, shipTexture, "Jon");
    Ship ship2({ 100.0f, 350.0f }, shipTexture2, "Javier");
    namePlayer = ship1.getName();
    nameEnemy = ship2.getName();

    sf::Sprite shipPlayer(shipTexture, sf::IntRect(0,0,38,32));
    sf::Sprite shipEnemy(shipTexture2, sf::IntRect(0, 0, 38, 32));


    shipPlayer.setScale(2.0f, 2.0f);
    shipPlayer.setPosition(150, 480);

    shipEnemy.setScale(2.0f, 2.0f);
    shipEnemy.setPosition(575, 480);

    sf::Sprite sand(sandTexture);
    sf::Sprite background(backgroundTexture);
    sf::Sprite cloud(cloudTexture);
    sf::Sprite sea(seaTexture);
    sf::Sprite mountain(mountainTexture);
    
    sea.setScale(2.5f, 6.5f);
    sea.setPosition(0, -472);
    background.setScale(2.5f, 2.5f);
    cloud.setScale(2.5f, 2.5f);
    mountain.setScale(2.5f, 2.5f);

    auto tp = std::chrono::steady_clock::now();
    int currentNumber = 0;
    int enemycurrentNumber = 0;
    bool rolling = false;
    bool isRunning = true;
    bool shipPlayerIsEnd = false;
    bool shipEnemyIsEnd = false;
    int turn = 0;
    bool buttonPressed = false;
    std::string textContent = "";

    sf::Vector2f dir = { 0,0 };

    while (window.isOpen() && isRunning)
    {
        sf::Vector2f mousePosition = sf::Vector2f(sf::Mouse::getPosition(window));
        sf::Vector2f dir = { 0,0 };
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            else if ((turn == 6 || shipEnemyIsEnd || shipPlayerIsEnd) && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space) {
                window.close();
                runGame();
            }
            nitroButton.update(window);
            button.update(window);

            if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && button.isClicked(mousePosition)) {
                buttonPressed = true;
            }

        }

        rolling = button.getRolling();
        int targetNumber = button.getTargetNumber();
        bool nitro = nitroButton.getNitro();
        

        if (nitro) {
            ship1.activateNitro();
            nitroButton.setNitro(false);
            
        }

        float deltaTime;
        {
            const auto new_tp = std::chrono::steady_clock::now();
            deltaTime = std::chrono::duration<float>(new_tp - tp).count();
            tp = new_tp;
        }


        shipPlayerIsEnd = ship1.getFinishStatus();
        shipEnemyIsEnd = ship2.getFinishStatus();

        if (rolling && turn < 6 && !shipPlayerIsEnd && !shipEnemyIsEnd) {


            float elapsedTime = 0.0f;
            const float animationTime = 0.3f;

            while (elapsedTime < animationTime) {
                currentNumber = ship1.lanzarDado();
                diceSprite.setTextureRect(sf::IntRect((currentNumber - 1) * 16, 0, 16, 16));
                window.draw(diceSprite);
                window.display();

                elapsedTime += 0.016f;
            }

            if (currentNumber == targetNumber) {
                ++turn;
                std::stringstream ss;
                ss << "Turn " << turn;
                std::string textContent = ss.str();


                ship1.calcularTurno(currentNumber);
                enemycurrentNumber = ship2.lanzarDado();
                ship2.calcularTurno(enemycurrentNumber);
                title.setString(textContent);


                elapsedTime = 0.15f;

                while (elapsedTime < animationTime) {

                    diceSprite2.setTextureRect(sf::IntRect((enemycurrentNumber - 1) * 16, 0, 16, 16));
                    window.draw(diceSprite2);
                    window.display();

                    elapsedTime += 0.016f;
                }

                std::cout << "El dado ha terminado en el número " << currentNumber << "." << std::endl;
                button.setRolling(false);
            }
        }

        if (turn == 6 || shipEnemyIsEnd || shipPlayerIsEnd) {



            velocityPlayer = ship1.getVelocity();
            velocityEnemy = ship2.getVelocity();
            distancePlayer = ship1.calculateDistance();
            distanceEnemy = ship2.calculateDistance();

            

            std::stringstream rr;

            sf::Texture book; 
            book.loadFromFile("assets/book.png");

            window.clear(sf::Color(36, 47, 64));
            sf::Sprite bookSprite(book);

            winner.setCharacterSize(36);
            loser.setCharacterSize(36);

            loser.setString("LOSER");
            winner.setString("WINNER");

            winner.setFillColor(sf::Color(0, 255, 0));
            loser.setFillColor(sf::Color(255, 0, 0));

            


            if (distanceEnemy > distancePlayer) {

                winner.setPosition(460, 40);
                loser.setPosition(100, 40);


            }
            else {
                winner.setPosition(100, 40);
                loser.setPosition(470, 40);
            }

            
            bookSprite.setScale(8.0f, 8.0f);
            bookSprite.setPosition(16, 100);
            window.draw(bookSprite);
            window.draw(winner);
            window.draw(loser);
            sf::Sprite shipSprite(shipTexture);
            shipSprite.setTextureRect(sf::IntRect(0, 0, 38, 32));
            shipSprite.setScale(3.0f, 3.0f);
            shipSprite.setPosition(150, 280);
            sf::Sprite shipSprite2(shipTexture2);
            shipSprite2.setTextureRect(sf::IntRect(0, 0, 38, 32));
            shipSprite2.setScale(3.0f, 3.0f);
            shipSprite2.setPosition(530, 280);
            window.draw(shipSprite);
            window.draw(shipSprite2);




            paragraph.setCharacterSize(24);
            paragraph.setString(namePlayer);
            paragraph.setPosition(185, 140);
            paragraph.setFillColor(black);
            window.draw(paragraph);

            paragraph.setString(nameEnemy);
            paragraph.setPosition(543, 140);
            window.draw(paragraph);

            paragraph.setCharacterSize(19);
            rr << "Speed:" <<velocityPlayer<< "km/h";
            textContent = rr.str();
            rr.str("");

            paragraph.setString(textContent);
            paragraph.setPosition(110, 200);
            window.draw(paragraph);
     
            rr << "Speed:" << velocityEnemy << "km/h";
            textContent = rr.str();

            paragraph.setString(textContent);
            paragraph.setPosition(486, 200);
            window.draw(paragraph);


            rr.str("");
            rr << "Distance:" << distancePlayer << "km";
            textContent = rr.str();;

            paragraph.setString(textContent);
            paragraph.setPosition(110, 230);
            window.draw(paragraph);

            rr.str("");
            rr << "Distance:" << distanceEnemy << "km";
            textContent = rr.str();;

            paragraph.setString(textContent);
            paragraph.setPosition(486, 230);
            window.draw(paragraph);


            paragraph.setString("Press Space to play Again");
            paragraph.setPosition(260, 520);
            paragraph.setFillColor(white);
            window.draw(paragraph);


            window.display();


        }

        else {
            window.draw(backgroundSpriteMap);
            cloud.move(-0.003f, 0.0f);
            sea.move(-0.003f, 0.0f);
            mountain.move(-0.003f, 0.0f);
            backgroundSpriteMap.move(-0.003f, 0.0f);
            ship1.Update(deltaTime);
            ship2.Update(deltaTime);
            window.draw(background);
            sand.setPosition(0, 438);
            window.draw(cloud);
            window.draw(sea);
            ship1.Draw(window);
            ship2.Draw(window);
            window.draw(mountain);
            window.draw(mapSprite);
            window.draw(diceSprite);
            window.draw(title);
            window.draw(diceSprite2);
            button.draw(window);
            if (buttonPressed) {
                nitroButton.draw(window);
            }
            paragraph.setString(namePlayer);
            paragraph.setPosition(173, 462);
            paragraph.setFillColor(black);
            window.draw(paragraph);

            paragraph.setString(nameEnemy);
            paragraph.setPosition(584, 462);
            paragraph.setFillColor(black);
            window.draw(paragraph);

            window.draw(shipPlayer);
            window.draw(shipEnemy);
            window.display();

        }
        
    }

}
   