#include "game_manager.hpp"

GameManager::GameManager()
{
    // Initialize window, renderer, and other members
    std::cout << "Initialising window, renderer, and other members in GameManager constructor" << std::endl;
    window = nullptr;
    renderer = nullptr;
    currentWidth = 800;
    currentHeight = 600;
    currentSelection = 0;
    viewport = std::make_shared<Viewport>(0.0f,0.0f,currentWidth, currentHeight);

    if (!initSDL(window, renderer, "My 2D Game Engine", currentWidth, currentHeight))
    {
        std::cerr << "Something wrong with initSDL" << std::endl;
    }

    // Initialize font
    std::cout << "Initialising TTF." << std::endl;
    if (TTF_Init() == -1)
    {
        std::cerr << "TTF_Init: " << TTF_GetError() << std::endl;
    }
    font = nullptr;
    std::cout << "Loading font in GameManager constructor" << std::endl;
    font = TTF_OpenFont("Lora-Regular.ttf", 18);
    if (!font)
    {
        std::cerr << "TTF_OpenFont: " << TTF_GetError() << std::endl;
    }

    // Initialize current state
    currentState = GameState::MainMenu;
}


GameManager::~GameManager()
{
    // Clean up resources
    TTF_CloseFont(font);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

int GameManager::loadGameObjectsForState(GameState state)
{
    std::cout << "Loading game objects for state" << std::endl;

    gameObjects.clear();
    playerObject.reset();

    switch (state)
    {
    case GameState::MainMenu:
    {
        // Load game objects for the main menu
        // Create the game objects outside the main loop
        std::cout << "Loading main menu objects" << std::endl;
        std::cout << "Font pointer: " << font << std::endl;
        gameObjects.push_back(std::make_shared<TextGameObject>(Vector2(150, 500), Vector2(100, 80), "Start", font, true));
        gameObjects.push_back(std::make_shared<TextGameObject>(Vector2(350, 500), Vector2(100, 80), "Options", font, false));
        gameObjects.push_back(std::make_shared<TextGameObject>(Vector2(550, 500), Vector2(100, 80), "Chapters", font, false));
        std::cout << "Main menu objects loaded" << std::endl;
        return 0;
        break;
    }
    case GameState::Playing:
    {
        std::cout << "Loading map for playing state" << std::endl;
        grid = std::make_shared<Grid>(currentWidth, currentHeight, 0);
        map = std::make_unique<Map>(grid, "C:/Users/theba/Documents/2dgameengine/test.csv");
        // Load game objects for the playing state
        std::cout << "Loading objects for playing state" << std::endl;
        playerObject = std::make_shared<PlayerGameObject>(Vector2(100, 100), Vector2(64, 64), false);
        if (!playerObject->loadTexture("C:/Users/theba/Documents/2dgameengine/cowboy1.png", renderer))
        {
            // Error loading texture
            return 1;
        }
        gameObjects.push_back(playerObject);
        return 0;
        break;
    }
    case GameState::Paused:
        // Load
        std::cout << "Loading pause objects" << std::endl;
        return 0;
        break;
    }
    return 0;
}

bool GameManager::initSDL(SDL_Window *&window, SDL_Renderer *&renderer, const char *title, int width, int height)
{

    std::cout << "Initialising SDL." << std::endl;
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
    {
        std::cerr << "Error initialising SDL: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Creating window." << std::endl;
    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);
    if (!window)
    {
        std::cerr << "Error creating window: " << SDL_GetError() << std::endl;
        return false;
    }

    std::cout << "Creating renderer." << std::endl;
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if (!renderer)
    {
        std::cerr << "Error creating renderer: " << SDL_GetError() << std::endl;
        return false;
    }
    return true;
}

void GameManager::scaleGameObjects(const Vector2 &scale)
{
    for (const auto &object : gameObjects)
    {
        object->getPosition().scaleByVector(scale);
        object->getSize().scaleByVector(scale);
    }
}

void GameManager::renderGameObject(SDL_Renderer *renderer, GameObject &object)
{
    object.render(renderer);
}

void GameManager::pollEvents()
{   
    // std::cout << "Polling events in GameManager.pollEvents()" << std::endl;
    SDL_Event event;
    while (SDL_PollEvent(&event))
    {
        switch (currentState)
        {
        case GameState::MainMenu:
            handleMainMenuEvent(event);
            break;
        case GameState::Playing:
            handlePlayingEvent(event);
            break;
        case GameState::Paused:
            handlePausedEvent(event);
            break;
        default:
            break;
        }
    }
}

void GameManager::handleWindowResizing(int newWidth, int newHeight)
{
    // Calculate scaling factors
    float scaleWidth = static_cast<float>(newWidth) / currentWidth;
    float scaleHeight = static_cast<float>(newHeight) / currentHeight;

    // Update the current window size
    currentWidth = newWidth;
    currentHeight = newHeight;

    // Apply the transformation matrix to game objects
    scaleGameObjects(Vector2(scaleWidth, scaleHeight));

    // Update the window size
    SDL_SetWindowSize(window, newWidth, newHeight);

    // Viewport.setHeight(currentHeight);
    // Viewport.setWidth(currentWidth);
}

void GameManager::handleMainMenuEvent(const SDL_Event &event)
{
    std::cout << "handleMainMenuEvent" << std::endl;
    switch (event.type)
    {
    case SDL_QUIT:
    {
        quit = true;
        break;
    }
    case SDL_WINDOWEVENT:
    {
        switch (event.window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
        {
            // Get new window dimensions
            int newWidth = event.window.data1;
            int newHeight = event.window.data2;

            handleWindowResizing(newWidth, newHeight);
            // Calculate scaling factors
            // float scaleWidth = static_cast<float>(newWidth) / currentWidth;
            // float scaleHeight = static_cast<float>(newHeight) / currentHeight;

            // // Update the current window size
            // currentWidth = newWidth;
            // currentHeight = newHeight;

            // // Apply the transformation matrix to game objects
            // scaleGameObjects(Vector2(scaleWidth, scaleHeight));

            // // Update the window size
            // SDL_SetWindowSize(window, newWidth, newHeight);
            break;
        }
        }
        break;
    }
    case SDL_KEYDOWN:
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_UP:
        {
            // Handle up arrow key input
            if (currentSelection < 2)
            {
                currentSelection++;
                gameObjects[0]->setIsActive(currentSelection == 0 ? true : false);
                gameObjects[1]->setIsActive(currentSelection == 1 ? true : false);
                gameObjects[2]->setIsActive(currentSelection == 2 ? true : false);
            }
            break;
        }
        case SDLK_RIGHT:
            // Handle right arrow key input
            if (currentSelection < 2)
            {
                currentSelection++;
                gameObjects[0]->setIsActive(currentSelection == 0 ? true : false);
                gameObjects[1]->setIsActive(currentSelection == 1 ? true : false);
                gameObjects[2]->setIsActive(currentSelection == 2 ? true : false);
            }
            break;

        case SDLK_LEFT:
            // Handle left arrow key input
            if (currentSelection > 0)
            {
                currentSelection--;
                gameObjects[0]->setIsActive(currentSelection == 0 ? true : false);
                gameObjects[1]->setIsActive(currentSelection == 1 ? true : false);
                gameObjects[2]->setIsActive(currentSelection == 2 ? true : false);
            }
            break;

        case SDLK_DOWN:
            // Handle down arrow key input
            if (currentSelection > 0)
            {
                currentSelection--;
                gameObjects[0]->setIsActive(currentSelection == 0 ? true : false);
                gameObjects[1]->setIsActive(currentSelection == 1 ? true : false);
                gameObjects[2]->setIsActive(currentSelection == 2 ? true : false);
            }
            break;

        case SDLK_RETURN:
            switch (currentSelection)
            {
            case 0:
                currentState = GameState::Playing;
                loadGameObjectsForState(currentState);
                break;
            }
            break;
        }
        break;
    default:
        break;
    }
    break;
    }
}

void GameManager::handlePlayingEvent(const SDL_Event &event)
{
    switch (event.type)
    {
    case SDL_QUIT:
    {
        quit = true;
        break;
    }
    case SDL_WINDOWEVENT:
    {
        switch (event.window.event)
        {
        case SDL_WINDOWEVENT_RESIZED:
        {
            // Get new window dimensions
            int newWidth = event.window.data1;
            int newHeight = event.window.data2;

            handleWindowResizing(newWidth, newHeight);
            // Calculate scaling factors
            // float scaleWidth = static_cast<float>(newWidth) / currentWidth;
            // float scaleHeight = static_cast<float>(newHeight) / currentHeight;

            // // Update the current window size
            // currentWidth = newWidth;
            // currentHeight = newHeight;

            // // Apply the transformation matrix to game objects
            // scaleGameObjects(Vector2(scaleWidth, scaleHeight));

            // // Update the window size
            // SDL_SetWindowSize(window, newWidth, newHeight);
            break;
        }
        }
        break;
    }
    case SDL_KEYDOWN:
    {
        switch (event.key.keysym.sym)
        {
        case SDLK_w:
        {
            // handle w press
            std::cout << "Handle w press" << std::endl;
            playerObject->transformPosition(1000.0f, Vector2(0,-1), deltaTime);
            std::cout << "Handle Viewport transform" << std::endl;
            // Viewport.transformPosition(1000.0f, Vector2(0,-1), deltaTime);
            // viewport->updateViewport(playerObject->getPosition());
            std::cout << "Position transformed" << std::endl;
            break;
        }
        case SDLK_a:
        {
            // handle a press
            playerObject->transformPosition(1000.0f, Vector2(-1,0), deltaTime);
            // viewport->updateViewport(playerObject->getPosition());
            break;
        }
        case SDLK_d:
        {
            // handle d press
            playerObject->transformPosition(1000.0f, Vector2(1,0), deltaTime);
            // viewport->updateViewport(playerObject->getPosition());
            break;
        }
        case SDLK_s:
        {
            // handle s press
            playerObject->transformPosition(1000.0f, Vector2(0,1), deltaTime);
            // viewport->updateViewport(playerObject->getPosition());
            break;
        }
        break;
        }
    }
    break;
    }
}

void GameManager::handlePausedEvent(const SDL_Event &event)
{
    //implement
}

void GameManager::updateAndRender()
{
    // Clear the renderer
    // std::cout << "Clearing the renderer in GameManager.updateAndRender()" << std::endl;
    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255); // Black background
    SDL_RenderClear(renderer);

    // Update game objects: We could use this for AI, tracking the player object, many things
    // for (const auto &object : gameObjects) {
    //     object->update();
    // }
    if (currentState == GameState::Playing)
    {   
        // std::cout << "Drawing map in updateAndRender" << std::endl;
        map->Draw(renderer, viewport);
    }

    // Render game objects
    // std::cout << "Calling object->render(renderer) on gameObjects in GameManager.updateAndRender()" << std::endl;
    for (const auto &object : gameObjects)
    {
        object->render(renderer); //Gets stuck here on first call
    }

    // Present the renderer
    // std::cout << "Calling SDL_RenderPresent(renderer) in GameManager.updateAndRender()" << std::endl;
    SDL_RenderPresent(renderer);
}

void GameManager::run()
{
    // Initialise game objects for the current state
    std::cout << "Call to loadingGameObjects(currentState) for state in GameManager.run()" << std::endl;
    loadGameObjectsForState(currentState);

    // Start the game loop
    std::cout << "Starting the game loop in GameManager.run()" << std::endl;
    quit = false;
    while (!quit)
    {
        frameStart = SDL_GetTicks();
        // Poll events
        // std::cout << "Call to pollEvents() in GameManager.run()" << std::endl;
        pollEvents();

        // Update game logic and render the current frame
        // std::cout << "Call to updateAndRender() in GameManager.run()" << std::endl;
        updateAndRender();

        // Do anything else.
        deltaTime = (SDL_GetTicks()-frameStart) / 1000.0f;
        // cap the frame rate
        if ((1000 / 60) > SDL_GetTicks() - frameStart)
        {
            SDL_Delay(1000 / 60 - (SDL_GetTicks() - frameStart));
        }
    }
}